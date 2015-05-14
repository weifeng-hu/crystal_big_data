#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include "integration.h"
#include "get_value.h"
#include "bomd_data.h"

#define LINE_MAX 1000

using namespace std;

namespace bomd {

int bomd_data :: run()
{

  int res;
  string cmd = "/home/wh288/orca/finally/orca" + " " + orca_input + " > out_initial ";
  res = system( ( const char* ) cmd.c_str() );

  if( res != 0 ){ cout << " bond_data :: initialrun: unable to execute the initial run with command " << cmd << endl; exit(1); }

}

int bomd_data :: read_in()
{

  string engrad = this-> basename + ".engrad";
  string str;
  ifstream file;
  file.open( engrad.c_str(), ios::in );
  if( !file.is_open() ){ cout << " bomd_data :: bomd_data(): cannot open orca energy gradient file" << engrad << endl; exit(1); }
  while( !file.eof() ){
   file >> str;
   if( strcmp( str.c_str(), "# The current gradient in Eh/bohr") )break;
  }
  file >> str;

  double val;
  for( int i = 0; i < this->natom; i++ ){
   for( int j = 0; j < 3; j++ ){
    file >> val >> endl;
    data.force[i][j] = val;
   }
  }

  while( !file.eof() ){
   file >> str;
   if( strcmp( str.c_str() , "# The atomic numbers and current coordinates in Bohr" ) ) break;
  }
  file >> str;

  int matom; double x, y, z;
  for( int i = 0; i < this->natom; i++ ){
    file >> matom >> x >> y >> z >> endl;
    data.coord[i][0] = x;
    data.coord[i][1] = y;
    data.coord[i][2] = z;
  }

  file.close();

}

int probagator( int it )
{
  std::vector newframe( natom );
  get_R( data[it], newframe, t );
  data.push_back( newframe );
}

int bomd_data :: write_data( int it )
{

  string outfile = basename + ".inp";
  ofstream file;
  file.open( outfile, ios:out );
  file << "!PAL2" << endl;
  file << "%" << "coords" << endl;
  file << " CTyp xyz" << endl;
  file << " Units Angs" << endl;
  file << " coords" << endl;
  for( int i = 0; i < natom; i++ ){
   file << data[it].element.at(i) << "\t" << data[it].coord[i][0] << "\t" << data.[it].coord[j][1] << "\t" << data[it].coord[j][2] << endl;
  }
  file << " end" << endl;
  file << "end" << endl;
  file << endl;
  file << "!hf cc-pvdz extremescf" << endl;
  file << "%" << "output" << endl;
  file << "  print[P_ReducedOrbPopMO_L] 1" << endl;
  file << "  pi_threshold  30.0 " << endl;
  file << endl;
  file << "$new_job"
  file << "%" << "coords" << endl;
  file << " CTyp xyz" << endl;
  file << " Units Angs " << endl;
  file << " coords" << endl;
  for( int i = 0; i < natom; i++ ){
   file << data[it].element.at(i) << "\t" << data[it].coord[i][0] << "\t" << data.[it].coord[j][1] << "\t" << data[it].coord[j][2] << endl;
  }
  file << " end" << endl;
  file << "end" << endl;
  file << endl;
  file << "!casscf cc-pvdz extremescf" << endl;
  file << "!engrad" << endl;
  file << "%" << "casscf" << endl;
  file << "\t" << "nel 8" << endl;
  file << "\t" << "norb 7" << endl;
  file << "\t" << "mult 1" << endl;
  file << "\t" << "nroots 2" << endl;
  file << "\t" << "weights[0] = 1,0" << endl;
  file << "\t" << "cistep 0" << endl;
  file << "\t" << "maxiter 1" << endl;
  file << "\t" << "doct 1" << endl;
  file << "\t" << "etol 1.0e-14" << endl;
  file << "\t" << "scfgrad_debug false" << endl;
  file << "\t" << "scfgrad_zvector false" << endl;
  file << "end"

  file.close();

}

bomd_data :: bomd_data( std::string orca_input )
{

  this->data.resize(1);
  char line[ LINE_MAX ];
  ifstream file;
  file.open( orca_input.c_str() );
  if( file.good() == false ){ cout << "error: bomd_data :: bomd_data(): error in opening orca input file " << orca_input << endl; exit(1); }

 // Read the orca input file, know about the job

  // Read atoms and coordinates
  while( !file.eof() ){
   file.getline( line, LINE_MAX );
   if( strcmp( line, " coords") == 0 )break;
  }
  if( file.eof() == true ){ cout << "error: bomd_data :: bomd_data(): reached the end of the file " << orca_input << " before getting coords" << endl; exit(1); }

  stringstream ss;
  char atom; double x,y,z;
  vector<double> element_first;
  vector< vector<double> > coord_first;
  while( !file.eof() ){
   file.getline( line, LINE_MAX );
   if( strcmp( line, " end" ) == 0 )break;
   ss << line;
   ss >> atom >> x >> y >> z ;
   this->element_first.push_back( atom );

   vector<double> xyz(3);
   xyz[0] = x;
   xyz[1] = y;
   xyz[2] = z;
   this->coord_first.push_back( xyz );
  }

  this->natom = data.element.size();
  this->ncoord = natom * 3;

  data[0]( natom );
  data[0].element = element_first;
  data[0].coord = coord_first;
  file.close();

  // Find casscf and basis
  this->method 		 = get_line ( "!casscf", orca_input );

  // Read other things
  this-> nel  		 = get_value<int>    ( "nel", 		orca_input );
  this-> norb 		 = get_value<int>    ( "norb", 		orca_input );
  this-> mult 		 = get_value<int>    ( "mult", 		orca_input );
  this-> nroots 	 = get_value<int>    ( "nroots", 	orca_input );
  this-> weights 	 = get_value< vector<int> > ( "weights[0]", 	orca_input );
  this-> cistep  	 = get_value<int>    ( "cistep", 	orca_input );
  this-> maxiter 	 = get_value<int>    ( "maxiter", 	orca_input );
  this-> etol   	 = get_value<double> ( "etol", 		orca_input );
  this-> scfgrad_debug   = get_value<bool>   ( "scfgrad_debug", orca_input );
  this-> scfgrad_zvector = get_value<bool>   ( "scfgrad_zvector", orca_input );

  // Whether doing dmrg is true? If true, read the settings
  this-> do_dmrg = find_flag ( "dmrg_para", orca_input );
  if( do_dmrg == true ){
   this-> sweeptol 	= get_value<double> ( "SweepTol", 	orca_input );
   this-> new_version 	= get_value<bool>   ( "new_version", 	orca_input );
   this-> nroots_dmrg 	= get_value<int>    ( "Nroots", 	orca_input );
   this-> weights_dmrg 	= get_value< vector<double> > ( "weights", 	orca_input );
   this-> irrep		= get_value<int>    ( "irrep", 		orca_input );
   this-> use_mpi 	= get_value<bool>   ( "use_mpi", 	orca_input );
   this-> use_host 	= get_value<bool>   ( "use_host", 	orca_input );
   this-> np 		= get_value<int>    ( "np", 		orca_input );
   this-> pathname 	= get_value<string> ( "pathname", 	orca_input );
   this-> nschedule 	= get_value<int>    ( "nschedule", 	orca_input );
   this-> m 		= get_value< vector<int> > ( "m", 		orca_input );
   this-> iteration 	= get_value< vector<int> > ( "iteration", 	orca_input );
   this-> david_tol 	= get_value< vector<double> > ( "david_tol", 	orca_input );
   this-> noise 	= get_value< vector<double> > ( "noise", 	orca_input );
   this-> two_to_one 	= get_value<int>    ( "Twodot_to_onedot", orca_input );
   this-> twodot 	= get_value<bool>   ( "twodot", 	orca_input );
   this-> maxiter_dmrg 	= get_value<int>    ( "Maxiter", 	orca_input );
   this-> restart 	= get_value<bool>   ( "Restart", 	orca_input );
   this-> reset_iter 	= get_value<bool>   ( "Reset_iter", 	orca_input );
   this-> savetransf 	= get_value<bool>   ( "Savetransf", 	orca_input );
   this-> mom 		= get_value<bool>   ( "MOM", 		orca_input );
   this-> prefix 	= get_value<string> ( "prefix", 	orca_input );
   this-> hostfile 	= get_value<string> ( "hostfile", 	orca_input );
  }

// Get the basename
  size_t pos = orca_input.find( ".", 0 );
  for( size_t i = 0; i < pos; i++ ){ 
   this->basename = this->basename + orca_input.at(i);
  }
  cout << " bond_data::bomd_data:   orca basename = " << this->basename << endl;

  string engrad = this->basename + ".engrad";
  string str;
  ifstream file;
  file.open( engrad.c_str(), ios::in ); 
  if( !file.is_open() ){ cout << " bomd_data :: bomd_data(): cannot open orca energy gradient file " << engrad << endl; exit(1); }
  file >> str ;
  file >> str ;
  file >> str ;
  file.close();

  int n = atoi( str.c_str() );
  cout << " bomd_data :: bomd_data(): get natom = " << n << endl;

  this->t = 1.0e0;

  this-> time_max = 100;
  this-> natom = n;
  this-> ncoord = natom * 3;

  timeframe first( natom );
  this-> data.push_back( first );
  
}

} // end of bomd
