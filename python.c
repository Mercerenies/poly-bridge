
#include <Python.h>
#include "python.h"
#include "assert.h"

static wchar_t* program;

void python_initialize(int* argc, char*** argv) {
  program = Py_DecodeLocale(argv[0][0], NULL);
  Py_SetProgramName(program);
  Py_Initialize();
}

void python_print(int n) {

  wchar_t *path = Py_DecodeLocale(".", NULL);
  PySys_SetPath(path);
  PyMem_RawFree(path);

  PyObject* module_name = PyUnicode_FromString("python");
  PyObject* module = PyImport_Import(module_name);
  Py_DECREF(module_name);
  assert(module != NULL);

  PyObject* func = PyObject_GetAttrString(module, "python_print");
  assert(func != NULL);
  assert(PyCallable_Check(func));

  PyObject* args = PyTuple_New(1);
  PyObject* value = PyLong_FromLong(n);
  assert(value);
  PyTuple_SetItem(args, 0, value);

  PyObject* result = PyObject_CallObject(func, args);
  Py_DECREF(args);
  Py_DECREF(result);
  Py_DECREF(func);
  Py_DECREF(module);

}

void python_release() {
  Py_Finalize();
  PyMem_RawFree(program);
}
