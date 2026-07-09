#include "python_manager.hpp"
#include "field.hpp"
#include "python.hpp"
#include "function.hpp"

namespace xios
{

  CPythonManager& CPythonManager::instance()
  {
    static CPythonManager singleton;
    return singleton;
  }

  CPythonManager::CPythonManager()
    : pythonInitialized_(false),
      numpyInitialized_(false),
      finalized_(false),
      filterCount_(0)
    {
      if (Py_IsInitialized())
        pythonInitialized_ = true;
    }

  CPythonManager::~CPythonManager()
  {
    finalize();
  }

  void CPythonManager::initialize()
  {
    if (!pythonInitialized_)
    {
      if (Py_IsInitialized())
        pythonOwnedByXios_ = false;
      else
      {
        Py_Initialize();
        pythonOwnedByXios_ = true;
      }
      if (PyErr_Occurred())
            ERROR("CPythonManager::initialize()", "Python initialization failed");
      pythonInitialized_ = true;
    }

    GILGuard gil;

    if (!numpyInitialized_)
    {
      import_array1();
      numpyInitialized_ = true;
    }
  }

  void CPythonManager::finalize()
  {
    if (pythonInitialized_ && !finalized_)
    {
      if (pythonOwnedByXios_)
      {
        // Stop all Python threads if you have any
        PyGILState_Ensure();  // Acquire GIL (safe for shutdown)
        Py_FinalizeEx();      // Safely finalize Python interpreter
        pythonInitialized_ = false;

      }
      finalized_ = true;
    }
    // else ERROR("void CPythonManager::finalize()", "Python finalization failed")
  }

  PyGILState_STATE CPythonManager::getGIL()
  {
    if (!pythonInitialized_)
        ERROR("CPythonManager::getGIL()", "Python not initialized");

    return PyGILState_Ensure();
  }

  void CPythonManager::releaseGIL(PyGILState_STATE gstate)
  {
    PyGILState_Release(gstate);
  }

  void CPythonManager::splitPath(const std::string& filepath, std::string& dir, std::string& moduleName)
  {
    size_t slashPos = filepath.find_last_of("/\\");
    if (slashPos != std::string::npos)
        dir = filepath.substr(0, slashPos);
    else
        dir = ".";

    std::string filename = filepath.substr(slashPos + 1);

    size_t dotPos = filename.rfind('.');
    if (dotPos != std::string::npos && filename.substr(dotPos) == ".py")
        moduleName = filename.substr(0, dotPos);
    else
        moduleName = filename;
  }

  void CPythonManager::addPythonPath(const std::string& dir)
  {
    if (!pythonInitialized_)
      ERROR("void CPythonManager::addPythonPath(const std::string& path)",
            " Python must be initialized before");

    PyObject* sysPath = PySys_GetObject("path");
    if (!sysPath)
      ERROR("void CPythonManager::addPythonPath(const std::string& path)",
            " Error getting sysPath");

    PyObject* pyPath = PyUnicode_FromString(dir.c_str());
    if (!pyPath)
    ERROR("void CPythonManager::addPythonPath(const std::string& path)",
            "Failed to convert path to Python string");

    int result = PyList_Append(sysPath, pyPath);
    Py_DECREF(pyPath);

    if (result != 0)
    ERROR("void CPythonManager::addPythonPath(const std::string& path)",
            "Failed to append path to sys.path");
  }

  PyObject* CPythonManager::importModule(const std::string& filepath)
  {
    std::string dir;
    std::string moduleName;
    splitPath(filepath, dir, moduleName);

    GILGuard guard;
    addPythonPath(dir);

    PyObject* pModule = PyImport_ImportModule(moduleName.c_str());
    if (!pModule)
    {
        PyObject *exc_type = nullptr, *exc_value = nullptr, *exc_traceback = nullptr;
        PyErr_Fetch(&exc_type, &exc_value, &exc_traceback);
        PyErr_NormalizeException(&exc_type, &exc_value, &exc_traceback);

        std::string errorMessage = "Unknown error";

        if (exc_value)
        {
            PyObject* strObj = PyObject_Str(exc_value);
            if (strObj && PyUnicode_Check(strObj))
            {
                const char* utf8 = PyUnicode_AsUTF8(strObj);
                if (utf8)
                    errorMessage = utf8;
            }
            Py_XDECREF(strObj);
        }

        std::string errorType = "Unknown exception";

        if (exc_type && PyType_Check(exc_type))
        {
            PyObject* typeName = PyObject_GetAttrString(exc_type, "__name__");
            if (typeName && PyUnicode_Check(typeName))
            {
                const char* utf8 = PyUnicode_AsUTF8(typeName);
                if (utf8)
                    errorType = utf8;
            }
            Py_XDECREF(typeName);
        }
        ERROR("PyObject* CPythonManager::importModule",
            << "Failed to import Python module '" << moduleName << "'\n"
            << "Exception type:    " << errorType << "\n"
            << "Exception details: " << errorMessage);

        Py_XDECREF(exc_type);
        Py_XDECREF(exc_value);
        Py_XDECREF(exc_traceback);
    }

    return pModule;
  }

