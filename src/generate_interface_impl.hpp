#ifndef __XIOS_GENERATE_INTERFACE_IMPL_HPP__
#define __XIOS_GENERATE_INTERFACE_IMPL_HPP__

#include "xios_spl.hpp"
#include "generate_interface.hpp"
#include "type_util.hpp"
#include "indent.hpp"
#include "enum.hpp"
#include "array_new.hpp"
#include "date.hpp"

namespace xios
{
  template<> string CInterface::getStrFortranType<int>(void) { return string("INTEGER"); }
  template<> string CInterface::getStrFortranType<bool>(void) { return string("LOGICAL"); }
  template<> string CInterface::getStrFortranType<double>(void) { return string("REAL"); }
  template<> string CInterface::getStrFortranType<float>(void) { return string("REAL"); }
  template<> string CInterface::getStrFortranType<CDate>(void) { return string("TYPE(txios(date))"); }
  template<> string CInterface::getStrFortranType<CDuration>(void) { return string("TYPE(txios(duration))"); }

  template<> string CInterface::getStrFortranKind<int>(void) { return string(""); }
  template<> string CInterface::getStrFortranKind<bool>(void) { return string(""); }
  template<> string CInterface::getStrFortranKind<double>(void) { return string("(KIND=8)"); }
  template<> string CInterface::getStrFortranKind<float>(void) { return string("(KIND=4)"); }
  template<> string CInterface::getStrFortranKind<CDate>(void) { return string(""); }
  template<> string CInterface::getStrFortranKind<CDuration>(void) { return string(""); }

  template<> string CInterface::getStrFortranKindC<int>(void) { return string("(KIND=C_INT)"); }
  template<> string CInterface::getStrFortranKindC<bool>(void) { return string("(KIND=C_BOOL)"); }
  template<> string CInterface::getStrFortranKindC<double>(void) { return string("(KIND=C_DOUBLE)"); }
  template<> string CInterface::getStrFortranKindC<float>(void) { return string("(KIND=C_FLOAT)"); }
  template<> string CInterface::getStrFortranKindC<CDate>(void) { return string(""); }
  template<> string CInterface::getStrFortranKindC<CDuration>(void) { return string(""); }

  template<> bool CInterface::matchingTypeCFortran<int>(void) { return true; }
  template<> bool CInterface::matchingTypeCFortran<bool>(void) { return false; }
  template<> bool CInterface::matchingTypeCFortran<double>(void) { return true; }
  template<> bool CInterface::matchingTypeCFortran<float>(void) { return true; }
  template<> bool CInterface::matchingTypeCFortran<CDate>(void) { return true; }
  template<> bool CInterface::matchingTypeCFortran<CDuration>(void) { return true; }

  // // For the python interface //
  template<> string CInterface::getStrPythonType<int>(void) { return string("Int"); }
  template<> string CInterface::getStrPythonType<bool>(void) { return string("Bool"); }
  template<> string CInterface::getStrPythonType<double>(void) { return string("Double"); }
  template<> string CInterface::getStrPythonType<float>(void) { return string("Double"); }
  template<> string CInterface::getStrPythonType<CDate>(void) { return string("Date"); }
  template<> string CInterface::getStrPythonType<CDuration>(void) { return string("Duration"); }
  template<> string CInterface::getStrPythonType<string>(void) { return string("String"); }
  
  template<> string CInterface::getStrPythonCType<int>(void) { return string("ctypes.c_int"); }
  template<> string CInterface::getStrPythonCType<bool>(void) { return string("ctypes.c_bool"); }
  template<> string CInterface::getStrPythonCType<double>(void) { return string("ctypes.c_double"); }
  template<> string CInterface::getStrPythonCType<float>(void) { return string("ctypes.c_double"); }
  template<> string CInterface::getStrPythonCType<string>(void) { return string("ctypes.c_char_p"); }
  template<> string CInterface::getStrPythonCType<CDate>(void) { return string("Date"); }
  template<> string CInterface::getStrPythonCType<CDuration>(void) { return string("Duration"); }
  
  template<> string CInterface::getStrPythonNativeType<int>(void) { return string("int"); }
  template<> string CInterface::getStrPythonNativeType<bool>(void) { return string("bool"); }
  template<> string CInterface::getStrPythonNativeType<double>(void) { return string("float"); }
  template<> string CInterface::getStrPythonNativeType<float>(void) { return string("float"); }
  template<> string CInterface::getStrPythonNativeType<string>(void) { return string("str"); }
  template<> string CInterface::getStrPythonNativeType<CDate>(void) { return string("Date"); }
  template<> string CInterface::getStrPythonNativeType<CDuration>(void) { return string("Duration"); }
  // For the python interface //



// /////////////////////////////////////////////////
// //                 C Interface                 //
// /////////////////////////////////////////////////

  void CInterface::AttributeIsDefinedCInterface(ostream& oss, const string& className, const string& name)
  {
    oss << "bool cxios_is_defined_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl)" << iendl;
    oss << "{" << iendl;
    oss << "   CTimer::get(\"XIOS\").resume();" << iendl;
    oss << "   bool isDefined = " << className << "_hdl->" << name << ".hasInheritedValue();" << iendl;
    oss << "   CTimer::get(\"XIOS\").suspend();" << iendl;
    oss << "   return isDefined;" << iendl;
    oss << "}" << std::endl;
  }

  template <class T>
  void CInterface::AttributeCInterface(ostream& oss, const string& className, const string& name)
  {
    string typeName = getStrType<T>();

    oss << "void cxios_set_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, " << typeName << " " << name << ")" << iendl;
    oss << "{" << iendl;
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl;
    oss << "  " << className << "_hdl->" << name << ".setValue(" << name << ");" << iendl;
    oss << "  CTimer::get(\"XIOS\").suspend();" << iendl;
    oss << "}" << std::endl;

    oss << iendl;
    oss << "void cxios_get_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, " << typeName << "* " << name << ")" << iendl;
    oss << "{" << iendl;
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl;
    oss << "  *" << name << " = " << className << "_hdl->" << name << ".getInheritedValue();" << iendl;
    oss << "  CTimer::get(\"XIOS\").suspend();" << iendl;
    oss << "}" << std::endl;
  }

  template<>
  void CInterface::AttributeCInterface<string>(ostream& oss, const string& className, const string& name)
  {
    oss << "void cxios_set_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, const char * " << name << ", int " << name << "_size)" << iendl;
    oss << "{" << iendl;
    oss << "  std::string " << name << "_str;" << iendl;
    oss << "  if (!cstr2string(" << name << ", " << name << "_size, " << name << "_str)) return;" << iendl;
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl;
    oss << "  " << className << "_hdl->" << name << ".setValue(" << name << "_str);" << iendl;
    oss << "  CTimer::get(\"XIOS\").suspend();" << iendl;
    oss << "}" << std::endl;

    oss << iendl;

    oss << "void cxios_get_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, char * " << name << ", int " << name << "_size)" << iendl;
    oss << "{" << iendl;
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl;
    oss << "  if (!string_copy(" << className << "_hdl->" << name << ".getInheritedValue(), " << name << ", " << name << "_size))" << iendl;
    oss << "    ERROR(\"void cxios_get_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, char * " << name << ", int "
        << name << "_size)\", << \"Input string is too short\");" << iendl;
    oss << "  CTimer::get(\"XIOS\").suspend();" << iendl;
    oss << "}" << std::endl;
  }

  template<>
  void CInterface::AttributeCInterface<CEnumBase>(ostream& oss, const string& className, const string& name)
  {
    oss << "void cxios_set_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, const char * " << name << ", int " << name << "_size)" << iendl;
    oss << "{" << iendl;
    oss << "  std::string " << name << "_str;" << iendl;
    oss << "  if (!cstr2string(" << name << ", " << name << "_size, " << name << "_str)) return;" << iendl;
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl;
    oss << "  " << className << "_hdl->" << name << ".fromString(" << name << "_str);" << iendl;
    oss << "  CTimer::get(\"XIOS\").suspend();" << iendl;
    oss << "}" << std::endl;

    oss << iendl;

    oss << "void cxios_get_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, char * " << name << ", int " << name << "_size)" << iendl;
    oss << "{" << iendl;
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl;
    oss << "  if (!string_copy(" << className << "_hdl->" << name << ".getInheritedStringValue(), " << name << ", " << name << "_size))" << iendl;
    oss << "    ERROR(\"void cxios_get_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, char * " << name << ", int "
        << name << "_size)\", << \"Input string is too short\");" << iendl;
    oss << "  CTimer::get(\"XIOS\").suspend();" << iendl;
    oss << "}" << std::endl;
  }

  template<>
  void CInterface::AttributeCInterface<CDate>(ostream& oss, const string& className, const string& name)
  {
    oss << "void cxios_set_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, cxios_date " << name << "_c)" << iendl;
    oss << "{" << iendl;
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl;
    oss << "  " << className << "_hdl->" << name << ".allocate();" << iendl;
    oss << "  CDate& " << name << " = " << className << "_hdl->" << name << ".get();" << iendl;
    oss << "  " << name << ".setDate(" << name << "_c.year," << iendl;
    oss << "                         " << name << "_c.month," << iendl;
    oss << "                         " << name << "_c.day," << iendl;
    oss << "                         " << name << "_c.hour," << iendl;
    oss << "                         " << name << "_c.minute," << iendl;
    oss << "                         " << name << "_c.second);" << iendl;
    oss << "  if (" << name << ".hasRelCalendar())" << iendl;
    oss << "    " << name << ".checkDate();" << iendl;
    oss << "  CTimer::get(\"XIOS\").suspend();" << iendl;
    oss << "}" << std::endl;

    oss << iendl;

    oss << "void cxios_get_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, cxios_date* " << name << "_c)" << iendl;
    oss << "{" << iendl;
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl;
    oss << "  CDate " << name << " = " << className << "_hdl->" << name << ".getInheritedValue();" << iendl;
    oss << "  " << name << "_c->year = " << name << ".getYear();" << iendl;
    oss << "  " << name << "_c->month = " << name << ".getMonth();" << iendl;
    oss << "  " << name << "_c->day = " << name << ".getDay();" << iendl;
    oss << "  " << name << "_c->hour = " << name << ".getHour();" << iendl;
    oss << "  " << name << "_c->minute = " << name << ".getMinute();" << iendl;
    oss << "  " << name << "_c->second = " << name << ".getSecond();" << iendl;
    oss << "  CTimer::get(\"XIOS\").suspend();" << iendl;
    oss << "}" << std::endl;
  }

  template<>
  void CInterface::AttributeCInterface<CDuration>(ostream& oss, const string& className, const string& name)
  {
    oss << "void cxios_set_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, cxios_duration " << name << "_c)" << iendl;
    oss << "{" << iendl;
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl;
    oss << "  " << className << "_hdl->" << name << ".allocate();" << iendl;
    oss << "  CDuration& " << name << " = " << className << "_hdl->" << name << ".get();" << iendl;
    oss << "  " << name << ".year = " << name << "_c.year;" << iendl;
    oss << "  " << name << ".month = " << name << "_c.month;" << iendl;
    oss << "  " << name << ".day = " << name << "_c.day;" << iendl;
    oss << "  " << name << ".hour = " << name << "_c.hour;" << iendl;
    oss << "  " << name << ".minute = " << name << "_c.minute;" << iendl;
    oss << "  " << name << ".second = " << name << "_c.second;" << iendl;
    oss << "  " << name << ".timestep = " << name << "_c.timestep;" << iendl;
    oss << "  CTimer::get(\"XIOS\").suspend();" << iendl;
    oss << "}" << std::endl;

    oss << iendl;

    oss << "void cxios_get_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, cxios_duration* " << name << "_c)" << iendl;
    oss << "{" << iendl;
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl;
    oss << "  CDuration " << name << " = " << className << "_hdl->" << name << ".getInheritedValue();" << iendl;
    oss << "  " << name << "_c->year = " << name << ".year;" << iendl;
    oss << "  " << name << "_c->month = " << name << ".month;" << iendl;
    oss << "  " << name << "_c->day = " << name << ".day;" << iendl;
    oss << "  " << name << "_c->hour = " << name << ".hour;" << iendl;
    oss << "  " << name << "_c->minute = " << name << ".minute;" << iendl;
    oss << "  " << name << "_c->second = " << name << ".second;" << iendl;
    oss << "  " << name << "_c->timestep = " << name << ".timestep;" << iendl;
    oss << "  CTimer::get(\"XIOS\").suspend();" << iendl;
    oss << "}" << std::endl;
  }

#undef macro

// /////////////////////////////////////////////////
// //          Fortran 2003 Interface             //
// /////////////////////////////////////////////////

  void CInterface::AttributeIsDefinedFortran2003Interface(ostream& oss, const string& className, const string& name)
  {
    oss << "FUNCTION cxios_is_defined_" << className << "_" << name << "(" << className << "_hdl) BIND(C)" << iendl;
    oss << "  USE ISO_C_BINDING" << iendl;
    oss << "  LOGICAL(kind=C_BOOL) :: cxios_is_defined_" << className << "_" << name << iendl;
    oss << "  INTEGER (kind = C_INTPTR_T), VALUE :: " << className << "_hdl" << iendl;
    oss << "END FUNCTION cxios_is_defined_" << className << "_" << name << std::endl;
  }

  template <class T>
  void CInterface::AttributeFortran2003Interface(ostream& oss, const string& className, const string& name)
  {
    string fortranType=getStrFortranType<T>();
    string fortranKindC=getStrFortranKindC<T>();

//    oss << "SUBROUTINE cxios_set_" << className << "_" << name << "(" << className << "_hdl, " << name << ") BIND(C)" << iendl;
    int indent = oss.iword(iendl.index);
    string str = "SUBROUTINE cxios_set_" + className + "_" + name + "(" + className + "_hdl, " + name + ") BIND(C)";
    if ((str.length() + indent) >132)
    {
      oss << str.substr(0,130-indent) ;
      oss << "&" << endl;
      oss << "&" << str.substr(130-indent,str.length()) ;
    }
    else
    {
      oss << str;
    }
    oss << iendl;
    oss << "  USE ISO_C_BINDING" << iendl;
    oss << "  INTEGER (kind = C_INTPTR_T), VALUE :: " << className << "_hdl" << iendl;
    oss << "  " << fortranType << " " << fortranKindC << "      , VALUE :: " << name << iendl;
    oss << "END SUBROUTINE cxios_set_" << className << "_" << name << std::endl;
    oss << iendl;
    oss << "SUBROUTINE cxios_get_" << className << "_" << name << "(" << className << "_hdl, " << name << ") BIND(C)" << iendl;
    oss << "  USE ISO_C_BINDING" << iendl;
    oss << "  INTEGER (kind = C_INTPTR_T), VALUE :: " << className << "_hdl" << iendl;
    oss << "  " << fortranType << " " << fortranKindC << "             :: " << name << iendl;
    oss << "END SUBROUTINE cxios_get_" << className << "_" << name << std::endl;
  }

