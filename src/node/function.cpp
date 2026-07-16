#include "function.hpp"
#include "filter_expr_node.hpp"
#include "lex_parser.hpp"
#include "field.hpp"
#include "variable.hpp"
#include "garbage_collector.hpp"
#include "output_pin.hpp"
#include "embedded_filter.hpp"
#include "filter.hpp"
#include "context.hpp"
#include "context_client.hpp"
#include "string_tools.hpp"
#include "services_manager.hpp"



namespace xios
{

  // Constructors 
  CFunction::CFunction(CContext* context)
    : CObjectTemplate<CFunction>(context)
    , CFunctionAttributes()
    , numArgout_(0)
    , numArgin_(0)
    , exprContent_("")
    , pySrcContent_("")
    , offload_("")
    , enabled_(false)
  {
    setVirtualFieldGroup(CFieldGroup::create(context_, getId() + "_virtual_field_group"));
    setVirtualVariableGroup(CVariableGroup::create(context_, getId() + "_virtual_variable_group"));
  }

  CFunction::CFunction(CContext* context, const StdString& id)
    : CObjectTemplate<CFunction>(context, id)
    , CFunctionAttributes()
    , numArgout_(0)
    , numArgin_(0)
    , exprContent_("")
    , pySrcContent_("")
    , offload_("")
    , enabled_(false)
  {
    setVirtualFieldGroup(CFieldGroup::create(context_, getId() + "_virtual_field_group"));
    setVirtualVariableGroup(CVariableGroup::create(context_, getId() + "_virtual_variable_group"));
  }

  StdString CFunction::GetDefName(void) { return "function_definition"; }
  StdString CFunction::GetName(void) { return "function"; }
  ENodeType CFunction::GetType(void) { return eFunction; } // eFunction must be in enum ENodeType


  //----------------------------------------------------------------
  /*!
  \brief Get the vector of filter expression nodes from the function expression
  \return Vector of pointers of filter expression nodes
  */
  const std::vector<std::shared_ptr<xios::IFilterExprNode>>& CFunction::getTreeFromExpr()
  {
    if (expr_.empty())
    {
        std::vector<IFilterExprNode*>* rawExprs = parseExpr(getExpr() + '\0');
        numArgout_ = rawExprs->size();
        expr_.reserve(rawExprs->size());
        for (auto* ptr : *rawExprs)
            expr_.emplace_back(ptr);
    }
    return expr_;
  }

  //----------------------------------------------------------------
  /*!
  \brief Get the expression content
  \return Reference to the expression content
  */
  const string& CFunction::getExpr()
  {
    if (!expr.isEmpty() && exprContent_.empty())
    {
      exprContent_ = expr.getValue();
      if (exprContent_.empty())
        ERROR("const string& CFunction::getExpr()",
                 "The attribute expr is not defined !");
      expr.reset();
    }
    return exprContent_;
  }
  
  //----------------------------------------------------------------
  /*!
  \brief Get the python source content
  \return Reference to the python source content
  */
  const string& CFunction::getPySrc()
  {
    if (!pysrc.isEmpty() && pySrcContent_.empty())
      pySrcContent_ = pysrc.getValue();
    return pySrcContent_;
  }

  // ---------------------------------------------------------------
  /*!
  \brief Get the vector of input arguments
  \return Vector of input argument names
  */
  std::vector<std::string> CFunction::getArgin() 
  {
    if (!argin.isEmpty() && arginContent_.empty())
    {
      arginContent_ = splitRegex(argin.getValue(), "\\s*,\\s*");
      numArgin_ = arginContent_.size();
    }
    return arginContent_;
  }
 
  // ---------------------------------------------------------------
  /*!
  \brief Get the number of input arguments
  \return Number of input arguments
  */
  size_t CFunction::getNumArgin()
  {
    if (!argin.isEmpty() && arginContent_.empty())
      getArgin();
    return numArgin_;
  }

  // ---------------------------------------------------------------
  /*!
  \brief Get the vector of output arguments
  \return Vector of output argument names
  */
  std::vector<std::string> CFunction::getArgout()
  {
    if (!argout.isEmpty() && argoutContent_.empty())
    {
      // Argout getter, allow things like "output0,,,output3,,"
      argoutContent_ = xios::splitRegex(argout.getValue(), "\\s*,\\s*");
      numArgout_ = argoutContent_.size();
    }
    if (numArgout_ == 0)
        numArgout_ = 1;
    return argoutContent_;
  }
 