  PyObject* CPythonManager::instanciatePyClass(PyObject* pyModule, CFunction& function, NodeId nodeId, std::vector<std::string> arginIds, const std::string& contextId)
  {
    GILGuard guard;
    PyObject* pyClass = PyObject_GetAttrString(pyModule, function.getId().c_str());
    if (!pyClass) {
        PyErr_Print();
        ERROR("CPythonManager::applyPythonFilter",
              "Failed to get class '" + function.getId() + "' from module");
    }
    PyObject* varDict = PyDict_New();
    PyObject* fieldDict = PyDict_New();
    PyObject* arginIdsPyTuple = PyTuple_New(function.getNumArgin());

    int idx = 0;

    for (const CFunction::SArgIn& arg : function.getArgs(nodeId))
    {
      PyObject* key = PyLong_FromLong(idx);
      PyObject* value = PyUnicode_FromString(arg.getId().c_str());
      if (arg.type == CFunction::SArgIn::Field)
        PyDict_SetItem(fieldDict, key, value);
      else
        PyDict_SetItem(varDict, key, value);
      PyTuple_SetItem(arginIdsPyTuple, idx, PyUnicode_FromString(function.getArgin()[idx].c_str())); 
      Py_DECREF(key);
      Py_DECREF(value);
      ++idx;
    }

    PyObject* args = PyTuple_New(4);
    PyTuple_SetItem(args, 0, PyUnicode_FromString(contextId.c_str())); 
    PyTuple_SetItem(args, 1, fieldDict); 
    PyTuple_SetItem(args, 2, varDict); 
    PyTuple_SetItem(args, 3, arginIdsPyTuple); 
    PyObject* instancePyClass = PyObject_CallObject(pyClass, args);
    if (!instancePyClass)
    {
      PyErr_Print(); 
      ERROR("CPythonManager::instanciatePyClass",
            "Python class instantiation failed");
    }
    return instancePyClass;
  }


  PyObject* CPythonManager::applyPython(const std::string& functionId, PyObject* pyFilter, PyObject* args) {
    GILGuard gil;

    PyObject* result = PyObject_CallMethod(pyFilter, "_framework_process",  "O", args);

    if (!result) {
        PyErr_Print(); 
        ERROR("CPythonManager::applyPythonFilter",
              "Call to '" + functionId + "' failed");
    }
    return result;
  }


  PyObject* CPythonManager::applyInitialize(PyObject* pyFilter) {
    GILGuard gil;

    PyObject* result = PyObject_CallMethod(pyFilter, "_framework_initialize", NULL);

    if (!result) {
        PyErr_Print();
        ERROR("CPythonManager::applyInitialize",
              "Call to intialize method failed");
    }
    return result;
  }


  PyObject* CPythonManager::packetsToNumpyTuple(const std::vector<CDataPacketPtr>& packets)
  {
    GILGuard gil;
    PyObject* numpyTuple = PyTuple_New(packets.size());
    if (!numpyTuple)
       ERROR("PyObject* CPythonManager::packetsToNumpy(const std::vector<CDataPacketPtr>& packets)",
            "Failed to allocate tuple for packets");

    for (size_t i = 0; i < packets.size(); ++i)
    {
      const auto& packet = packets[i];
      npy_intp dims[1] = { static_cast<npy_intp>(packet->data.numElements()) };
      PyObject* arr = PyArray_SimpleNew(1, dims, NPY_DOUBLE);
      if (!arr)
      {
        Py_DECREF(numpyTuple);
         ERROR("PyObject* CPythonManager::packetsToNumpy(const std::vector<CDataPacketPtr>& packets)",
            "Failed to allocate numpy array for packets");
      }
      std::memcpy(PyArray_DATA((PyArrayObject*)arr),
                  packet->data.dataFirst(),
                  packet->data.numElements() * sizeof(double));
      
      PyTuple_SetItem(numpyTuple, i, arr);
    }
    return numpyTuple;
  }

