#ifndef __XIOS_FILTER_EXPR_NODE_HPP__
#define __XIOS_FILTER_EXPR_NODE_HPP__

#include <string>
#include <memory>
#include <vector>

#include "filter_graph_types.hpp"

namespace xios
{
  class COutputPin;
  class CGarbageCollector;
  class CField;
  class CFunction;
  class IScalarExprNode;
  class CSuperFilter;


    /*! 
     * Interface implemented by all nodes of an expression tree that can be
     * transformed into a filter-graph representation.
     */
    struct IFilterExprNode 
    {
      /*! 
       \brief Reduce the expression node into its compact filter-graph representation.
       \param [in] gc The garbage collector used to register any created graph resources.
       \param [in] thisField The field to which the expression is attached; used to propagate grid/context info.
       \param [in] parentFilter If non-null, indicates this reduction is inside a super-filter and allows
                                setting internal connections for that super-filter.
       \return An SReducedNode describing the reduced node (type, value/id, node id, etc.).
      */
      virtual SReducedNode reduce(CGarbageCollector& gc, CField& thisField, NodeId parentId = -1) const = 0;
      virtual SArg getArg() const { return SArg(); };
      virtual ~IFilterExprNode() {};
    };

  struct IExprNode 
  {
    enum Kind{ Scalar, Field } kind;
    IScalarExprNode* scalar;
    IFilterExprNode* field;

    IExprNode(IScalarExprNode* s)
      : kind(Scalar), scalar(s), field(nullptr) {}

    IExprNode(IFilterExprNode* f)
      : kind(Field), scalar(nullptr), field(f) {}
  };

  /*!
   * Expression node corresponding to a field.
   */
  class CFilterFieldExprNode : public IFilterExprNode
  {
    public:
      /*!
       * Constructs an expression node representing a reference to a field.
       * \param [in] fieldId Identifier of the referenced field.
       */
      CFilterFieldExprNode(const std::string& fieldId);

      virtual SReducedNode reduce(CGarbageCollector& gc, CField& thisField, NodeId parentId = -1) const;
      std::string& getfieldId();

    private:
      std::string fieldId; //!< The identifier of the field
  };

  /*!
   * Expression node corresponding to a field for which the result of
   * the temporal operation is requested instead of the instant value.
   */
  class CFilterTemporalFieldExprNode : public IFilterExprNode
  {
    public:
      /*!
       * Constructs an expression node representing a temporal reference to a field (e.g. an aggregated or
       * time-shifted value).
       * \param [in] fieldId Identifier of the referenced field.
       */
      CFilterTemporalFieldExprNode(const std::string& fieldId);

      virtual SReducedNode reduce(CGarbageCollector& gc, CField& thisField, NodeId parentId = -1) const;


    private:
      std::string fieldId; //!< The identifier of the field
  };

  /*!
   * Expression node corresponding to a n-ary operation on scalar(s)/field(s)
   */
  class CFilterOpExprNode : public IFilterExprNode
  {
    public:
      /*!
       * Constructs an expression node representing an n-ary operation.
       * The operation is identified by `opId` and is applied to the provided child nodes.
       * Child nodes may be scalars or field expressions.
       * \param [in] opId Identifier of the operation to apply.
       * \param [in] argsList Initializer list of child nodes (scalar or field) to which the operation is applied.
       * \param [in] arg Optional argument descriptor (positional or named) for this operation.
       */
      CFilterOpExprNode(const std::string& opId, std::initializer_list<IExprNode> argsList, const SArg& arg = SArg());
      /*!
       * Alternate constructor taking an explicit vector of child nodes.
       */
      CFilterOpExprNode(const std::string& opId, const std::vector<IExprNode> argsVect, const SArg& arg = SArg());

      virtual SReducedNode reduce(CGarbageCollector& gc, CField& thisField, NodeId parentId = -1) const;
      SArg getArg() const override { return arg_; }

    private:
      std::string opId_;                 //!< The identifier of the operation
      std::vector<IExprNode> args_;      //!< Vector of child nodes to which the operator is applied
      SArg arg_;                         //!< Optional argument descriptor (positional or named)

  };


}

#endif // __XIOS_FILTER_EXPR_NODE_HPP__
