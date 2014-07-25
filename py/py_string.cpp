#include <string>
#include <Python.h>
#include <py_string.h>

namespace ithaca { namespace py {

template <>
std::string strg( PyObject* strg_ptr )
{
  return static_cast<std::string>( PyString_AsString( strg_ptr ) );
}

} } // end of ithaca::py
