#ifndef __XIOS_CFunction__
#define __XIOS_CFunction__

#include "xios_spl.hpp"
#include "group_factory.hpp"
#include "filter_graph_types.hpp"
#include "declare_group.hpp"
#include "attribute_array.hpp"
#include "date.hpp"


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
    This class describes function in xml file.
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
      const string& getExpr(void);
      const std::vector<std::shared_ptr<xios::IFilterExprNode>>& getTreeFromExpr();

      size_t getNumArgin();
      size_t getNumArgout();
      std::vector<std::string> getArgin(void) ;
      std::vector<std::string> getArgout(void);
      size_t getArgoutIdx(const SArg& arg);
      size_t getArgoutIdx(std::string argoutName);

      const string& getPySrc(void);
      std::vector<CField*> getFilterFields();
      std::vector<CVariable*> getFilterVariables();

      std::string getOffload();
      bool isOffload();
      bool isOffloaded(); 
      bool isEnabled();
      void getOffloadServicesId(const string& defaultPoolOffloadId_, const string& defaultOffloadId_, string& poolOffloadId, string& offloadId);
      CContextClient* getContextClient();
      std::vector<CField*> getOffloadFieldOuts();

      CDuration getOffset();



      // Setters
      void setContextClient(const string& defaultPoolId, const string& defaultServiceId, int partitionId);
      void setContextClient(CContextClient* newContextClient);
      void setEnabled();
      void setIsOffloaded();


      void addFilterArgin(NodeId nodeId, CField* field, size_t idx);
      void addFilterArgin(NodeId nodeId, CVariable* var, size_t idx);
      void addOffloadFieldOut(CField* offloadFieldOut);

      struct SArgIn
      {
        enum Type
        {
          Variable,
          Field
        };

        Type type;

        union
        {
          CVariable* var;
          CField* field;
        };

        SArgIn() : type(Field), field(nullptr) {}

        SArgIn(CVariable* v)
        : type(Variable), var(v)
        {}

        SArgIn(CField* f)
        : type(Field), field(f)
        {}

        bool isVariable() const;
        bool isField() const;
        const std::string& getId() const;

      };


      //Server related methods
      void sendFunctionToServer();
      void sendAddField(const string& id, CContextClient* client);   
      void sendAddVariable(const string& id, CContextClient* client);   
      static bool dispatchEvent(CContext* context, CEventServer& event);
      static void recvAddField(CContext* context, CEventServer& event);
      static void recvAddVariable(CContext* context, CEventServer& event);
      void recvAddField(CBufferIn& buffer);
      void recvAddVariable(CBufferIn& buffer);
      CField* addField(const string& id = "");
      CVariable* addVariable(const string& id = "");
      void setVirtualFieldGroup(CFieldGroup* newVFieldGroup);
      void setVirtualVariableGroup(CVariableGroup* newVVariableGroup);
      const std::vector<SArgIn>& getArgs(NodeId nodeId) const;


    private:

      std::string exprContent_;                                  // Function Expression
      int numArgin_;                                             // Number of argin
      int numArgout_;                                            // Number of argout
      std::vector<std::string> arginContent_;                    // Vector of argin names
      std::vector<std::string> argoutContent_;                   // Vector of argout names
      std::string pySrcContent_;                                 // Function python src file
      std::string offload_;                                      // Offload service name
      bool isOffloaded_;                                         // True if this function is offloaded
      std::vector<CField*> offloadFieldOuts_;                    // Vector of outgoing fields that will be sent to server for offload
      bool enabled_;                                             // True only if this function is used in the workflow
      CDuration offset_;                                         // Offset on the reception

      std::map<NodeId, std::vector<SArgIn>> filterArginsMap_;      


      std::vector<std::shared_ptr<xios::IFilterExprNode>> expr_; // Vector of call tree associated to the function expression

      CContextClient* client_;                                   
      std::set<CContextClient*> sendFunctionToServer_done_ ;

      CFieldGroup* vFieldGroup_;
      CVariableGroup* vVariableGroup_;

    
  };

  DECLARE_GROUP(CFunction);
}

#endif // __XIOS_CFunction__
