#ifndef __XIOS_SCALAR_EXPR_NODE_HPP__
#define __XIOS_SCALAR_EXPR_NODE_HPP__

#include <string>
#include <memory>
#include <vector>
#include "filter_graph_types.hpp"

namespace xios
{
  /*!
   * Interface implemented by all the nodes of a tree representing an expression
   * which can be reduced to a scalar value.
   */
  class CContext ;
  class CSuperFilter ;

  struct IScalarExprNode 
  {
    /*!
     * Builds a filter graph corresponding to the expression tree.
     *
     * \return the output pin of the filter producing the result of the expression 
     */
    virtual SReducedNode reduce(CContext* context, NodeId parentId = -1) const = 0;
    virtual ~IScalarExprNode() {};
  };

  /*!
   * Expression node corresponding to a scalar value.
   */
  class CScalarValExprNode : public IScalarExprNode
  {
    public:
      /*!
       * Constructs an expression node corresponding to the specified scalar value.
       *
       * \param strVal the string representation of the scalar value
       */
      CScalarValExprNode(const std::string& strVal);

      virtual SReducedNode reduce(CContext* context, NodeId parentId = -1) const;

    private:
      std::string strVal; //!< The string representation of the scalar value
  };

  /*!
   * Expression node corresponding to a scalar variable.
   */
  class CScalarVarExprNode : public IScalarExprNode
  {
    public:
      /*!
       * Constructs an expression node corresponding
       * to the scalar variable whose id is provided.
       * also used for scalar used as function arguments
       * \param varId the identifier of the scalar variable
       */
      CScalarVarExprNode(const std::string& varId);

      virtual SReducedNode reduce(CContext* context, NodeId parentId = -1) const;
      const std::string& getVarId() const;

    private:
      std::string varId; //!< The identifier of the field
  };

  /*!
   * Expression node corresponding to an operation on a scalar.
   */
  class CScalarOpExprNode : public IScalarExprNode
  {
    public:
      /*!
       * Constructs an expression node corresponding to the specified operation
       * applied to the provided scalar node.
       * Note that the child node will be destroyed automatically when the parent node
       * is destroyed.
       *
       * \param opId the identifier of the operator
       * \param child the scalar child node to which the operator is applied
       */
      CScalarOpExprNode(const std::string& opId, std::initializer_list<IScalarExprNode*> argsList);
      CScalarOpExprNode(const std::string& opId, const std::vector<IScalarExprNode*> argsVect);

      virtual SReducedNode reduce(CContext* context, NodeId parentId = -1) const;

    private:
      std::string opId; //!< The identifier of the field
      std::vector<IScalarExprNode*> args; //!< The  child vector node to which the operator is applied
  };
}

#endif //__XIOS_SCALAR_EXPR_NODE_HPP__
