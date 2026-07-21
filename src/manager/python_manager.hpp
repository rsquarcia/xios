#ifndef __XIOS_CPythonManager
#define __XIOS_CPythonManager

#include <python.hpp>
#include "exception.hpp"
#include "data_packet.hpp"
#include "function.hpp"
#include <iostream>


namespace xios
{
  class CVariable;

  /*!
   * A manager for Python operations within XIOS.
   */

  class CPythonManager
  {
    public:

      /*!
       * Returns the singleton instance of the Python manager.
       * \return The singleton instance of the Python manager.
       */
      static CPythonManager& instance();

      /*!
       * Initializes Python and or numpy if needed.
       */
      void initialize();

      /*!
       * Finalizes Python if it was initialized by the manager.
       */
      void finalize();

      /*!
       * Adds a path to the Python path.
       * \param path The path to add.
       */
      void addPythonPath(const std::string& path);

      /*!
       * Initializes a Python filter. Import the module, instantiate the class, and call the initialize method.
       * \param function The function associated with the filter.
       * \param nodeId The node ID of the filter.
       * \param contextId The context ID.
       * \return The instance index of the initialized Python filter.
       */
      int initializePythonFilter(CFunction& function, NodeId nodeId, const std::string& contextId);

      /*!
       * Applies a Python filter to the input data.
       * \param inputData The input data packets.
       * \param function The function associated with the filter.
       * \param pyFilterIdx The instance index of the Python filter.
       * \return The output data packets.
       */
      std::vector<CDataPacketPtr> applyPythonFilter(std::vector<CDataPacketPtr>& inputData, CFunction& function, int pyFilterIdx);

      /* A guard for managing the Python GIL (Global Interpreter Lock) */
      class GILGuard {
        PyGILState_STATE state_;

        public:
          GILGuard() : state_(CPythonManager::instance().getGIL()) {}
          ~GILGuard() { CPythonManager::instance().releaseGIL(state_);}
      };

      private:

        // Private constructor and destructor for singleton pattern
        CPythonManager();
        ~CPythonManager();
        CPythonManager(const CPythonManager&) = delete;
        CPythonManager& operator=(const CPythonManager&) = delete;

        /*!
       * Gets the Python GIL (Global Interpreter Lock).
       * \return The state of the GIL.
       */
        PyGILState_STATE getGIL();

        /*!
       * Releases the Python GIL (Global Interpreter Lock).
       * \param gstate The state of the GIL to release.
       */
        void releaseGIL(PyGILState_STATE gstate);

        /*!
       * Splits a file path into directory and module name.
       * \param filepath The file path to split.
       * \param dir The directory.
       * \param moduleName The module name.
       */
        void splitPath(const std::string& filepath, std::string& dir, std::string& moduleName);

        /*!
       * Converts a NumPy tuple to a vector of data packets.
       * \param numpyTuple The NumPy tuple to convert.
       * \param inputData The input data packets.
       * \return The converted data packets.
       */
        std::vector<CDataPacketPtr> numpyTupleToPackets(PyObject* numpyTuple, const std::vector<CDataPacketPtr>& inputData);

        /*!
       * Imports a Python module.
       * \param moduleName The name of the module to import.
       * \return The imported module.
       */

        PyObject* importModule(const std::string& moduleName);
        /*!
       * Instantiates a Python class.
       * \param pyModule The Python module.
       * \param function The function associated with the class.
       * \param nodeId The node ID of the class.
       * \param arginIds The IDs of the input arguments.
       * \param contextId The context ID.
       * \return The instantiated Python class.
       */

        PyObject* instanciatePyClass(PyObject* pyModule, CFunction& function, NodeId nodeId, std::vector<std::string> arginIds, const std::string& contextId);
        /*!
       * Applies a Python function.
       * \param functionId The ID of the function to apply.
       * \param pyFilter The Python filter.
       * \param args The arguments for the function.
       * \return The result of the function application.
       */

        PyObject* applyPython(const std::string& functionId, PyObject* pyFilter, PyObject* args);
        /*!
       * Applies the initialize method to a Python filter.
       * \param pyFilter The Python filter.
       * \return The result of the initialization.
       */
        PyObject* applyInitialize(PyObject* pyFilter);
        /*!

       * Converts a vector of data packets to a NumPy tuple.
       * \param packets The vector of data packets to convert.
       * \return The converted NumPy tuple.
       */
        PyObject* packetsToNumpyTuple(const std::vector<CDataPacketPtr>& packets);


        bool pythonInitialized_; // <! Boolean indicating if Python has been initialized
        bool pythonOwnedByXios_; // <! Boolean indicating if Python is owned by XIOS
        bool numpyInitialized_;  // <! Boolean indicating if NumPy has been initialized
        bool finalized_;         // <! Boolean indicating if Python has been finalized
        int filterCount_;        // <! Counter for the number of initialized Python filters

        std::map<int, PyObject*> pyFilterMap_;  // <! Map of Python filter instances indexed by their instance index
};

} // namespace xios

#endif // __XIOS_CPythonManager