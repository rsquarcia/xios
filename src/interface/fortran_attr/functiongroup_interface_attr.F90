! * ************************************************************************** *
! *               Interface auto generated - do not modify                     *
! * ************************************************************************** *
#include "../fortran/xios_fortran_prefix.hpp"

MODULE functiongroup_interface_attr
  USE, INTRINSIC :: ISO_C_BINDING

  INTERFACE
    ! Do not call directly / interface FORTRAN 2003 <-> C99

    SUBROUTINE cxios_set_functiongroup_argin(functiongroup_hdl, argin, argin_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: functiongroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: argin
      INTEGER  (kind = C_INT)     , VALUE        :: argin_size
    END SUBROUTINE cxios_set_functiongroup_argin

    SUBROUTINE cxios_get_functiongroup_argin(functiongroup_hdl, argin, argin_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: functiongroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: argin
      INTEGER  (kind = C_INT)     , VALUE        :: argin_size
    END SUBROUTINE cxios_get_functiongroup_argin

    FUNCTION cxios_is_defined_functiongroup_argin(functiongroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_functiongroup_argin
      INTEGER (kind = C_INTPTR_T), VALUE :: functiongroup_hdl
    END FUNCTION cxios_is_defined_functiongroup_argin


    SUBROUTINE cxios_set_functiongroup_argout(functiongroup_hdl, argout, argout_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: functiongroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: argout
      INTEGER  (kind = C_INT)     , VALUE        :: argout_size
    END SUBROUTINE cxios_set_functiongroup_argout

    SUBROUTINE cxios_get_functiongroup_argout(functiongroup_hdl, argout, argout_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: functiongroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: argout
      INTEGER  (kind = C_INT)     , VALUE        :: argout_size
    END SUBROUTINE cxios_get_functiongroup_argout

    FUNCTION cxios_is_defined_functiongroup_argout(functiongroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_functiongroup_argout
      INTEGER (kind = C_INTPTR_T), VALUE :: functiongroup_hdl
    END FUNCTION cxios_is_defined_functiongroup_argout


    SUBROUTINE cxios_set_functiongroup_comment(functiongroup_hdl, comment, comment_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: functiongroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: comment
      INTEGER  (kind = C_INT)     , VALUE        :: comment_size
    END SUBROUTINE cxios_set_functiongroup_comment

    SUBROUTINE cxios_get_functiongroup_comment(functiongroup_hdl, comment, comment_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: functiongroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: comment
      INTEGER  (kind = C_INT)     , VALUE        :: comment_size
    END SUBROUTINE cxios_get_functiongroup_comment

    FUNCTION cxios_is_defined_functiongroup_comment(functiongroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_functiongroup_comment
      INTEGER (kind = C_INTPTR_T), VALUE :: functiongroup_hdl
    END FUNCTION cxios_is_defined_functiongroup_comment


    SUBROUTINE cxios_set_functiongroup_expr(functiongroup_hdl, expr, expr_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: functiongroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: expr
      INTEGER  (kind = C_INT)     , VALUE        :: expr_size
    END SUBROUTINE cxios_set_functiongroup_expr

    SUBROUTINE cxios_get_functiongroup_expr(functiongroup_hdl, expr, expr_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: functiongroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: expr
      INTEGER  (kind = C_INT)     , VALUE        :: expr_size
    END SUBROUTINE cxios_get_functiongroup_expr

    FUNCTION cxios_is_defined_functiongroup_expr(functiongroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_functiongroup_expr
      INTEGER (kind = C_INTPTR_T), VALUE :: functiongroup_hdl
    END FUNCTION cxios_is_defined_functiongroup_expr


    SUBROUTINE cxios_set_functiongroup_group_ref(functiongroup_hdl, group_ref, group_ref_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: functiongroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: group_ref
      INTEGER  (kind = C_INT)     , VALUE        :: group_ref_size
    END SUBROUTINE cxios_set_functiongroup_group_ref

    SUBROUTINE cxios_get_functiongroup_group_ref(functiongroup_hdl, group_ref, group_ref_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: functiongroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: group_ref
      INTEGER  (kind = C_INT)     , VALUE        :: group_ref_size
    END SUBROUTINE cxios_get_functiongroup_group_ref

    FUNCTION cxios_is_defined_functiongroup_group_ref(functiongroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_functiongroup_group_ref
      INTEGER (kind = C_INTPTR_T), VALUE :: functiongroup_hdl
    END FUNCTION cxios_is_defined_functiongroup_group_ref


    SUBROUTINE cxios_set_functiongroup_long_name(functiongroup_hdl, long_name, long_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: functiongroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: long_name
      INTEGER  (kind = C_INT)     , VALUE        :: long_name_size
    END SUBROUTINE cxios_set_functiongroup_long_name

    SUBROUTINE cxios_get_functiongroup_long_name(functiongroup_hdl, long_name, long_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: functiongroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: long_name
      INTEGER  (kind = C_INT)     , VALUE        :: long_name_size
    END SUBROUTINE cxios_get_functiongroup_long_name

    FUNCTION cxios_is_defined_functiongroup_long_name(functiongroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_functiongroup_long_name
      INTEGER (kind = C_INTPTR_T), VALUE :: functiongroup_hdl
    END FUNCTION cxios_is_defined_functiongroup_long_name


    SUBROUTINE cxios_set_functiongroup_name(functiongroup_hdl, name, name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: functiongroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: name
      INTEGER  (kind = C_INT)     , VALUE        :: name_size
    END SUBROUTINE cxios_set_functiongroup_name

    SUBROUTINE cxios_get_functiongroup_name(functiongroup_hdl, name, name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: functiongroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: name
      INTEGER  (kind = C_INT)     , VALUE        :: name_size
    END SUBROUTINE cxios_get_functiongroup_name

    FUNCTION cxios_is_defined_functiongroup_name(functiongroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_functiongroup_name
      INTEGER (kind = C_INTPTR_T), VALUE :: functiongroup_hdl
    END FUNCTION cxios_is_defined_functiongroup_name


    SUBROUTINE cxios_set_functiongroup_standard_name(functiongroup_hdl, standard_name, standard_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: functiongroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: standard_name
      INTEGER  (kind = C_INT)     , VALUE        :: standard_name_size
    END SUBROUTINE cxios_set_functiongroup_standard_name

    SUBROUTINE cxios_get_functiongroup_standard_name(functiongroup_hdl, standard_name, standard_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: functiongroup_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: standard_name
      INTEGER  (kind = C_INT)     , VALUE        :: standard_name_size
    END SUBROUTINE cxios_get_functiongroup_standard_name

    FUNCTION cxios_is_defined_functiongroup_standard_name(functiongroup_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_functiongroup_standard_name
      INTEGER (kind = C_INTPTR_T), VALUE :: functiongroup_hdl
    END FUNCTION cxios_is_defined_functiongroup_standard_name

  END INTERFACE

END MODULE functiongroup_interface_attr
