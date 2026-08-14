PROGRAM test_remap_conservation
  !
  ! Regression test for conservative remapping across shared small-circle
  ! boundaries.
  !
  ! A first-order conservative remap with renormalize=false must reproduce a
  ! constant source field exactly: the weights of every destination row sum to
  ! one only if the source polygons tile the sphere without gap or overlap. On a
  ! REDUCED grid the two owners of a shared row boundary carry different numbers
  ! of cells, so before the shared-boundary fix they approximated that boundary
  ! with different great-circle chains and the tiling was broken.
  !
  ! Four properties are checked, all self-contained (no reference file needed):
  !
  !   1 reduced -> regular, constant field preserved
  !       fails on unmodified XIOS; this is the defect itself.
  !   2 the same with the north row boundaries shifted by one ulp in sin(lat)
  !       guards against a return to exact equality matching of row latitudes,
  !       which silently disables the correction.
  !   3 reduced -> reduced, global overlap identity  sum_i v_i A_i = 4 pi
  !       row closure alone cannot see a target-side defect, so this one is
  !       checked with analytic cell areas rather than with row sums.
  !   4 a masked source leaves the destination cells that it does not touch
  !       bit-for-bit unchanged
  !       guards the complete-pre-mask-geometry path, which must contribute
  !       geometry without contributing weights.
  !
  ! Exit status is non-zero if any check fails.
  !
  USE xios
  USE netcdf
  IMPLICIT NONE
  INCLUDE "mpif.h"

  INTEGER, PARAMETER :: dp = KIND(1.0D0)
  REAL(dp), PARAMETER :: PI = 3.14159265358979323846264338327950288_dp
  ! grid sizes: small enough to run in a couple of seconds on one rank
  INTEGER, PARAMETER :: SRC_NLAT = 32, SRC_NLON = 64
  INTEGER, PARAMETER :: DST_NLAT = 24, DST_NLON = 48
  ! the defect is of order 1e-5 on these grids; the corrected result is ~1e-10
  REAL(dp), PARAMETER :: TOL_CLOSURE      = 1.0e-8_dp
  REAL(dp), PARAMETER :: TOL_CONSERVATION = 1.0e-8_dp
  ! destination cells the mask cannot reach must be unchanged to rounding
  REAL(dp), PARAMETER :: TOL_MASK         = 1.0e-12_dp

  INTEGER :: ierr, rank, csize, comm
  TYPE(xios_duration) :: dtime
  TYPE(xios_context)  :: ctx_hdl

  INTEGER :: src_ncell, dst_ncell
  INTEGER, ALLOCATABLE :: src_i_index(:), dst_i_index(:)
  REAL(dp), ALLOCATABLE :: src_lon(:), src_lat(:), src_blon(:,:), src_blat(:,:)
  REAL(dp), ALLOCATABLE :: pert_blon(:,:), pert_blat(:,:)
  REAL(dp), ALLOCATABLE :: dst_lon(:), dst_lat(:), dst_blon(:,:), dst_blat(:,:)
  REAL(dp), ALLOCATABLE :: src_field(:), dst_area_glo(:)
  LOGICAL, ALLOCATABLE :: src_mask(:)
  INTEGER :: failures

  CALL MPI_INIT(ierr)
  CALL xios_initialize("client", return_comm=comm)
  CALL MPI_COMM_RANK(comm, rank, ierr)
  CALL MPI_COMM_SIZE(comm, csize, ierr)

  CALL build_reduced_grid(SRC_NLAT, SRC_NLON, 0, src_ncell, src_i_index,        &
                          src_lon, src_lat, src_blon, src_blat)
  ! same grid, north boundary of every interior row moved by one ulp in sin(lat)
  CALL build_reduced_grid(SRC_NLAT, SRC_NLON, 1, src_ncell, src_i_index,        &
                          src_lon, src_lat, pert_blon, pert_blat)
  CALL build_reduced_grid(DST_NLAT, DST_NLON, 0, dst_ncell, dst_i_index,        &
                          dst_lon, dst_lat, dst_blon, dst_blat)

  ALLOCATE(src_field(src_ncell), src_mask(src_ncell))
  src_field = 1.0_dp
  ! mask a compact block of source cells well away from the poles
  CALL build_mask(src_lon, src_lat, src_mask)

  CALL xios_context_initialize("test", comm)
  CALL xios_get_handle("test", ctx_hdl)
  CALL xios_set_current_context(ctx_hdl)

  CALL declare_reduced_domain("src_reduced",           src_ncell, src_i_index,  &
                              src_lon, src_lat, src_blon, src_blat)
  CALL declare_reduced_domain("src_reduced_perturbed", src_ncell, src_i_index,  &
                              src_lon, src_lat, pert_blon, pert_blat)
  CALL declare_reduced_domain("src_reduced_masked",    src_ncell, src_i_index,  &
                              src_lon, src_lat, src_blon, src_blat)
  CALL xios_set_domain_attr("src_reduced_masked", mask_1d=src_mask)
  CALL declare_reduced_domain("dst_reduced",           dst_ncell, dst_i_index,  &
                              dst_lon, dst_lat, dst_blon, dst_blat)

  dtime%second = 3600
  CALL xios_set_timestep(dtime)
  CALL xios_close_context_definition()

  CALL xios_update_calendar(1)
  CALL xios_send_field("src_const",           src_field)
  CALL xios_send_field("src_const_perturbed", src_field)
  CALL xios_send_field("src_const_masked",    src_field)

  CALL xios_context_finalize()
  CALL xios_finalize()

  failures = 0
  IF (rank == 0) THEN
    CALL analytic_areas(DST_NLAT, DST_NLON, dst_area_glo)
    CALL run_checks(failures)
  END IF
  CALL MPI_BCAST(failures, 1, MPI_INTEGER, 0, MPI_COMM_WORLD, ierr)

  CALL MPI_FINALIZE(ierr)
  IF (failures /= 0) THEN
    IF (rank == 0) WRITE(*,'(A,I0,A)') "test_remap_conservation: ", failures, " CHECK(S) FAILED"
    STOP 1
  END IF
  IF (rank == 0) WRITE(*,'(A)') "test_remap_conservation: ALL CHECKS PASSED"

