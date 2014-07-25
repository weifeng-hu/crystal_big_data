#include "../BOOST/boost/tokenizer.hpp"
#include <iostream>
#include "py_value.h"
#include "py_string.h"
#include "py_structure.h"
#include "py_vector.h"

using namespace std;

namespace ithaca { namespace py {

PyObject* GetAttr( std::string opt_name, PyObject* module )
{
  boost::char_separator<char> sep(".");
  boost::tokenizer<boost::char_separator<char> > opt_name_iter( opt_name, sep );

  PyObject* obj = module;
  boost::tokenizer<boost::char_separator<char> >::iterator i;

  for( i = opt_name_iter.begin(); i != opt_name_iter.end(); i++ ){
    std::string attr_name = *i;
    if( !PyObject_HasAttrString( obj, attr_name.c_str() ) ){
      cout << "    Error: The option [" << attr_name << "] is not in the dictionary --- Abort. " << endl;
      exit(1);
    }

    PyObject* string_ptr = PyObject_GetAttrString( obj, attr_name.c_str()  );
    obj = string_ptr;

    if( PyObject_HasAttrString( obj, const_cast<char*>("required_option") ) ){
      cout << "    Error: The option [" << opt_name << "] is a required option but not yet defined --- Abort. " << endl;
      exit(1);
    }

    if( PyObject_HasAttrString( obj, const_cast<char*>("undefined_option")) ){
      cout << "    Note: The option [" << opt_name << "] has not been defined but is not an essential one, default setting will be used. " << endl;
      obj = PyString_FromString("undefined_option");
    }

  }

  return obj;
}

template < typename T > inline 
T get_value( const std::string opt_name, ithaca::py::interface PY )
{
   return value<T>( GetAttr( opt_name, PY.main_module) );
//  T retval;
//  PyObject* val_ptr = GetAttr( opt_name, PY.main_module );
//  retval = value<T>( val_ptr );
//  return retval;
}

template < typename T > inline
T get_string( const std::string opt_name, ithaca::py::interface PY )
{
   return strg<T>( GetAttr( opt_name, PY.main_module) );
}

template < typename T > inline
T get_structure( const std::string opt_name, ithaca::py::interface PY )
{
  return structure <T> ( GetAttr( opt_name, PY.main_module) );
}

template < typename T > inline 
T get_vector( const std::string opt_name, ithaca::py::interface PY )
{
  return vtr<T> ( GetAttr( opt_name, PY.main_module) );
}


} } // end of ithaca::py
