! * ************************************************************************** *
! *               Interface auto generated - do not modify                     *
! * ************************************************************************** *
#include "../fortran/xios_fortran_prefix.hpp"

MODULE function_interface_attr
  USE, INTRINSIC :: ISO_C_BINDING

  INTERFACE
    ! Do not call directly / interface FORTRAN 2003 <-> C99

    SUBROUTINE cxios_set_function_argin(function_hdl, argin, argin_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: function_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: argin
      INTEGER  (kind = C_INT)     , VALUE        :: argin_size
    END SUBROUTINE cxios_set_function_argin

    SUBROUTINE cxios_get_function_argin(function_hdl, argin, argin_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: function_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: argin
      INTEGER  (kind = C_INT)     , VALUE        :: argin_size
    END SUBROUTINE cxios_get_function_argin

    FUNCTION cxios_is_defined_function_argin(function_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_function_argin
      INTEGER (kind = C_INTPTR_T), VALUE :: function_hdl
    END FUNCTION cxios_is_defined_function_argin


    SUBROUTINE cxios_set_function_argout(function_hdl, argout, argout_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: function_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: argout
      INTEGER  (kind = C_INT)     , VALUE        :: argout_size
    END SUBROUTINE cxios_set_function_argout

    SUBROUTINE cxios_get_function_argout(function_hdl, argout, argout_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: function_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: argout
      INTEGER  (kind = C_INT)     , VALUE        :: argout_size
    END SUBROUTINE cxios_get_function_argout

    FUNCTION cxios_is_defined_function_argout(function_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_function_argout
      INTEGER (kind = C_INTPTR_T), VALUE :: function_hdl
    END FUNCTION cxios_is_defined_function_argout


    SUBROUTINE cxios_set_function_comment(function_hdl, comment, comment_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: function_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: comment
      INTEGER  (kind = C_INT)     , VALUE        :: comment_size
    END SUBROUTINE cxios_set_function_comment

    SUBROUTINE cxios_get_function_comment(function_hdl, comment, comment_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: function_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: comment
      INTEGER  (kind = C_INT)     , VALUE        :: comment_size
    END SUBROUTINE cxios_get_function_comment

    FUNCTION cxios_is_defined_function_comment(function_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_function_comment
      INTEGER (kind = C_INTPTR_T), VALUE :: function_hdl
    END FUNCTION cxios_is_defined_function_comment


    SUBROUTINE cxios_set_function_expr(function_hdl, expr, expr_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: function_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: expr
      INTEGER  (kind = C_INT)     , VALUE        :: expr_size
    END SUBROUTINE cxios_set_function_expr

    SUBROUTINE cxios_get_function_expr(function_hdl, expr, expr_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: function_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: expr
      INTEGER  (kind = C_INT)     , VALUE        :: expr_size
    END SUBROUTINE cxios_get_function_expr

    FUNCTION cxios_is_defined_function_expr(function_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_function_expr
      INTEGER (kind = C_INTPTR_T), VALUE :: function_hdl
    END FUNCTION cxios_is_defined_function_expr


    SUBROUTINE cxios_set_function_long_name(function_hdl, long_name, long_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: function_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: long_name
      INTEGER  (kind = C_INT)     , VALUE        :: long_name_size
    END SUBROUTINE cxios_set_function_long_name

    SUBROUTINE cxios_get_function_long_name(function_hdl, long_name, long_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: function_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: long_name
      INTEGER  (kind = C_INT)     , VALUE        :: long_name_size
    END SUBROUTINE cxios_get_function_long_name

    FUNCTION cxios_is_defined_function_long_name(function_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_function_long_name
      INTEGER (kind = C_INTPTR_T), VALUE :: function_hdl
    END FUNCTION cxios_is_defined_function_long_name


    SUBROUTINE cxios_set_function_name(function_hdl, name, name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: function_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: name
      INTEGER  (kind = C_INT)     , VALUE        :: name_size
    END SUBROUTINE cxios_set_function_name

    SUBROUTINE cxios_get_function_name(function_hdl, name, name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: function_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: name
      INTEGER  (kind = C_INT)     , VALUE        :: name_size
    END SUBROUTINE cxios_get_function_name

    FUNCTION cxios_is_defined_function_name(function_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_function_name
      INTEGER (kind = C_INTPTR_T), VALUE :: function_hdl
    END FUNCTION cxios_is_defined_function_name


    SUBROUTINE cxios_set_function_standard_name(function_hdl, standard_name, standard_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: function_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: standard_name
      INTEGER  (kind = C_INT)     , VALUE        :: standard_name_size
    END SUBROUTINE cxios_set_function_standard_name

    SUBROUTINE cxios_get_function_standard_name(function_hdl, standard_name, standard_name_size) BIND(C)
      USE ISO_C_BINDING
      INTEGER (kind = C_INTPTR_T), VALUE :: function_hdl
      CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: standard_name
      INTEGER  (kind = C_INT)     , VALUE        :: standard_name_size
    END SUBROUTINE cxios_get_function_standard_name

    FUNCTION cxios_is_defined_function_standard_name(function_hdl) BIND(C)
      USE ISO_C_BINDING
      LOGICAL(kind=C_BOOL) :: cxios_is_defined_function_standard_name
      INTEGER (kind = C_INTPTR_T), VALUE :: function_hdl
    END FUNCTION cxios_is_defined_function_standard_name

  END INTERFACE

END MODULE function_interface_attr