  template <>
  void CInterface::AttributeFortran2003Interface<string>(ostream& oss, const string& className, const string& name)
  {
//    oss << "SUBROUTINE cxios_set_" << className << "_" << name << "(" << className << "_hdl, " << name << ", " << name << "_size) BIND(C)" << iendl;
    int indent = oss.iword(iendl.index);
    string str ="SUBROUTINE cxios_set_" + className + "_" + name + "(" + className + "_hdl, " + name + ", " + name + "_size) BIND(C)";
    if ((str.length() + indent) >132)
    {
      oss << str.substr(0,130-indent) ;
      oss << "&" << endl;
      oss << "&" << str.substr(130-indent,str.length()) ;
    }
    else
    {
      oss << str;
    }
    oss << iendl;
    oss << "  USE ISO_C_BINDING" << iendl;
    oss << "  INTEGER (kind = C_INTPTR_T), VALUE :: " << className << "_hdl" << iendl;
    oss << "  CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: " << name << iendl;
    oss << "  INTEGER  (kind = C_INT)     , VALUE        :: " << name << "_size" << iendl;
    oss << "END SUBROUTINE cxios_set_" << className << "_" << name << std::endl;
    oss << iendl;
//    oss << "SUBROUTINE cxios_get_" << className << "_" << name << "(" << className << "_hdl, " << name << ", " << name << "_size) BIND(C)" << iendl;
    str = "SUBROUTINE cxios_get_" + className + "_" + name + "(" + className + "_hdl, " + name + ", " + name + "_size) BIND(C)";
    if ((str.length() + indent) >132)
    {
      oss << str.substr(0,130-indent) ;
      oss << "&" << endl;
      oss << "&" << str.substr(130-indent,str.length()) ;
    }
    else
    {
      oss << str;
    }
    oss << iendl;
    oss << "  USE ISO_C_BINDING" << iendl;
    oss << "  INTEGER (kind = C_INTPTR_T), VALUE :: " << className << "_hdl" << iendl;
    oss << "  CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: " << name << iendl;
    oss << "  INTEGER  (kind = C_INT)     , VALUE        :: " << name << "_size" << iendl;
    oss << "END SUBROUTINE cxios_get_" << className << "_" << name << std::endl;
  }

  template <>
  void CInterface::AttributeFortran2003Interface<CDuration>(ostream& oss, const string& className, const string& name)
  {
//    oss << "SUBROUTINE cxios_set_" << className << "_" << name << "(" << className << "_hdl, " << name << ") BIND(C)" << iendl;
    string str = "SUBROUTINE cxios_set_" + className + "_" + name + "(" + className + "_hdl, " + name + ") BIND(C)";
    int indent = oss.iword(iendl.index);
    if ((str.length() + indent) >132)
    {
      oss << str.substr(0,130-indent) ;
      oss << "&" << endl;
      oss << "&" << str.substr(130-indent,str.length()) ;
    }
    else
    {
      oss << str;
    }
    oss << iendl;
    oss << "  USE ISO_C_BINDING" << iendl;
    oss << "  USE IDURATION" << iendl;
    oss << "  INTEGER (kind = C_INTPTR_T), VALUE :: " << className << "_hdl" << iendl;
    oss << "  TYPE(txios(duration)), VALUE :: " << name << iendl;
    oss << "END SUBROUTINE cxios_set_" << className << "_" << name << std::endl;
    oss << iendl;
    oss << "SUBROUTINE cxios_get_" << className << "_" << name << "(" << className << "_hdl, " << name << ") BIND(C)" << iendl;
    oss << "  USE ISO_C_BINDING" << iendl;
    oss << "  USE IDURATION" << iendl;
    oss << "  INTEGER (kind = C_INTPTR_T), VALUE :: " << className << "_hdl" << iendl;
    oss << "  TYPE(txios(duration)) :: " << name << iendl;
    oss << "END SUBROUTINE cxios_get_" << className << "_" << name << std::endl;
  }

  template <class T>
  void CInterface::AttributeFortranInterfaceDeclaration(ostream& oss, const string& className, const string& name)
  {
    oss << getStrFortranType<T>() << " " << getStrFortranKind<T>() << " , OPTIONAL, INTENT(IN) :: " << name;
    if (!matchingTypeCFortran<T>()) oss << iendl << getStrFortranType<T>() << " " << getStrFortranKindC<T>() << " :: " << name << "_tmp";
  }


  template <class T>
  void CInterface::AttributePythonInterfaceCArgs(ostream& oss, const string& className, const string& name, const string& funcName, const string& pyName)
  {
    if (funcName == "set"){
      oss << "lib.cxios_" << funcName << "_" << className << "_" << name  << ".argtypes = [" << pyName << ", " << getStrPythonCType<T>() << "]" << iendl;     
    }else if (funcName == "get"){
      oss << "lib.cxios_" << funcName << "_" << className << "_" << name  << ".argtypes = [" << pyName << ", ctypes.POINTER(" << getStrPythonCType<T>() << ")]" << iendl;     
    }else{
      oss << "lib.cxios_" << funcName << "_" << className << "_" << name  << ".argtypes = [" << pyName << "]" << iendl;     
    }
  }
  
  template <class T>
  void CInterface::AttributePythonInterfaceCRes(ostream& oss, const string& className, const string& name, const string& funcName)
  {
    if (funcName == "is_defined"){
      oss << "lib.cxios_" << funcName << "_" << className << "_" << name  << ".restypes = ctypes.c_bool" << iendl;     
    }else{
      oss << "lib.cxios_" << funcName << "_" << className << "_" << name  << ".restypes = None" << iendl;     
    }
  }
  
  template <class T>
  void CInterface::AttributeObjPythonInterfaceBody(ostream& oss, const string& className, const string& name)
  {
    oss << "'" << name  << "': {'type': " << getStrPythonType<T>() << "}," << iendl;     
    
  }

  template <class T>
  void CInterface::AttributePythonInterfaceDeclaration(ostream& oss, const string& className, const string& name, bool isSet)
  {
    if (isSet){
      oss << " : Optional[Union[" << getStrPythonType<T>() << ", " << getStrPythonNativeType<T>() << "]] = None";
    }else{
      oss << " : Optional[" << getStrPythonType<T>() << "] = None";
    }
  }
  
  template <class T>
  void CInterface::AttributePythonInterfaceIsDefinedDeclaration(ostream& oss, const string& className, const string& name)
  {
    oss << " : Optional[Bool] = None";
  }

  template <class T>
  void CInterface::AttributeFortranInterfaceGetDeclaration(ostream& oss, const string& className, const string& name)
  {
    oss << getStrFortranType<T>() << " " << getStrFortranKind<T>() << " , OPTIONAL, INTENT(OUT) :: " << name;
    if (!matchingTypeCFortran<T>()) oss << iendl << getStrFortranType<T>() << " " << getStrFortranKindC<T>() << " :: " << name << "_tmp";
  }

  void CInterface::AttributeFortranInterfaceIsDefinedDeclaration(ostream& oss, const string& className, const string& name)
  {
    oss << "LOGICAL, OPTIONAL, INTENT(OUT) :: " << name << iendl;
    oss << "LOGICAL(KIND=C_BOOL) :: " << name << "_tmp";
  }

  template <>
  void CInterface::AttributeFortranInterfaceDeclaration<string>(ostream& oss, const string& className, const string& name)
  {
    oss << "CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: " << name;
  }


  template <>
  void CInterface::AttributePythonInterfaceCArgs<string>(ostream& oss, const string& className, const string& name, const string& funcName, const string& pyName)
  {
    if (funcName == "is_defined"){
      oss << "lib.cxios_" << funcName << "_" << className << "_" << name  << ".argtypes = [" << pyName << "]" << iendl;     
    }else{
       oss << "lib.cxios_" << funcName << "_" << className << "_" << name  << ".argtypes = [" << pyName << ", " << getStrPythonCType<string>() << ", ctypes.c_int]" << iendl;     
    }
  }
  
  template <>
  void CInterface::AttributePythonInterfaceCRes<string>(ostream& oss, const string& className, const string& name, const string& funcName)
  {
    if (funcName == "is_defined"){
      oss << "lib.cxios_" << funcName << "_" << className << "_" << name  << ".restypes = ctypes.c_bool" << iendl;     
    }else{
      oss << "lib.cxios_" << funcName << "_" << className << "_" << name  << ".restypes = None" << iendl;     
    }
  }

  template <>
  void CInterface::AttributeObjPythonInterfaceBody<string>(ostream& oss, const string& className, const string& name)
  {
    oss << "'" << name  << "': {'type': String}," << iendl;     
    
  }

  template <>
  void CInterface::AttributePythonInterfaceIsDefinedDeclaration<string>(ostream& oss, const string& className, const string& name)
  {
    oss << " : Optional[Bool] = None";
  }
  
  template <>
  void CInterface::AttributePythonInterfaceDeclaration<string>(ostream& oss, const string& className, const string& name, bool isSet)
  {
    if (isSet){
      oss << " : Optional[Union[str, String]] = None";
    }else{
      oss << " : Optional[String] = None";
    }
  }

  template <>
  void CInterface::AttributeFortranInterfaceGetDeclaration<string>(ostream& oss, const string& className, const string& name)
  {
    oss << "CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: " << name;
  }

  template <class T>
  void CInterface::AttributeFortranInterfaceBody(ostream& oss, const string& className, const string& name)
  {
    string name_tmp=name+"__tmp";

    oss << "IF (PRESENT(" << name << "_)) THEN" << iendl;
    if (!matchingTypeCFortran<T>())
    {
      oss << "  " << name_tmp << " = " << name << "_" << iendl;
      oss << "  CALL xios_logical_to_bool_0d(" << name_tmp << ")" << iendl; \
      oss << "  CALL cxios_set_" << className << "_" << name << " &" << iendl;
      oss << "(" << className << "_hdl%daddr, " << name_tmp << ")" << iendl;
    }
    else { oss << "  CALL cxios_set_" << className << "_" << name << " &" << iendl;
           oss << "(" << className << "_hdl%daddr, " << name << "_)" << iendl; }
    oss << "ENDIF";
  }

  template <class T>
  void CInterface::AttributePythonInterfaceBody(ostream& oss, const string& className, const string& name ,const string& pyName)
  {

    oss << "if " << name << "_ is not None: " << iendl << (iendl += 1);
    string t = getStrPythonType<T>();
    if (t == "Duration" || t == "Date"){
      oss << name << "_c = " << name << "_" << iendl;
    }else{
      oss << name << "_ = " << t << "(" << name << "_)" << iendl;
      oss << name << "_c = " << name << "_._c_value" << iendl;
    }
    oss << "lib.cxios_set_" << className << "_" << name;
    oss << "(" << className << "_hdl, " << name << "_c)" << iendl << (iendl -= 1); 
  }
  
  template <class T>
  void CInterface::AttributePythonInterfaceGetBody(ostream& oss, const string& className, const string& name)
  {

    // oss << "#there we are 0_0" << iendl;
    oss << "if " << name << "_ is not None: " << iendl << (iendl += 1);
    if (getStrPythonType<T>() == "Duration" || getStrPythonType<T>() == "Date"){
      oss << name << "_c = ctypes.pointer(" << name << "_)" << iendl;
      oss << "# DATE ?" << iendl;
    }else{
      oss << name << "_c = " << name << "_._c_value" << iendl;
    }
    oss << "lib.cxios_get_" << className << "_" << name;
    oss << "(" << className << "_hdl, " << name << "_c)" << iendl << (iendl -= 1); 
  }

  template <class T>
  void CInterface::AttributeFortranInterfaceGetBody(ostream& oss, const string& className, const string& name)
  {
    string name_tmp=name+"__tmp";

    oss << "IF (PRESENT(" << name << "_)) THEN" << iendl;
    if (!matchingTypeCFortran<T>())
    {
      oss << "  CALL cxios_get_" << className << "_" << name << " &" << iendl;
      oss << "(" << className << "_hdl%daddr, " << name_tmp << ")" << iendl;
      oss << "  CALL xios_bool_to_logical_0d(" << name_tmp << ")" << iendl; \
      oss << "  " << name << "_ = " << name_tmp << iendl;
    }
    else { oss << "  CALL cxios_get_" << className << "_" << name << " &" << iendl;
           oss << "(" << className << "_hdl%daddr, " << name << "_)" << iendl; }
    oss << "ENDIF";
  }

  void CInterface::AttributeFortranInterfaceIsDefinedBody(ostream& oss, const string& className, const string& name)
  {
    string name_tmp=name+"__tmp";

    oss << "IF (PRESENT(" << name << "_)) THEN" << iendl;
    oss << "  " << name << "__tmp = cxios_is_defined_" << className << "_" << name << " &" << iendl;
    oss << "(" << className << "_hdl%daddr)" << iendl;
    oss << "  " << name << "_ = " << name_tmp << iendl;
    oss << "ENDIF";
  }

  void CInterface::AttributePythonInterfaceIsDefinedBody(ostream& oss, const string& className, const string& name)
  {
    oss << "if " << name << "_  is not None:" << (iendl+=1); 
    oss << name << "_c = lib.cxios_is_defined_" << className << "_" << name << "(" << className << "_hdl)" << iendl; 
    oss << name << "_._c_value = ctypes.c_bool(" << name << "_c)" << iendl;
    oss << (iendl -= 1); 
  }
  

  template <>
  void CInterface::AttributeFortranInterfaceBody<string>(ostream& oss, const string& className, const string& name)
  {
    oss << "IF (PRESENT(" << name << "_)) THEN" << iendl;
    oss << "  CALL cxios_set_" << className << "_" << name << " &" << iendl;
    oss << "(" << className << "_hdl%daddr, " << name << "_, len(" << name << "_))" << iendl;
    oss << "ENDIF";
  }
  
  template <>
  void CInterface::AttributePythonInterfaceBody<string>(ostream& oss, const string& className, const string& name ,const string& pyName)
  {
    oss << "if " << name << "_ is not None:" << iendl << (iendl+=1);
    oss << name << "_= String(" << name << "_)" << iendl;
    oss << name << "_c = " << name << "_._c_value" << iendl;
    oss << "len_" << name << "_c = len(ctypes.string_at(" << name << "_c))" << iendl;
    oss << "lib.cxios_set_" << className << "_" << name;
    oss << "(" << className << "_hdl, " << name << "_c, len_" << name << "_c)" << iendl << (iendl -= 1); 
  }
  
  template <>
  void CInterface::AttributePythonInterfaceGetBody<string>(ostream& oss, const string& className, const string& name)
  {
    oss << "if " << name << "_ is not None:" << iendl << (iendl+=1);
    oss << name << "_c = " << name << "_._c_value" << iendl;
    oss << "len_" << name << "_c = len(ctypes.string_at(" << name << "_c))" << iendl;
    oss << "lib.cxios_get_" << className << "_" << name;
    oss << "(" << className << "_hdl, " << name << "_c, len_" << name << "_c)" << iendl << (iendl -= 1); 
  }


