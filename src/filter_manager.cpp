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

  void CFilterManager::addFilter(NodeId id, std::shared_ptr<CFilter> filter)
  {
    filterMap_[id] = filter;
  }

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
   * it returns 0 expect for embeddedFilter (filter related to a function)
   * \param [in] id The unique node identifier of the filter to retrieve.
   * \param [in] arg The representation of the argout (idx or name)
   * \return The argout idx
   */
  size_t CFilterManager::getFilterArgoutIdx(NodeId id, SArg& arg)
  {
    std::shared_ptr<CFilter> filter = getFilter(id);
    std::shared_ptr<CEmbeddedFilter> embeddedFilter = std::dynamic_pointer_cast<CEmbeddedFilter>(filter);
    if (embeddedFilter)
        return embeddedFilter->getFunctionArgoutIdx(arg);
    else
      return 0;
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

  // Only for debug uses 
  std::string CFilterManager::toString(NodeId id) const
  {
    if (id == -1) return "None"; 
    const FilterKey* key = getKey(id);
    if (!key)
      return "not_reusable";
    std::ostringstream oss;
    oss << key->op << "(";

    for (size_t i = 0; i < key->inputs.size(); ++i)
    {
      if (i) oss << ", ";
      const auto& input = key->inputs[i];
      switch (input.node.type)
      {
        case SReducedNode::Scalar:
          oss << input.node.value;
          break;

        case SReducedNode::Field:
          oss << input.node.fieldId;
          break;

        case SReducedNode::Filter:
          oss << toString(input.node.nodeId);
          oss << "[" << input.outIdx << "]";
          break;
      }
    }

    oss << ")";
    return oss.str();
  }

}