  // ---------------------------------------------------------------
  /*!
  \brief Get the number of output arguments
  \return Number of output arguments
  */
  size_t CFunction::getNumArgout()
  TRY
  {
    if (expr_.empty() && !expr.isEmpty())
      getTreeFromExpr();
    if (numArgout_ == 0)
      getArgout();
    return numArgout_;
  }
  CATCH_DUMP_ATTR


  /*!
   \brief Get index of output argument
   \param [in] argoutName string representing the outputArg name
   \return Index of the output argument
   */
  size_t CFunction::getArgoutIdx(std::string argoutName)
  TRY
  {
    getArgout();   
    for (size_t i = 0; i< argoutContent_.size(); ++i)
      if (argoutContent_[i] == argoutName)
        return i;
    ERROR("size_t CFunction::getArgoutIdx(SArg& arg) const",
      " The argoutName " << argoutName << " does not match any argout for the function " << getId() << endl);
  }
  CATCH_DUMP_ATTR

  /*!
   \brief Get index of output argument
   \param [in] arg Sarg representing the output idx information (idx or name)
   \return Index of the output argument
   */
  size_t CFunction::getArgoutIdx(const SArg& arg)
  TRY
  {
    getArgout();
    switch (arg.type)
    {
      case SArg::Type::None: return 0;
      case SArg::Type::Positional: return arg.index;
      case SArg::Type::Named: return getArgoutIdx(arg.name);
    }
    ERROR("size_t CFunction::getArgoutIdx(const SArg& arg)",
          "Undefined arg type : " << arg.type);
    return 0;
  }
  CATCH_DUMP_ATTR
  
  // ---------------------------------------------------------------
  /*!
  \brief Get the offload service name
  \return Offload service name
  */
  std::string CFunction::getOffload()
  {
    if (!offload.isEmpty() && offload_.empty())
      offload_ = offload.getValue();
    return offload_;
  }

  // ---------------------------------------------------------------
  /*!
  \brief Check if the function has its offload attribute set
  \return True if the function is has its offload attribute set, false otherwise
  */
  bool CFunction::isOffload() 
  {
    return (getOffload()!="");
  }

  // ---------------------------------------------------------------
  /*!
  \brief Get the offload service and pool names
  \param[in] defaultPoolOffloadId_ Default pool offload id
  \param[in] defaultOffloadId_ Default offload id
  \param[out] poolOffloadId Pool offload id
  \param[out] offloadId Offload id
  */
  void CFunction::getOffloadServicesId(const string& defaultPoolOffloadId_, const string& defaultOffloadId_,
                                   string& poolOffloadId, string& offloadId)
   {
     poolOffloadId = defaultPoolOffloadId_ ;
     offloadId = defaultOffloadId_ ;

     if (!pool_offload.isEmpty()) poolOffloadId = pool_offload;
     if (!offload.isEmpty()) offloadId = offload;
   }

  // ---------------------------------------------------------------
  /*!
  \brief Send the function definition to the server
  */
   void CFunction::sendFunctionToServer()
   TRY
   {
     if (sendFunctionToServer_done_.count(client_)!=0) return ;
     else sendFunctionToServer_done_.insert(client_) ;
     
     StdString functionDefRoot("function_definition");
     CFunctionGroup* cfgrpPtr = CFunctionGroup::get(context_, functionDefRoot);

     // We concatenate _offload_ to the function Id to notify that it is an offloaded function
     // -> we'll directly build a pythonFilter on serverSide  
     cfgrpPtr->sendCreateChild(this->getId(), client_);
     this->sendAllAttributesToServer(client_, this->getId());
     context_->sendContextToFileServer(client_);

   }
    CATCH_DUMP_ATTR

    /*!
   \brief Send a message to create a field on server side
   \param[in] id String identity of field that will be created on server
   */
   void CFunction::sendAddField(const string& id, CContextClient* client)
   TRY
   {
      sendAddItem(id, EVENT_ID_ADD_FIELD, client);
   }
   CATCH_DUMP_ATTR

    /*!
   \brief Send a message to create a variable on server side
   \param[in] id String identity of field that will be created on server
   */
   void CFunction::sendAddVariable(const string& id, CContextClient* client)
   TRY
   {
      sendAddItem(id, EVENT_ID_ADD_VARIABLE, client);
   }
   CATCH_DUMP_ATTR

  // ---------------------------------------------------------------
  /*!
  \brief Add a filter variable input argument to the function
  \param[in] nodeId Node id of the filter
  \param[in] var Pointer to the variable to be added as input argument
  \param[in] idx Index of the input argument
  */
  void CFunction::addFilterArgin(NodeId nodeId, CVariable* var, size_t idx)
  {
    auto& vec = filterArginsMap_[nodeId];
    if (vec.empty()) {
        vec.resize(getNumArgin());
    }
    vec[idx] = CFunction::SArgIn(var);
  }

