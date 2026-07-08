#ifndef __XIOS_FilterGraphTypes__
#define __XIOS_FilterGraphTypes__

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace xios
{

  class COutputPin;
  class CField;

  /*!
   \struct SArg
    Represents the argument slector (either idx or name)
   */
  struct SArg
  {
    enum Type
    {
      None,
      Positional,
      Named
    };

    Type type;
    int index;
    std::string name;

    SArg(Type t = None, int i = 0, const std::string& n = "")
      : type(t), index(i), name(n)
    {}

    static SArg positional(int idx)
    {
      return SArg(Positional, idx);
    }

    static SArg named(const std::string& name)
    {
      return SArg(Named, 0, name);
    }
  };

  /*!
   \typedef NodeId
    Unique identifier for a node in the filter graph. Uses 64-bit unsigned integer.
   */
  using NodeId = uint64_t;

  static const NodeId InvalidNodeId = static_cast<NodeId>(-1);

  /*!
   \fn void hashCombine(std::size_t& seed, std::size_t value)
    Combines a hash value with an existing seed to produce a new combined hash.
    \param [in/out] seed The initial hash seed, which is updated with the combined hash.
    \param [in] value The hash value to combine with the seed.
   */
  inline void hashCombine(std::size_t& seed, std::size_t value)
  {
    seed ^= value + 0x9e3779b9 + (seed << 6) + (seed >> 2);
  }

  /*!
   \struct SReducedNode
    Represents a node in the filter graph. Used to compact filter graph representations for comparison.
   */
  struct SReducedNode
  {
    /*!
     \enum Type
      Enumeration defining the possible types of a reduced node in the filter graph.
     */
    enum Type
    {
      Scalar,   /*!< Represents a constant scalar value */
      Field, /*!< Represents a reference to an input field */
      Filter    /*!< Represents a filter operation with child inputs */
    };

    Type type;                                 /*!< The type of this node */
    double value;                              /*!< Scalar value (only meaningful when type == Scalar) */
    std::string fieldId;                       /*!< Field identifier (only meaningful when type == Field) */
    NodeId nodeId;                             /*!< Node identifier in the filter graph (only meaningful when type == Filter) */
    std::shared_ptr<COutputPin> outputPin;     /*!< Reference to the output pin of the filter (only meaningful when type == Filter or Field) */
    CField* fieldIn;                           /*!< Pointer to the input field */

    /*!
     \fn bool operator==(const SReducedNode& other) const
      Compares two reduced nodes for equality. Two nodes are equal if they have the same type and their
      type-specific values match
      \param [in] other The other reduced node to compare with.
      \return true if both nodes are equal, false otherwise.
     */
    bool operator==(const SReducedNode& other) const
    {
      if (type != other.type)
        return false;

      switch (type)
      {
        case Scalar:
          return value == other.value;

        case Field:
          return fieldId == other.fieldId;

        case Filter:
          return nodeId == other.nodeId;
      }
      return false;
    }
  };


  /*!
   \struct SInputPoint
    Representation of what will be used as input by any filter. This structure combines a reduced node
    with an output index to uniquely identify a specific input source for a filter operation.
   */
  struct SInputPoint
  {
    SReducedNode node;     /*!< The reduced node representing the input source */
    size_t outIdx;         /*!< Output index of the node (in case the node produces multiple outputs) */
    
    /*!
     \fn bool operator==(const SInputPoint& other) const
      Compares two input points for equality. Two input points are equal if they reference the same node
      and the same output index.
      \param [in] other The other input point to compare with.
      \return true if both input points are equal, false otherwise.
     */
    bool operator==(const SInputPoint& other) const
    {
      return node == other.node && outIdx == other.outIdx;
    }
  };
 

  /*!
   \struct FilterKey
    Provides a unique representation of a filter based on its operation and input points. This key is used
    to identify filters in the graph that have the same operation and child connections, enabling filter
    graph optimization and deduplication.
   */
  struct FilterKey
  {
    std::string op;                          /*!< The operation identifier/name of the filter */
    std::vector<SInputPoint> inputs;         /*!< List of input points connected to this filter */
    NodeId parentId;                         /*!< parentId of this filter (-1 if no parent) */
      
    /*!
     \fn bool operator==(const FilterKey& other) const
      Compares two filter keys for equality. Two filter keys are equal if they have the same operation
      and identical input points in the same order.
      \param [in] other The other filter key to compare with.
      \return true if both filter keys are equal, false otherwise.
     */
    bool operator==(const FilterKey& other) const
      {
        return op == other.op && inputs == other.inputs && parentId == other.parentId;
      }

    };

    /*!
     \struct SReducedNodeHash
      Hash functor for reduced nodes. Provides a hash function that combines the node type with its
      type-specific value (scalar, field ID, or node ID) to produce a consistent hash code suitable
      for use in hash tables and unordered containers.
     */
    struct SReducedNodeHash
    {
      /*!
       \fn std::size_t operator()(const SReducedNode& node) const
        Computes the hash code for a reduced node. Combines the hash of the node type with the hash of
        its type-specific value to ensure that different node types and values produce different hashes.
        \param [in] node The reduced node to hash.
        \return The computed hash code for the node.
       */
      std::size_t operator()(const SReducedNode& node) const
      {
        std::size_t h = 0;
        hashCombine(h, std::hash<int>()(static_cast<int>(node.type)));

        switch (node.type)
        {
          case SReducedNode::Scalar:
            hashCombine(h, std::hash<double>()(node.value));
            break;

          case SReducedNode::Field:
            hashCombine(h, std::hash<std::string>()(node.fieldId));
            break;

          case SReducedNode::Filter:
            hashCombine(h, std::hash<NodeId>()(node.nodeId));
            break;
        }

        return h;
      }
    };

    /*!
     \struct SInputPointHash
      Hash functor for input points. Provides a hash function that combines the hash of the underlying
      reduced node with the hash of the output index to produce a consistent and unique hash code for
      input points in hash tables.
     */
    struct SInputPointHash
    {
      /*!
       \fn std::size_t operator()(const SInputPoint& input) const
        Computes the hash code for an input point. Combines the hash of the input's reduced node with
        the hash of its output index.
        \param [in] input The input point to hash.
        \return The computed hash code for the input point.
       */
      std::size_t operator()(const SInputPoint& input) const
      {
        std::size_t h = SReducedNodeHash()(input.node);
        hashCombine(h, std::hash<size_t>()(input.outIdx));
        return h;
      }
    };

    /*!
     \struct FilterKeyHash
      Hash functor for filter keys. Provides a hash function that combines the hash of the operation string
      with the hashes of all input points to produce a consistent hash code for filter keys in hash tables.
      This enables efficient storage and retrieval of filter configurations in associative containers.
     */
    struct FilterKeyHash
    {
      /*!
       \fn std::size_t operator()(const FilterKey& key) const
        Computes the hash code for a filter key. Combines the hash of the operation name with the hashes
        of all input points connected to the filter, ensuring that different filter configurations produce
        different hash codes.
        \param [in] key The filter key to hash.
        \return The computed hash code for the filter key.
       */
      std::size_t operator()(const FilterKey& key) const
      {
        std::size_t h = std::hash<std::string>()(key.op);
        SInputPointHash inputHash;

        for (const auto& input : key.inputs)
          hashCombine(h, inputHash(input));

        hashCombine(h, std::hash<NodeId>()(key.parentId));

        return h;
      }
    };

  ///---------------------------------------------------------------
  // End of filter graph type definitions
  ///---------------------------------------------------------------

}

#endif //__XIOS_FilterGraphTypes__