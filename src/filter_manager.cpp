#include "filter.hpp"
#include "embedded_filter.hpp"
#include "filter_expr_node.hpp"
#include "scalar_expr_node.hpp"
#include "filter_manager.hpp"
#include "garbage_collector.hpp"
#include "super_filter.hpp"
#include "field.hpp"


namespace xios
{

  ///---------------------------------------------------------------
  /*!
   * \fn CFilterManager::CFilterManager(CContext& context)
   * Constructor for the CFilterManager class. Initializes the filter manager with a reference to the XIOS context.
   * \param [in] context Reference to the XIOS context.
   */
  // Constructor
  CFilterManager::CFilterManager(CContext& context)
    : context_(context)
  {}

  ///---------------------------------------------------------------
  /*!
   * \fn bool CFilterManager::isReusable(const std::string& opId)
   * Return true for the filter that may be reuse without beiing duplicated depending on the opId.
   * \param [in] opId The operation identifier string representing the filter operation.
   * \return A boolean that indicates if the filter is reusable or not
   */
  bool CFilterManager::isReusable(const std::string& opId)
  {
    if (opId == "@")
      return false;
    return true;
  }


  ///---------------------------------------------------------------
  /*!
   * \fn NodeId CFilterManager::computeOrGetNodeId(std::string opId, std::vector<SInputPoint> inputs)
   * Computes or retrieves a unique node identifier for a filter based on its operation and input points.
   * If a filter with the same operation and inputs already exists in the key-to-ID mapping, returns its existing node ID.
   * Otherwise, creates a new unique node ID, it has to be stored with addFilter() after filter creation.
   * This mechanism enables filter graph optimization by avoiding duplication of identical filters.
   * \param [in] opId The operation identifier string representing the filter operation.
   * \param [in] inputs A vector of input points that serve as inputs to the filter.
   * \return A unique node identifier for the filter with the given operation and inputs.
   */
  NodeId CFilterManager::computeOrGetNodeId(std::string opId, std::vector<SInputPoint> inputs, NodeId parentId)
  {
    FilterKey key{opId, inputs, parentId};

    if (isReusable(opId))
    {
      auto it = keyToId_.find(key);
      if (it != keyToId_.end())
        return it->second;
    }

    NodeId id = nextId_++;
    keyToId_[key] = id;
    return id;
  }

  ///---------------------------------------------------------------
  /*!
   * \fn void CFilterManager::addFilter(NodeId id, std::shared_ptr<CFilter> filter)
   * Registers a filter instance in the filter manager's internal map, associating it with a unique node identifier.
   * This method allows the filter manager to maintain and retrieve filter objects by their computed node IDs.
   * \param [in] id The unique node identifier for the filter (typically obtained from computeOrGetNodeId()).
   * \param [in] filter A shared pointer to the filter object to be registered.
   */
  void CFilterManager::addFilter(NodeId id, std::shared_ptr<CFilter> filter)
  {
    filterMap_[id] = filter;
  }

  ///---------------------------------------------------------------
  /*!
   * \fn std::shared_ptr<CFilter> CFilterManager::getFilter(NodeId id)
   * Retrieves a filter object from the filter manager by its node identifier.
   * Returns a null shared pointer if no filter with the given node ID is found.
   * \param [in] id The unique node identifier of the filter to retrieve.
   * \return A shared pointer to the filter object, or nullptr if the filter is not found.
   */
  std::shared_ptr<CFilter> CFilterManager::getFilter(NodeId id)
  {
    auto it = filterMap_.find(id);

    if (it == filterMap_.end())
      return nullptr;

    return it->second;
  }

  ///---------------------------------------------------------------
  /*!
   * \fn size_t CFilterManager::getFilterArgoutIdx(NodeId id, SArg& arg)
   * Retrieves the argoutIdx of the filter associated to nodeId
   * it returns 0 expect for embededFilter (filter related to a function)
   * \param [in] id The unique node identifier of the filter to retrieve.
   * \param [in] arg The representation of the argout (idx or name)
   * \return The argout idx
   */
  size_t CFilterManager::getFilterArgoutIdx(NodeId id, SArg& arg)
  {
    if (arg.type == SArg::None)
      return 0;
    else
    {
      std::shared_ptr<CFilter> filter = getFilter(id);
      std::shared_ptr<CEmbeddedFilter> embeddedFilter = std::dynamic_pointer_cast<CEmbeddedFilter>(filter);
      return embeddedFilter->getFunctionArgoutIdx(arg);
    }
  }

