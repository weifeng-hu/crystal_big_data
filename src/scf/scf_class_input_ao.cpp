#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "tensor.h"
#include "scf_class_input_ao.h"
#include <Python.h>
#include "../py/interface.h"
#include "../py/py_api.h"

using namespace std;

namespace ithaca { namespace scf {
// Constructor for Input_AO

Input_AO::Input_AO( ithaca::scf::cmd_options cmd_opt )
{

  cout << endl << ">>> scf::Input_AO constructor " << endl << endl;

  cout << "    initializing python interface  " ;
  char* _input_path = cmd_opt._infile_path;
  ithaca::py::interface PY( _input_path );
  cout << "    ................. success "  << endl;

//  ^  ^
// (=  =)
// ( \/ )
//
// Read the scf input parameters

//  this->basis = ithaca::py::get_value <char> ( "scf.basis", PY );

  cout << "    reading required parameters from input file                      " << endl; 
  this->nele  = ithaca::py::get_value <int>  ( "scf.nele", PY );       cout << "    scf.nele ........ success" << endl;
  this->ns  = ithaca::py::get_value <double> ( "scf.ns", PY );         cout << "    scf.ns   ........ success"   << endl ;
  this->coord = ithaca::py::get_vector < std::vector<ithaca::scf::coordinate> > ( "scf.coord", PY );           cout << "    scf.coord ................. success " << endl;
  cout << endl;

// diis
  if( cmd_opt.diis_is_set == true  ){ this->diis = 1; }
  else if( cmd_opt.diis_is_set == false ){
    this->diis = ithaca::py::get_value<int> ( "scf.diis", PY );
    if( diis == -1 ){ diis = DEFAULT_DIIS; } // Note: why are we using -1 here? The python interface will get "undefined_option" does not match the desired data type. The python function will return a  -1.
  }

// scf_tolerance
  if( cmd_opt.scf_tol_is_set == true ){ this->scf_tol = atof( (char*) (cmd_opt.scf_tol).c_str() ); }
  else if( cmd_opt.scf_tol_is_set == false ){
    this->scf_tol = ithaca::py::get_value<double> ( "scf.scf_tol", PY );
    if( scf_tol == -1 ){ scf_tol = DEFAULT_SCF_TOL; }
  }

// initial guess
  if( cmd_opt.init_guess_is_set == true ){ this->init_guess = cmd_opt.init_guess; }
  else if( cmd_opt.init_guess_is_set == false ){ 
    this->init_guess = ithaca::py::get_string<std::string> ( "scf.init_guess", PY );
    if( init_guess == "undefined_option"){ init_guess = DEFAULT_GUESS; }
  }

  this->natom = coord.size();  // Note: The python interface above does not return the natom, however, this value can be given by the size of coordinate vector.
  this->na = static_cast<int>(nele + 2 * ns)/2;
  this->nb = static_cast<int>(nele - 2 * ns)/2;

  this->nbas = 2;
  this->norb = 2;

// print the numbers out

  cout << endl;
  cout << "     scf.nele   number of electrons       = " << nele << endl;
  cout << "     scf.na     number of alpha electrons = " << na << endl;
  cout << "     scf.nb     number of beta electrons  = " << nb << endl;
  cout << "     scf.ns     spin                      = " << ns << endl;
  cout << endl; unit = "angstrom";
  cout << "     atomic coordinates(" << this->unit << "):" << endl;

  std::vector <ithaca::scf::coordinate> :: iterator iter;
  for( iter = coord.begin(); iter < coord.end(); iter++ ){
     char* a = (char*) (iter->element).c_str();
     double b1 = iter->x; 
     double b2 = iter->y;
     double b3 = iter->z;
     printf( "       %s     %14.6f     %14.6f     %14.6f\n", a, b1, b2, b3);
  }
  cout << endl;
  cout << "     scf.diis   use diis or not           = " << diis << endl;
  cout << "     scf.tol    scf convergence tolerance = " << scf_tol << endl;
  cout << "     scf.init_guess    scf initial guess  = " << init_guess << endl;

} // end of Input_AO::Input_AO

}}
