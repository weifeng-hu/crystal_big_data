#include <Python.h>
#include <iostream>
#include "interface.h"

using namespace std;

namespace ithaca { namespace py {

interface::interface( char* input_path )
{
  this->main_module = NULL;
  this->main_dict   = NULL;
  this->pyfile      = NULL;
  this->global      = NULL;
  this->local       = NULL;
  this->isInitialized = false;

// Initialize Python Environment
  Py_Initialize();
  if( Py_IsInitialized() )
  {
    this->isInitialized = true;
  }
  else
  {
    cout << "Python Environment cannot be initialized ---Abort; Please check the Python package in system " << endl;
    exit(1);
  }

// build reference to the namespace main_module and main dictionary 
  this->main_module = PyImport_AddModule( "__main__" );
  if(this->main_module == NULL ){
      cout << " failure in PyImport_AddModule( '__main__') --- Abort ; Please check the Python envrionment " << endl;
      exit(1); 
  }
  this->main_dict = PyModule_GetDict( this->main_module );
  if(this->main_module == NULL ){
      cout << " failure in PyObject_GetDict(main_module) --- Abort ; Please check the Python envrionment " << endl;
      exit(1); 
  }

// Open scriptfile and run it
  FILE* fp = fopen( input_path, "r" );
  this->global = this->main_dict;
  this->local  = this->global;
  this->pyfile = PyRun_File( fp, input_path, Py_file_input, global, local );
  if( this->pyfile == NULL ){
    cout << " Python failed to execute the scriptfile, please check whether file exists or file path is correct or not " << endl;
    exit(1);
  }

}  // end of interface::interface

} } // end of ithaca::py
