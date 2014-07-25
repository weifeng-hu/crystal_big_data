#include <stdlib.h>
#include <iostream>
#include <Python.h>
#include <vector>
#include "../scf/scf_class_input_ao.h"
#include "py_vector.h"

using namespace std;

namespace ithaca { namespace py {

template <>
std::vector<ithaca::scf::coordinate> vtr( PyObject* vtr_ptr )
{

  int size = PyTuple_Size( vtr_ptr ); // Note: after python 2.5, the return type of PyTuple_Size is int, otherwise it is Py_ssize_t //

  if( size%4 > 0 ){
   cout << " Error: The coordinate input is not complete. Please check. " << endl;
   cout << endl;
   cout << "        The correct format is like: " << endl;
   cout << "          scf.coord = ( 'h', 0.000, 0.000, 1.000, " << endl;
   cout << "                        'h', 0.000, 0.000, 1.000 )" << endl;
   cout << endl;
   cout << "        There must be 4*n values in the parentheses. " << endl;
   exit(1);
  }

  int natom = size /4;

// construct the std::vector data structure for the coordinates. This is the first time that I use std::vector. Seems cool.
  std::vector<ithaca::scf::coordinate> retval;

// put the values into the data structure
  int pos = 0;
  for( int i = 0; i < natom; i++ ){

    ithaca::scf::coordinate coord;
    
    std::string str = PyString_AsString( PyTuple_GetItem( vtr_ptr, pos ) );
    coord.element = str;
    coord.x = PyFloat_AsDouble( PyTuple_GetItem( vtr_ptr, pos + 1 ));
    coord.y = PyFloat_AsDouble( PyTuple_GetItem( vtr_ptr, pos + 2 ));
    coord.z = PyFloat_AsDouble( PyTuple_GetItem( vtr_ptr, pos + 3 ));
    
    retval.push_back(coord);

//    cout << coord.element << " " << coord.x << " " << coord.y << " " << coord.z << " " << endl;

    pos = pos + 4;
  }
  
  return retval;

}; 

} } // end of ithaca::py
