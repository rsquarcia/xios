#ifndef __XIOS_CSuperFilter
#define __XIOS_CSuperFilter

#include <algorithm>
#include <unordered_map>

#include "filter.hpp"
#include "filter_engine.hpp"
#include "internal_input_pin.hpp"
#include "internal_output_pin.hpp"
#include "function.hpp"
#include "filter_manager.hpp"
#include "embedded_filter.hpp"
#include "filter_graph_types.hpp"

namespace xios{

  class CSuperFilter: public CEmbeddedFilter, public std::enable_shared_from_this<CSuperFilter>
  {    
    public:

        /*!
       * Constructs the filter associated to the function function
       * and a garbage collector.
       *
       * \param gc the associated garbage collector
       * \param function the associated function
       */
      CSuperFilter(CGarbageCollector& gc, CFunction& function);

      // Destructor
      /**
       * Destructor for `CSuperFilter`.
       */
      ~CSuperFilter();

      /**
       * Reduce the function expression for a given field reference and
       * return a vector of tuples describing output pins, their slot index
       * and the associated hash for the reduced expression.
       *
       * @param gc the garbage collector to use for temporary allocations
       * @param field_ref reference to the field to reduce the function on
       * @param nodeId the unique representation of the superFilter
       * @param arg the curent required argout 
       * @return A SinputPoint 
       */
      SInputPoint reduceFunction(CGarbageCollector& gc, CField& fieldOut, NodeId nodeId, int argoutIdx) override;

  
      // Connection methods
      /**
       * Check whether the output slot at `slotIdx` must be connected
       * internally (inside the super filter) rather than externally.
       *
       * @param slotIdx the slot index to check
       * @return non-zero if it must be internally connected, zero otherwise
       */
      int mustBeInternalyConnected(size_t slotIdx);

      /**
       * Create (if necessary) and return internal connections for the given inputPoint. This
       * typically produces an internal output pin associated to inputPoint.
       *
       * @param gc the garbage collector to use
       * @param inputPoint the identifier for which to set internal connections
       * @return a shared pointer to the created `CInternalOutputPin`
       */
      const std::shared_ptr<CInternalOutputPin> setInternalConnections(CGarbageCollector& gc, SInputPoint inputPoint);

      /**
       * Push the internal connection corresponding to `idx` onto the
       * internal connection stack to record a new active connection scope.
       *
       * @param idx the index of the internal connection to push
       */
      void fillInternalConnectionStack(size_t idx);

      /**
       * Pop the most recent internal connection scope from the stack.
       */
      void popInternalConnections();


      /**
       * Return the list of argument identifiers (argin) of the
       * function in order.
       *
       * @return vector of argin identifier strings
       */
      const std::vector<std::string> getFunctionArgin();



    private:

      std::stack<std::vector<int>> internalConnection_;                  // Stack to handle internal connections

  };
 
}


#endif //__XIOS_CSuperFilter