  template <>
  void CInterface::AttributeFortranInterfaceGetBody<string>(ostream& oss, const string& className, const string& name)
  {
    oss << "IF (PRESENT(" << name << "_)) THEN" << iendl;
    oss << "  CALL cxios_get_" << className << "_" << name << " &" << iendl;
    oss << "(" << className << "_hdl%daddr, " << name << "_, len(" << name << "_))" << iendl;
    oss << "ENDIF";
  }

// declaration for CArray

#define macro(T) \
  template <> \
  void CInterface::AttributeCInterface<CArray<T,1> >(ostream& oss, const string& className, const string& name) \
  { \
    string typeName=getStrType<T>(); \
\
    oss << "void cxios_set_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, " << typeName << "* " << name << ", int* extent)" << iendl; \
    oss << "{" << iendl; \
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl; \
    oss << "  CArray<" << typeName << ",1> tmp(" << name << ", shape(extent[0]), neverDeleteData);" << iendl; \
    oss << "  " << className << "_hdl->" << name << ".reference(tmp.copy());" << iendl; \
    /*oss << "  " << className << "_hdl->sendAttributToServer(" << className << "_hdl->" << name << ");" << iendl;*/ \
    oss << "   CTimer::get(\"XIOS\").suspend();" << iendl; \
    oss << "}" << std::endl; \
    oss << iendl; \
    oss << "void cxios_get_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, " << typeName << "* " << name << ", int* extent)" << iendl; \
    oss << "{" << iendl; \
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl; \
    oss << "  CArray<" << typeName << ",1> tmp(" << name << ", shape(extent[0]), neverDeleteData);" << iendl; \
    oss << "  tmp=" << className << "_hdl->" << name << ".getInheritedValue();" << iendl; \
    oss << "   CTimer::get(\"XIOS\").suspend();" << iendl; \
    oss << "}" << std::endl; \
    oss << iendl; \
    oss << "void cxios_" << className << "_" << name << "_shape(" << className << "_Ptr " << className << "_hdl, " << "int* shape)" << iendl; \
    oss << "{" << (iendl+=1); \
    oss << "const CArray<" << typeName << ", 1> data = " << className  << "_hdl->" << name << ".getInheritedValue();" << iendl; \
    oss << "shape[0] = data.extent(0);" << iendl; \
		oss << (iendl-=1); \
    oss << "}" << std::endl; \
  } \
\
  template <> \
  void CInterface::AttributeCInterface<CArray<T,2> >(ostream& oss, const string& className, const string& name) \
  { \
    string typeName=getStrType<T>(); \
\
    oss << "void cxios_set_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, " << typeName << "* " << name << ", int* extent)" << iendl; \
    oss << "{" << iendl; \
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl; \
    oss << "  CArray<" << typeName << ",2> tmp(" << name << ", shape(extent[0], extent[1]), neverDeleteData);" << iendl; \
    oss << "  " << className << "_hdl->" << name << ".reference(tmp.copy());" << iendl; \
    /*oss << "  " << className << "_hdl->sendAttributToServer(" << className << "_hdl->" << name << ");" << iendl;*/ \
    oss << "   CTimer::get(\"XIOS\").suspend();" << iendl; \
    oss << "}" << std::endl; \
    oss << iendl; \
    oss << "void cxios_get_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, " << typeName << "* " << name << ", int* extent)" << iendl; \
    oss << "{" << iendl; \
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl; \
    oss << "  CArray<" << typeName << ",2> tmp(" << name << ", shape(extent[0], extent[1]), neverDeleteData);" << iendl; \
    oss << "  tmp=" << className << "_hdl->" << name << ".getInheritedValue();" << iendl; \
    oss << "   CTimer::get(\"XIOS\").suspend();" << iendl; \
    oss << "}" << std::endl; \
    oss << iendl; \
    oss <<  "void cxios_" << className << "_" << name << "_shape(" << className << "_Ptr " << className << "_hdl, " << "int* shape)" << iendl; \
    oss << "{" << (iendl+=1); \
    oss << "const CArray<" << typeName << ", 2> data = " << className  << "_hdl->" << name << ".getInheritedValue();" << iendl; \
    oss << "shape[0] = data.extent(0);" << iendl; \
    oss << "shape[1] = data.extent(1);" << iendl; \
		oss  << (iendl-=1); \
    oss << "}" << std::endl; \
  } \
\
  template <> \
  void CInterface::AttributeCInterface<CArray<T,3> >(ostream& oss, const string& className, const string& name) \
  { \
    string typeName=getStrType<T>(); \
\
    oss << "void cxios_set_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, " << typeName << "* " << name << ", int* extent)" << iendl; \
    oss << "{" << iendl; \
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl; \
    oss << "  CArray<" << typeName << ",3> tmp(" << name << ", shape(extent[0], extent[1], extent[2]), neverDeleteData);" << iendl; \
    oss << "  " << className << "_hdl->" << name << ".reference(tmp.copy());" << iendl; \
    /*oss << "  " << className << "_hdl->sendAttributToServer(" << className << "_hdl->" << name << ");" << iendl;*/ \
    oss << "   CTimer::get(\"XIOS\").suspend();" << iendl; \
    oss << "}" << std::endl; \
    oss << iendl; \
    oss << "void cxios_get_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, " << typeName << "* " << name << ", int* extent)" << iendl; \
    oss << "{" << iendl; \
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl; \
    oss << "  CArray<" << typeName << ",3> tmp(" << name << ", shape(extent[0], extent[1], extent[2]), neverDeleteData);" << iendl; \
    oss << "  tmp=" << className << "_hdl->" << name << ".getInheritedValue();" << iendl; \
    oss << "   CTimer::get(\"XIOS\").suspend();" << iendl; \
    oss << "}" << std::endl; \
    oss << iendl; \
    oss <<  "void cxios_" << className << "_" << name << "_shape(" << className << "_Ptr " << className << "_hdl, " << "int* shape)" << iendl; \
    oss << "{" << (iendl+=1); \
    oss << "const CArray<" << typeName << ", 3> data = " << className  << "_hdl->" << name << ".getInheritedValue();" << iendl; \
    oss << "shape[0] = data.extent(0);" << iendl; \
    oss << "shape[1] = data.extent(1);" << iendl; \
    oss << "shape[2] = data.extent(2);" << iendl; \
		oss << (iendl-=1); \
    oss << "}" << std::endl; \
  } \
\
  template <> \
  void CInterface::AttributeCInterface<CArray<T,4> >(ostream& oss, const string& className, const string& name) \
  { \
    string typeName=getStrType<T>(); \
\
    oss << "void cxios_set_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, " << typeName << "* " << name << ", int* extent)" << iendl; \
    oss << "{" << iendl; \
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl; \
    oss << "  CArray<" << typeName << ",4> tmp(" << name << ", shape(extent[0], extent[1], extent[2], extent[3]), neverDeleteData);" << iendl; \
    oss << "  " << className << "_hdl->" << name << ".reference(tmp.copy());" << iendl; \
    /*oss << "  " << className << "_hdl->sendAttributToServer(" << className << "_hdl->" << name << ");" << iendl;*/ \
    oss << "   CTimer::get(\"XIOS\").suspend();" << iendl; \
    oss << "}" << std::endl; \
    oss << iendl; \
    oss << "void cxios_get_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, " << typeName << "* " << name << ", int* extent)" << iendl; \
    oss << "{" << iendl; \
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl; \
    oss << "  CArray<" << typeName << ",4> tmp(" << name << ", shape(extent[0], extent[1], extent[2], extent[3]), neverDeleteData);" << iendl; \
    oss << "  tmp=" << className << "_hdl->" << name << ".getInheritedValue();" << iendl; \
    oss << "   CTimer::get(\"XIOS\").suspend();" << iendl; \
    oss << "}" << std::endl; \
    oss << iendl; \
    oss <<  "void cxios_" << className << "_" << name << "_shape(" << className << "_Ptr " << className << "_hdl, " << "int* shape)" << iendl; \
    oss << "{" << (iendl+=1); \
    oss << "const CArray<" << typeName << ", 4> data = " << className  << "_hdl->" << name << ".getInheritedValue();" << iendl; \
    oss << "shape[0] = data.extent(0);" << iendl; \
    oss << "shape[1] = data.extent(1);" << iendl; \
    oss << "shape[2] = data.extent(2);" << iendl; \
    oss << "shape[3] = data.extent(3);" << iendl; \
		oss << (iendl-=1); \
    oss << "}" << std::endl; \
  } \
\
  template <> \
  void CInterface::AttributeCInterface<CArray<T,5> >(ostream& oss, const string& className, const string& name) \
  { \
    string typeName=getStrType<T>(); \
\
    oss << "void cxios_set_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, " << typeName << "* " << name << ", int* extent)" << iendl; \
    oss << "{" << iendl; \
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl; \
    oss << "  CArray<" << typeName << ",5> tmp(" << name << ", shape(extent[0], extent[1], extent[2], extent[3], extent[4]), neverDeleteData);" << iendl; \
    oss << "  " << className << "_hdl->" << name << ".reference(tmp.copy());" << iendl; \
    /*oss << "  " << className << "_hdl->sendAttributToServer(" << className << "_hdl->" << name << ");" << iendl;*/ \
    oss << "   CTimer::get(\"XIOS\").suspend();" << iendl; \
    oss << "}" << std::endl; \
    oss << iendl; \
    oss << "void cxios_get_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, " << typeName << "* " << name << ", int* extent)" << iendl; \
    oss << "{" << iendl; \
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl; \
    oss << "  CArray<" << typeName << ",5> tmp(" << name << ", shape(extent[0], extent[1], extent[2], extent[3], extent[4]), neverDeleteData);" << iendl; \
    oss << "  tmp=" << className << "_hdl->" << name << ".getInheritedValue();" << iendl; \
    oss << "   CTimer::get(\"XIOS\").suspend();" << iendl; \
    oss << "}" << std::endl; \
    oss << iendl; \
    oss <<  "void cxios_" << className << "_" << name << "_shape(" << className << "_Ptr " << className << "_hdl, " << "int* shape)" << iendl; \
    oss << "{" << (iendl+=1); \
    oss << "CArray<" << typeName << ", 5> data = " << className  << "_hdl->" << name << ".getInheritedValue();" << iendl; \
    oss << "shape[0] = data.extent(0);" << iendl; \
    oss << "shape[1] = data.extent(1);" << iendl; \
    oss << "shape[2] = data.extent(2);" << iendl; \
    oss << "shape[3] = data.extent(3);" << iendl; \
    oss << "shape[4] = data.extent(4);" << iendl; \
		oss << (iendl-=1); \
    oss << "}" << std::endl; \
  } \
\
  template <> \
  void CInterface::AttributeCInterface<CArray<T,6> >(ostream& oss, const string& className, const string& name) \
  { \
    string typeName=getStrType<T>(); \
\
    oss << "void cxios_set_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, " << typeName << "* " << name << ", int* extent)" << iendl; \
    oss << "{" << iendl; \
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl; \
    oss << "  CArray<" << typeName << ",6> tmp(" << name << ", shape(extent[0], extent[1], extent[2], extent[3], extent[4], extent[5]), neverDeleteData);" << iendl; \
    oss << "  " << className << "_hdl->" << name << ".reference(tmp.copy());" << iendl; \
    /*oss << "  " << className << "_hdl->sendAttributToServer(" << className << "_hdl->" << name << ");" << iendl;*/ \
    oss << "   CTimer::get(\"XIOS\").suspend();" << iendl; \
    oss << "}" << std::endl; \
    oss << iendl; \
    oss << "void cxios_get_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, " << typeName << "* " << name << ", int* extent)" << iendl; \
    oss << "{" << iendl; \
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl; \
    oss << "  CArray<" << typeName << ",6> tmp(" << name << ", shape(extent[0], extent[1], extent[2], extent[3], extent[4], extent[5]), neverDeleteData);" << iendl; \
    oss << "  tmp=" << className << "_hdl->" << name << ".getInheritedValue();" << iendl; \
    oss << "   CTimer::get(\"XIOS\").suspend();" << iendl; \
    oss << "}" << std::endl; \
    oss << iendl; \
    oss <<  "void cxios_" << className << "_" << name << "_shape(" << className << "_Ptr " << className << "_hdl, " << "int* shape)" << iendl; \
    oss << "{" << (iendl+=1); \
    oss << "CArray<" << typeName << ", 6> data = " << className  << "_hdl->" << name << ".getInheritedValue();" << iendl; \
    oss << "shape[0] = data.extent(0);" << iendl; \
    oss << "shape[1] = data.extent(1);" << iendl; \
    oss << "shape[2] = data.extent(2);" << iendl; \
    oss << "shape[3] = data.extent(3);" << iendl; \
    oss << "shape[4] = data.extent(4);" << iendl; \
    oss << "shape[5] = data.extent(5);" << iendl; \
		oss << (iendl-=1); \
    oss << "}" << std::endl; \
  }  \
\
  template <> \
  void CInterface::AttributeCInterface<CArray<T,7> >(ostream& oss, const string& className, const string& name) \
  { \
    string typeName=getStrType<T>(); \
\
    oss << "void cxios_set_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, " << typeName << "* " << name << ", int* extent)" << iendl; \
    oss << "{" << iendl; \
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl; \
    oss << "  CArray<" << typeName << ",7> tmp(" << name << ", shape(extent[0], extent[1], extent[2], extent[3], extent[4], extent[5], extent[6]), neverDeleteData);" << iendl; \
    oss << "  " << className << "_hdl->" << name << ".reference(tmp.copy());" << iendl; \
    /*oss << "  " << className << "_hdl->sendAttributToServer(" << className << "_hdl->" << name << ");" << iendl;*/ \
    oss << "   CTimer::get(\"XIOS\").suspend();" << iendl; \
    oss << "}" << std::endl; \
    oss << iendl; \
    oss << "void cxios_get_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, " << typeName << "* " << name << ", int* extent)" << iendl; \
    oss << "{" << iendl; \
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl; \
    oss << "  CArray<" << typeName << ",7> tmp(" << name << ", shape(extent[0], extent[1], extent[2], extent[3], extent[4], extent[5], extent[6]), neverDeleteData);" << iendl; \
    oss << "  tmp=" << className << "_hdl->" << name << ".getInheritedValue();" << iendl; \
    oss << "   CTimer::get(\"XIOS\").suspend();" << iendl; \
    oss << "}" << std::endl; \
    oss << iendl; \
    oss <<  "void cxios_" << className << "_" << name << "_shape(" << className << "_Ptr " << className << "_hdl, " << "int* shape)" << iendl; \
    oss << "{" << (iendl+=1); \
    oss << "CArray<" << typeName << ", 7> data = " << className  << "_hdl->" << name << ".getInheritedValue();" << iendl; \
    oss << "shape[0] = data.extent(0);" << iendl; \
    oss << "shape[1] = data.extent(1);" << iendl; \
    oss << "shape[2] = data.extent(2);" << iendl; \
    oss << "shape[3] = data.extent(3);" << iendl; \
    oss << "shape[4] = data.extent(4);" << iendl; \
    oss << "shape[5] = data.extent(5);" << iendl; \
    oss << "shape[6] = data.extent(6);" << iendl; \
		oss << (iendl-=1); \
    oss << "}" << std::endl; \
  }

macro(bool)
macro(double)
macro(int)

#undef macro

#define macro(N,EXTENT)\
  template <>\
  void CInterface::AttributeCInterface<CArray<StdString,N> >(ostream& oss, const string& className, const string& name)\
  { \
    oss << "void cxios_set_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, " << "char* " << name <<", int str_len, int* str_size, int* extent)" << iendl; \
    oss << "{" << iendl; \
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl; \
    oss << "  "<<className<<"_hdl->"<<name<<".resize(shape("<<EXTENT<<"));"<<iendl;\
    oss << "  Array<StdString,"<<#N<<">::iterator it, itb="<<className<<"_hdl->"<<name<<".begin(), ite="<<className<<"_hdl->"<<name<<".end() ;"<<iendl ;\
    oss << "  int i, n ;"<< iendl; \
    oss << "  for(it=itb, i=0, n=0 ; it!=ite ; ++it,n+=str_len,++i) *it=StdString(&"<<name<<"[n],str_size[i]) ;"<<iendl ;\
    oss << "  CTimer::get(\"XIOS\").suspend();" << iendl; \
    oss << "}" << std::endl; \
    oss << iendl; \
    oss << "void cxios_get_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, " << "char* " << name << ", int str_size, int* extent)" << iendl; \
    oss << "{" << iendl; \
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl; \
    oss << "  Array<StdString,"<<#N<<">::const_iterator it, itb="<<className<<"_hdl->"<<name<<".getInheritedValue().begin(), ite="<<className<<"_hdl->"<<name<<".getInheritedValue().end() ;" << iendl; \
    oss << "  int n ;"<< iendl; \
    oss << "  for(it=itb, n=0 ; it!=ite ; ++it, n+=str_size) it->copy(&"<<name<<"[n],it->size()) ; "<< iendl; \
    oss << "  CTimer::get(\"XIOS\").suspend();" << iendl; \
    oss << "}" << std::endl; \
  }

macro(1,"extent[0]")
macro(2,"extent[0],extent[1]")
macro(3,"extent[0],extent[1],extent[2]")
macro(4,"extent[0],extent[1],extent[2],extent[3]")
macro(5,"extent[0],extent[1],extent[2],extent[3],extent[4]")
macro(6,"extent[0],extent[1],extent[2],extent[3],extent[4],extent[5]")
macro(7,"extent[0],extent[1],extent[2],extent[3],extent[4],extent[5],extent[6]")
#undef macro
// /////////////////////////////////////////////////
// //          Fortran 2003 Interface             //
// /////////////////////////////////////////////////

#define macro(T) \
  template <> \
  void CInterface::AttributeFortran2003Interface<CArray<T,1> >(ostream& oss, const string& className, const string& name) \
  { \
    string fortranType=getStrFortranType<T>(); \
    string fortranKindC=getStrFortranKindC<T>(); \
      \
    oss << "SUBROUTINE cxios_set_" << className << "_" << name << "(" << className << "_hdl, " << name << ", extent) BIND(C)" << iendl; \
    oss << "  USE ISO_C_BINDING" << iendl; \
    oss << "  INTEGER (kind = C_INTPTR_T), VALUE       :: " << className << "_hdl" << iendl; \
    oss << "  " << fortranType << " " << fortranKindC << "     , DIMENSION(*) :: " << name << iendl; \
    oss << "  INTEGER (kind = C_INT), DIMENSION(*)     :: extent" << iendl; \
    oss << "END SUBROUTINE cxios_set_" << className << "_" << name << std::endl; \
    oss << iendl; \
    oss << "SUBROUTINE cxios_get_" << className << "_" << name << "(" << className << "_hdl, " << name << ", extent) BIND(C)" << iendl; \
    oss << "  USE ISO_C_BINDING" << iendl; \
    oss << "  INTEGER (kind = C_INTPTR_T), VALUE       :: " << className << "_hdl" << iendl; \
    oss << "  " << fortranType << " " << fortranKindC << "     , DIMENSION(*) :: " << name << iendl; \
    oss << "  INTEGER (kind = C_INT), DIMENSION(*)     :: extent" << iendl; \
    oss << "END SUBROUTINE cxios_get_" << className << "_" << name << std::endl; \
  } \
 \
  template <> \
  void CInterface::AttributeFortran2003Interface<CArray<T,2> >(ostream& oss, const string& className, const string& name) \
  { \
    string fortranType=getStrFortranType<T>(); \
    string fortranKindC=getStrFortranKindC<T>(); \
      \
    oss << "SUBROUTINE cxios_set_" << className << "_" << name << "(" << className << "_hdl, " << name << ", extent) BIND(C)" << iendl; \
    oss << "  USE ISO_C_BINDING" << iendl; \
    oss << "  INTEGER (kind = C_INTPTR_T), VALUE       :: " << className << "_hdl" << iendl; \
    oss << "  " << fortranType << " " << fortranKindC << "     , DIMENSION(*) :: " << name << iendl; \
    oss << "  INTEGER (kind = C_INT), DIMENSION(*)     :: extent" << iendl; \
    oss << "END SUBROUTINE cxios_set_" << className << "_" << name << std::endl; \
    oss << iendl; \
    oss << "SUBROUTINE cxios_get_" << className << "_" << name << "(" << className << "_hdl, " << name << ", extent) BIND(C)" << iendl; \
    oss << "  USE ISO_C_BINDING" << iendl; \
    oss << "  INTEGER (kind = C_INTPTR_T), VALUE       :: " << className << "_hdl" << iendl; \
    oss << "  " << fortranType << " " << fortranKindC << "     , DIMENSION(*) :: " << name << iendl; \
    oss << "  INTEGER (kind = C_INT), DIMENSION(*)     :: extent" << iendl; \
    oss << "END SUBROUTINE cxios_get_" << className << "_" << name << std::endl; \
  } \
 \
  template <> \
  void CInterface::AttributeFortran2003Interface<CArray<T,3> >(ostream& oss, const string& className, const string& name) \
  { \
    string fortranType=getStrFortranType<T>(); \
    string fortranKindC=getStrFortranKindC<T>(); \
      \
    oss << "SUBROUTINE cxios_set_" << className << "_" << name << "(" << className << "_hdl, " << name << ", extent) BIND(C)" << iendl; \
    oss << "  USE ISO_C_BINDING" << iendl; \
    oss << "  INTEGER (kind = C_INTPTR_T), VALUE       :: " << className << "_hdl" << iendl; \
    oss << "  " << fortranType << " " << fortranKindC << "     , DIMENSION(*) :: " << name << iendl; \
    oss << "  INTEGER (kind = C_INT), DIMENSION(*)     :: extent" << iendl; \
    oss << "END SUBROUTINE cxios_set_" << className << "_" << name << std::endl; \
    oss << iendl; \
    oss << "SUBROUTINE cxios_get_" << className << "_" << name << "(" << className << "_hdl, " << name << ", extent) BIND(C)" << iendl; \
    oss << "  USE ISO_C_BINDING" << iendl; \
    oss << "  INTEGER (kind = C_INTPTR_T), VALUE       :: " << className << "_hdl" << iendl; \
    oss << "  " << fortranType << " " << fortranKindC << "     , DIMENSION(*) :: " << name << iendl; \
    oss << "  INTEGER (kind = C_INT), DIMENSION(*)     :: extent" << iendl; \
    oss << "END SUBROUTINE cxios_get_" << className << "_" << name << std::endl; \
  }  \
 \
  template <> \
  void CInterface::AttributeFortran2003Interface<CArray<T,4> >(ostream& oss, const string& className, const string& name) \
  { \
    string fortranType=getStrFortranType<T>(); \
    string fortranKindC=getStrFortranKindC<T>(); \
      \
    oss << "SUBROUTINE cxios_set_" << className << "_" << name << "(" << className << "_hdl, " << name << ", extent) BIND(C)" << iendl; \
    oss << "  USE ISO_C_BINDING" << iendl; \
    oss << "  INTEGER (kind = C_INTPTR_T), VALUE       :: " << className << "_hdl" << iendl; \
    oss << "  " << fortranType << " " << fortranKindC << "     , DIMENSION(*) :: " << name << iendl; \
    oss << "  INTEGER (kind = C_INT), DIMENSION(*)     :: extent" << iendl; \
    oss << "END SUBROUTINE cxios_set_" << className << "_" << name << std::endl; \
    oss << iendl; \
    oss << "SUBROUTINE cxios_get_" << className << "_" << name << "(" << className << "_hdl, " << name << ", extent) BIND(C)" << iendl; \
    oss << "  USE ISO_C_BINDING" << iendl; \
    oss << "  INTEGER (kind = C_INTPTR_T), VALUE       :: " << className << "_hdl" << iendl; \
    oss << "  " << fortranType << " " << fortranKindC << "     , DIMENSION(*) :: " << name << iendl; \
    oss << "  INTEGER (kind = C_INT), DIMENSION(*)     :: extent" << iendl; \
    oss << "END SUBROUTINE cxios_get_" << className << "_" << name << std::endl; \
  }\
 \
  template <> \
  void CInterface::AttributeFortran2003Interface<CArray<T,5> >(ostream& oss, const string& className, const string& name) \
  { \
    string fortranType=getStrFortranType<T>(); \
    string fortranKindC=getStrFortranKindC<T>(); \
      \
    oss << "SUBROUTINE cxios_set_" << className << "_" << name << "(" << className << "_hdl, " << name << ", extent) BIND(C)" << iendl; \
    oss << "  USE ISO_C_BINDING" << iendl; \
    oss << "  INTEGER (kind = C_INTPTR_T), VALUE       :: " << className << "_hdl" << iendl; \
    oss << "  " << fortranType << " " << fortranKindC << "     , DIMENSION(*) :: " << name << iendl; \
    oss << "  INTEGER (kind = C_INT), DIMENSION(*)     :: extent" << iendl; \
    oss << "END SUBROUTINE cxios_set_" << className << "_" << name << std::endl; \
    oss << iendl; \
    oss << "SUBROUTINE cxios_get_" << className << "_" << name << "(" << className << "_hdl, " << name << ", extent) BIND(C)" << iendl; \
    oss << "  USE ISO_C_BINDING" << iendl; \
    oss << "  INTEGER (kind = C_INTPTR_T), VALUE       :: " << className << "_hdl" << iendl; \
    oss << "  " << fortranType << " " << fortranKindC << "     , DIMENSION(*) :: " << name << iendl; \
    oss << "  INTEGER (kind = C_INT), DIMENSION(*)     :: extent" << iendl; \
    oss << "END SUBROUTINE cxios_get_" << className << "_" << name << std::endl; \
  }\
 \
  template <> \
  void CInterface::AttributeFortran2003Interface<CArray<T,6> >(ostream& oss, const string& className, const string& name) \
  { \
    string fortranType=getStrFortranType<T>(); \
    string fortranKindC=getStrFortranKindC<T>(); \
      \
    oss << "SUBROUTINE cxios_set_" << className << "_" << name << "(" << className << "_hdl, " << name << ", extent) BIND(C)" << iendl; \
    oss << "  USE ISO_C_BINDING" << iendl; \
    oss << "  INTEGER (kind = C_INTPTR_T), VALUE       :: " << className << "_hdl" << iendl; \
    oss << "  " << fortranType << " " << fortranKindC << "     , DIMENSION(*) :: " << name << iendl; \
    oss << "  INTEGER (kind = C_INT), DIMENSION(*)     :: extent" << iendl; \
    oss << "END SUBROUTINE cxios_set_" << className << "_" << name << std::endl; \
    oss << iendl; \
    oss << "SUBROUTINE cxios_get_" << className << "_" << name << "(" << className << "_hdl, " << name << ", extent) BIND(C)" << iendl; \
    oss << "  USE ISO_C_BINDING" << iendl; \
    oss << "  INTEGER (kind = C_INTPTR_T), VALUE       :: " << className << "_hdl" << iendl; \
    oss << "  " << fortranType << " " << fortranKindC << "     , DIMENSION(*) :: " << name << iendl; \
    oss << "  INTEGER (kind = C_INT), DIMENSION(*)     :: extent" << iendl; \
    oss << "END SUBROUTINE cxios_get_" << className << "_" << name << std::endl; \
  }\
 \
  template <> \
  void CInterface::AttributeFortran2003Interface<CArray<T,7> >(ostream& oss, const string& className, const string& name) \
  { \
    string fortranType=getStrFortranType<T>(); \
    string fortranKindC=getStrFortranKindC<T>(); \
      \
    oss << "SUBROUTINE cxios_set_" << className << "_" << name << "(" << className << "_hdl, " << name << ", extent) BIND(C)" << iendl; \
    oss << "  USE ISO_C_BINDING" << iendl; \
    oss << "  INTEGER (kind = C_INTPTR_T), VALUE       :: " << className << "_hdl" << iendl; \
    oss << "  " << fortranType << " " << fortranKindC << "     , DIMENSION(*) :: " << name << iendl; \
    oss << "  INTEGER (kind = C_INT), DIMENSION(*)     :: extent" << iendl; \
    oss << "END SUBROUTINE cxios_set_" << className << "_" << name << std::endl; \
    oss << iendl; \
    oss << "SUBROUTINE cxios_get_" << className << "_" << name << "(" << className << "_hdl, " << name << ", extent) BIND(C)" << iendl; \
    oss << "  USE ISO_C_BINDING" << iendl; \
    oss << "  INTEGER (kind = C_INTPTR_T), VALUE       :: " << className << "_hdl" << iendl; \
    oss << "  " << fortranType << " " << fortranKindC << "     , DIMENSION(*) :: " << name << iendl; \
    oss << "  INTEGER (kind = C_INT), DIMENSION(*)     :: extent" << iendl; \
    oss << "END SUBROUTINE cxios_get_" << className << "_" << name << std::endl; \
  }