  // ------------------------------------------------------------------
  /*!
  \brief Add a filter input argument to the function
  \param[in] nodeId Node id of the filter
  \param[in] field Pointer to the field to be added as input argument
  \param[in] idx Index of the input argument
  */
  void CFunction::addFilterArgin(NodeId nodeId, CField* field, size_t idx)
  {
    auto& vec = filterArginsMap_[nodeId];
    if (vec.empty()) {
        vec.resize(getNumArgin());
    }
    vec[idx] = CFunction::SArgIn(field);
  }

  // ---------------------------------------------------------------
  /*!
  \brief Get the vector of filter fields from the function input arguments
  \return Vector of pointers of filter fields
  */
  vector<CField*> CFunction::getFilterFields()
  {
    std::vector<CField*> offloadFields;
    std::set<std::string> seen;
    for (const auto& entry : filterArginsMap_)
    {
      const auto& vec = entry.second;
      for (const CFunction::SArgIn& arg : vec)
        if (arg.type == CFunction::SArgIn::Field && seen.insert(arg.getId()).second)
          offloadFields.push_back(arg.field);
    }
    return offloadFields;
  }

  // ---------------------------------------------------------------
  /*!
  \brief Get the vector of filter variables from the function input arguments
  \return Vector of pointers of filter variables
  */
  vector<CVariable*> CFunction::getFilterVariables()
  {
    std::vector<CVariable*> offloadVariables;
    set<std::string> seen;
    for (const auto& entry : filterArginsMap_)
    {
      const auto& vec = entry.second;
      for (const CFunction::SArgIn& arg : vec)
        if (arg.type == CFunction::SArgIn::Variable && seen.insert(arg.getId()).second)
          offloadVariables.push_back(arg.var);
    }
    return offloadVariables;
  }
    
  // ---------------------------------------------------------------
  /*!
  \brief Add a field to the list of offload output fields
  \param[in] offloadFieldOut Pointer to the field to be added as offload output field
  */
  void CFunction::addOffloadFieldOut(CField* offloadFieldOut)
  {
    offloadFieldOuts_.push_back(offloadFieldOut);
  }

  // ---------------------------------------------------------------
  /*!
  \brief Get the vector of offload output fields
  \return Vector of pointers of offload output fields
  */
  std::vector<CField*> CFunction::getOffloadFieldOuts()
  {
    return offloadFieldOuts_;
  }

  // ---------------------------------------------------------------
  /*!
  \brief Set the context client for the function
  \param[in] defaultPoolId Default pool ID
  \param[in] defaultServiceId Default service ID
  \param[in] partitionId Partition ID
  */
  void CFunction::setContextClient(const string& defaultPoolId, const string& defaultServiceId, int partitionId)
  TRY
  {
    CContext* context = context_;
    vector<CContextClient*> clients = context->getContextClient(defaultPoolId, defaultServiceId) ;
    setContextClient(clients[partitionId]) ;
  }
  CATCH_DUMP_ATTR

   // ---------------------------------------------------------------
  /*!
  \brief Set the context client for the function
  \param[in] newContextClient Pointer to the new context client
  */
   void CFunction::setContextClient(CContextClient* newContextClient)
   TRY
   {
     client_ = newContextClient;
     for (auto field : getFilterFields())  field->setContextClient(newContextClient);
     for (auto field : offloadFieldOuts_) field->setContextClient(newContextClient);
     for (auto scalar : getFilterVariables()) scalar->setContextClient(newContextClient);
   }
   CATCH_DUMP_ATTR

   // ---------------------------------------------------------------
    /*!
  \brief Set the virtual field group for the function
  \param[in] newVFieldGroup Pointer to the new virtual field group
    */
   void CFunction::setVirtualFieldGroup(CFieldGroup* newVFieldGroup)
   TRY
   {
      this->vFieldGroup_ = newVFieldGroup;
   }
   CATCH_DUMP_ATTR

    // ---------------------------------------------------------------
      /*!
   \brief Set the virtual variable group for the function
   \param[in] newVVariableGroup Pointer to the new virtual variable group
   */
   void CFunction::setVirtualVariableGroup(CVariableGroup* newVVariableGroup)
   TRY
   {
      this->vVariableGroup_ = newVVariableGroup;
   }
   CATCH_DUMP_ATTR

  // ---------------------------------------------------------------
  /*!
  \brief Get the context client for the function
  \return Pointer to the context client
  */
  CContextClient* CFunction::getContextClient()
  {
    return client_;
  }

