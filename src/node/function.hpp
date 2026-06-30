#ifndef __XIOS_CFunction__
#define __XIOS_CFunction__

#include "xios_spl.hpp"
#include "group_factory.hpp"
#include "declare_group.hpp"
#include "attribute_array.hpp"
#include "filter_expr_node.hpp"


namespace xios
{
  class CFunctionGroup;
  class CFunction;
  class CFunctionAttributes;
  class IFilterExprNode;
  class CContext ;
  class CField;
  class CFieldGroup;
  class CVariable;
  class CVariableGroup;
  class CFilter;

  /// Declare/Define CFunctionAttribute from .conf
  BEGIN_DECLARE_ATTRIBUTE_MAP(CFunction)
# include "function_attribute.conf"
  END_DECLARE_ATTRIBUTE_MAP(CFunction)

  ///--------------------------------------------------------------
  /*!
   \class CFunction
   This class describe the function element.
   The class contains all the nessceary information to describe an XIOS function, 
   it allows user to define itself a combination of arithmetic filters associated with :
   id, argins, argouts and use it along the XIOS workflow.
   */

  class CFunction
    : public CObjectTemplate<CFunction>
    , public CFunctionAttributes

  {
    public:

      typedef CObjectTemplate<CFunction> SuperClass;
      typedef CFunctionAttributes SuperClassAttribute;
      typedef CFunctionAttributes RelAttributes;
      typedef CFunctionGroup      RelGroup; 

      enum EEventId
        {
          EVENT_ID_COLLECTIVE=100,
          EVENT_ID_ADD_FIELD, EVENT_ID_ADD_FIELD_GROUP, EVENT_ID_ADD_VARIABLE,
          EVENT_ID_ADD_VARIABLE_GROUP, EVENT_ID_CREATE_ENABLED_FIELDS,
          EVENT_ID_NO_COLLECTIVE=1000,
        };

      // Constructors
      CFunction(CContext* context);
      explicit CFunction(CContext* context, const StdString& id);

      // Destructor
      virtual ~CFunction(void) {}

      // Static getters
      static StdString GetName(void);
      static StdString GetDefName(void);
      static ENodeType GetType(void);

      // Getters
      const std::vector<std::shared_ptr<xios::IFilterExprNode>>& getTreeFromExpr();
      size_t getNumArgin();
      size_t getNumArgout();
      const string& getExpr(void);
      std::vector<std::string> getArgin(void) ;
      std::vector<std::string> getArgout(void);
      size_t getArgoutIdx(const SArg& arg);
      size_t getArgoutIdx(std::string argoutName);

    private:

      std::string exprContent_;                                  // Function Expression
      int numArgin_;                                             // Number of argin
      int numArgout_;                                            // Number of argout
      std::vector<std::string> arginContent_;                    // Vector of argin names
      std::vector<std::string> argoutContent_;                   // Vector of argout names
      std::vector<std::shared_ptr<xios::IFilterExprNode>> expr_; // Vector of call tree associated to the function expression

  };

  DECLARE_GROUP(CFunction);
}

#endif // __XIOS_CFunction__
