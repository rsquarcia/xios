#include "generate_interface_impl.hpp"

namespace xios
{

#define macro(T) \
  template void CInterface::AttributeCInterface<T>(ostream& oss,const string& className,const string& name) ; \
  template void CInterface::AttributeFortran2003Interface<T>(ostream& oss,const string& className,const string& name) ; \
  template void CInterface::AttributeFortranInterfaceDeclaration<T>(ostream& oss,const string& className,const string& name) ; \
  template void CInterface::AttributePythonInterfaceDeclaration<T>(ostream& oss,const string& className,const string& name, bool isSet) ; \
  template void CInterface::AttributePythonInterfaceIsDefinedDeclaration<T>(ostream& oss,const string& className,const string& name) ; \
  template void CInterface::AttributeFortranInterfaceGetDeclaration<T>(ostream& oss,const string& className,const string& name) ; \
  template void CInterface::AttributeFortranInterfaceBody<T>(ostream& oss,const string& className,const string& name) ; \
  template void CInterface::AttributePythonInterfaceBody<T>(ostream& oss,const string& className,const string& name, const string& pyName) ; \
  template void CInterface::AttributeFortranInterfaceGetBody<T>(ostream& oss,const string& className,const string& name) ; \
  template void CInterface::AttributePythonInterfaceGetBody<T>(ostream& oss,const string& className,const string& name) ; \
  template void CInterface::AttributePythonInterfaceCArgs<T>(ostream& oss,const string& className,const string& name, const string&, const string&) ; \
  template void CInterface::AttributePythonInterfaceCRes<T>(ostream& oss,const string& className,const string& name, const string&) ; \
  template void CInterface::AttributeObjPythonInterfaceBody<T>(ostream& oss,const string& className, const string& name) ; \
  template string CInterface::getStrFortranType<T>(void) ; \
  template string CInterface::getStrPythonType<T>(void) ; \
  template string CInterface::getStrPythonCType<T>(void) ; \
  template string CInterface::getStrPythonNativeType<T>(void) ; \
  template string CInterface::getStrFortranKind<T>(void) ; \
  template string CInterface::getStrFortranKindC<T>(void) ; \
  template bool CInterface::matchingTypeCFortran<T>(void) ; 
  
  
  macro(bool)
  macro(int)
  macro(double)
  macro(CDate)
  macro(CDuration)
}