  macro(bool)
  macro(double)
  macro(int)

  #undef macro

#define macro(T)\
  template <>\
  void CInterface::AttributeFortran2003Interface<CArray<StdString,T> >(ostream& oss, const string& className, const string& name)\
  {\
    oss << "SUBROUTINE cxios_set_" << className << "_" << name << "(" << className << "_hdl, " << name << ", str_len, str_size, extent) BIND(C)" << iendl; \
    oss << "  USE ISO_C_BINDING" << iendl; \
    oss << "  INTEGER (kind = C_INTPTR_T), VALUE       :: " << className << "_hdl" << iendl; \
    oss << "  CHARACTER (KIND=C_CHAR), DIMENSION(*)    :: " << name << iendl; \
    oss << "  INTEGER (kind = C_INT), VALUE            :: str_len" << iendl; \
    oss << "  INTEGER (kind = C_INT), DIMENSION(*)     :: str_size" << iendl; \
    oss << "  INTEGER (kind = C_INT), DIMENSION(*)     :: extent" << iendl; \
    oss << "END SUBROUTINE cxios_set_" << className << "_" << name << std::endl; \
    oss << iendl; \
    oss << "SUBROUTINE cxios_get_" << className << "_" << name << "(" << className << "_hdl, " << name << ", str_size, extent) BIND(C)" << iendl; \
    oss << "  USE ISO_C_BINDING" << iendl; \
    oss << "  INTEGER (kind = C_INTPTR_T), VALUE       :: " << className << "_hdl" << iendl; \
    oss << "  CHARACTER (KIND=C_CHAR), DIMENSION(*)    :: " << name << iendl; \
    oss << "  INTEGER (kind = C_INT), VALUE            :: str_size" << iendl; \
    oss << "  INTEGER (kind = C_INT), DIMENSION(*)     :: extent" << iendl; \
    oss << "END SUBROUTINE cxios_get_" << className << "_" << name << std::endl; \
  }
  macro(1)
  macro(2)
  macro(3)
  macro(4)
  macro(5)
  macro(6)
  macro(7)

#undef macro

#define macro(T) \
  template <> \
  void CInterface::AttributeFortranInterfaceDeclaration<CArray<T,1> >(ostream& oss, const string& className, const string& name) \
  { \
    oss << getStrFortranType<T>() << " " << getStrFortranKind<T>() << " , OPTIONAL, INTENT(IN) :: " << name << "(:)"; \
    if (!matchingTypeCFortran<T>()) oss << iendl << getStrFortranType<T>() << " " << getStrFortranKindC<T>() << " , ALLOCATABLE :: " << name << "_tmp(:)"; \
  } \
  template <> \
  void CInterface::AttributeFortranInterfaceGetDeclaration<CArray<T,1> >(ostream& oss, const string& className, const string& name) \
  { \
    oss << getStrFortranType<T>() << " " << getStrFortranKind<T>() << " , OPTIONAL, INTENT(OUT) :: " << name << "(:)"; \
    if (!matchingTypeCFortran<T>()) oss << iendl << getStrFortranType<T>() << " " << getStrFortranKindC<T>() << " , ALLOCATABLE :: " << name << "_tmp(:)"; \
  } \
 \
  template <> \
  void CInterface::AttributeFortranInterfaceDeclaration<CArray<T,2> >(ostream& oss, const string& className, const string& name) \
  { \
    oss << getStrFortranType<T>() << " " << getStrFortranKind<T>() << " , OPTIONAL, INTENT(IN) :: " << name << "(:,:)"; \
    if (!matchingTypeCFortran<T>()) oss << iendl << getStrFortranType<T>() << " " << getStrFortranKindC<T>() << " , ALLOCATABLE :: " << name << "_tmp(:,:)"; \
  } \
 \
  template <> \
  void CInterface::AttributeFortranInterfaceGetDeclaration<CArray<T,2> >(ostream& oss, const string& className, const string& name) \
  { \
    oss << getStrFortranType<T>() << " " << getStrFortranKind<T>() << " , OPTIONAL, INTENT(OUT) :: " << name << "(:,:)"; \
    if (!matchingTypeCFortran<T>()) oss << iendl << getStrFortranType<T>() << " " << getStrFortranKindC<T>() << " , ALLOCATABLE :: " << name << "_tmp(:,:)"; \
  } \
 \
  template <> \
  void CInterface::AttributeFortranInterfaceDeclaration<CArray<T,3> >(ostream& oss, const string& className, const string& name) \
  { \
    oss << getStrFortranType<T>() << " " << getStrFortranKind<T>() << " , OPTIONAL, INTENT(IN) :: " << name << "(:,:,:)"; \
    if (!matchingTypeCFortran<T>()) oss << iendl << getStrFortranType<T>() << " " << getStrFortranKindC<T>() << " , ALLOCATABLE :: " << name << "_tmp(:,:,:)"; \
  } \
 \
  template <> \
  void CInterface::AttributeFortranInterfaceGetDeclaration<CArray<T,3> >(ostream& oss, const string& className, const string& name) \
  { \
    oss << getStrFortranType<T>() << " " << getStrFortranKind<T>() << " , OPTIONAL, INTENT(OUT) :: " << name << "(:,:,:)"; \
    if (!matchingTypeCFortran<T>()) oss << iendl << getStrFortranType<T>() << " " << getStrFortranKindC<T>() << " , ALLOCATABLE :: " << name << "_tmp(:,:,:)"; \
  }\
 \
  template <> \
  void CInterface::AttributeFortranInterfaceDeclaration<CArray<T,4> >(ostream& oss, const string& className, const string& name) \
  { \
    oss << getStrFortranType<T>() << " " << getStrFortranKind<T>() << " , OPTIONAL, INTENT(IN) :: " << name << "(:,:,:,:)"; \
    if (!matchingTypeCFortran<T>()) oss << iendl << getStrFortranType<T>() << " " << getStrFortranKindC<T>() << " , ALLOCATABLE :: " << name << "_tmp(:,:,:,:)"; \
  } \
 \
  template <> \
  void CInterface::AttributeFortranInterfaceGetDeclaration<CArray<T,4> >(ostream& oss, const string& className, const string& name) \
  { \
    oss << getStrFortranType<T>() << " " << getStrFortranKind<T>() << " , OPTIONAL, INTENT(OUT) :: " << name << "(:,:,:,:)"; \
    if (!matchingTypeCFortran<T>()) oss << iendl << getStrFortranType<T>() << " " << getStrFortranKindC<T>() << " , ALLOCATABLE :: " << name << "_tmp(:,:,:,:)"; \
  }\
 \
  template <> \
  void CInterface::AttributeFortranInterfaceDeclaration<CArray<T,5> >(ostream& oss, const string& className, const string& name) \
  { \
    oss << getStrFortranType<T>() << " " << getStrFortranKind<T>() << " , OPTIONAL, INTENT(IN) :: " << name << "(:,:,:,:,:)"; \
    if (!matchingTypeCFortran<T>()) oss << iendl << getStrFortranType<T>() << " " << getStrFortranKindC<T>() << " , ALLOCATABLE :: " << name << "_tmp(:,:,:,:,:)"; \
  } \
 \
  template <> \
  void CInterface::AttributeFortranInterfaceGetDeclaration<CArray<T,5> >(ostream& oss, const string& className, const string& name) \
  { \
    oss << getStrFortranType<T>() << " " << getStrFortranKind<T>() << " , OPTIONAL, INTENT(OUT) :: " << name << "(:,:,:,:,:)"; \
    if (!matchingTypeCFortran<T>()) oss << iendl << getStrFortranType<T>() << " " << getStrFortranKindC<T>() << " , ALLOCATABLE :: " << name << "_tmp(:,:,:,:,:)"; \
  }\
 \
  template <> \
  void CInterface::AttributeFortranInterfaceDeclaration<CArray<T,6> >(ostream& oss, const string& className, const string& name) \
  { \
    oss << getStrFortranType<T>() << " " << getStrFortranKind<T>() << " , OPTIONAL, INTENT(IN) :: " << name << "(:,:,:,:,:,:)"; \
    if (!matchingTypeCFortran<T>()) oss << iendl << getStrFortranType<T>() << " " << getStrFortranKindC<T>() << " , ALLOCATABLE :: " << name << "_tmp(:,:,:,:,:,:)"; \
  } \
 \
  template <> \
  void CInterface::AttributeFortranInterfaceGetDeclaration<CArray<T,6> >(ostream& oss, const string& className, const string& name) \
  { \
    oss << getStrFortranType<T>() << " " << getStrFortranKind<T>() << " , OPTIONAL, INTENT(OUT) :: " << name << "(:,:,:,:,:,:)"; \
    if (!matchingTypeCFortran<T>()) oss << iendl << getStrFortranType<T>() << " " << getStrFortranKindC<T>() << " , ALLOCATABLE :: " << name << "_tmp(:,:,:,:,:,:)"; \
  }\
 \
  template <> \
  void CInterface::AttributeFortranInterfaceDeclaration<CArray<T,7> >(ostream& oss, const string& className, const string& name) \
  { \
    oss << getStrFortranType<T>() << " " << getStrFortranKind<T>() << " , OPTIONAL, INTENT(IN) :: " << name << "(:,:,:,:,:,:,:)"; \
    if (!matchingTypeCFortran<T>()) oss << iendl << getStrFortranType<T>() << " " << getStrFortranKindC<T>() << " , ALLOCATABLE :: " << name << "_tmp(:,:,:,:,:,:,:)"; \
  } \
 \
  template <> \
  void CInterface::AttributeFortranInterfaceGetDeclaration<CArray<T,7> >(ostream& oss, const string& className, const string& name) \
  { \
    oss << getStrFortranType<T>() << " " << getStrFortranKind<T>() << " , OPTIONAL, INTENT(OUT) :: " << name << "(:,:,:,:,:,:,:)"; \
    if (!matchingTypeCFortran<T>()) oss << iendl << getStrFortranType<T>() << " " << getStrFortranKindC<T>() << " , ALLOCATABLE :: " << name << "_tmp(:,:,:,:,:,:,:)"; \
  }

