#include <iostream>
#include <string>

#ifndef SERIAL
#include "boost/mpi/environment.hpp"
#include "boost/mpi/communicator.hpp"
#include "boost/mpi.hpp"
#endif

#include "fci.h"

using namespace std;

int main( int argc, char* argv[] )
{

#ifndef SERIAL
  boost::mpi::environment env(argc, argv );
#endif

  if( argc != 3 ){
   cout << " error: incorrect number of arguments " << endl;
   cout << " usage: " << endl;
   cout << " fci <config> ( <output> )" << endl;
  }

  string configfile = argv[1];
  string outfile;
  if( argc == 3 ){
   outfile = argv[2];
  }
  if( argc == 2 ){
   outfile = "not set";
  }
  string configfile = argv[1];
  int res = fci::fci_main( configfile, outfile );

}
