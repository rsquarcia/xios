! * ************************************************************************** *
! *               Interface auto generated - do not modify                     *
! * ************************************************************************** *
#include "xios_fortran_prefix.hpp"

MODULE ifunction_attr
  USE, INTRINSIC :: ISO_C_BINDING
  USE ifunction
  USE function_interface_attr
  USE LOGICAL_BOOL_CONVERSION

CONTAINS

  SUBROUTINE xios(set_function_attr)  &
    ( function_id, argin, argout, comment, expr, long_name, name, offload, pool_offload, pysrc, standard_name  &
     )

    IMPLICIT NONE
      TYPE(txios(function))  :: function_hdl
      CHARACTER(LEN=*), INTENT(IN) ::function_id
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: argin
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: argout
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: comment
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: expr
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: long_name
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: name
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: offload
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: pool_offload
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: pysrc
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: standard_name

      CALL xios(get_function_handle) &
      (function_id,function_hdl)
      CALL xios(set_function_attr_hdl_)   &
      ( function_hdl, argin, argout, comment, expr, long_name, name, offload, pool_offload, pysrc  &
      , standard_name )

  END SUBROUTINE xios(set_function_attr)

  SUBROUTINE xios(set_function_attr_hdl)  &
    ( function_hdl, argin, argout, comment, expr, long_name, name, offload, pool_offload, pysrc  &
    , standard_name )

    IMPLICIT NONE
      TYPE(txios(function)) , INTENT(IN) :: function_hdl
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: argin
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: argout
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: comment
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: expr
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: long_name
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: name
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: offload
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: pool_offload
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: pysrc
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: standard_name

      CALL xios(set_function_attr_hdl_)  &
      ( function_hdl, argin, argout, comment, expr, long_name, name, offload, pool_offload, pysrc  &
      , standard_name )

  END SUBROUTINE xios(set_function_attr_hdl)

  SUBROUTINE xios(set_function_attr_hdl_)   &
    ( function_hdl, argin_, argout_, comment_, expr_, long_name_, name_, offload_, pool_offload_  &
    , pysrc_, standard_name_ )

    IMPLICIT NONE
      TYPE(txios(function)) , INTENT(IN) :: function_hdl
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: argin_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: argout_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: comment_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: expr_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: long_name_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: name_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: offload_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: pool_offload_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: pysrc_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: standard_name_

      IF (PRESENT(argin_)) THEN
        CALL cxios_set_function_argin &
      (function_hdl%daddr, argin_, len(argin_))
      ENDIF

      IF (PRESENT(argout_)) THEN
        CALL cxios_set_function_argout &
      (function_hdl%daddr, argout_, len(argout_))
      ENDIF

      IF (PRESENT(comment_)) THEN
        CALL cxios_set_function_comment &
      (function_hdl%daddr, comment_, len(comment_))
      ENDIF

      IF (PRESENT(expr_)) THEN
        CALL cxios_set_function_expr &
      (function_hdl%daddr, expr_, len(expr_))
      ENDIF

      IF (PRESENT(long_name_)) THEN
        CALL cxios_set_function_long_name &
      (function_hdl%daddr, long_name_, len(long_name_))
      ENDIF

      IF (PRESENT(name_)) THEN
        CALL cxios_set_function_name &
      (function_hdl%daddr, name_, len(name_))
      ENDIF

      IF (PRESENT(offload_)) THEN
        CALL cxios_set_function_offload &
      (function_hdl%daddr, offload_, len(offload_))
      ENDIF

      IF (PRESENT(pool_offload_)) THEN
        CALL cxios_set_function_pool_offload &
      (function_hdl%daddr, pool_offload_, len(pool_offload_))
      ENDIF

      IF (PRESENT(pysrc_)) THEN
        CALL cxios_set_function_pysrc &
      (function_hdl%daddr, pysrc_, len(pysrc_))
      ENDIF

      IF (PRESENT(standard_name_)) THEN
        CALL cxios_set_function_standard_name &
      (function_hdl%daddr, standard_name_, len(standard_name_))
      ENDIF

  END SUBROUTINE xios(set_function_attr_hdl_)

  SUBROUTINE xios(get_function_attr)  &
    ( function_id, argin, argout, comment, expr, long_name, name, offload, pool_offload, pysrc, standard_name  &
     )

    IMPLICIT NONE
      TYPE(txios(function))  :: function_hdl
      CHARACTER(LEN=*), INTENT(IN) ::function_id
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: argin
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: argout
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: comment
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: expr
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: long_name
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: name
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: offload
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: pool_offload
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: pysrc
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: standard_name

      CALL xios(get_function_handle) &
      (function_id,function_hdl)
      CALL xios(get_function_attr_hdl_)   &
      ( function_hdl, argin, argout, comment, expr, long_name, name, offload, pool_offload, pysrc  &
      , standard_name )

  END SUBROUTINE xios(get_function_attr)

  SUBROUTINE xios(get_function_attr_hdl)  &
    ( function_hdl, argin, argout, comment, expr, long_name, name, offload, pool_offload, pysrc  &
    , standard_name )

    IMPLICIT NONE
      TYPE(txios(function)) , INTENT(IN) :: function_hdl
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: argin
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: argout
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: comment
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: expr
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: long_name
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: name
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: offload
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: pool_offload
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: pysrc
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: standard_name

      CALL xios(get_function_attr_hdl_)  &
      ( function_hdl, argin, argout, comment, expr, long_name, name, offload, pool_offload, pysrc  &
      , standard_name )

  END SUBROUTINE xios(get_function_attr_hdl)

  SUBROUTINE xios(get_function_attr_hdl_)   &
    ( function_hdl, argin_, argout_, comment_, expr_, long_name_, name_, offload_, pool_offload_  &
    , pysrc_, standard_name_ )

    IMPLICIT NONE
      TYPE(txios(function)) , INTENT(IN) :: function_hdl
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: argin_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: argout_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: comment_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: expr_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: long_name_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: name_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: offload_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: pool_offload_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: pysrc_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: standard_name_

      IF (PRESENT(argin_)) THEN
        CALL cxios_get_function_argin &
      (function_hdl%daddr, argin_, len(argin_))
      ENDIF

      IF (PRESENT(argout_)) THEN
        CALL cxios_get_function_argout &
      (function_hdl%daddr, argout_, len(argout_))
      ENDIF

      IF (PRESENT(comment_)) THEN
        CALL cxios_get_function_comment &
      (function_hdl%daddr, comment_, len(comment_))
      ENDIF

      IF (PRESENT(expr_)) THEN
        CALL cxios_get_function_expr &
      (function_hdl%daddr, expr_, len(expr_))
      ENDIF

      IF (PRESENT(long_name_)) THEN
        CALL cxios_get_function_long_name &
      (function_hdl%daddr, long_name_, len(long_name_))
      ENDIF

      IF (PRESENT(name_)) THEN
        CALL cxios_get_function_name &
      (function_hdl%daddr, name_, len(name_))
      ENDIF

      IF (PRESENT(offload_)) THEN
        CALL cxios_get_function_offload &
      (function_hdl%daddr, offload_, len(offload_))
      ENDIF

      IF (PRESENT(pool_offload_)) THEN
        CALL cxios_get_function_pool_offload &
      (function_hdl%daddr, pool_offload_, len(pool_offload_))
      ENDIF

      IF (PRESENT(pysrc_)) THEN
        CALL cxios_get_function_pysrc &
      (function_hdl%daddr, pysrc_, len(pysrc_))
      ENDIF

      IF (PRESENT(standard_name_)) THEN
        CALL cxios_get_function_standard_name &
      (function_hdl%daddr, standard_name_, len(standard_name_))
      ENDIF

  END SUBROUTINE xios(get_function_attr_hdl_)

  SUBROUTINE xios(is_defined_function_attr)  &
    ( function_id, argin, argout, comment, expr, long_name, name, offload, pool_offload, pysrc, standard_name  &
     )

    IMPLICIT NONE
      TYPE(txios(function))  :: function_hdl
      CHARACTER(LEN=*), INTENT(IN) ::function_id
      LOGICAL, OPTIONAL, INTENT(OUT) :: argin
      LOGICAL(KIND=C_BOOL) :: argin_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: argout
      LOGICAL(KIND=C_BOOL) :: argout_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: comment
      LOGICAL(KIND=C_BOOL) :: comment_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: expr
      LOGICAL(KIND=C_BOOL) :: expr_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: long_name
      LOGICAL(KIND=C_BOOL) :: long_name_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: name
      LOGICAL(KIND=C_BOOL) :: name_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: offload
      LOGICAL(KIND=C_BOOL) :: offload_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: pool_offload
      LOGICAL(KIND=C_BOOL) :: pool_offload_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: pysrc
      LOGICAL(KIND=C_BOOL) :: pysrc_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: standard_name
      LOGICAL(KIND=C_BOOL) :: standard_name_tmp

      CALL xios(get_function_handle) &
      (function_id,function_hdl)
      CALL xios(is_defined_function_attr_hdl_)   &
      ( function_hdl, argin, argout, comment, expr, long_name, name, offload, pool_offload, pysrc  &
      , standard_name )

  END SUBROUTINE xios(is_defined_function_attr)

  SUBROUTINE xios(is_defined_function_attr_hdl)  &
    ( function_hdl, argin, argout, comment, expr, long_name, name, offload, pool_offload, pysrc  &
    , standard_name )

    IMPLICIT NONE
      TYPE(txios(function)) , INTENT(IN) :: function_hdl
      LOGICAL, OPTIONAL, INTENT(OUT) :: argin
      LOGICAL(KIND=C_BOOL) :: argin_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: argout
      LOGICAL(KIND=C_BOOL) :: argout_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: comment
      LOGICAL(KIND=C_BOOL) :: comment_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: expr
      LOGICAL(KIND=C_BOOL) :: expr_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: long_name
      LOGICAL(KIND=C_BOOL) :: long_name_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: name
      LOGICAL(KIND=C_BOOL) :: name_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: offload
      LOGICAL(KIND=C_BOOL) :: offload_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: pool_offload
      LOGICAL(KIND=C_BOOL) :: pool_offload_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: pysrc
      LOGICAL(KIND=C_BOOL) :: pysrc_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: standard_name
      LOGICAL(KIND=C_BOOL) :: standard_name_tmp

      CALL xios(is_defined_function_attr_hdl_)  &
      ( function_hdl, argin, argout, comment, expr, long_name, name, offload, pool_offload, pysrc  &
      , standard_name )

  END SUBROUTINE xios(is_defined_function_attr_hdl)

  SUBROUTINE xios(is_defined_function_attr_hdl_)   &
    ( function_hdl, argin_, argout_, comment_, expr_, long_name_, name_, offload_, pool_offload_  &
    , pysrc_, standard_name_ )

    IMPLICIT NONE
      TYPE(txios(function)) , INTENT(IN) :: function_hdl
      LOGICAL, OPTIONAL, INTENT(OUT) :: argin_
      LOGICAL(KIND=C_BOOL) :: argin__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: argout_
      LOGICAL(KIND=C_BOOL) :: argout__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: comment_
      LOGICAL(KIND=C_BOOL) :: comment__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: expr_
      LOGICAL(KIND=C_BOOL) :: expr__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: long_name_
      LOGICAL(KIND=C_BOOL) :: long_name__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: name_
      LOGICAL(KIND=C_BOOL) :: name__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: offload_
      LOGICAL(KIND=C_BOOL) :: offload__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: pool_offload_
      LOGICAL(KIND=C_BOOL) :: pool_offload__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: pysrc_
      LOGICAL(KIND=C_BOOL) :: pysrc__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: standard_name_
      LOGICAL(KIND=C_BOOL) :: standard_name__tmp

      IF (PRESENT(argin_)) THEN
        argin__tmp = cxios_is_defined_function_argin &
      (function_hdl%daddr)
        argin_ = argin__tmp
      ENDIF

      IF (PRESENT(argout_)) THEN
        argout__tmp = cxios_is_defined_function_argout &
      (function_hdl%daddr)
        argout_ = argout__tmp
      ENDIF

      IF (PRESENT(comment_)) THEN
        comment__tmp = cxios_is_defined_function_comment &
      (function_hdl%daddr)
        comment_ = comment__tmp
      ENDIF

      IF (PRESENT(expr_)) THEN
        expr__tmp = cxios_is_defined_function_expr &
      (function_hdl%daddr)
        expr_ = expr__tmp
      ENDIF

      IF (PRESENT(long_name_)) THEN
        long_name__tmp = cxios_is_defined_function_long_name &
      (function_hdl%daddr)
        long_name_ = long_name__tmp
      ENDIF

      IF (PRESENT(name_)) THEN
        name__tmp = cxios_is_defined_function_name &
      (function_hdl%daddr)
        name_ = name__tmp
      ENDIF

      IF (PRESENT(offload_)) THEN
        offload__tmp = cxios_is_defined_function_offload &
      (function_hdl%daddr)
        offload_ = offload__tmp
      ENDIF

      IF (PRESENT(pool_offload_)) THEN
        pool_offload__tmp = cxios_is_defined_function_pool_offload &
      (function_hdl%daddr)
        pool_offload_ = pool_offload__tmp
      ENDIF

      IF (PRESENT(pysrc_)) THEN
        pysrc__tmp = cxios_is_defined_function_pysrc &
      (function_hdl%daddr)
        pysrc_ = pysrc__tmp
      ENDIF

      IF (PRESENT(standard_name_)) THEN
        standard_name__tmp = cxios_is_defined_function_standard_name &
      (function_hdl%daddr)
        standard_name_ = standard_name__tmp
      ENDIF

  END SUBROUTINE xios(is_defined_function_attr_hdl_)

END MODULE ifunction_attr
