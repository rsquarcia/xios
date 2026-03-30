MODULE logical_bool_conversion

   USE, INTRINSIC :: ISO_C_BINDING

   IMPLICIT NONE

   ! Static declaration of fortran representation
   ! of C++ bool type
   LOGICAL (KIND=C_BOOL) :: ktrue, kfalse

   ! Accessor to the c++ bool true and false constants

   INTERFACE
      FUNCTION cxios_set_logical_true() BIND(C)
         USE ISO_C_BINDING
         LOGICAL(kind=C_BOOL) :: cxios_set_logical_true
      END FUNCTION cxios_set_logical_true

      FUNCTION cxios_set_logical_false() BIND(C)
         USE ISO_C_BINDING
         LOGICAL(kind=C_BOOL) :: cxios_set_logical_false
      END FUNCTION cxios_set_logical_false
   END INTERFACE

   ! Generic interface to functions from f90 logical to c++ bool
   ! Input can be standard f90 logical or c_bool

   INTERFACE logical_to_bool
      MODULE PROCEDURE xios_logical_to_bool_0d, &
         &             xios_logical_to_bool_1d, &
         &             xios_logical_to_bool_2d, &
         &             xios_logical_to_bool_3d, &
         &             xios_logical_to_bool_4d, &
         &             xios_logical_to_bool_5d, &
         &             xios_logical_to_bool_6d, &
         &             xios_logical_to_bool_7d, &
         &             xios_clogical_to_bool_0d, &
         &             xios_clogical_to_bool_1d, &
         &             xios_clogical_to_bool_2d, &
         &             xios_clogical_to_bool_3d, &
         &             xios_clogical_to_bool_4d, &
         &             xios_clogical_to_bool_5d, &
         &             xios_clogical_to_bool_6d, &
         &             xios_clogical_to_bool_7d
   END INTERFACE logical_to_bool

   ! Generic interface to functions from c++ bool to f90 standard logical
   
   INTERFACE bool_to_logical
      MODULE PROCEDURE xios_bool_to_logical_0d, &
         &             xios_bool_to_logical_1d, &
         &             xios_bool_to_logical_2d, &
         &             xios_bool_to_logical_3d, &
         &             xios_bool_to_logical_4d, &
         &             xios_bool_to_logical_5d, &
         &             xios_bool_to_logical_6d, &
         &             xios_bool_to_logical_7d
   END INTERFACE bool_to_logical

