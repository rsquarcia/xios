#include "attribute.hpp"
#include "base_type.hpp"
#include "generate_interface.hpp"


namespace xios
{

      const StdString CAttribute::resetInheritanceStr("_reset_") ;

      /// ////////////////////// Définitions ////////////////////// ///
      CAttribute::CAttribute(const StdString & id)
         : CObject(id), CBaseType(), _canInherite(true)
//         , value()
      { /* Ne rien faire de plus */ }
/*
*/      
      CAttribute::~CAttribute(void)
      { /* Ne rien faire de plus */ }
      
      ///--------------------------------------------------------------

      const StdString & CAttribute::getName(void) const
      { 
         return (this->getId()); 
      }
      
      StdString CAttribute::getPyName(void) const
      {
          string s = this->getId();
          stringstream ss(s);
          string token;
          string result;

          while (getline(ss, token, '_')) {
              if (token.empty()) continue;
              result += toupper(token[0]);
              for (size_t i = 1; i < token.size(); ++i) {
                  result += tolower(token[i]);
              }
          }

          return result;
      }


   
      void CAttribute::generateCInterfaceIsDefined(ostream& oss, const string& className)
      {
        CInterface::AttributeIsDefinedCInterface(oss, className, this->getName()) ;
      }
      
      void CAttribute::generateFortran2003InterfaceIsDefined(ostream& oss, const string& className)
      {
        CInterface::AttributeIsDefinedFortran2003Interface(oss, className, this->getName()) ;
      }
      
      
      void CAttribute::generateFortranInterfaceIsDefinedDeclaration_(ostream& oss,const string& className)
      {
        CInterface::AttributeFortranInterfaceIsDefinedDeclaration(oss, className, this->getName()+"_") ;
      }

      void CAttribute::generateFortranInterfaceIsDefinedDeclaration(ostream& oss,const string& className)
      {
        CInterface::AttributeFortranInterfaceIsDefinedDeclaration(oss, className, this->getName()) ;
      }

      void CAttribute::generateFortranInterfaceIsDefinedBody_(ostream& oss,const string& className)
      {
        CInterface::AttributeFortranInterfaceIsDefinedBody(oss, className, this->getName()) ;
      }
      
      void CAttribute::generatePythonInterfaceIsDefinedBody_(ostream& oss,const string& className)
      {
        CInterface::AttributePythonInterfaceIsDefinedBody(oss, className, this->getName()) ;
      }

      ///--------------------------------------------------------------

      CMessage& operator<<(CMessage& msg,CAttribute& type)
      {
        msg.push(type) ;
        return msg ;
      }

     CMessage& operator<<(CMessage& msg, const CAttribute& type)
     {
//       msg.push(*type.clone()) ;
       return msg ;
     }
 
      CBufferOut& operator<<(CBufferOut& buffer, CAttribute& type)
     {
    
       if (!type.toBuffer(buffer)) ERROR("CBufferOut& operator<<(CBufferOut& buffer, CAttribute& type)",
                                         << "Not enough free space in buffer to queue the attribute.");
      return buffer ;
     }
     
     CBufferIn& operator>>(CBufferIn& buffer, CAttribute& type)
     {
    
       if (!type.fromBuffer(buffer)) ERROR("CBufferInt& operator>>(CBufferIn& buffer, CAttribute& type)",
                                           << "Not enough data in buffer to unqueue the attribute.");
       return buffer ;
     }

 
} // namespace xios
