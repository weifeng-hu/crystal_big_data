#include <Python.h>
#include <iostream>
#include <string>
#include "interface.h"
#include "py_api.h"

using namespace std;

int main( int argc, char* argv[] )
{

  std::string input_path = "/home/wh288/ithaca/py/input.py";
  char* _input_path = (char*)input_path.c_str();
  ithaca::py::interface PY(_input_path);

  int i = ithaca::py::get_value<int>( "dmrg.nsites" , PY);
  int j = ithaca::py::get_value<int>( "dmrg.max_sweep.undefined_option", PY);

  cout << i << endl;
  cout << j << endl;

  exit(1);

  PyObject* pyobj,*global,*local,*string;
  PyObject* sub;
  PyObject* retval;
  FILE* fp;

  char* h2;

  global == NULL;

  Py_Initialize();

  global = PyImport_AddModule("__main__");
  if( global == NULL ) cout << " global is NULL " << endl;
  local  = global;

  char* file = const_cast<char*>("input.py");
  char* r = (char*)("r");
  PyObject *m = PyFile_FromString( file,r);
  if( m == NULL ) cout << "file not found" << endl; 
//  PyRun_AnyFile(fp,"input.py");

  PyObject* main_dict = PyModule_GetDict(global);

  pyobj = PyRun_File( PyFile_AsFile(m), (char*)("input.py") , Py_file_input, main_dict, main_dict );
  if( pyobj == NULL ) cout << "file NULL" << endl;

  string = PyString_FromString("dmrg");

  retval = PyImport_ImportModule("__main__");

  cout << PyObject_HasAttr( retval, string ) << endl;

  PyObject* input  = PyString_FromString("input");
  PyObject* dmrg   = PyString_FromString("dmrg");
  PyObject* mod  = PyImport_Import(input);

  cout << PyObject_HasAttr( mod, dmrg ) << endl;

   
  dmrg = PyObject_GetAttrString( global, "dmrg" );

  if( dmrg == NULL ) cout << "NULL" << endl;


  const char* substring = "oneintegral";

  cout << PyObject_HasAttrString( dmrg, substring ) << endl;
  sub = PyObject_GetAttrString( dmrg, substring );

  if( sub == NULL ) cout << "NULL" << endl;
  h2 = PyString_AsString( sub );
  cout << h2 << endl;

  Py_Finalize();

}