CONTAINS

   ! Scalar functions (to be used for higher rank operations)

   LOGICAL (KIND=C_BOOL) FUNCTION xios_logical_to_bool_0d(tmp)
      LOGICAL, INTENT(IN) :: tmp
      IF (tmp) THEN
         xios_logical_to_bool_0d = ktrue
      ELSE
         xios_logical_to_bool_0d = kfalse
      END IF
   END FUNCTION xios_logical_to_bool_0d

   LOGICAL (KIND=C_BOOL) FUNCTION xios_clogical_to_bool_0d(tmp)
      LOGICAL (KIND=C_BOOL), INTENT(IN) :: tmp
      IF (tmp) THEN
         xios_clogical_to_bool_0d = ktrue
      ELSE
         xios_clogical_to_bool_0d = kfalse
      END IF
   END FUNCTION xios_clogical_to_bool_0d

   ! Higher ranks implemented recursively from previous rank
   
   FUNCTION xios_logical_to_bool_1d(tmp)
      LOGICAL, INTENT(IN), DIMENSION(:) :: tmp
      LOGICAL (KIND=C_BOOL), DIMENSION(SIZE(tmp)) :: xios_logical_to_bool_1d
      INTEGER :: ij
      DO ij = 1, SIZE(tmp)
         xios_logical_to_bool_1d(ij) = logical_to_bool(tmp(ij))
      END DO
   END FUNCTION xios_logical_to_bool_1d

   FUNCTION xios_clogical_to_bool_1d(tmp)
      LOGICAL (KIND=C_BOOL), INTENT(IN), DIMENSION(:) :: tmp
      LOGICAL (KIND=C_BOOL), DIMENSION(SIZE(tmp)) :: xios_clogical_to_bool_1d
      INTEGER :: ij
      DO ij = 1, SIZE(tmp)
         xios_clogical_to_bool_1d(ij) = logical_to_bool(tmp(ij))
      END DO
   END FUNCTION xios_clogical_to_bool_1d

   FUNCTION xios_logical_to_bool_2d(tmp)
      LOGICAL, INTENT(IN) :: tmp(:,:)
      LOGICAL (KIND=C_BOOL), DIMENSION(SIZE(tmp,dim=1),SIZE(tmp,dim=2)) :: xios_logical_to_bool_2d
      INTEGER :: ij
      DO ij = 1,SIZE(tmp,dim=2)
         xios_logical_to_bool_2d(:,ij) = logical_to_bool(tmp(:,ij))
      ENDDO
   END FUNCTION xios_logical_to_bool_2d

   FUNCTION xios_clogical_to_bool_2d(tmp)
      LOGICAL (KIND=C_BOOL), INTENT(IN) :: tmp(:,:)
      LOGICAL (KIND=C_BOOL), DIMENSION(SIZE(tmp,dim=1),SIZE(tmp,dim=2)) :: xios_clogical_to_bool_2d
      INTEGER :: ij
      DO ij = 1,SIZE(tmp,dim=2)
         xios_clogical_to_bool_2d(:,ij) = logical_to_bool(tmp(:,ij))
      ENDDO
   END FUNCTION xios_clogical_to_bool_2d

   FUNCTION xios_logical_to_bool_3d(tmp)
      LOGICAL, INTENT(IN) :: tmp(:,:,:)
      LOGICAL (KIND=C_BOOL), DIMENSION(SIZE(tmp,dim=1),SIZE(tmp,dim=2),SIZE(tmp,dim=3)) :: xios_logical_to_bool_3d
      INTEGER :: ij
      DO ij = 1,SIZE(tmp,dim=3)
         xios_logical_to_bool_3d(:,:,ij) = logical_to_bool(tmp(:,:,ij))
      ENDDO
   END FUNCTION xios_logical_to_bool_3d

   FUNCTION xios_clogical_to_bool_3d(tmp)
      LOGICAL (KIND=C_BOOL), INTENT(IN) :: tmp(:,:,:)
      LOGICAL (KIND=C_BOOL), DIMENSION(SIZE(tmp,dim=1),SIZE(tmp,dim=2),SIZE(tmp,dim=3)) :: xios_clogical_to_bool_3d
      INTEGER :: ij
      DO ij = 1,SIZE(tmp,dim=3)
         xios_clogical_to_bool_3d(:,:,ij) = logical_to_bool(tmp(:,:,ij))
      ENDDO
   END FUNCTION xios_clogical_to_bool_3d

   FUNCTION xios_logical_to_bool_4d(tmp)
      LOGICAL, INTENT(IN) :: tmp(:,:,:,:)
      LOGICAL (KIND=C_BOOL), DIMENSION(SIZE(tmp,dim=1),SIZE(tmp,dim=2),SIZE(tmp,dim=3), &
         & SIZE(tmp,dim=4)) :: xios_logical_to_bool_4d
      INTEGER :: ij
      DO ij = 1,SIZE(tmp,dim=4)
         xios_logical_to_bool_4d(:,:,:,ij) = logical_to_bool(tmp(:,:,:,ij))
      ENDDO
   END FUNCTION xios_logical_to_bool_4d

   FUNCTION xios_clogical_to_bool_4d(tmp)
      LOGICAL (KIND=C_BOOL), INTENT(IN) :: tmp(:,:,:,:)
      LOGICAL (KIND=C_BOOL), DIMENSION(SIZE(tmp,dim=1),SIZE(tmp,dim=2),SIZE(tmp,dim=3), &
         & SIZE(tmp,dim=4)) :: xios_clogical_to_bool_4d
      INTEGER :: ij
      DO ij = 1,SIZE(tmp,dim=4)
         xios_clogical_to_bool_4d(:,:,:,ij) = logical_to_bool(tmp(:,:,:,ij))
      ENDDO
   END FUNCTION xios_clogical_to_bool_4d

   FUNCTION xios_logical_to_bool_5d(tmp)
      LOGICAL, INTENT(IN) :: tmp(:,:,:,:,:)
      LOGICAL (KIND=C_BOOL), DIMENSION(SIZE(tmp,dim=1),SIZE(tmp,dim=2),SIZE(tmp,dim=3), &
         & SIZE(tmp,dim=4),SIZE(tmp,dim=5)) :: xios_logical_to_bool_5d
      INTEGER :: ij
      DO ij = 1,SIZE(tmp,dim=5)
         xios_logical_to_bool_5d(:,:,:,:,ij) = logical_to_bool(tmp(:,:,:,:,ij))
      ENDDO
   END FUNCTION xios_logical_to_bool_5d

   FUNCTION xios_clogical_to_bool_5d(tmp)
      LOGICAL (KIND=C_BOOL), INTENT(IN) :: tmp(:,:,:,:,:)
      LOGICAL (KIND=C_BOOL), DIMENSION(SIZE(tmp,dim=1),SIZE(tmp,dim=2),SIZE(tmp,dim=3), &
         & SIZE(tmp,dim=4),SIZE(tmp,dim=5)) :: xios_clogical_to_bool_5d
      INTEGER :: ij
      DO ij = 1,SIZE(tmp,dim=5)
         xios_clogical_to_bool_5d(:,:,:,:,ij) = logical_to_bool(tmp(:,:,:,:,ij))
      ENDDO
   END FUNCTION xios_clogical_to_bool_5d

   FUNCTION xios_logical_to_bool_6d(tmp)
      LOGICAL, INTENT(IN) :: tmp(:,:,:,:,:,:)
      LOGICAL (KIND=C_BOOL), DIMENSION(SIZE(tmp,dim=1),SIZE(tmp,dim=2),SIZE(tmp,dim=3), &
         & SIZE(tmp,dim=4),SIZE(tmp,dim=5),SIZE(tmp,dim=6)) :: xios_logical_to_bool_6d
      INTEGER :: ij
      DO ij = 1,SIZE(tmp,dim=6)
         xios_logical_to_bool_6d(:,:,:,:,:,ij) = logical_to_bool(tmp(:,:,:,:,:,ij))
      ENDDO
   END FUNCTION xios_logical_to_bool_6d

   FUNCTION xios_clogical_to_bool_6d(tmp)
      LOGICAL (KIND=C_BOOL), INTENT(IN) :: tmp(:,:,:,:,:,:)
      LOGICAL (KIND=C_BOOL), DIMENSION(SIZE(tmp,dim=1),SIZE(tmp,dim=2),SIZE(tmp,dim=3), &
         & SIZE(tmp,dim=4),SIZE(tmp,dim=5),SIZE(tmp,dim=6)) :: xios_clogical_to_bool_6d
      INTEGER :: ij
      DO ij = 1,SIZE(tmp,dim=6)
         xios_clogical_to_bool_6d(:,:,:,:,:,ij) = logical_to_bool(tmp(:,:,:,:,:,ij))
      ENDDO
   END FUNCTION xios_clogical_to_bool_6d

   FUNCTION xios_logical_to_bool_7d(tmp)
      LOGICAL, INTENT(IN) :: tmp(:,:,:,:,:,:,:)
      LOGICAL (KIND=C_BOOL), DIMENSION(SIZE(tmp,dim=1),SIZE(tmp,dim=2),SIZE(tmp,dim=3), &
         & SIZE(tmp,dim=4),SIZE(tmp,dim=5),SIZE(tmp,dim=6),SIZE(tmp,dim=6)) :: xios_logical_to_bool_7d
      INTEGER :: ij
      DO ij = 1,SIZE(tmp,dim=7)
         xios_logical_to_bool_7d(:,:,:,:,:,:,ij) = logical_to_bool(tmp(:,:,:,:,:,:,ij))
      ENDDO
   END FUNCTION xios_logical_to_bool_7d

   FUNCTION xios_clogical_to_bool_7d(tmp)
      LOGICAL (KIND=C_BOOL), INTENT(IN) :: tmp(:,:,:,:,:,:,:)
      LOGICAL (KIND=C_BOOL), DIMENSION(SIZE(tmp,dim=1),SIZE(tmp,dim=2),SIZE(tmp,dim=3), &
         & SIZE(tmp,dim=4),SIZE(tmp,dim=5),SIZE(tmp,dim=6),SIZE(tmp,dim=6)) :: xios_clogical_to_bool_7d
      INTEGER :: ij
      DO ij = 1,SIZE(tmp,dim=7)
         xios_clogical_to_bool_7d(:,:,:,:,:,:,ij) = logical_to_bool(tmp(:,:,:,:,:,:,ij))
      ENDDO
   END FUNCTION xios_clogical_to_bool_7d

   ! Scalar function (to be used for higher rank operations)
   
   LOGICAL FUNCTION xios_bool_to_logical_0d(tmp)
      LOGICAL (KIND=C_BOOL), INTENT(IN) :: tmp
      IF (tmp.EQV.kfalse) THEN
         xios_bool_to_logical_0d = .FALSE.
      ELSE
         xios_bool_to_logical_0d = .TRUE.
      END IF
   END FUNCTION xios_bool_to_logical_0d

   ! Higher ranks implemented recursively from previous rank
   
   FUNCTION xios_bool_to_logical_1d(tmp)
      LOGICAL (KIND=C_BOOL), INTENT(IN) :: tmp(:)
      LOGICAL, DIMENSION(SIZE(tmp)) :: xios_bool_to_logical_1d
      INTEGER :: ij
      DO ij = 1, SIZE(tmp)
         xios_bool_to_logical_1d(ij) = bool_to_logical(tmp(ij))
      END DO
   END FUNCTION xios_bool_to_logical_1d

   FUNCTION xios_bool_to_logical_2d(tmp)
      LOGICAL (KIND=C_BOOL), INTENT(IN) :: tmp(:,:)
      LOGICAL, DIMENSION(SIZE(tmp,dim=1),SIZE(tmp,dim=2)) :: xios_bool_to_logical_2d
      INTEGER :: ij
      DO ij = 1, SIZE(tmp,dim=2)
         xios_bool_to_logical_2d(:,ij) = bool_to_logical(tmp(:,ij))
      END DO
   END FUNCTION xios_bool_to_logical_2d

   FUNCTION xios_bool_to_logical_3d(tmp)
      LOGICAL (KIND=C_BOOL), INTENT(IN) :: tmp(:,:,:)
      LOGICAL, DIMENSION(SIZE(tmp,dim=1),SIZE(tmp,dim=2),SIZE(tmp,dim=3)) :: xios_bool_to_logical_3d
      INTEGER :: ij
      DO ij = 1, SIZE(tmp,dim=3)
         xios_bool_to_logical_3d(:,:,ij) = bool_to_logical(tmp(:,:,ij))
      END DO
   END FUNCTION xios_bool_to_logical_3d

   FUNCTION xios_bool_to_logical_4d(tmp)
      LOGICAL (KIND=C_BOOL), INTENT(IN) :: tmp(:,:,:,:)
      LOGICAL, DIMENSION(SIZE(tmp,dim=1),SIZE(tmp,dim=2),SIZE(tmp,dim=3), &
         & SIZE(tmp,dim=4)) :: xios_bool_to_logical_4d
      INTEGER :: ij
      DO ij = 1, SIZE(tmp,dim=4)
         xios_bool_to_logical_4d(:,:,:,ij) = bool_to_logical(tmp(:,:,:,ij))
      END DO
   END FUNCTION xios_bool_to_logical_4d

   FUNCTION xios_bool_to_logical_5d(tmp)
      LOGICAL (KIND=C_BOOL), INTENT(IN) :: tmp(:,:,:,:,:)
      LOGICAL, DIMENSION(SIZE(tmp,dim=1),SIZE(tmp,dim=2),SIZE(tmp,dim=3), &
         & SIZE(tmp,dim=4),SIZE(tmp,dim=5)) :: xios_bool_to_logical_5d
      INTEGER :: ij
      DO ij = 1, SIZE(tmp,dim=5)
         xios_bool_to_logical_5d(:,:,:,:,ij) = bool_to_logical(tmp(:,:,:,:,ij))
      END DO
   END FUNCTION xios_bool_to_logical_5d

   FUNCTION xios_bool_to_logical_6d(tmp)
      LOGICAL (KIND=C_BOOL), INTENT(IN) :: tmp(:,:,:,:,:,:)
      LOGICAL, DIMENSION(SIZE(tmp,dim=1),SIZE(tmp,dim=2),SIZE(tmp,dim=3), &
         & SIZE(tmp,dim=4),SIZE(tmp,dim=5),SIZE(tmp,dim=6)) :: xios_bool_to_logical_6d
      INTEGER :: ij
      DO ij = 1, SIZE(tmp,dim=6)
         xios_bool_to_logical_6d(:,:,:,:,:,ij) = bool_to_logical(tmp(:,:,:,:,:,ij))
      END DO
   END FUNCTION xios_bool_to_logical_6d

   FUNCTION xios_bool_to_logical_7d(tmp)
      LOGICAL (KIND=C_BOOL), INTENT(IN) :: tmp(:,:,:,:,:,:,:)
      LOGICAL, DIMENSION(SIZE(tmp,dim=1),SIZE(tmp,dim=2),SIZE(tmp,dim=3), &
         & SIZE(tmp,dim=4),SIZE(tmp,dim=5),SIZE(tmp,dim=6),SIZE(tmp,dim=7)) :: xios_bool_to_logical_7d
      INTEGER :: ij
      DO ij = 1, SIZE(tmp,dim=7)
         xios_bool_to_logical_7d(:,:,:,:,:,:,ij) = bool_to_logical(tmp(:,:,:,:,:,:,ij))
      END DO
   END FUNCTION xios_bool_to_logical_7d

END MODULE logical_bool_conversion


