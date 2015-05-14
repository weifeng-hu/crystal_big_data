#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp> // case insensitive string comparison
#include <boost/filesystem.hpp>
#include "iquads/command.h"

using namespace std;
using namespace boost;

namespace iquads {

struct command
{

void read_input( const string input )
{

   this->input = input;

   {
    filesystem::path workdir_tmp = filesystem::current_path();
    this->workdir = workdir_tmp.string();
   }

   // determine the op_code_name
   {
    string input_tmp = input;
    vector<string> fields;
    split( fields, input, algorithm::is_any_of("."), algorithm::token_compress_on);
    this->op_code_name = fields.at(0);
   }

   // get coordinate and instruction keywords
   ifstream f_input;
   f_input.open( input.c_str(), std::ios::in );
   while( f_input.eof() == false )
   {
     string entry;
     f_input >> entry;
     if( iequals( entry, "coord" ) || iequals( entry, "coordinate" ) ){
      vector< tuple < string, double, double, double > > coord_temp;

      int ncoord;
      f_input >> ncoord;
      for( int i = 0; i < ncoord; i++ ){
       tuple< string, double, double, double > single_coord;
       {
        string element; double x,y,z;
        f_input >> element >> x >> y >> z; 
        single_coord = make_tuple( element, x, y, z );
       }
       coord_tmp.push_back( single_coord );
      } // end of for

      this->coord.set_store() = coord_temp;
      this->coord_is_set = true;
     }
     else if( iequals( entry, "instruct_keywd" ) )
     {
      char line[256];
      ifstream.getline( line, 256 );
      entry = line;
      {
       vector<string> fields;
       split( fields, entry, algorithm::is_any_of(", \t"), algorithm::token_compress_on );
       this->instruct_key = fields;
      }
      if( this->instruct_key.size() > 0 ){
       this->instruct_key_is_set = true;
      }
     } // end of if
   } // end of while

}

void setup_instructions()
{

  this->instruct.init();

  const int n_instruct = this->instruct_key.size();
  for( int i = 0; i < n_instruct; i++ ){
   const string keyword = this->instruct_key.at(i);

   instruct.set_instruct_keyword() = keyword;

   if( iequals( keyword, "qm") ){
     instruct.request_quantum_mechanics();
   }
   else if( iequals( keyword, "scf" ) ){
     instruct.request_quantum_mechanics();
     instruct.request_mean_field();
   }
   else if( iequals( keyword, "excited_state" ) || iequals( keyword, "multi_state") )
   {
     instruct.request_quantum_mechanics();
     instruct.request_mean_field();
     instruct.request_multi_reference();
   }
   else if( iequals( keyword, "mr") ){
     instruct.request_quantum_mechanics();
     instruct.request_multi_reference();
   }
   else if( iequals( keyword, "dmrg" ) || iequals( keyword, "mps" ) || iequals( keyword, "tns" ) ){
     instruct.request_quantum_mechanics();
     instruct.request_mean_field();
     instruct.request_multi_reference();
     instruct.request_nonlinear_wavefunction();
   }
   else if( iequals( keyword, "orb_opt" ) ){
     instruct.request_quantum_mechanics();
     instruct.request_mean_field();
     instruct.request_multi_reference();
     instruct.request_orbital_optimization();
   }
   else if( iequals( keyword, "lrt" ) ){
     instruct.request_quantum_mechanics();
     instruct.request_mean_field();
     instruct.request_linear_response();
   }
   else if( iequals( keyword, "energy_grad" ) ){
     instruct.request_quantum_mechanics();
     instruct.request_mean_field();
     instruct.request_multi_perturbation();
     instruct.request_energy_gradient();
   }
   else if( iequals( keyword, "geo_opt" ) ){
     instruct.request_energy_gradient();
     instruct.request_nuclei_relaxation();
   }
   else if( iequals( keyword, "electron_propagation" ) ){
     instruct.request_quantum_mechanics();
     instruct.request_electron_relaxation();
     instruct.request_time_evolved();
     instruct.request_quantum_dynamics();
   }
   else if( iequals( keyword, "nonadiabatic" ) ){
     instruct.request_quantum_mechanics();
     instruct.request_mean_field();
     instruct.request_multi_reference();
     instruct.request_multi_state();
     instruct.request_linear_response();
     instruct.request_multi_perturbation();
     instruct.request_nonadiabatic();
   }
   else if( iequals( keyword, "md" ) ){
     instruct.request_energy_gradient();
     instruct.request_nuclei_relaxation();
     instruct.request_time_evolved();
   }
   // idiomatic keywords
   else if( iequals( keyword, "dmrgci" ) || iequals( keyword, "ss_dmrgci" ) )
   {
     instruct.request_quantum_mechanics();
     instruct.request_mean_field();
     instruct.request_multi_reference();
     instruct.request_nonlinear_wavefunction();
   }
   else if( iequals( keyword, "dmrgscf" ) || iequals( keyword, "ss_dmrgscf" ) )
   {
     instruct.request_quantum_mechanics();
     instruct.request_mean_field();
     instruct.request_multi_reference();
     instruct.request_nonlinear_wavefunction();
     instruct.request_orbtial_optimization();
   }
   else if( iequals( keyword, "sa_dmrgci" ) )
   {
     instruct.request_quantum_mechanics();
     instruct.request_mean_field();
     instruct.request_multi_reference();
     instruct.request_multi_state();
     instruct.request_nonlinear_wavefunction();
   }
   else if( iequals( keyword, "sa_dmrgscf" ) )
   {
     instruct.request_quantum_mechanics();
     instruct.request_mean_field();
     instruct.request_multi_reference();
     instruct.request_multi_state();
     instruct.request_nonlinear_wavefunction();
     instruct.request_linear_response();
     instruct.request_orbital_optimization();
   }
   else if( iequals( keyword, "dmrgci_geo_opt" ) ){
     instruct.request_quantum_mechanics();
     instruct.request_mean_field();
     instruct.request_multi_reference();
     instruct.request_nonlinear_wavefunction();
     instruct.request_energy_gradient();
     instruct.request_nuclei_relaxation();
     instruct.request_multi_perturbation();
   }
   else if( iequals( keyword, "dmrgci_bomd" ) ){
     instruct.request_quantum_mechanics();
     instruct.request_mean_field();
     instruct.request_multi_reference();
     instruct.request_nonlinear_wavefunction();
     instruct.request_energy_gradient();
     instruct.request_nuclei_relaxation();
     instruct.request_multi_perturbation();
     instruct.request_time_evolved();
   }
   else if( iequals( keyword, "dmrgci_nac" ) )
   {
     instruct.request_quantum_mechanics();
     instruct.request_mean_field();
     instruct.request_multi_reference();
     instruct.request_multi_state();
     instruct.request_nonlinear_wavefunction();
     instruct.request_linear_response();
     instruct.request_energy_gradient();
     instruct.request_nuclei_relaxation();
     instruct.request_multi_perturbation();
     instruct.request_nonadiabatic();
   }
   else
   {
     cout << " error: unknown keyword " << keyword << endl;
     abort();
   }

  }
  this->instruct.compute_code();

}

} // end of struct command

} // end of namespace iquads
