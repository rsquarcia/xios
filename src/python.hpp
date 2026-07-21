#ifndef __PYTHON_HPP__
#define __PYTHON_HPP__

#ifdef USE_PYTHON

  #define PY_SSIZE_T_CLEAN
  #include <Python.h>
  #include <numpy/arrayobject.h>

#else

  #include "exception.hpp"

  namespace xios
  {

    // ========================
    // Basic fake types
    // ========================

    struct PyObject {};
    struct PyArrayObject : PyObject {};

    typedef int PyGILState_STATE;

    typedef long Py_ssize_t;
    typedef long npy_intp;

    // ========================
    // Central error trigger
    // ========================

    inline void python_not_available()
    {
      ERROR("python_not_available()",
            "Python support is not enabled (you must compile with --use_python)");
    }

    // ========================
    // Python core API
    // ========================

    inline int Py_IsInitialized()
    {
      return 0;
    }

    inline void Py_Initialize()
    {
      python_not_available();
    }

    inline int Py_FinalizeEx()
    {
      python_not_available();
      return -1;
    }

    inline PyGILState_STATE PyGILState_Ensure()
    {
      python_not_available();
      return 0;
    }

    inline void PyGILState_Release(PyGILState_STATE)
    {
      python_not_available();
    }

    inline PyObject* PyImport_ImportModule(const char*)
    {
      python_not_available();
      return nullptr;
    }

    inline PyObject* PyObject_GetAttrString(PyObject*, const char*)
    {
      python_not_available();
      return nullptr;
    }

    inline PyObject* PyObject_CallObject(PyObject*, PyObject*)
    {
      python_not_available();
      return nullptr;
    }

    inline PyObject* PyObject_CallMethod(PyObject*, const char*, const char*, ...)
    {
      python_not_available();
      return nullptr;
    }

    inline PyObject* PyObject_Str(PyObject*)
    {
      python_not_available();
      return nullptr;
    }

    inline const char* PyUnicode_AsUTF8(PyObject*)
    {
      python_not_available();
      return nullptr;
    }

    inline PyObject* PyUnicode_FromString(const char*)
    {
      python_not_available();
      return nullptr;
    }

    inline int PyUnicode_Check(PyObject*)
    {
      return 0;
    }

    inline PyObject* PySys_GetObject(const char*)
    {
      python_not_available();
      return nullptr;
    }

    inline int PyList_Append(PyObject*, PyObject*)
    {
      python_not_available();
      return -1;
    }

    inline PyObject* PyLong_FromLong(Py_ssize_t)
    {
      python_not_available();
      return nullptr;
    }

    // ========================
    // Dict API
    // ========================

    inline PyObject* PyDict_New()
    {
      python_not_available();
      return nullptr;
    }

    inline int PyDict_SetItem(PyObject*, PyObject*, PyObject*)
    {
      python_not_available();
      return -1;
    }

    // ========================
    // Tuple API
    // ========================

    inline PyObject* PyTuple_New(Py_ssize_t)
    {
      python_not_available();
      return nullptr;
    }

    inline int PyTuple_SetItem(PyObject*, Py_ssize_t, PyObject*)
    {
      python_not_available();
      return -1;
    }

    inline PyObject* PyTuple_GetItem(PyObject*, Py_ssize_t)
    {
      python_not_available();
      return nullptr;
    }

    inline Py_ssize_t PyTuple_Size(PyObject*)
    {
      python_not_available();
      return 0;
    }

    inline int PyTuple_Check(PyObject*) { return 0; }

    // ========================
    // Reference counting
    // ========================

    inline void Py_DECREF(PyObject*)
    {
      python_not_available();
    }

    inline void Py_XDECREF(PyObject*)
    {
      python_not_available();
    }

    // ========================
    // Errors
    // ========================

    inline int PyErr_Occurred() { return 0; }

    inline void PyErr_Print()
    {
      python_not_available();
    }

    inline void PyErr_Fetch(PyObject**, PyObject**, PyObject**) {}

    inline void PyErr_NormalizeException(PyObject**, PyObject**, PyObject**) {}

    inline int PyType_Check(PyObject*) { return 0; }

    // ========================
    // NumPy API
    // ========================

    inline void import_array1()
    {
      python_not_available();
    }

    inline PyObject* PyArray_SimpleNew(int, npy_intp*, int)
    {
      python_not_available();
      return nullptr;
    }

    inline void* PyArray_DATA(PyArrayObject*)
    {
      python_not_available();
      return nullptr;
    }

    inline int PyArray_TYPE(PyArrayObject*)
    {
      python_not_available();
      return 0;
    }

    inline int PyArray_NDIM(PyArrayObject*)
    {
      python_not_available();
      return 0;
    }

    inline npy_intp PyArray_SIZE(PyArrayObject*)
    {
      python_not_available();
      return 0;
    }

    inline int PyArray_Check(PyObject*)
    {
      return 0;
    }

    #define NPY_DOUBLE 0

  }

#endif // USE_PYTHON

#endif // __PYTHON_HPP__