  macro(bool)
  macro(double)
  macro(int)

#undef macro


#define macro(T) \
template <> \
void CInterface::AttributePythonInterfaceCArgs<CArray<T,1> >(ostream& oss, const string& className, const string& name, const string& funcName, const string& pyName) \
{ \
  if (funcName == "is_defined"){ \
    oss << "lib.cxios_" << funcName << "_" << className << "_" << name  << ".argtypes = [" << pyName << "]" << iendl; \
  }else{ \
    oss << "lib.cxios_" << funcName << "_" << className << "_" << name  << ".argtypes = [" << pyName << ", ctypes.POINTER(" << getStrPythonCType<T>() << "), ctypes.POINTER(ctypes.c_int)]" << iendl; \
  } \
} \
template <> \
void CInterface::AttributePythonInterfaceCArgs<CArray<T,2> >(ostream& oss, const string& className, const string& name, const string& funcName, const string& pyName) \
{ \
  if (funcName == "is_defined"){ \
    oss << "lib.cxios_" << funcName << "_" << className << "_" << name  << ".argtypes = [" << pyName << "]" << iendl; \
  }else{ \
    oss << "lib.cxios_" << funcName << "_" << className << "_" << name  << ".argtypes = [" << pyName << ", ctypes.POINTER(" << getStrPythonCType<T>() << "), ctypes.POINTER(ctypes.c_int)]" << iendl; \
  } \
} \
template <> \
void CInterface::AttributePythonInterfaceCArgs<CArray<T,3> >(ostream& oss, const string& className, const string& name, const string& funcName, const string& pyName) \
{ \
  if (funcName == "is_defined"){ \
    oss << "lib.cxios_" << funcName << "_" << className << "_" << name  << ".argtypes = [" << pyName << "]" << iendl; \
  }else{ \
    oss << "lib.cxios_" << funcName << "_" << className << "_" << name  << ".argtypes = [" << pyName << ", ctypes.POINTER(" << getStrPythonCType<T>() << "), ctypes.POINTER(ctypes.c_int)]" << iendl; \
  } \
} \
template <> \
void CInterface::AttributePythonInterfaceCArgs<CArray<T,4> >(ostream& oss, const string& className, const string& name, const string& funcName, const string& pyName) \
{ \
  if (funcName == "is_defined"){ \
    oss << "lib.cxios_" << funcName << "_" << className << "_" << name  << ".argtypes = [" << pyName << "]" << iendl; \
  }else{ \
    oss << "lib.cxios_" << funcName << "_" << className << "_" << name  << ".argtypes = [" << pyName << ", ctypes.POINTER(" << getStrPythonCType<T>() << "), ctypes.POINTER(ctypes.c_int)]" << iendl; \
  } \
} \
template <> \
void CInterface::AttributePythonInterfaceCArgs<CArray<T,5> >(ostream& oss, const string& className, const string& name, const string& funcName, const string& pyName) \
{ \
  if (funcName == "is_defined"){ \
    oss << "lib.cxios_" << funcName << "_" << className << "_" << name  << ".argtypes = [" << pyName << "]" << iendl; \
  }else{ \
    oss << "lib.cxios_" << funcName << "_" << className << "_" << name  << ".argtypes = [" << pyName << ", ctypes.POINTER(" << getStrPythonCType<T>() << "), ctypes.POINTER(ctypes.c_int)]" << iendl; \
  } \
} \
template <> \
void CInterface::AttributePythonInterfaceCArgs<CArray<T,6> >(ostream& oss, const string& className, const string& name, const string& funcName, const string& pyName) \
{ \
  if (funcName == "is_defined"){ \
    oss << "lib.cxios_" << funcName << "_" << className << "_" << name  << ".argtypes = [" << pyName << "]" << iendl; \
  }else{ \
    oss << "lib.cxios_" << funcName << "_" << className << "_" << name  << ".argtypes = [" << pyName << ", ctypes.POINTER(" << getStrPythonCType<T>() << "), ctypes.POINTER(ctypes.c_int)]" << iendl; \
  } \
} \
template <> \
void CInterface::AttributePythonInterfaceCArgs<CArray<T,7> >(ostream& oss, const string& className, const string& name, const string& funcName, const string& pyName) \
{ \
  if (funcName == "is_defined"){ \
    oss << "lib.cxios_" << funcName << "_" << className << "_" << name  << ".argtypes = [" << pyName << "]" << iendl; \
  }else{ \
    oss << "lib.cxios_" << funcName << "_" << className << "_" << name  << ".argtypes = [" << pyName << ", ctypes.POINTER(" << getStrPythonCType<T>() << "), ctypes.POINTER(ctypes.c_int)]" << iendl; \
  } \
} 

macro(bool)
macro(double)
macro(int)
macro(string)

#undef macro

#define macro(T) \
template <> \
void CInterface::AttributePythonInterfaceCRes<CArray<T,1> >(ostream& oss, const string& className, const string& name, const string& funcName) \
{ \
  if (funcName == "is_defined"){ \
    oss << "lib.cxios_" << funcName << "_" << className << "_" << name  << ".restypes = ctypes.c_bool" << iendl;  \
  }else{ \
    oss << "lib.cxios_" << funcName << "_" << className << "_" << name  << ".restypes = None" << iendl;    \
  } \
} \
template <> \
void CInterface::AttributePythonInterfaceCRes<CArray<T,2> >(ostream& oss, const string& className, const string& name, const string& funcName) \
{ \
  if (funcName == "is_defined"){ \
    oss << "lib.cxios_" << funcName << "_" << className << "_" << name  << ".restypes = ctypes.c_bool" << iendl;  \
  }else{ \
    oss << "lib.cxios_" << funcName << "_" << className << "_" << name  << ".restypes = None" << iendl;    \
  } \
} \
template <> \
void CInterface::AttributePythonInterfaceCRes<CArray<T,3> >(ostream& oss, const string& className, const string& name, const string& funcName) \
{ \
  if (funcName == "is_defined"){ \
    oss << "lib.cxios_" << funcName << "_" << className << "_" << name  << ".restypes = ctypes.c_bool" << iendl;  \
  }else{ \
    oss << "lib.cxios_" << funcName << "_" << className << "_" << name  << ".restypes = None" << iendl;    \
  } \
} \
template <> \
void CInterface::AttributePythonInterfaceCRes<CArray<T,4> >(ostream& oss, const string& className, const string& name, const string& funcName) \
{ \
  if (funcName == "is_defined"){ \
    oss << "lib.cxios_" << funcName << "_" << className << "_" << name  << ".restypes = ctypes.c_bool" << iendl;  \
  }else{ \
    oss << "lib.cxios_" << funcName << "_" << className << "_" << name  << ".restypes = None" << iendl;    \
  } \
} \
template <> \
void CInterface::AttributePythonInterfaceCRes<CArray<T,5> >(ostream& oss, const string& className, const string& name, const string& funcName) \
{ \
  if (funcName == "is_defined"){ \
    oss << "lib.cxios_" << funcName << "_" << className << "_" << name  << ".restypes = ctypes.c_bool" << iendl;  \
  }else{ \
    oss << "lib.cxios_" << funcName << "_" << className << "_" << name  << ".restypes = None" << iendl;    \
  } \
} \
template <> \
void CInterface::AttributePythonInterfaceCRes<CArray<T,6> >(ostream& oss, const string& className, const string& name, const string& funcName) \
{ \
  if (funcName == "is_defined"){ \
    oss << "lib.cxios_" << funcName << "_" << className << "_" << name  << ".restypes = ctypes.c_bool" << iendl;  \
  }else{ \
    oss << "lib.cxios_" << funcName << "_" << className << "_" << name  << ".restypes = None" << iendl;    \
  } \
} \
template <> \
void CInterface::AttributePythonInterfaceCRes<CArray<T,7> >(ostream& oss, const string& className, const string& name, const string& funcName) \
{ \
  if (funcName == "is_defined"){ \
    oss << "lib.cxios_" << funcName << "_" << className << "_" << name  << ".restypes = ctypes.c_bool" << iendl;  \
  }else{ \
    oss << "lib.cxios_" << funcName << "_" << className << "_" << name  << ".restypes = None" << iendl;    \
  } \
} 

macro(bool)
macro(double)
macro(int)
macro(string)

#undef macro


#define macro(T) \
template <> \
void CInterface::AttributeObjPythonInterfaceBody<CArray<T,1> >(ostream& oss, const string& className, const string& name) \
{ \
   if (getStrPythonType<T>().compare("Double") == 0){ \
      oss << "'" << name  << "': {'type': NpArray, 'ndim': 1}," << iendl;     \
    }else{ \
      oss << "'" << name  << "': {'type': NpArray" << getStrPythonType<T>() << ", 'ndim': 1}," << iendl;     \
    } \
} \
template <> \
void CInterface::AttributeObjPythonInterfaceBody<CArray<T,2> >(ostream& oss, const string& className, const string& name) \
{ \
   if (getStrPythonType<T>().compare("Double") == 0){ \
      oss << "'" << name  << "': {'type': NpArray, 'ndim': 2}," << iendl;     \
    }else{ \
      oss << "'" << name  << "': {'type': NpArray" << getStrPythonType<T>() << ", 'ndim': 2}," << iendl;     \
    } \
} \
template <> \
void CInterface::AttributeObjPythonInterfaceBody<CArray<T,3> >(ostream& oss, const string& className, const string& name) \
{ \
   if (getStrPythonType<T>().compare("Double") == 0){ \
      oss << "'" << name  << "': {'type': NpArray, 'ndim': 3}," << iendl;     \
    }else{ \
      oss << "'" << name  << "': {'type': NpArray" << getStrPythonType<T>() << ", 'ndim': 3}," << iendl;     \
    } \
} \
template <> \
void CInterface::AttributeObjPythonInterfaceBody<CArray<T,4> >(ostream& oss, const string& className, const string& name) \
{ \
   if (getStrPythonType<T>().compare("Double") == 0){ \
      oss << "'" << name  << "': {'type': NpArray, 'ndim': 4}," << iendl;     \
    }else{ \
      oss << "'" << name  << "': {'type': NpArray" << getStrPythonType<T>() << ", 'ndim': 4}," << iendl;     \
    } \
} \
template <> \
void CInterface::AttributeObjPythonInterfaceBody<CArray<T,5> >(ostream& oss, const string& className, const string& name) \
{ \
   if (getStrPythonType<T>().compare("Double") == 0){ \
      oss << "'" << name  << "': {'type': NpArray, 'ndim': 5}," << iendl;     \
    }else{ \
      oss << "'" << name  << "': {'type': NpArray" << getStrPythonType<T>() << ", 'ndim': 5}," << iendl;     \
    } \
} \
template <> \
void CInterface::AttributeObjPythonInterfaceBody<CArray<T,6> >(ostream& oss, const string& className, const string& name) \
{ \
   if (getStrPythonType<T>().compare("Double") == 0){ \
      oss << "'" << name  << "': {'type': NpArray, 'ndim': 6}," << iendl;     \
    }else{ \
      oss << "'" << name  << "': {'type': NpArray" << getStrPythonType<T>() << ", 'ndim': 6}," << iendl;     \
    } \
} \
template <> \
void CInterface::AttributeObjPythonInterfaceBody<CArray<T,7> >(ostream& oss, const string& className, const string& name) \
{ \
   if (getStrPythonType<T>().compare("Double") == 0){ \
      oss << "'" << name  << "': {'type': NpArray, 'ndim': 7}," << iendl;     \
    }else{ \
      oss << "'" << name  << "': {'type': NpArray" << getStrPythonType<T>() << ", 'ndim': 7}," << iendl;     \
    } \
} 

macro(bool)
macro(double)
macro(int)

#undef macro

template <>
void CInterface::AttributeObjPythonInterfaceBody<CArray<std::string, 2>>(std::ostream& oss, const std::string& className, const std::string& name)
{
    oss << "'" << name << "': {'type': String}," << iendl;
}

template <>
void CInterface::AttributeObjPythonInterfaceBody<CArray<std::string, 1>>(std::ostream& oss, const std::string& className, const std::string& name)
{
    oss << "'" << name << "': {'type': String}," << iendl;
}

#define macro(T,EXTENT)\
  template <> \
  void CInterface::AttributeFortranInterfaceDeclaration<CArray<StdString,T> >(ostream& oss, const string& className, const string& name)\
  {\
    oss << "CHARACTER(len=*) , OPTIONAL, INTENT(IN) :: " << name << "("<<EXTENT<<")"; \
  }\
\
  template <>\
  void CInterface::AttributeFortranInterfaceGetDeclaration<CArray<StdString,T> >(ostream& oss, const string& className, const string& name)\
  {\
    oss << "CHARACTER(len=*) , OPTIONAL, INTENT(OUT) :: " << name << "("<<EXTENT<<")"; \
  }
  macro(1,":")
  macro(2,":,:")
  macro(3,":,:,:")
  macro(4,":,:,:,:")
  macro(5,":,:,:,:,:")
  macro(6,":,:,:,:,:,:")
  macro(7,":,:,:,:,:,:,:")

#undef macro


#define macro(T, N) \
  template<> \
  void CInterface::AttributePythonInterfaceDeclaration<CArray<T, N>>(std::ostream& oss, const std::string& className, const std::string& name, bool isSet) { \
    std::string t = ""; \
    if (getStrPythonType<T>() != "Double") { \
        t = getStrPythonType<T>(); \
    } \
    if (isSet) { \
        oss << " : Optional[Union[np.ndarray, NpArray" << t << "]] = None"; \
    } else { \
        oss << " : Optional[NpArray" << t << "] = None"; \
    } \
  }
  macro(int, 1)
  macro(int, 2)
  macro(int, 3)
  macro(int, 4)
  macro(int, 5)
  macro(int, 6)
  macro(int, 7)
  macro(double, 1)
  macro(double, 2)
  macro(double, 3)
  macro(double, 4)
  macro(double, 5)
  macro(double, 6)
  macro(double, 7)
  macro(bool, 1)
  macro(bool, 2)
  macro(bool, 3)
  macro(bool, 4)
  macro(bool, 5)
  macro(bool, 6)
  macro(bool, 7)


#undef macro


#define macro(T) \
  template <> \
  void CInterface::AttributePythonInterfaceIsDefinedDeclaration<CArray<T,1> >(ostream& oss, const string& className, const string& name) \
  { \
  oss << " : Optional[Bool] = None" ; \
  } \
  \
  template <> \
  void CInterface::AttributePythonInterfaceIsDefinedDeclaration<CArray<T,2> >(ostream& oss, const string& className, const string& name) \
  { \
  oss << " : Optional[Bool] = None" ; \
  } \
  \
  template <> \
  void CInterface::AttributePythonInterfaceIsDefinedDeclaration<CArray<T,3> >(ostream& oss, const string& className, const string& name) \
  { \
    oss << " : Optional[Bool] = None" ; \
  } \
  \
  template <> \
  void CInterface::AttributePythonInterfaceIsDefinedDeclaration<CArray<T,4> >(ostream& oss, const string& className, const string& name) \
  { \
    oss << " : Optional[Bool] = None" ; \
  } \
  \
  template <> \
  void CInterface::AttributePythonInterfaceIsDefinedDeclaration<CArray<T,5> >(ostream& oss, const string& className, const string& name) \
  { \
    oss << " : Optional[Bool] = None" ; \
  } \
  \
  template <> \
  void CInterface::AttributePythonInterfaceIsDefinedDeclaration<CArray<T,6> >(ostream& oss, const string& className, const string& name) \
  { \
    oss << " : Optional[Bool] = None" ; \
  } \
  \
  template <> \
  void CInterface::AttributePythonInterfaceIsDefinedDeclaration<CArray<T,7> >(ostream& oss, const string& className, const string& name) \
  { \
    oss << " : Optional[Bool] = None" ; \
  } 

