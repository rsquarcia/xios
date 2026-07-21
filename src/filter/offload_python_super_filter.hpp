#ifndef __XIOS_COffloadPythonSuperFilter
#define __XIOS_COffloadPythonSuperFilter

#include <algorithm>
#include <queue>

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
  class COffloadPythonSuperFilter: public CEmbeddedFilter, public std::enable_shared_from_this<COffloadPythonSuperFilter>
  {    
    public:

       /*!
       * Constructs a PythonSuperFilter.
       *
       * \param gc the garbage collector associated with this filter
       * \param function the function associated to this filter
       * \param nodeId the unique representation of this filter in the workflow
       */
      COffloadPythonSuperFilter(CGarbageCollector& gc, CFunction& function);

      // Destructor
      ~COffloadPythonSuperFilter();

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
       * Override the connectInternalInputPin method to add dynamically an internal connection to the pythonSuperFilter.
       * Actually does nothing in the offload case since the internal connection is created in the createInternalFieldOut method.
       * \param inputPoint the input point to connect
       * \param argoutIdx the argument name/idx associated to the output field
       */
      void connectInternalInputPin(SInputPoint inputPoint, int argoutIdx) override;


      /*!
       * Add dynamically an internal connection to the pythonSuperFilter. 
       * It is called when a new output of the pythonFilter is used in the workflow.
       * It creates an internal input slot for this output.
       * \param gc the garbage collector associated with this filter
       * \param fieldOut the output field of the pythonSuperFilter
       * \param arg the argument name/idx associated to the output field
       */
       void createInternalFieldOut(CGarbageCollector& gc, CField& fieldOut, NodeId nodeId, int argoutIdx, size_t internalIdx);

      /*!
       * Method to apply the filter transformation on the input data packets.
       * For this filter, no transformation is applied since its done by the pythonFilter.
       * It still register the timestamp of the data to ensure the offload data are received at the right time.
       * \param data the input data packets
       */
      std::vector<CDataPacketPtr> apply(std::vector<CDataPacketPtr> data) override;

      /*!
       * Method to check if the filter is expecting offloaded data.
       * \return true if the filter is expecting offloaded data, false otherwise
       */
      bool isExpectingOffloadData();

      /*!
       * Method to register the reception of offloaded data.
       * It increments the counter of received offloaded data.
       */
      void receivedOffloadedData();

      /*!
       * Method to check if all expected offloaded data have been received.
       * If not, it triggers the event loop until all data are received.
       */
      void checkForLateData(void);






    private:

      std::shared_ptr<CPythonFilter> pythonFilter_; // PythonFilter associated to this pythonSuperFilter
      std::queue<Time> expectedData_;               // FIFO to handle asynchronism and keep track of waiting timestamps
      int nbReceivedOffloadedData_= 0 ;             // Counter to ensure all the lateData arrived     

  };
 
}


#endif //__XIOS_COffloadPythonSuperFilter