  ///---------------------------------------------------------------
  /*!
   * \fn std::shared_ptr<CSuperFilter> CFilterManager::getSuperFilter(NodeId id)
   * Retrieves a superFilter object from the filter manager by its node identifier.
   * Returns a null shared pointer if no filter with the given node ID is found.
   * Alternative to this is to use a superFilterMap_ 
   * \param [in] id The unique node identifier of the filter to retrieve.
   * \return A shared pointer to the filter object, or nullptr if the filter is not found.
   */
  std::shared_ptr<CSuperFilter> CFilterManager::getSuperFilter(NodeId id)
  {
    std::shared_ptr<CFilter> filter = getFilter(id);
    if (!filter) return nullptr;
    std::shared_ptr<CSuperFilter> superFilter = std::dynamic_pointer_cast<CSuperFilter>(filter);
    if (!superFilter)
        ERROR("std::shared_ptr<CSuperFilter> CFilterManager::getSuperFilter(NodeId id)", 
              "You're asking for a CSuperFilter while the filter " << toString(id) << " is not a CSuperFilter" );
    return superFilter;
  }

  ///---------------------------------------------------------------
  /*!
   * \fn const FilterKey* CFilterManager::getKey(NodeId id) const
   * Retrieves the filter key (operation and inputs) associated with a given node identifier.
   * This function is primarily intended for debugging purposes to inspect filter configurations.
   * Returns a null pointer if no filter with the given node ID is found.
   * \note This function performs a linear search through the key-to-ID mapping, making it less efficient
   *       than the forward lookup operations. Should only be used for diagnostic or debugging purposes.
   * \param [in] id The unique node identifier of the filter.
   * \return A constant pointer to the FilterKey associated with the node ID, or nullptr if not found.
   */
  // Only for debug uses 
  const FilterKey* CFilterManager::getKey(NodeId id) const
  {
    for (const auto& kv : keyToId_)
      if (kv.second == id)
          return &kv.first;
    return nullptr;
  }

  ///---------------------------------------------------------------
  /*!
   * \fn std::string CFilterManager::toString(NodeId id) const
   * Generates a human-readable string representation of a filter identified by its node ID.
   * The output format is "operation(input1, input2, ...)" where each input is recursively formatted based on its type
   * (scalar value for Scalar nodes, field ID for Field nodes, or nested filter representation for Filter nodes).
   * This function is primarily intended for debugging and diagnostic purposes.
   * \note This function performs a recursive conversion for nested filters and will trigger an error if the node ID
   *       is not found in the filter manager.
   * \param [in] id The unique node identifier of the filter to convert to a string.
   * \return A string representation of the filter operation and its inputs.
   */
  // Only for debug uses 
  std::string CFilterManager::toString(NodeId id) const
  {
    const FilterKey* key = getKey(id);
    if (!key)
      return "not_reusable";
    std::ostringstream oss;
    oss << key->op << "(";

    // Format each input point based on its node type
    for (size_t i = 0; i < key->inputs.size(); ++i)
    {
      if (i) oss << ", ";
      const auto& input = key->inputs[i];
      switch (input.node.type)
      {
        case SReducedNode::Scalar:
          // Output scalar value directly
          oss << input.node.value;
          break;

        case SReducedNode::Field:
          // Output field identifier
          oss << input.node.fieldId;
          break;

        case SReducedNode::Filter:
          // Recursively format nested filter, with output index if non-zero
          oss << toString(input.node.nodeId);
          oss << "[" << input.outIdx << "]";
          break;
      }
    }

    oss << ")";
    return oss.str();
  }

  ///---------------------------------------------------------------
  // End of CFilterManager class implementation
  ///---------------------------------------------------------------
  
}