  macro(bool)
  macro(double)
  macro(int)

#undef macro

#define macro(T,EXTENT)\
  template <> \
  void CInterface::AttributePythonInterfaceDeclaration<CArray<StdString,T> >(ostream& oss, const string& className, const string& name, bool isSet)\
  {\
    oss << " : Optional[String] = None" ; \
  }

  macro(1,":")
  macro(2,":,:")
  macro(3,":,:,:")
  macro(4,":,:,:,:")
  macro(5,":,:,:,:,:")
  macro(6,":,:,:,:,:,:")
  macro(7,":,:,:,:,:,:,:")

#undef macro

#define macro(T,EXTENT)\
  template <> \
  void CInterface::AttributePythonInterfaceIsDefinedDeclaration<CArray<StdString,T> >(ostream& oss, const string& className, const string& name)\
  {\
    oss << " : Optional[Bool] = None" ; \
  }

  macro(1,":")
  macro(2,":,:")
  macro(3,":,:,:")
  macro(4,":,:,:,:")
  macro(5,":,:,:,:,:")
  macro(6,":,:,:,:,:,:")
  macro(7,":,:,:,:,:,:,:")

#undef macro



  

#define macro(T) \
  template <>  \
  void CInterface::AttributeFortranInterfaceBody< CArray<T,1> >(ostream& oss, const string& className, const string& name) \
  {  \
    string name_tmp=name+"__tmp"; \
      \
    oss << "IF (PRESENT(" << name << "_)) THEN" << iendl; \
    if (!matchingTypeCFortran<T>())  \
    { \
      oss << "  ALLOCATE(" << name_tmp << "(SIZE(" << name << "_,1)))" << iendl; \
      oss << "  " << name_tmp << " = " << name << "_" << iendl; \
      oss << "  CALL xios_logical_to_bool_1d(" << name_tmp << ", SHAPE("<< name_tmp << "))" << iendl; \
      oss << "  CALL cxios_set_" << className << "_" << name << " &" << iendl; \
      oss << "(" << className << "_hdl%daddr, " << name_tmp << ", SHAPE(" << name << "_))" << iendl; \
    } \
    else { oss << "  CALL cxios_set_" << className << "_" << name << " &" << iendl; \
           oss << "(" << className << "_hdl%daddr, " << name << "_, SHAPE(" << name << "_))" << iendl; } \
    oss << "ENDIF"; \
  } \
 \
  template <>  \
  void CInterface::AttributeFortranInterfaceBody< CArray<T,2> >(ostream& oss, const string& className, const string& name) \
  {  \
    string name_tmp=name+"__tmp"; \
      \
    oss << "IF (PRESENT(" << name << "_)) THEN" << iendl; \
    if (!matchingTypeCFortran<T>())  \
    { \
      oss << "  ALLOCATE(" << name_tmp << "(SIZE(" << name << "_,1), SIZE(" << name << "_,2)))" << iendl; \
      oss << "  " << name_tmp << " = " << name << "_" << iendl; \
      oss << "  CALL xios_logical_to_bool_2d(" << name_tmp << ", SHAPE("<< name_tmp << "))" << iendl; \
      oss << "  CALL cxios_set_" << className << "_" << name << " &" << iendl; \
      oss << "(" << className << "_hdl%daddr, " << name_tmp << ", SHAPE(" << name << "_))" << iendl; \
    } \
    else { oss << "  CALL cxios_set_" << className << "_" << name << " &" << iendl; \
           oss << "(" << className << "_hdl%daddr, " << name << "_, SHAPE(" << name << "_))" << iendl; } \
    oss << "ENDIF"; \
  } \
  \
  template <>  \
  void CInterface::AttributeFortranInterfaceBody< CArray<T,3> >(ostream& oss, const string& className, const string& name) \
  {  \
    string name_tmp=name+"__tmp"; \
      \
    oss << "IF (PRESENT(" << name << "_)) THEN" << iendl; \
    if (!matchingTypeCFortran<T>())  \
    { \
      oss << "  ALLOCATE(" << name_tmp << "(SIZE(" << name << "_,1), SIZE(" << name << "_,2), SIZE(" << name << "_,3)))" << iendl; \
      oss << "  " << name_tmp << " = " << name << "_" << iendl; \
      oss << "  CALL xios_logical_to_bool_3d(" << name_tmp << ", SHAPE("<< name_tmp << "))" << iendl; \
      oss << "  CALL cxios_set_" << className << "_" << name << " &" << iendl; \
      oss << "(" << className << "_hdl%daddr, " << name_tmp << ", SHAPE(" << name << "_))" << iendl; \
    } \
    else { oss << "  CALL cxios_set_" << className << "_" << name << " &" << iendl; \
           oss << "(" << className << "_hdl%daddr, " << name << "_, SHAPE(" << name << "_))" << iendl; } \
    oss << "ENDIF"; \
  }\
  \
  template <>  \
  void CInterface::AttributeFortranInterfaceBody< CArray<T,4> >(ostream& oss, const string& className, const string& name) \
  {  \
    string name_tmp=name+"__tmp"; \
      \
    oss << "IF (PRESENT(" << name << "_)) THEN" << iendl; \
    if (!matchingTypeCFortran<T>())  \
    { \
      oss << "  ALLOCATE(" << name_tmp << "(SIZE(" << name << "_,1), SIZE(" << name << "_,2), SIZE(" << name << "_,3), &" << iendl; \
      oss << " SIZE(" << name << "_,4)))" << iendl; \
      oss << "  " << name_tmp << " = " << name << "_" << iendl; \
      oss << "  CALL xios_logical_to_bool_4d(" << name_tmp << ", SHAPE("<< name_tmp << "))" << iendl; \
      oss << "  CALL cxios_set_" << className << "_" << name << " &" << iendl; \
      oss << "(" << className << "_hdl%daddr, " << name_tmp << ", SHAPE(" << name << "_))" << iendl; \
    } \
    else { oss << "  CALL cxios_set_" << className << "_" << name << " &" << iendl; \
           oss << "(" << className << "_hdl%daddr, " << name << "_, SHAPE(" << name << "_))" << iendl; } \
    oss << "ENDIF"; \
  }\
  \
  template <>  \
  void CInterface::AttributeFortranInterfaceBody< CArray<T,5> >(ostream& oss, const string& className, const string& name) \
  {  \
    string name_tmp=name+"__tmp"; \
      \
    oss << "IF (PRESENT(" << name << "_)) THEN" << iendl; \
    if (!matchingTypeCFortran<T>())  \
    { \
      oss << "  ALLOCATE(" << name_tmp << "(SIZE(" << name << "_,1), SIZE(" << name << "_,2), SIZE(" << name << "_,3), &" << iendl; \
      oss << " SIZE(" << name << "_,4), SIZE(" << name << "_,5)))" << iendl; \
      oss << "  " << name_tmp << " = " << name << "_" << iendl; \
      oss << "  CALL xios_logical_to_bool_5d(" << name_tmp << ", SHAPE("<< name_tmp << "))" << iendl; \
      oss << "  CALL cxios_set_" << className << "_" << name << " &" << iendl; \
      oss << "(" << className << "_hdl%daddr, " << name_tmp << ", SHAPE(" << name << "_))" << iendl; \
    } \
    else { oss << "  CALL cxios_set_" << className << "_" << name << " &" << iendl; \
           oss << "(" << className << "_hdl%daddr, " << name << "_, SHAPE(" << name << "_))" << iendl; } \
    oss << "ENDIF"; \
  }\
  \
  template <>  \
  void CInterface::AttributeFortranInterfaceBody< CArray<T,6> >(ostream& oss, const string& className, const string& name) \
  {  \
    string name_tmp=name+"__tmp"; \
      \
    oss << "IF (PRESENT(" << name << "_)) THEN" << iendl; \
    if (!matchingTypeCFortran<T>())  \
    { \
      oss << "  ALLOCATE(" << name_tmp << "(SIZE(" << name << "_,1), SIZE(" << name << "_,2), SIZE(" << name << "_,3), &" << iendl; \
      oss << " SIZE(" << name << "_,4), SIZE(" << name << "_,5), SIZE(" << name << "_,6)))" << iendl; \
      oss << "  " << name_tmp << " = " << name << "_" << iendl; \
      oss << "  CALL xios_logical_to_bool_6d(" << name_tmp << ", SHAPE("<< name_tmp << "))" << iendl; \
      oss << "  CALL cxios_set_" << className << "_" << name << " &" << iendl; \
      oss << "(" << className << "_hdl%daddr, " << name_tmp << ", SHAPE(" << name << "_))" << iendl; \
    } \
    else { oss << "  CALL cxios_set_" << className << "_" << name << " &" << iendl; \
           oss << "(" << className << "_hdl%daddr, " << name << "_, SHAPE(" << name << "_))" << iendl; } \
    oss << "ENDIF"; \
  }\
  \
  template <>  \
  void CInterface::AttributeFortranInterfaceBody< CArray<T,7> >(ostream& oss, const string& className, const string& name) \
  {  \
    string name_tmp=name+"__tmp"; \
      \
    oss << "IF (PRESENT(" << name << "_)) THEN" << iendl; \
    if (!matchingTypeCFortran<T>())  \
    { \
      oss << "  ALLOCATE(" << name_tmp << "(SIZE(" << name << "_,1), SIZE(" << name << "_,2), SIZE(" << name << "_,3), &" << iendl; \
      oss << " SIZE(" << name << "_,4), SIZE(" << name << "_,5), SIZE(" << name << "_,6), &" << iendl; \
      oss << " SIZE(" << name << "_,7)))" << iendl; \
      oss << "  " << name_tmp << " = " << name << "_" << iendl; \
      oss << "  CALL xios_logical_to_bool_7d(" << name_tmp << ", SHAPE("<< name_tmp << "))" << iendl; \
      oss << "  CALL cxios_set_" << className << "_" << name << " &" << iendl; \
      oss << "(" << className << "_hdl%daddr, " << name_tmp << ", SHAPE(" << name << "_))" << iendl; \
    } \
    else { oss << "  CALL cxios_set_" << className << "_" << name << " &" << iendl; \
           oss << "(" << className << "_hdl%daddr, " << name << "_, SHAPE(" << name << "_))" << iendl; } \
    oss << "ENDIF"; \
  }

