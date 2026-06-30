#ifndef __XIOS_CFilterManager__
#define __XIOS_CFilterManager__

#include <map>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include "filter_graph_types.hpp"

namespace xios
{
  class CFilter;
  class CContext;

  ///--------------------------------------------------------------
  /*!
   \class CFilterManager
    This class manages the filters. At filter creation, it compute a hash based on the filter operator and its input filters. 
    If a filter with the same hash already exists, it returns a pointer to this filter instead of creating a new one. 
    This allows to reuse filters and avoid creating duplicated filters in the graph.
   */

  using Hash = std::string;

  class CFilterManager
  {

    public:

      // Constructor
      explicit CFilterManager(CContext& ctx);

      NodeId generateId();
      bool isReusable(const std::string& opId);
      NodeId computeOrGetNodeId(std::string opId, std::vector<SInputPoint> inputs, NodeId parentId);
      void addFilter(NodeId id, std::shared_ptr<CFilter> filter);
      std::shared_ptr<CFilter> getFilter(NodeId id);
      std::shared_ptr<CSuperFilter> getSuperFilter(NodeId id);
      size_t getFilterArgoutIdx(NodeId id, SArg& arg);
      const FilterKey* getKey(NodeId id) const;
      std::string toString(NodeId id) const;


    private:

      CContext& context_;                                              // Reference to the context
      NodeId nextId_ = 1;                                              // Id counter
      std::unordered_map<FilterKey, NodeId, FilterKeyHash> keyToId_;   // Map from filter keys to node IDs for quick lookup
      std::unordered_map<NodeId, std::shared_ptr<CFilter>> filterMap_; // Map from node IDs to filter instances

    
  };

}

#endif //__XIOS_CFilterManager