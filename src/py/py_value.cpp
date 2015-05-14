#include <Python.h>
#include "py_value.h"

namespace ithaca { namespace py {

template <> 
int value( PyObject* val_ptr )
{
  return static_cast<int>( PyInt_AsLong( val_ptr ) );
}

template <>
double value( PyObject* val_ptr )
{
  return static_cast<double>( PyFloat_AsDouble( val_ptr ) );
}

} } // end of ithaca::py
