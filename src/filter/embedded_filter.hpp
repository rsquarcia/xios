#ifndef __XIOS_CEmbeddedFilter
#define __XIOS_CEmbeddedFilter

#include <algorithm>

#include "filter.hpp"
#include "filter_engine.hpp"
#include "internal_input_pin.hpp"
#include "internal_output_pin.hpp"
#include "function.hpp"
#include "filter_graph_types.hpp"



namespace xios{

  class CEmbeddedFilter : public CFilter, public IFilterEngine
  {
    friend class CInternalInputPin;
    
    public:

      // Constructor 
      CEmbeddedFilter(CGarbageCollector& gc, CFunction& function);

      // Destructor
      ~CEmbeddedFilter();


      std::vector<CDataPacketPtr> apply(std::vector<CDataPacketPtr> data) override;
  
      // Connection methods


      /*!
       * connect a filter inputPin to the internalOutputPin
       *
       * \param inputPin the inputPin which is used to be connected
       * \param inputSlot the inputSlot of the inputPin
       * \param internalOutputSlot the outputSlot of the internalOutputPin
       */
      void connectInternalOutputPin(std::shared_ptr<CInputPin> inputPin, size_t inputSlot, size_t internalOutputSlot);

      /*!
       * connect a filter outputPin to the internalInputPin
       *
       * \param inputPoint the inputPoint which is used to be connected
       * \param argoutIdx
       */
      virtual void connectInternalInputPin(SInputPoint inputPoint, int argoutIdx);

      /*!
       * connect directly an internalOutputPin to an internalInputPin
       *
       * \param internalInputSlot the inputSlot of the internalInputSlot
       * \param internalOutputSlot the inputSlot of the internalOutputSlot
       */
      void connectInternal(size_t internalInputSlot, size_t internalOutputSlot);

      /*!
       * propagate the trigger to its internal filters
       *
       * \param timestamp the timestamp corresponding to the trigger
       */
      void trigger(Time timestamp) override;

       /*!
       * Get the function argoutIdx associate to the argoutName
       *
       * \param argoutName
       */
      size_t getFunctionArgoutIdx(SArg& arg);

      /**
       * Retrieve the `CField*` stored in the argin hash map for the given
       * argument identifier.
       *
       * @param arginId the argument identifier (optional)
       * @return pointer to the associated `CField`
       */
      CField* getFieldIn(const std::string& arginId = "");

      /**
       * Check if we ever ask for the given arg argOut
       *
       * @param arg the argout description (idx or named)
       * @return -1 if we ever met arg, otherwise the idx corresponding to arg
       */

      int isFirstOccurence(const SArg& arg);

      /**
       * virtual method that return the inputPoint corresponding to the last
       * one of the filters inside the embeddedFilter (just before the internalInputPin)
       *
       * @param gc the garbage collector
       * @param fieldOut the field of wich the filter result is 
       * @param nodeId the embeddedFilter id
       * @param argoutIdx the idx of the argout of the embeddedFilter we are reducing
       */

      virtual SInputPoint reduceFunction(CGarbageCollector& gc, CField& fieldOut, NodeId nodeId, int argoutIdx) = 0;

       /**
       * Add an entry into the arginMap_ at the position corresponding
       * to `arginIdx` associating the provided inputPin.
       *
       * @param arginIdx index of the argin slot
       * @param inputPoints the vector of inputPoints to add
       */
      void addInputPoints(std::vector<SInputPoint> inputPoints);

            // Getters
      /**
       * Return the number of internal output pin slots available for the
       * function.
       *
       * @return count of internal output pin slots
       */
      size_t getInternalOutputPinSlotNumber();

      /**
       * Get the slot index corresponding to the argument at idx argIdx of the
       * function. Used to translate argument indices to pin slots.
       *
       * @param argIdx argument index
       * @return slot index associated to the argument
       */
      size_t getArgSlotIdx(size_t argIdx);


      // arginHashMap
      /**
       * Retrieve the inputPoint stored in the arginMap_ for the given
       * argument identifier.
       *
       * @param arginId the argument identifier
       * @return the inputPoint associated to `arginId`
       */
      const SInputPoint getInputPointFromArgId(std::string arginId);

       /**
       * Return the SinputPoint associated to an output pin index.
       *
       * @param pinIdx the pin index
       * @return the field id string
       */
      SInputPoint getInputPointFromSlotIdx(size_t pinIdx);
      

    protected:

      void onInternalPacket(std::vector<CDataPacketPtr> packets);  
      void virtual onInputReady(std::vector<CDataPacketPtr> data);
      std::shared_ptr<CInternalOutputPin> internalOutputPin_;            // EmbeddedFilter internal outputPin
      std::shared_ptr<CInternalInputPin>  internalInputPin_;             // EmbeddedFilter internal intputPin      
      CFunction& function_;                                              // Function associated to this embeddedFilter
      std::map<string, SInputPoint> arginMap_;                           // Map from argin id to its SinputPoint representation (variable substitution)
      std::unordered_map<SInputPoint, size_t, SInputPointHash> slotMap_; // Map from argin representation to slot index
      std::map<size_t, size_t> internalSlotsMap_;                        // Map from arginIdx to slotIdx

  };
 
}


#endif //__XIOS_CEmbeddedFilter