  macro(bool)
  macro(double)
  macro(int)

#undef macro


#define macro(T) \
  template <>  \
  void CInterface::AttributePythonInterfaceBody< CArray<T,1> >(ostream& oss, const string& className, const string& name, const string& pyName) \
  {  \
      string t = ""; \
      if (getStrPythonType<T>().compare("Double") != 0){ \
        t = getStrPythonType<T>(); \
      } \
      oss << "if " << name << "_ is not None:" << (iendl+=1); \
      oss << name << "_ = NpArray" << t << "(" << name << "_)" << iendl; \
      oss << name << "_c = " << name << "_._c_value" << iendl; \
      oss << "if len(" << name << "_.shape" << ") != 1 : " << (iendl+=1); \
      oss << "raise ValueError('The array dimension should be 1')" << (iendl -= 1); \
      oss << "else : " << (iendl += 1); \
      oss << "shape = ctypes.c_int * len(" << name << "_.shape)" << iendl; \
      oss << "shape_c = shape(*" << name << "_.shape)" << iendl; \
      oss << "lib.cxios_set_" << className << "_" << name; \
      oss << "(" << className << "_hdl, " << name << "_c, shape_c)" << (iendl -= 2); \
  } \
 \
 template <>  \
  void CInterface::AttributePythonInterfaceBody< CArray<T,2> >(ostream& oss, const string& className, const string& name, const string& pyName) \
  {  \
      string t = ""; \
      if (getStrPythonType<T>().compare("Double") != 0){ \
        t = getStrPythonType<T>(); \
      } \
      oss << "if " << name << "_ is not None:" << (iendl+=1); \
      oss << name << "_ = NpArray" << t << "(" << name << "_)" << iendl; \
      oss << name << "_c = " << name << "_._c_value" << iendl; \
      oss << "if len(" << name << "_.shape" << ") != 2 : " << (iendl+=1); \
      oss << "raise ValueError('The array dimension should be 2')" << (iendl -= 1); \
      oss << "else : " << (iendl += 1); \
      oss << "shape = ctypes.c_int * len(" << name << "_.shape)" << iendl; \
      oss << "shape_c = shape(*" << name << "_.shape)" << iendl; \
      oss << "lib.cxios_set_" << className << "_" << name; \
      oss << "(" << className << "_hdl, " << name << "_c, shape_c)" << (iendl -= 2); \
  } \
 \
 template <>  \
  void CInterface::AttributePythonInterfaceBody< CArray<T,3> >(ostream& oss, const string& className, const string& name, const string& pyName) \
  {  \
      string t = ""; \
      if (getStrPythonType<T>().compare("Double") != 0){ \
        t = getStrPythonType<T>(); \
      } \
      oss << "if " << name << "_ is not None:" << (iendl+=1); \
      oss << name << "_ = NpArray" << t << "(" << name << "_)" << iendl; \
      oss << name << "_c = " << name << "_._c_value" << iendl; \
      oss << "if len(" << name << "_.shape" << ") != 3 : " << (iendl+=1); \
      oss << "raise ValueError('The array dimension should be 3')" << (iendl -= 1); \
      oss << "else : " << (iendl += 1); \
      oss << "shape = ctypes.c_int * len(" << name << "_.shape)" << iendl; \
      oss << "shape_c = shape(*" << name << "_.shape)" << iendl; \
      oss << "lib.cxios_set_" << className << "_" << name; \
      oss << "(" << className << "_hdl, " << name << "_c, shape_c)" << (iendl -= 2); \
  } \
 \
 template <>  \
  void CInterface::AttributePythonInterfaceBody< CArray<T,4> >(ostream& oss, const string& className, const string& name, const string& pyName) \
  {  \
      string t = ""; \
      if (getStrPythonType<T>().compare("Double") != 0){ \
        t = getStrPythonType<T>(); \
      } \
      oss << "if " << name << "_ is not None:" << (iendl+=1); \
      oss << name << "_ = NpArray" << t << "(" << name << "_)" << iendl; \
      oss << name << "_c = " << name << "_._c_value" << iendl; \
      oss << "if len(" << name << "_.shape" << ") != 4 : " << (iendl+=1); \
      oss << "raise ValueError('The array dimension should be 4')" << (iendl -= 1); \
      oss << "else : " << (iendl += 1); \
      oss << "shape = ctypes.c_int * len(" << name << "_.shape)" << iendl; \
      oss << "shape_c = shape(*" << name << "_.shape)" << iendl; \
      oss << "lib.cxios_set_" << className << "_" << name; \
      oss << "(" << className << "_hdl, " << name << "_c, shape_c)" << (iendl -= 2); \
  } \
 \
 template <>  \
  void CInterface::AttributePythonInterfaceBody< CArray<T,5> >(ostream& oss, const string& className, const string& name, const string& pyName) \
  {  \
      string t = ""; \
      if (getStrPythonType<T>().compare("Double") != 0){ \
        t = getStrPythonType<T>(); \
      } \
      oss << "if " << name << "_ is not None:" << (iendl+=1); \
      oss << name << "_ = NpArray" << t << "(" << name << "_)" << iendl; \
      oss << name << "_c = " << name << "_._c_value" << iendl; \
      oss << "if len(" << name << "_.shape" << ") != 5 : " << (iendl+=1); \
      oss << "raise ValueError('The array dimension should be 5')" << (iendl -= 1); \
      oss << "else : " << (iendl += 1); \
      oss << "shape = ctypes.c_int * len(" << name << "_.shape)" << iendl; \
      oss << "shape_c = shape(*" << name << "_.shape)" << iendl; \
      oss << "lib.cxios_set_" << className << "_" << name; \
      oss << "(" << className << "_hdl, " << name << "_c, shape_c)" << (iendl -= 2); \
  } \
 \
 template <>  \
  void CInterface::AttributePythonInterfaceBody< CArray<T,6> >(ostream& oss, const string& className, const string& name, const string& pyName) \
  {  \
      string t = ""; \
      if (getStrPythonType<T>().compare("Double") != 0){ \
        t = getStrPythonType<T>(); \
      } \
      oss << "if " << name << "_ is not None:" << (iendl+=1); \
      oss << name << "_ = NpArray" << t << "(" << name << "_)" << iendl; \
      oss << name << "_c = " << name << "_._c_value" << iendl; \
      oss << "if len(" << name << "_.shape" << ") != 6 : " << (iendl+=1); \
      oss << "raise ValueError('The array dimension should be 6')" << (iendl -= 1); \
      oss << "else : " << (iendl += 1); \
      oss << "shape = ctypes.c_int * len(" << name << "_.shape)" << iendl; \
      oss << "shape_c = shape(*" << name << "_.shape)" << iendl; \
      oss << "lib.cxios_set_" << className << "_" << name; \
      oss << "(" << className << "_hdl, " << name << "_c, shape_c)" << (iendl -= 2); \
  } \
 \
 template <>  \
  void CInterface::AttributePythonInterfaceBody< CArray<T,7> >(ostream& oss, const string& className, const string& name, const string& pyName) \
  {  \
      string t = ""; \
      if (getStrPythonType<T>().compare("Double") != 0){ \
        t = getStrPythonType<T>(); \
      } \
      oss << "if " << name << "_ is not None:" << (iendl+=1); \
      oss << name << "_ = NpArray" << t << "(" << name << "_)" << iendl; \
      oss << name << "_c = " << name << "_._c_value" << iendl; \
      oss << "if len(" << name << "_.shape" << ") != 7 : " << (iendl+=1); \
      oss << "raise ValueError('The array dimension should be 7')" << (iendl -= 1); \
      oss << "else : " << (iendl += 1); \
      oss << "shape = ctypes.c_int * len(" << name << "_.shape)" << iendl; \
      oss << "shape_c = shape(*" << name << "_.shape)" << iendl; \
      oss << "lib.cxios_set_" << className << "_" << name; \
      oss << "(" << className << "_hdl, " << name << "_c, shape_c)" << (iendl -= 2); \
  }
  

  macro(bool)
  macro(double)
  macro(int)

#undef macro

#define macro(T) \
  template <>  \
  void CInterface::AttributePythonInterfaceGetBody< CArray<T,1> >(ostream& oss, const string& className, const string& name) \
  {  \
      oss << "if " << name << "_ is not None:" << (iendl+=1); \
      oss << "if " << name << "_.shape_is_needed: " << (iendl+=1); \
      oss << "shape_c = (ctypes.c_int * 1)()" << iendl; \
      oss << "lib.cxios_" << className << "_" << name << "_shape(" << className << "_hdl, shape_c)" << iendl; \
      oss << name << "_.arr = np.zeros(shape_c[0], order = 'F')" << iendl; \
      oss << "lib.cxios_get_" << className << "_" << name << "(" << className << "_hdl, " << name << "_._c_value, shape_c)" << (iendl-=1); \
      oss << "else: " << (iendl+=1); \
      oss << name << "_c = " << name << "_._c_value" << iendl; \
      oss << "if len(" << name << "_.shape" << ") != 1 : " << (iendl+=1); \
      oss << "raise ValueError('The array dimension should be 1')" << (iendl -= 1); \
      oss << "else : " << (iendl += 1); \
      oss << "shape_c = NpArrayInt(" << name << "_.shape)._c_value" << iendl; \
      oss << "lib.cxios_get_" << className << "_" << name; \
      oss << "(" << className << "_hdl, " << name << "_c, shape_c)" << (iendl -= 3); \
  } \
 \
 template <>  \
  void CInterface::AttributePythonInterfaceGetBody< CArray<T,2> >(ostream& oss, const string& className, const string& name) \
    {  \
      oss << "if " << name << "_ is not None:" << (iendl+=1); \
      oss << "if " << name << "_.shape_is_needed: " << (iendl+=1); \
      oss << "shape_c = (ctypes.c_int * 2)()" << iendl; \
      oss << "lib.cxios_" << className << "_" << name << "_shape(" << className << "_hdl, shape_c)" << iendl; \
      oss << name << "_.arr = np.zeros((shape_c[0], shape_c[1]) , order = 'F')" << iendl; \
      oss << "lib.cxios_get_" << className << "_" << name << "(" << className << "_hdl, " << name << "_._c_value, shape_c)" << (iendl-=1); \
      oss << "else: " << (iendl+=1); \
      oss << name << "_c = " << name << "_._c_value" << iendl; \
      oss << "if len(" << name << "_.shape" << ") != 2 : " << (iendl+=1); \
      oss << "raise ValueError('The array dimension should be 2')" << (iendl -= 1); \
      oss << "else : " << (iendl += 1); \
      oss << "shape_c = NpArrayInt(" << name << "_.shape)._c_value" << iendl; \
      oss << "lib.cxios_get_" << className << "_" << name; \
      oss << "(" << className << "_hdl, " << name << "_c, shape_c)" << (iendl -= 3); \
  } \
 \
 template <>  \
  void CInterface::AttributePythonInterfaceGetBody< CArray<T,3> >(ostream& oss, const string& className, const string& name) \
    {  \
      oss << "if " << name << "_ is not None:" << (iendl+=1); \
      oss << "if " << name << "_.shape_is_needed: " << (iendl+=1); \
      oss << "shape_c = (ctypes.c_int * 3)()" << iendl; \
      oss << "lib.cxios_" << className << "_" << name << "_shape(" << className << "_hdl, shape_c)" << iendl; \
      oss << name << "_.arr = np.zeros((shape_c[0], shape_c[1], shape_c[2]) , order = 'F')" << iendl; \
      oss << "lib.cxios_get_" << className << "_" << name << "(" << className << "_hdl, " << name << "_._c_value, shape_c)" << (iendl-=1); \
      oss << "else: " << (iendl+=1); \
      oss << name << "_c = " << name << "_._c_value" << iendl; \
      oss << "if len(" << name << "_.shape" << ") != 3 : " << (iendl+=1); \
      oss << "raise ValueError('The array dimension should be 3')" << (iendl -= 1); \
      oss << "else : " << (iendl += 1); \
      oss << "shape_c = NpArrayInt(" << name << "_.shape)._c_value" << iendl; \
      oss << "lib.cxios_get_" << className << "_" << name; \
      oss << "(" << className << "_hdl, " << name << "_c, shape_c)" << (iendl -= 3); \
  } \
 \
 template <>  \
  void CInterface::AttributePythonInterfaceGetBody< CArray<T,4> >(ostream& oss, const string& className, const string& name) \
    {  \
      oss << "if " << name << "_ is not None:" << (iendl+=1); \
      oss << "if " << name << "_.shape_is_needed: " << (iendl+=1); \
      oss << "shape_c = (ctypes.c_int * 4)()" << iendl; \
      oss << "lib.cxios_" << className << "_" << name << "_shape(" << className << "_hdl, shape_c)" << iendl; \
      oss << name << "_.arr = np.zeros((shape_c[0], shape_c[1], shape_c[2], shape_c[3]) , order = 'F')" << iendl; \
      oss << "lib.cxios_get_" << className << "_" << name << "(" << className << "_hdl, " << name << "_._c_value, shape_c)" << (iendl-=1); \
      oss << "else: " << (iendl+=1); \
      oss << name << "_c = " << name << "_._c_value" << iendl; \
      oss << "if len(" << name << "_.shape" << ") != 4 : " << (iendl+=1); \
      oss << "raise ValueError('The array dimension should be 4')" << (iendl -= 1); \
      oss << "else : " << (iendl += 1); \
      oss << "shape_c = NpArrayInt(" << name << "_.shape)._c_value" << iendl; \
      oss << "lib.cxios_get_" << className << "_" << name; \
      oss << "(" << className << "_hdl, " << name << "_c, shape_c)" << (iendl -= 3); \
  } \
 \
 template <>  \
  void CInterface::AttributePythonInterfaceGetBody< CArray<T,5> >(ostream& oss, const string& className, const string& name) \
    {  \
      oss << "if " << name << "_ is not None:" << (iendl+=1); \
      oss << "if " << name << "_.shape_is_needed: " << (iendl+=1); \
      oss << "shape_c = (ctypes.c_int * 5)()" << iendl; \
      oss << "lib.cxios_" << className << "_" << name << "_shape(" << className << "_hdl, shape_c)" << iendl; \
      oss << name << "_.arr = np.zeros((shape_c[0], shape_c[1], shape_c[2], shape_c[3], shape_c[4]) , order = 'F')" << iendl; \
      oss << "lib.cxios_get_" << className << "_" << name << "(" << className << "_hdl, " << name << "_._c_value, shape_c)" << (iendl-=1); \
      oss << "else: " << (iendl+=1); \
      oss << name << "_c = " << name << "_._c_value" << iendl; \
      oss << "if len(" << name << "_.shape" << ") != 5 : " << (iendl+=1); \
      oss << "raise ValueError('The array dimension should be 5')" << (iendl -= 1); \
      oss << "else : " << (iendl += 1); \
      oss << "shape_c = NpArrayInt(" << name << "_.shape)._c_value" << iendl; \
      oss << "lib.cxios_get_" << className << "_" << name; \
      oss << "(" << className << "_hdl, " << name << "_c, shape_c)" << (iendl -= 3); \
  } \
 \
 template <>  \
  void CInterface::AttributePythonInterfaceGetBody< CArray<T,6> >(ostream& oss, const string& className, const string& name) \
    {  \
      oss << "if " << name << "_ is not None:" << (iendl+=1); \
      oss << "if " << name << "_.shape_is_needed: " << (iendl+=1); \
      oss << "shape_c = (ctypes.c_int * 6)()" << iendl; \
      oss << "lib.cxios_" << className << "_" << name << "_shape(" << className << "_hdl, shape_c)" << iendl; \
      oss << name << "_.arr = np.zeros((shape_c[0], shape_c[1], shape_c[2], shape_c[3], shape_c[4], shape_c[5]) , order = 'F')" << iendl; \
      oss << "lib.cxios_get_" << className << "_" << name << "(" << className << "_hdl, " << name << "_._c_value, shape_c)" << (iendl-=1); \
      oss << "else: " << (iendl+=1); \
      oss << name << "_c = " << name << "_._c_value" << iendl; \
      oss << "if len(" << name << "_.shape" << ") != 6 : " << (iendl+=1); \
      oss << "raise ValueError('The array dimension should be 6')" << (iendl -= 1); \
      oss << "else : " << (iendl += 1); \
      oss << "shape_c = NpArrayInt(" << name << "_.shape)._c_value" << iendl; \
      oss << "lib.cxios_get_" << className << "_" << name; \
      oss << "(" << className << "_hdl, " << name << "_c, shape_c)" << (iendl -= 3); \
  } \
 \
 template <>  \
  void CInterface::AttributePythonInterfaceGetBody< CArray<T,7> >(ostream& oss, const string& className, const string& name) \
    {  \
      oss << "if " << name << "_ is not None:" << (iendl+=1); \
      oss << "if " << name << "_.shape_is_needed: " << (iendl+=1); \
      oss << "shape_c = (ctypes.c_int * 7)()" << iendl; \
      oss << "lib.cxios_" << className << "_" << name << "_shape(" << className << "_hdl, shape_c)" << iendl; \
      oss << name << "_.arr = np.zeros((shape_c[0], shape_c[1], shape_c[2], shape_c[3], shape_c[4], shape_c[5], shape_c[6]) , order = 'F')" << iendl; \
      oss << "lib.cxios_get_" << className << "_" << name << "(" << className << "_hdl, " << name << "_._c_value, shape_c)" << (iendl-=1); \
      oss << "else: " << (iendl+=1); \
      oss << name << "_c = " << name << "_._c_value" << iendl; \
      oss << "if len(" << name << "_.shape" << ") != 7 : " << (iendl+=1); \
      oss << "raise ValueError('The array dimension should be 7')" << (iendl -= 1); \
      oss << "else : " << (iendl += 1); \
      oss << "shape_c = NpArrayInt(" << name << "_.shape)._c_value" << iendl; \
      oss << "lib.cxios_get_" << className << "_" << name; \
      oss << "(" << className << "_hdl, " << name << "_c, shape_c)" << (iendl -= 3); \
  } 
  

