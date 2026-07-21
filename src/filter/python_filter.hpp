#ifndef __XIOS_CPythonFilter
#define __XIOS_CPythonFilter

#include "filter.hpp"
#include "filter_engine.hpp"

namespace xios
{
  class CVariable;
  class CFunction;


  /*!
   * A filter that apply a transformation described in a python script
   */
  class CPythonFilter : public CFilter, public IFilterEngine
  {

    public:

      /*!
       * Constructs a PythonFilter.
       *
       * \param gc the garbage collector associated with this filter
       * \param function the function associated to this filter
       * \param superFilterId the unique representation of its superFilter
       */
      CPythonFilter(CGarbageCollector& gc, CFunction& function, NodeId superFilterId);

      // Destructor
      ~CPythonFilter();

      /*!
       * Applies the filter to the input data. The transformation is described in a python script associated to the function.
       * \param data the input data
       * \return the filtered data
       */
      std::vector<CDataPacketPtr> virtual apply(std::vector<CDataPacketPtr> data);
      
    private:

      CFunction& function_;  //!< The function associated to this filter
      bool isInitialized_;   //!< Whether the filter has been initialized
      NodeId superFilterId_; //!< The unique representation of its superFilter
      int pyFilterIdx_;      //!< The index of the Python filter

  };

}



#endif // __XIOS_CPythonFilter