  // ---------------------------------------------------------------
  /*!
  \brief dispatch an event to the function
  \param[in] context Pointer to the context
  \param[in] event Reference to the event to be dispatched
  \return True if the event was dispatched successfully, false otherwise
  */
  bool CFunction::dispatchEvent(CContext* context, CEventServer& event)
  TRY
  {
    if (SuperClass::dispatchEvent(context, event)) return true;
    else
    {
      switch(event.type)
      {
        case EVENT_ID_ADD_FIELD :
          recvAddField(context, event);
          return true;
          break;

        case EVENT_ID_ADD_VARIABLE :
          recvAddVariable(context, event);
          return true;
          break;

          // Do we need other event types for function ?
          default :
            ERROR("bool CFunction::dispatchEvent(CContext* context, CEventServer& event)", << "Unknown Event");
          return false;
      }
    }
  }
  CATCH

  // ---------------------------------------------------------------
  /*!
  \brief Receive a message annoucing the creation of a variable on server side
  \param[in] event Received event
  */
  void CFunction::recvAddVariable(CContext* context, CEventServer& event)
  TRY
  {
    CBufferIn* buffer = event.subEvents.begin()->buffer;
    string id;
    *buffer>>id;
    get(context, id)->recvAddVariable(*buffer);
  }
  CATCH

   /*!
   \brief Receive a message annoucing the creation of a field on server side
   \param[in] event Received event
   */
   void CFunction::recvAddField(CContext* context, CEventServer& event)
   TRY
   {
    CBufferIn* buffer = event.subEvents.begin()->buffer;
    string id;
    *buffer>>id;
    get(context, id)->recvAddField(*buffer);
   }
   CATCH

       /*!
   \brief Receive a message annoucing the creation of a field on server side
   \param[in] buffer Buffer containing message
   */
   void CFunction::recvAddField(CBufferIn& buffer)
   TRY
   {
    string id;
    buffer>>id;
    addField(id);
   }
   CATCH_DUMP_ATTR

  // ---------------------------------------------------------------
  /*!
  \brief Add a field to the function
  \param[in] id String identity of the field to be added
  \return Pointer to the newly created field
  */ 
  CField* CFunction::addField(const string& id)
   TRY
   {
     return vFieldGroup_->createChild(id);
   }
   CATCH_DUMP_ATTR

    /*!
   \brief Receive a message annoucing the creation of a field on server side
   \param[in] buffer Buffer containing message
   */
   void CFunction::recvAddVariable(CBufferIn& buffer)
   TRY
   {
      string id;
      buffer>>id;
      addVariable(id);
   }
   CATCH_DUMP_ATTR

   // ---------------------------------------------------------------
  /*!
  \brief Add a variable to the function
  \param[in] id String identity of the variable to be added
  \return Pointer to the newly created variable
  */
   CVariable* CFunction::addVariable(const string& id)
   TRY
   {
     return vVariableGroup_->createChild(id);
   }
   CATCH_DUMP_ATTR

  // ---------------------------------------------------------------
  /*!
  \brief Set the function as enabled
  */
  void CFunction::setEnabled()
  {
    enabled_=true;
  }

  /*!
  \brief Check if the function is enabled
  \return True if the function is enabled, false otherwise
  */
  bool CFunction::isEnabled()
  {
    return enabled_;
  }

  /*!
  \brief Set the function as offloaded
  */
  void CFunction::setIsOffloaded()
  {
    offload_ = "already_offload";
  }

  /*!
  \brief Check if the function is offloaded
  \return True if the function is offloaded, false otherwise
  */
  bool CFunction::isOffloaded()
  {
    return offload_ == "already_offload";
  } 

  /*!
  \brief Get the offset attribute, it is 0 if not set
  \return The offset attribute of the function
  */
  CDuration CFunction::getOffset()
  {
    if (!offset.isEmpty())
      return offset;
    return CDuration();
  }

  const std::vector<CFunction::SArgIn>& CFunction::getArgs(NodeId nodeId) const
  {
    auto it = filterArginsMap_.find(nodeId);
    if (it == filterArginsMap_.end())
      ERROR("forEachArgIndexed", "Node not found in the filterArginsMap_");
    return it->second;
  }

  const std::string& CFunction::CFunction::SArgIn::getId() const
  {
    return isVariable() ? var->getId() : field->getId();
  }

  bool CFunction::CFunction::SArgIn::isField() const
  {
    return type == Field;
  }

  bool CFunction::CFunction::SArgIn::isVariable() const
  {
    return type == Variable;
  }











}