CONTAINS

  !> Reduced latitude-longitude grid: row j carries max(8, nint(cos(lat)*nlon))
  !> cells, so neighbouring rows generally disagree on where the shared row
  !> boundary is subdivided. With ulp_shift /= 0 the NORTH boundary of every
  !> interior row is moved by that many ulps in sin(lat) while the neighbour's
  !> SOUTH boundary is left alone, so the two owners of one logical boundary
  !> disagree at the 1e-16 level -- inside the tolerance XIOS itself uses to
  !> classify the edge as a small circle.
  SUBROUTINE build_reduced_grid(nlat, nlon, ulp_shift, ncell, i_index,          &
                                lon, lat, blon, blat)
    INTEGER, INTENT(IN) :: nlat, nlon, ulp_shift
    INTEGER, INTENT(OUT) :: ncell
    INTEGER, ALLOCATABLE, INTENT(OUT) :: i_index(:)
    REAL(dp), ALLOCATABLE, INTENT(OUT) :: lon(:), lat(:), blon(:,:), blat(:,:)
    INTEGER, ALLOCATABLE :: npr(:)
    REAL(dp), ALLOCATABLE :: north(:), south(:)
    REAL(dp) :: z, w, cl
    INTEGER :: j, q, k, ind

    ALLOCATE(npr(nlat), north(nlat), south(nlat))
    DO j = 1, nlat
      npr(j) = NINT(COS(PI/2.0_dp - (j-0.5_dp)*PI/nlat)*nlon)
      IF (npr(j) < 8) npr(j) = 8
      north(j) = 90.0_dp - REAL(j-1, dp)*180.0_dp/nlat
      south(j) = 90.0_dp - REAL(j,   dp)*180.0_dp/nlat
    END DO
    IF (ulp_shift /= 0) THEN
      DO j = 2, nlat
        z = SIN(north(j)*PI/180.0_dp)
        DO k = 1, ABS(ulp_shift)
          z = NEAREST(z, 1.0_dp)
        END DO
        north(j) = ASIN(z)*180.0_dp/PI
      END DO
    END IF

    ncell = SUM(npr)
    ALLOCATE(i_index(ncell), lon(ncell), lat(ncell))
    ALLOCATE(blon(4, ncell), blat(4, ncell))

    ind = 0
    DO j = 1, nlat
      w = 360.0_dp/REAL(npr(j), dp)
      DO q = 0, npr(j)-1
        ind = ind + 1
        cl = REAL(q, dp)*w
        i_index(ind) = ind - 1
        lon(ind) = cl
        lat(ind) = 90.0_dp - (j-0.5_dp)*180.0_dp/nlat
        blon(1,ind) = cl - 0.5_dp*w ; blat(1,ind) = south(j)
        blon(2,ind) = cl + 0.5_dp*w ; blat(2,ind) = south(j)
        blon(3,ind) = cl + 0.5_dp*w ; blat(3,ind) = north(j)
        blon(4,ind) = cl - 0.5_dp*w ; blat(4,ind) = north(j)
      END DO
    END DO
    DEALLOCATE(npr, north, south)
  END SUBROUTINE build_reduced_grid

  !> Exact spherical areas of the reduced destination cells, in global order.
  !> Each cell is bounded by two meridians and two latitude circles, so its area
  !> is d(lambda) * (sin(phi_north) - sin(phi_south)) exactly.
  SUBROUTINE analytic_areas(nlat, nlon, area)
    INTEGER, INTENT(IN) :: nlat, nlon
    REAL(dp), ALLOCATABLE, INTENT(OUT) :: area(:)
    INTEGER :: j, q, n, ind, ncell
    REAL(dp) :: dlam, sn, ss

    ncell = 0
    DO j = 1, nlat
      n = NINT(COS(PI/2.0_dp - (j-0.5_dp)*PI/nlat)*nlon)
      IF (n < 8) n = 8
      ncell = ncell + n
    END DO
    ALLOCATE(area(ncell))
    ind = 0
    DO j = 1, nlat
      n = NINT(COS(PI/2.0_dp - (j-0.5_dp)*PI/nlat)*nlon)
      IF (n < 8) n = 8
      dlam = 2.0_dp*PI/REAL(n, dp)
      sn = SIN((90.0_dp - REAL(j-1, dp)*180.0_dp/nlat)*PI/180.0_dp)
      ss = SIN((90.0_dp - REAL(j,   dp)*180.0_dp/nlat)*PI/180.0_dp)
      DO q = 1, n
        ind = ind + 1
        area(ind) = dlam*(sn - ss)
      END DO
    END DO
  END SUBROUTINE analytic_areas

  SUBROUTINE build_mask(lon, lat, mask)
    REAL(dp), INTENT(IN) :: lon(:), lat(:)
    LOGICAL, INTENT(OUT) :: mask(:)
    INTEGER :: i
    DO i = 1, SIZE(mask)
      mask(i) = .NOT. (lon(i) > 40.0_dp .AND. lon(i) < 140.0_dp .AND.           &
                       lat(i) > 10.0_dp .AND. lat(i) <  60.0_dp)
    END DO
  END SUBROUTINE build_mask

  SUBROUTINE declare_reduced_domain(id, ncell, i_index, lon, lat, blon, blat)
    CHARACTER(LEN=*), INTENT(IN) :: id
    INTEGER, INTENT(IN) :: ncell, i_index(:)
    REAL(dp), INTENT(IN) :: lon(:), lat(:), blon(:,:), blat(:,:)
    ! every rank declares the whole grid; the test runs at small size and the
    ! point of the test is the geometry, not the decomposition
    CALL xios_set_domain_attr(TRIM(id), ni_glo=ncell, ibegin=0, ni=ncell,       &
                              i_index=i_index)
    CALL xios_set_domain_attr(TRIM(id), data_dim=1, data_ibegin=0, data_ni=ncell)
    CALL xios_set_domain_attr(TRIM(id), lonvalue_1d=lon, latvalue_1d=lat)
    CALL xios_set_domain_attr(TRIM(id), nvertex=4, bounds_lon_1d=blon,          &
                              bounds_lat_1d=blat)
  END SUBROUTINE declare_reduced_domain

  SUBROUTINE read_var(fname, vname, values, ok)
    CHARACTER(LEN=*), INTENT(IN) :: fname, vname
    REAL(dp), ALLOCATABLE, INTENT(OUT) :: values(:)
    LOGICAL, INTENT(OUT) :: ok
    INTEGER :: ncid, varid, ndims, st, n, i
    INTEGER :: dimids(4), dlen(4)
    REAL(dp), ALLOCATABLE :: v1(:), v2(:,:), v3(:,:,:)
    ok = .FALSE.
    dlen = 1
    st = NF90_OPEN(TRIM(fname), NF90_NOWRITE, ncid) ; IF (st /= NF90_NOERR) RETURN
    st = NF90_INQ_VARID(ncid, TRIM(vname), varid)
    IF (st /= NF90_NOERR) THEN ; st = NF90_CLOSE(ncid) ; RETURN ; END IF
    st = NF90_INQUIRE_VARIABLE(ncid, varid, ndims=ndims, dimids=dimids)
    IF (st /= NF90_NOERR .OR. ndims < 1 .OR. ndims > 3) THEN
      st = NF90_CLOSE(ncid) ; RETURN
    END IF
    n = 1
    DO i = 1, ndims
      st = NF90_INQUIRE_DIMENSION(ncid, dimids(i), len=dlen(i))
      n = n*dlen(i)
    END DO
    ! netCDF-Fortran resolves NF90_GET_VAR on the rank of the receiving array, so
    ! it has to match the variable's rank; the result is then flattened.
    ALLOCATE(values(n))
    SELECT CASE (ndims)
    CASE (1)
      ALLOCATE(v1(dlen(1)))
      st = NF90_GET_VAR(ncid, varid, v1)
      values = v1
    CASE (2)
      ALLOCATE(v2(dlen(1), dlen(2)))
      st = NF90_GET_VAR(ncid, varid, v2)
      values = RESHAPE(v2, (/ n /))
    CASE (3)
      ALLOCATE(v3(dlen(1), dlen(2), dlen(3)))
      st = NF90_GET_VAR(ncid, varid, v3)
      values = RESHAPE(v3, (/ n /))
    END SELECT
    ok = (st == NF90_NOERR)
    st = NF90_CLOSE(ncid)
  END SUBROUTINE read_var

  SUBROUTINE report(name, value, tol, nfail)
    CHARACTER(LEN=*), INTENT(IN) :: name
    REAL(dp), INTENT(IN) :: value, tol
    INTEGER, INTENT(INOUT) :: nfail
    IF (value <= tol) THEN
      WRITE(*,'(A,A,A,ES12.5,A,ES12.5,A)') "  PASS  ", name, "  (", value, " <= ", tol, ")"
    ELSE
      WRITE(*,'(A,A,A,ES12.5,A,ES12.5,A)') "  FAIL  ", name, "  (", value, " >  ", tol, ")"
      nfail = nfail + 1
    END IF
  END SUBROUTINE report

  SUBROUTINE run_checks(nfail)
    INTEGER, INTENT(INOUT) :: nfail
    REAL(dp), ALLOCATABLE :: a(:), b(:), c(:), d(:), dlat(:)
    LOGICAL :: ok1, ok2, ok3, ok4
    REAL(dp) :: total
    INTEGER :: i, j, nlon_dst, nsel

    WRITE(*,'(A)') "test_remap_conservation:"

    CALL read_var("remap_conservation.nc",         "const_reduced_to_regular",   a, ok1)
    CALL read_var("remap_conservation.nc",         "const_perturbed_to_regular", b, ok2)
    CALL read_var("remap_conservation.nc",         "const_masked_to_regular",    c, ok3)
    CALL read_var("remap_conservation_reduced.nc", "const_reduced_to_reduced",   d, ok4)

    IF (.NOT. (ok1 .AND. ok2 .AND. ok3 .AND. ok4)) THEN
      WRITE(*,'(A)') "  FAIL  could not read the interpolated fields back"
      nfail = nfail + 1
      RETURN
    END IF

    ! 1 constant field preserved, reduced -> regular
    CALL report("reduced->regular constant closure   ", MAXVAL(ABS(a - 1.0_dp)), TOL_CLOSURE, nfail)

    ! 2 the same with one-ulp disagreement between the owners of each row boundary
    CALL report("one-ulp perturbed source closure    ", MAXVAL(ABS(b - 1.0_dp)), TOL_CLOSURE, nfail)

    ! 3 reduced -> reduced global overlap identity, sum_i v_i A_i = 4 pi.
    !   Row closure is blind to a target-side defect, so this uses areas.
    IF (SIZE(d) /= SIZE(dst_area_glo)) THEN
      WRITE(*,'(A,I0,A,I0)') "  FAIL  reduced destination size mismatch ", SIZE(d), " /= ", SIZE(dst_area_glo)
      nfail = nfail + 1
    ELSE
      total = 0.0_dp
      DO i = 1, SIZE(d)
        total = total + d(i)*dst_area_glo(i)
      END DO
      CALL report("reduced->reduced overlap - 4pi (sr)", ABS(total - 4.0_dp*PI), TOL_CONSERVATION, nfail)
    END IF

    ! 4 A masked source must not disturb the destination cells it cannot reach.
    !   The mask covers lon 40..140, lat 10..60, so every destination cell in the
    !   southern hemisphere draws all of its weight from source cells that are
    !   active in BOTH runs. Its value must therefore be unchanged to rounding.
    !   This is what checks that the complete pre-mask bounds act as a geometry
    !   provider only: if masking had altered the surviving source geometry, these
    !   far-away cells would move too. (The stronger statement -- that the masked
    !   matrix is bitwise the unmasked matrix with the inactive source columns
    !   deleted -- needs the weight file and is not checked here.)
    CALL read_var("remap_conservation.nc", "lat_dst_regular_c", dlat, ok1)
    IF (.NOT. ok1) THEN
      WRITE(*,'(A)') "  FAIL  could not read the destination latitudes"
      nfail = nfail + 1
    ELSE
      nlon_dst = SIZE(c)/SIZE(dlat)
      total = 0.0_dp
      nsel = 0
      DO i = 1, SIZE(c)
        j = (i - 1)/nlon_dst + 1          ! longitude varies fastest
        IF (j >= 1 .AND. j <= SIZE(dlat)) THEN
          IF (dlat(j) < -5.0_dp) THEN
            total = MAX(total, ABS(c(i) - a(i)))
            nsel = nsel + 1
          END IF
        END IF
      END DO
      WRITE(*,'(A,I0,A)') "  (source-mask check uses ", nsel, " southern destination cells)"
      CALL report("source mask: unreached rows unmoved", total, TOL_MASK, nfail)
    END IF
  END SUBROUTINE run_checks

END PROGRAM test_remap_conservation
