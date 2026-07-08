! * ************************************************************************** *
! *               Interface auto generated - do not modify                     *
! * ************************************************************************** *
#include "xios_fortran_prefix.hpp"

MODULE ifunctiongroup_attr
  USE, INTRINSIC :: ISO_C_BINDING
  USE ifunction
  USE functiongroup_interface_attr
  USE LOGICAL_BOOL_CONVERSION

CONTAINS

  SUBROUTINE xios(set_functiongroup_attr)  &
    ( functiongroup_id, argin, argout, comment, expr, group_ref, long_name, name, standard_name  &
     )

    IMPLICIT NONE
      TYPE(txios(functiongroup))  :: functiongroup_hdl
      CHARACTER(LEN=*), INTENT(IN) ::functiongroup_id
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: argin
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: argout
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: comment
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: expr
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: group_ref
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: long_name
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: name
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: standard_name

      CALL xios(get_functiongroup_handle) &
      (functiongroup_id,functiongroup_hdl)
      CALL xios(set_functiongroup_attr_hdl_)   &
      ( functiongroup_hdl, argin, argout, comment, expr, group_ref, long_name, name, standard_name  &
       )

  END SUBROUTINE xios(set_functiongroup_attr)

  SUBROUTINE xios(set_functiongroup_attr_hdl)  &
    ( functiongroup_hdl, argin, argout, comment, expr, group_ref, long_name, name, standard_name  &
     )

    IMPLICIT NONE
      TYPE(txios(functiongroup)) , INTENT(IN) :: functiongroup_hdl
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: argin
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: argout
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: comment
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: expr
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: group_ref
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: long_name
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: name
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: standard_name

      CALL xios(set_functiongroup_attr_hdl_)  &
      ( functiongroup_hdl, argin, argout, comment, expr, group_ref, long_name, name, standard_name  &
       )

  END SUBROUTINE xios(set_functiongroup_attr_hdl)

  SUBROUTINE xios(set_functiongroup_attr_hdl_)   &
    ( functiongroup_hdl, argin_, argout_, comment_, expr_, group_ref_, long_name_, name_, standard_name_  &
     )

    IMPLICIT NONE
      TYPE(txios(functiongroup)) , INTENT(IN) :: functiongroup_hdl
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: argin_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: argout_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: comment_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: expr_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: group_ref_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: long_name_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: name_
      CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: standard_name_

      IF (PRESENT(argin_)) THEN
        CALL cxios_set_functiongroup_argin &
      (functiongroup_hdl%daddr, argin_, len(argin_))
      ENDIF

      IF (PRESENT(argout_)) THEN
        CALL cxios_set_functiongroup_argout &
      (functiongroup_hdl%daddr, argout_, len(argout_))
      ENDIF

      IF (PRESENT(comment_)) THEN
        CALL cxios_set_functiongroup_comment &
      (functiongroup_hdl%daddr, comment_, len(comment_))
      ENDIF

      IF (PRESENT(expr_)) THEN
        CALL cxios_set_functiongroup_expr &
      (functiongroup_hdl%daddr, expr_, len(expr_))
      ENDIF

      IF (PRESENT(group_ref_)) THEN
        CALL cxios_set_functiongroup_group_ref &
      (functiongroup_hdl%daddr, group_ref_, len(group_ref_))
      ENDIF

      IF (PRESENT(long_name_)) THEN
        CALL cxios_set_functiongroup_long_name &
      (functiongroup_hdl%daddr, long_name_, len(long_name_))
      ENDIF

      IF (PRESENT(name_)) THEN
        CALL cxios_set_functiongroup_name &
      (functiongroup_hdl%daddr, name_, len(name_))
      ENDIF

      IF (PRESENT(standard_name_)) THEN
        CALL cxios_set_functiongroup_standard_name &
      (functiongroup_hdl%daddr, standard_name_, len(standard_name_))
      ENDIF

  END SUBROUTINE xios(set_functiongroup_attr_hdl_)

  SUBROUTINE xios(get_functiongroup_attr)  &
    ( functiongroup_id, argin, argout, comment, expr, group_ref, long_name, name, standard_name  &
     )

    IMPLICIT NONE
      TYPE(txios(functiongroup))  :: functiongroup_hdl
      CHARACTER(LEN=*), INTENT(IN) ::functiongroup_id
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: argin
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: argout
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: comment
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: expr
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: group_ref
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: long_name
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: name
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: standard_name

      CALL xios(get_functiongroup_handle) &
      (functiongroup_id,functiongroup_hdl)
      CALL xios(get_functiongroup_attr_hdl_)   &
      ( functiongroup_hdl, argin, argout, comment, expr, group_ref, long_name, name, standard_name  &
       )

  END SUBROUTINE xios(get_functiongroup_attr)

  SUBROUTINE xios(get_functiongroup_attr_hdl)  &
    ( functiongroup_hdl, argin, argout, comment, expr, group_ref, long_name, name, standard_name  &
     )

    IMPLICIT NONE
      TYPE(txios(functiongroup)) , INTENT(IN) :: functiongroup_hdl
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: argin
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: argout
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: comment
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: expr
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: group_ref
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: long_name
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: name
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: standard_name

      CALL xios(get_functiongroup_attr_hdl_)  &
      ( functiongroup_hdl, argin, argout, comment, expr, group_ref, long_name, name, standard_name  &
       )

  END SUBROUTINE xios(get_functiongroup_attr_hdl)

  SUBROUTINE xios(get_functiongroup_attr_hdl_)   &
    ( functiongroup_hdl, argin_, argout_, comment_, expr_, group_ref_, long_name_, name_, standard_name_  &
     )

    IMPLICIT NONE
      TYPE(txios(functiongroup)) , INTENT(IN) :: functiongroup_hdl
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: argin_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: argout_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: comment_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: expr_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: group_ref_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: long_name_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: name_
      CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: standard_name_

      IF (PRESENT(argin_)) THEN
        CALL cxios_get_functiongroup_argin &
      (functiongroup_hdl%daddr, argin_, len(argin_))
      ENDIF

      IF (PRESENT(argout_)) THEN
        CALL cxios_get_functiongroup_argout &
      (functiongroup_hdl%daddr, argout_, len(argout_))
      ENDIF

      IF (PRESENT(comment_)) THEN
        CALL cxios_get_functiongroup_comment &
      (functiongroup_hdl%daddr, comment_, len(comment_))
      ENDIF

      IF (PRESENT(expr_)) THEN
        CALL cxios_get_functiongroup_expr &
      (functiongroup_hdl%daddr, expr_, len(expr_))
      ENDIF

      IF (PRESENT(group_ref_)) THEN
        CALL cxios_get_functiongroup_group_ref &
      (functiongroup_hdl%daddr, group_ref_, len(group_ref_))
      ENDIF

      IF (PRESENT(long_name_)) THEN
        CALL cxios_get_functiongroup_long_name &
      (functiongroup_hdl%daddr, long_name_, len(long_name_))
      ENDIF

      IF (PRESENT(name_)) THEN
        CALL cxios_get_functiongroup_name &
      (functiongroup_hdl%daddr, name_, len(name_))
      ENDIF

      IF (PRESENT(standard_name_)) THEN
        CALL cxios_get_functiongroup_standard_name &
      (functiongroup_hdl%daddr, standard_name_, len(standard_name_))
      ENDIF

  END SUBROUTINE xios(get_functiongroup_attr_hdl_)

  SUBROUTINE xios(is_defined_functiongroup_attr)  &
    ( functiongroup_id, argin, argout, comment, expr, group_ref, long_name, name, standard_name  &
     )

    IMPLICIT NONE
      TYPE(txios(functiongroup))  :: functiongroup_hdl
      CHARACTER(LEN=*), INTENT(IN) ::functiongroup_id
      LOGICAL, OPTIONAL, INTENT(OUT) :: argin
      LOGICAL(KIND=C_BOOL) :: argin_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: argout
      LOGICAL(KIND=C_BOOL) :: argout_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: comment
      LOGICAL(KIND=C_BOOL) :: comment_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: expr
      LOGICAL(KIND=C_BOOL) :: expr_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: group_ref
      LOGICAL(KIND=C_BOOL) :: group_ref_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: long_name
      LOGICAL(KIND=C_BOOL) :: long_name_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: name
      LOGICAL(KIND=C_BOOL) :: name_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: standard_name
      LOGICAL(KIND=C_BOOL) :: standard_name_tmp

      CALL xios(get_functiongroup_handle) &
      (functiongroup_id,functiongroup_hdl)
      CALL xios(is_defined_functiongroup_attr_hdl_)   &
      ( functiongroup_hdl, argin, argout, comment, expr, group_ref, long_name, name, standard_name  &
       )

  END SUBROUTINE xios(is_defined_functiongroup_attr)

  SUBROUTINE xios(is_defined_functiongroup_attr_hdl)  &
    ( functiongroup_hdl, argin, argout, comment, expr, group_ref, long_name, name, standard_name  &
     )

    IMPLICIT NONE
      TYPE(txios(functiongroup)) , INTENT(IN) :: functiongroup_hdl
      LOGICAL, OPTIONAL, INTENT(OUT) :: argin
      LOGICAL(KIND=C_BOOL) :: argin_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: argout
      LOGICAL(KIND=C_BOOL) :: argout_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: comment
      LOGICAL(KIND=C_BOOL) :: comment_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: expr
      LOGICAL(KIND=C_BOOL) :: expr_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: group_ref
      LOGICAL(KIND=C_BOOL) :: group_ref_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: long_name
      LOGICAL(KIND=C_BOOL) :: long_name_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: name
      LOGICAL(KIND=C_BOOL) :: name_tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: standard_name
      LOGICAL(KIND=C_BOOL) :: standard_name_tmp

      CALL xios(is_defined_functiongroup_attr_hdl_)  &
      ( functiongroup_hdl, argin, argout, comment, expr, group_ref, long_name, name, standard_name  &
       )

  END SUBROUTINE xios(is_defined_functiongroup_attr_hdl)

  SUBROUTINE xios(is_defined_functiongroup_attr_hdl_)   &
    ( functiongroup_hdl, argin_, argout_, comment_, expr_, group_ref_, long_name_, name_, standard_name_  &
     )

    IMPLICIT NONE
      TYPE(txios(functiongroup)) , INTENT(IN) :: functiongroup_hdl
      LOGICAL, OPTIONAL, INTENT(OUT) :: argin_
      LOGICAL(KIND=C_BOOL) :: argin__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: argout_
      LOGICAL(KIND=C_BOOL) :: argout__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: comment_
      LOGICAL(KIND=C_BOOL) :: comment__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: expr_
      LOGICAL(KIND=C_BOOL) :: expr__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: group_ref_
      LOGICAL(KIND=C_BOOL) :: group_ref__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: long_name_
      LOGICAL(KIND=C_BOOL) :: long_name__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: name_
      LOGICAL(KIND=C_BOOL) :: name__tmp
      LOGICAL, OPTIONAL, INTENT(OUT) :: standard_name_
      LOGICAL(KIND=C_BOOL) :: standard_name__tmp

      IF (PRESENT(argin_)) THEN
        argin__tmp = cxios_is_defined_functiongroup_argin &
      (functiongroup_hdl%daddr)
        argin_ = argin__tmp
      ENDIF

      IF (PRESENT(argout_)) THEN
        argout__tmp = cxios_is_defined_functiongroup_argout &
      (functiongroup_hdl%daddr)
        argout_ = argout__tmp
      ENDIF

      IF (PRESENT(comment_)) THEN
        comment__tmp = cxios_is_defined_functiongroup_comment &
      (functiongroup_hdl%daddr)
        comment_ = comment__tmp
      ENDIF

      IF (PRESENT(expr_)) THEN
        expr__tmp = cxios_is_defined_functiongroup_expr &
      (functiongroup_hdl%daddr)
        expr_ = expr__tmp
      ENDIF

      IF (PRESENT(group_ref_)) THEN
        group_ref__tmp = cxios_is_defined_functiongroup_group_ref &
      (functiongroup_hdl%daddr)
        group_ref_ = group_ref__tmp
      ENDIF

      IF (PRESENT(long_name_)) THEN
        long_name__tmp = cxios_is_defined_functiongroup_long_name &
      (functiongroup_hdl%daddr)
        long_name_ = long_name__tmp
      ENDIF

      IF (PRESENT(name_)) THEN
        name__tmp = cxios_is_defined_functiongroup_name &
      (functiongroup_hdl%daddr)
        name_ = name__tmp
      ENDIF

      IF (PRESENT(standard_name_)) THEN
        standard_name__tmp = cxios_is_defined_functiongroup_standard_name &
      (functiongroup_hdl%daddr)
        standard_name_ = standard_name__tmp
      ENDIF

  END SUBROUTINE xios(is_defined_functiongroup_attr_hdl_)

END MODULE ifunctiongroup_attr