  std::vector<CDataPacketPtr> CPythonManager::numpyTupleToPackets(PyObject* numpyTuple, const std::vector<CDataPacketPtr>& inputData)
  {
    GILGuard gil;
    std::vector<CDataPacketPtr> packets;
    if (!PyTuple_Check(numpyTuple))
        ERROR("std::vector<CDataPacketPtr> CPythonManager::numpyTupleToPackets(PyObject* numpyTuple, const std::vector<CDataPacketPtr>& inputData)",
              "Expected a python tuple");

    Py_ssize_t n = PyTuple_Size(numpyTuple);
    packets.reserve(n);

    for (Py_ssize_t i = 0; i < n; ++i)
    {
        PyObject* arrObj = PyTuple_GetItem(numpyTuple, i);
        if (!arrObj)
        {
          PyErr_Print();
          ERROR("std::vector<CDataPacketPtr> CPythonManager::numpyTupleToPackets(PyObject* numpyTuple, const std::vector<CDataPacketPtr>& inputData)",
                "PyTuple_GetItem returned NULL");
        }
        if (!PyArray_Check(arrObj))
            ERROR("std::vector<CDataPacketPtr> CPythonManager::numpyTupleToPackets(PyObject* numpyTuple, const std::vector<CDataPacketPtr>& inputData)",
                  "Tuple element is not a numpy array");

        PyArrayObject* arr = reinterpret_cast<PyArrayObject*>(arrObj);

        if (PyArray_TYPE(arr) != NPY_DOUBLE || PyArray_NDIM(arr) != 1)
            ERROR("std::vector<CDataPacketPtr> CPythonManager::numpyTupleToPackets(PyObject* numpyTuple, const std::vector<CDataPacketPtr>& inputData)",
                  "Expected a 1D numpy array of double");

        npy_intp size = PyArray_SIZE(arr);
        double* dataPtr = static_cast<double*>(PyArray_DATA(arr));
        if (!dataPtr)
          ERROR("std::vector<CDataPacketPtr> CPythonManager::numpyTupleToPackets(PyObject* numpyTuple, const std::vector<CDataPacketPtr>& inputData)",
                "PyArray_DATA returned NULL");

        CDataPacketPtr packet(new CDataPacket);
        if (inputData.empty())
          ERROR("std::vector<CDataPacketPtr> CPythonManager::numpyTupleToPackets(PyObject* numpyTuple, const std::vector<CDataPacketPtr>& inputData)",
                "inputData is empty");

        packet->date       = inputData[0]->date;
        packet->timestamp  = inputData[0]->timestamp;
        packet->status     = inputData[0]->status;

        if (packet->status == CDataPacket::NO_ERROR) 
        {
          packet->data.resize(size);
          for (npy_intp j = 0; j < size; ++j)
              packet->data(j) = dataPtr[j];
        }

        packets.push_back(packet);

    }

    return packets;
}

  int CPythonManager::initializePythonFilter(CFunction& function, NodeId nodeId, const std::string& contextId)
  {
    PyObject* pyModule = importModule(function.getPySrc());
    PyObject* pyFilter = instanciatePyClass(pyModule, function, nodeId, function.getArgin(), contextId);
    PyObject* result = applyInitialize(pyFilter);
    Py_DECREF(result);
    pyFilterMap_[filterCount_] = pyFilter;
    filterCount_ = filterCount_ + 1;
    return filterCount_ - 1;
  }

  std::vector<CDataPacketPtr> CPythonManager::applyPythonFilter(std::vector<CDataPacketPtr>& inputData, CFunction& function, int pyFilterIdx)
  {
    PyObject* args = packetsToNumpyTuple(inputData);
    PyObject* res = applyPython(function.getId(), pyFilterMap_[pyFilterIdx], args);
    return numpyTupleToPackets(res, inputData);
  }


} // namespace xios
