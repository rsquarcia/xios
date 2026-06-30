#include "function.hpp"
#include "filter_expr_node.hpp"
#include "lex_parser.hpp"
#include "field.hpp"
#include "garbage_collector.hpp"
#include "output_pin.hpp"
#include "filter.hpp"
#include "context.hpp"
#include "context_client.hpp"
#include "string_tools.hpp"


namespace xios
{

  // Constructors 
  CFunction::CFunction(CContext* context)
    : CObjectTemplate<CFunction>(context)
    , CFunctionAttributes()
    , numArgout_(0)
    , numArgin_(0)
    , exprContent_("")
  { }

  CFunction::CFunction(CContext* context, const StdString& id)
    : CObjectTemplate<CFunction>(context, id)
    , CFunctionAttributes()
    , numArgout_(0)
    , numArgin_(0)
    , exprContent_("")
  { }

  // Static getters
  StdString CFunction::GetName(void) { return "function"; }
  StdString CFunction::GetDefName(void) { return "function_definition"; }
  ENodeType CFunction::GetType(void) { return eFunction; } // eFunction must be in enum ENodeType

  /*!
   \brief Parse function expression
   \return vector of nargout nodes corresponding to each root tree of the function expression 
   */
  const std::vector<std::shared_ptr<xios::IFilterExprNode>>& CFunction::getTreeFromExpr()
  TRY
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
  CATCH_DUMP_ATTR

  /*!
   \brief Get expression content
   \return Reference to the expression string content
   */
  const string& CFunction::getExpr()
  TRY
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
  CATCH_DUMP_ATTR
  
  /*!
   \brief Get input arguments list
   \return Vector of input argument names
   */
  std::vector<std::string> CFunction::getArgin()
  TRY
  {
    if (!argin.isEmpty() && arginContent_.empty())
    {
      arginContent_ = splitRegex(argin.getValue(), "\\s*,\\s*");
      numArgin_ = arginContent_.size();
    }
    return arginContent_;
  }
  CATCH_DUMP_ATTR
 
  /*!
   \brief Get number of input arguments
   \return Count of input arguments
   */
  size_t CFunction::getNumArgin()
  TRY
  {
    if (!argin.isEmpty() && arginContent_.empty())
      getArgin();
    return numArgin_;   
  }
  CATCH_DUMP_ATTR

  /*!
   \brief Get output arguments list
   \return Vector of output argument names (allows empty entries like "output0,,,output3,,")
   */
  std::vector<std::string> CFunction::getArgout()
  TRY
  {
    if (!argout.isEmpty() && argoutContent_.empty())
    {
      argoutContent_ = xios::splitRegex(argout.getValue(), "\\s*,\\s*");
    }
    if (numArgout_ == 0)
      numArgout_ = 1;
    return argoutContent_;
  }
  CATCH_DUMP_ATTR
 
  /*!
   \brief Get number of output arguments
   \return Count of output arguments
   */
  size_t CFunction::getNumArgout()
  TRY
  {
    if (expr_.empty())
      getTreeFromExpr();
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
    for (size_t i = 0; i< getNumArgout(); ++i)
      if (argoutContent_[i] == argoutName)
        return i;
    ERROR("size_t CFunction::getArgoutIdx(SArg& arg) const",
          "The argoutName " << argoutName << " does not match any argout for the function " << getId() << endl);
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
  }
  CATCH_DUMP_ATTR
  
}