  macro(bool)
  macro(double)
  macro(int)

#undef macro

#define macro(T)\
  template <>\
  void CInterface::AttributeFortranInterfaceBody< CArray<StdString,T> >(ostream& oss, const string& className, const string& name)\
  {\
     oss << "IF (PRESENT(" << name << "_)) THEN" << iendl; \
     oss << "  CALL cxios_set_" << className << "_" << name << " &" << iendl; \
     oss << "(" << className << "_hdl%daddr, " << name <<"_, LEN("<<name<<"_), LEN_TRIM("<<name<< "_), SHAPE(" << name << "_))" << iendl; \
     oss << "ENDIF"; \
  }

  macro(1)
  macro(2)
#undef macro

#define macro(T)\
  template <>\
  void CInterface::AttributePythonInterfaceBody< CArray<StdString,T> >(ostream& oss, const string& className, const string& name, const string& pyName)\
  {\
    oss << "#CArray<StdString, T> !!" << iendl; \
    oss << "if " << name <<  "_ is not None:" << iendl << (iendl+=1); \
    oss << name << "_c = " << name << "_._c_value" << iendl; \
    oss << "lib.cxios_set_" << className << "_" << name; \
    oss << "(" << className << "_hdl, " << name << "_c)" << iendl << (iendl -= 1); \
  }

  macro(1)
  macro(2)
#undef macro

#define macro(T)\
  template <>\
  void CInterface::AttributePythonInterfaceGetBody< CArray<StdString,T> >(ostream& oss, const string& className, const string& name)\
  {\
    oss << "if " << name <<  "_ is not None:" << iendl << (iendl+=1); \
    oss << name << "_c = " << name << "_._c_value" << iendl; \
    oss << "lib.cxios_get_" << className << "_" << name; \
    oss << "(" << className << "_hdl, " << name << "_c)" << iendl << (iendl -= 1); \
  }

  macro(1)
  macro(2)
#undef macro

#define macro(T) \
  template <>  \
  void CInterface::AttributeFortranInterfaceGetBody< CArray<T,1> >(ostream& oss, const string& className, const string& name) \
  {  \
    string name_tmp=name+"__tmp"; \
      \
    oss << "IF (PRESENT(" << name << "_)) THEN" << iendl; \
    if (!matchingTypeCFortran<T>())  \
    { \
      oss << "  ALLOCATE(" << name_tmp << "(SIZE(" << name << "_,1)))" << iendl; \
      oss << "  CALL cxios_get_" << className << "_" << name << " &" << iendl; \
      oss << "(" << className << "_hdl%daddr, " << name_tmp << ", SHAPE(" << name << "_))" << iendl; \
      oss << "  CALL xios_bool_to_logical_1d(" << name_tmp << ", SHAPE("<< name_tmp << "))" << iendl; \
      oss << "  " << name << "_ = " << name_tmp << iendl; \
    } \
    else { oss << "  CALL cxios_get_" << className << "_" << name << " &" << iendl; \
           oss << "(" << className << "_hdl%daddr, " << name << "_, SHAPE(" << name << "_))" << iendl; } \
    oss << "ENDIF"; \
  } \
 \
  template <>  \
  void CInterface::AttributeFortranInterfaceGetBody< CArray<T,2> >(ostream& oss, const string& className, const string& name) \
  {  \
    string name_tmp=name+"__tmp"; \
      \
    oss << "IF (PRESENT(" << name << "_)) THEN" << iendl; \
    if (!matchingTypeCFortran<T>())  \
    { \
      oss << "  ALLOCATE(" << name_tmp << "(SIZE(" << name << "_,1), SIZE(" << name << "_,2)))" << iendl; \
      oss << "  CALL cxios_get_" << className << "_" << name << " &" << iendl; \
      oss << "(" << className << "_hdl%daddr, " << name_tmp << ", SHAPE(" << name << "_))" << iendl; \
      oss << "  CALL xios_bool_to_logical_2d(" << name_tmp << ", SHAPE("<< name_tmp << "))" << iendl; \
      oss << "  " << name << "_ = " << name_tmp << iendl; \
    } \
    else { oss << "  CALL cxios_get_" << className << "_" << name << " &" << iendl; \
           oss << "(" << className << "_hdl%daddr, " << name << "_, SHAPE(" << name << "_))" << iendl; } \
    oss << "ENDIF"; \
  } \
 \
  template <>  \
  void CInterface::AttributeFortranInterfaceGetBody< CArray<T,3> >(ostream& oss, const string& className, const string& name) \
  {  \
    string name_tmp=name+"__tmp"; \
      \
    oss << "IF (PRESENT(" << name << "_)) THEN" << iendl; \
    if (!matchingTypeCFortran<T>())  \
    { \
      oss << "  ALLOCATE(" << name_tmp << "(SIZE(" << name << "_,1), SIZE(" << name << "_,2), SIZE(" << name << "_,3)))" << iendl; \
      oss << "  CALL cxios_get_" << className << "_" << name << " &" << iendl; \
      oss << "(" << className << "_hdl%daddr, " << name_tmp << ", SHAPE(" << name << "_))" << iendl; \
      oss << "  CALL xios_bool_to_logical_3d(" << name_tmp << ", SHAPE("<< name_tmp << "))" << iendl; \
      oss << "  " << name << "_ = " << name_tmp << iendl; \
      } \
    else { oss << "  CALL cxios_get_" << className << "_" << name << " &" << iendl; \
           oss << "(" << className << "_hdl%daddr, " << name << "_, SHAPE(" << name << "_))" << iendl; } \
    oss << "ENDIF"; \
  } \
 \
  template <>  \
  void CInterface::AttributeFortranInterfaceGetBody< CArray<T,4> >(ostream& oss, const string& className, const string& name) \
  {  \
    string name_tmp=name+"__tmp"; \
      \
    oss << "IF (PRESENT(" << name << "_)) THEN" << iendl; \
    if (!matchingTypeCFortran<T>())  \
    { \
      oss << "  ALLOCATE(" << name_tmp << "(SIZE(" << name << "_,1), SIZE(" << name << "_,2), SIZE(" << name << "_,3), &" << iendl; \
      oss << " SIZE(" << name << "_,4)))" << iendl; \
      oss << "  CALL cxios_get_" << className << "_" << name << " &" << iendl; \
      oss << "(" << className << "_hdl%daddr, " << name_tmp << ", SHAPE(" << name << "_))" << iendl; \
      oss << "  CALL xios_bool_to_logical_4d(" << name_tmp << ", SHAPE("<< name_tmp << "))" << iendl; \
      oss << "  " << name << "_ = " << name_tmp << iendl; \
      } \
    else { oss << "  CALL cxios_get_" << className << "_" << name << " &" << iendl; \
           oss << "(" << className << "_hdl%daddr, " << name << "_, SHAPE(" << name << "_))" << iendl; }\
    oss << "ENDIF"; \
  } \
 \
  template <>  \
  void CInterface::AttributeFortranInterfaceGetBody< CArray<T,5> >(ostream& oss, const string& className, const string& name) \
  {  \
    string name_tmp=name+"__tmp"; \
      \
    oss << "IF (PRESENT(" << name << "_)) THEN" << iendl; \
    if (!matchingTypeCFortran<T>())  \
    { \
      oss << "  ALLOCATE(" << name_tmp << "(SIZE(" << name << "_,1), SIZE(" << name << "_,2), SIZE(" << name << "_,3), &" << iendl; \
      oss << " SIZE(" << name << "_,4), SIZE(" << name << "_,5)))" << iendl; \
      oss << "  CALL cxios_get_" << className << "_" << name << " &" << iendl; \
      oss << "(" << className << "_hdl%daddr, " << name_tmp << ", SHAPE(" << name << "_))" << iendl; \
      oss << "  CALL xios_bool_to_logical_5d(" << name_tmp << ", SHAPE("<< name_tmp << "))" << iendl; \
      oss << "  " << name << "_ = " << name_tmp << iendl; \
      } \
    else { oss << "  CALL cxios_get_" << className << "_" << name << " &" << iendl; \
           oss << "(" << className << "_hdl%daddr, " << name << "_, SHAPE(" << name << "_))" << iendl; } \
    oss << "ENDIF"; \
  }\
 \
  template <>  \
  void CInterface::AttributeFortranInterfaceGetBody< CArray<T,6> >(ostream& oss, const string& className, const string& name) \
  {  \
    string name_tmp=name+"__tmp"; \
      \
    oss << "IF (PRESENT(" << name << "_)) THEN" << iendl; \
    if (!matchingTypeCFortran<T>())  \
    { \
      oss << "  ALLOCATE(" << name_tmp << "(SIZE(" << name << "_,1), SIZE(" << name << "_,2), SIZE(" << name << "_,3), &" << iendl; \
      oss << " SIZE(" << name << "_,4), SIZE(" << name << "_,5), SIZE(" << name << "_,6)))" << iendl; \
      oss << "  CALL cxios_get_" << className << "_" << name << " &" << iendl; \
      oss << "(" << className << "_hdl%daddr, " << name_tmp << ", SHAPE(" << name << "_))" << iendl; \
      oss << "  CALL xios_bool_to_logical_6d(" << name_tmp << ", SHAPE("<< name_tmp << "))" << iendl; \
      oss << "  " << name << "_ = " << name_tmp << iendl; \
      } \
    else { oss << "  CALL cxios_get_" << className << "_" << name << " &" << iendl; \
           oss << "(" << className << "_hdl%daddr, " << name << "_, SHAPE(" << name << "_))" << iendl; } \
    oss << "ENDIF"; \
  } \
 \
  template <>  \
  void CInterface::AttributeFortranInterfaceGetBody< CArray<T,7> >(ostream& oss, const string& className, const string& name) \
  {  \
    string name_tmp=name+"__tmp"; \
      \
    oss << "IF (PRESENT(" << name << "_)) THEN" << iendl; \
    if (!matchingTypeCFortran<T>())  \
    { \
      oss << "  ALLOCATE(" << name_tmp << "(SIZE(" << name << "_,1), SIZE(" << name << "_,2), SIZE(" << name << "_,3), &" << iendl; \
      oss << " SIZE(" << name << "_,4), SIZE(" << name << "_,5), SIZE(" << name << "_,6), &" << iendl; \
      oss << " SIZE(" << name << "_,7)))" << iendl; \
      oss << "  CALL cxios_get_" << className << "_" << name << " &" << iendl; \
      oss << "(" << className << "_hdl%daddr, " << name_tmp << ", SHAPE(" << name << "_))" << iendl; \
      oss << "  CALL xios_bool_to_logical_7d(" << name_tmp << ", SHAPE("<< name_tmp << "))" << iendl; \
      oss << "  " << name << "_ = " << name_tmp << iendl; \
      } \
    else { oss << "  CALL cxios_get_" << className << "_" << name << " &" << iendl; \
           oss << "(" << className << "_hdl%daddr, " << name << "_, SHAPE(" << name << "_))" << iendl; } \
    oss << "ENDIF"; \
  }

  macro(bool)
  macro(double)
  macro(int)

#undef macro

#define macro(T)\
  template <> \
  void CInterface::AttributeFortranInterfaceGetBody< CArray<StdString,T> >(ostream& oss, const string& className, const string& name)\
  {\
    oss << "IF (PRESENT(" << name << "_)) THEN" << iendl; \
    oss << "  CALL cxios_get_" << className << "_" << name << " &" << iendl; \
    oss << "(" << className << "_hdl%daddr, " << name << "_, LEN("<<name<<"_), SHAPE(" << name << "_))" << iendl; \
    oss << "ENDIF"; \
  }
  macro(1)
  macro(2)
  macro(3)
  macro(4)
  macro(5)
  macro(6)
  macro(7)

#undef macro

}
#endif
