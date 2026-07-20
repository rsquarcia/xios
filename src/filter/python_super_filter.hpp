#ifndef __XIOS_CPythonSuperFilter
#define __XIOS_CPythonSuperFilter

#include <algorithm>

#include "filter.hpp"
#include "filter_engine.hpp"
#include "internal_input_pin.hpp"
#include "internal_output_pin.hpp"
#include "embedded_filter.hpp"
#include "python_filter.hpp"

namespace xios{

  class CFunction;

  /*!
   * An embedded filter which contains a python filter. It is used to proceed the python function.
   */
  class CPythonSuperFilter: public CEmbeddedFilter, public std::enable_shared_from_this<CPythonSuperFilter>
  {    
    public:

       /*!
       * Constructs a PythonSuperFilter.
       *
       * \param gc the garbage collector associated with this filter
       * \param function the function associated to this filter
       * \param nodeId the unique representation of this filter in the workflow
       */
      CPythonSuperFilter(CGarbageCollector& gc, CFunction& function);

      // Destructor
      ~CPythonSuperFilter();

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
      SInputPoint reduceFunction(CGarbageCollector& gc, CField& fieldOut, NodeId nodeId, size_t argoutIdx) override;
    

      /*!
      * Applies the filter to the input data. Here nothing it is done, the python filter will be applied in the pythonFilter_.
      * \param data the input data
      * \return the filtered data
      */
      std::vector<CDataPacketPtr> apply(std::vector<CDataPacketPtr> data) override;

    private:

      std::shared_ptr<CPythonFilter> pythonFilter_; // PythonFilter associated to this pythonSuperFilter

  };
 
}


#endif //__XIOS_CPythonSuperFilter