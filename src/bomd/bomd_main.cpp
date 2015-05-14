// Bohn Oppenheimer Molecular Dynames 
// 	Main driver
//
// This program invokes ORCA to do DMRG-CI gradients

// Weifeng Hu

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>

#define pout if( world.rank() == 0)cout

using namespace std;

int run_bomd( std::string orca_input);

int main( int argc, char* argv[] )
{

  boost::mpi::environment env( argc, argv );
  boost::mpi::communicator world;

  pout << "  Entering " << endl;
  pout << "\tBohn Oppenheimer Molecular Dynamics Module " << endl;
  pout << endl;

  int res;
  if( argc == 1 ){ pout << " error: bomd main(): no input file" << endl; exit(1); }
  string input = argv[1];
  pout << "bomd main(): input = " << input << endl;

  res = run_bomd( input );
  if( res != 0 ){ cout << " error: run_bomd() ended with exception" << endl; exit(1); }

  return 0;

}
