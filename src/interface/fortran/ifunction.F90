#include "xios_fortran_prefix.hpp"

MODULE IFUNCTION
   USE, INTRINSIC :: ISO_C_BINDING
   USE FUNCTION_INTERFACE
   USE FUNCTIONGROUP_INTERFACE
!   USE IFUNCTION_ATTR
!   USE IFUNCTIONGROUP_ATTR
   USE IDURATION
   USE LOGICAL_BOOL_CONVERSION
   
   TYPE txios(function)
      INTEGER(kind = C_INTPTR_T) :: daddr
   END TYPE txios(function)
   
   TYPE txios(functiongroup)
      INTEGER(kind = C_INTPTR_T) :: daddr
   END TYPE txios(functiongroup)
   
   CONTAINS ! Fonctions disponibles pour les utilisateurs.

   SUBROUTINE xios(get_function_handle)( idt, ret)
      IMPLICIT NONE
      CHARACTER(len = *),   INTENT(IN) :: idt      
      TYPE(txios(function)) , INTENT(OUT):: ret

      CALL cxios_function_handle_create(ret%daddr, idt, len(idt))            

   END SUBROUTINE xios(get_function_handle)
   
   SUBROUTINE xios(get_functiongroup_handle)(idt,ret)
      IMPLICIT NONE
      CHARACTER(len = *)    ,   INTENT(IN) :: idt      
      TYPE(txios(functiongroup)), INTENT(OUT):: ret

      CALL cxios_functiongroup_handle_create(ret%daddr, idt, len(idt))            

   END SUBROUTINE xios(get_functiongroup_handle)

   LOGICAL FUNCTION xios(is_valid_function)(idt)
      IMPLICIT NONE
      CHARACTER(len  = *)    , INTENT(IN) :: idt
      LOGICAL  (kind = 1)                 :: val

      CALL cxios_function_valid_id(val, idt, len(idt));
      xios(is_valid_function) = bool_to_logical(val)

   END FUNCTION  xios(is_valid_function)

   LOGICAL FUNCTION xios(is_valid_functiongroup)(idt)
      IMPLICIT NONE
      CHARACTER(len  = *)    , INTENT(IN) :: idt
      LOGICAL  (kind = 1)                 :: val

      CALL cxios_functiongroup_valid_id(val, idt, len(idt));
      xios(is_valid_functiongroup) = bool_to_logical(val)

   END FUNCTION  xios(is_valid_functiongroup)

   
END MODULE IFUNCTION
