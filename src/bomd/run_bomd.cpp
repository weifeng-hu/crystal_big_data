// RUN_BOMD_CPP

//  This program will initiate an orca run and get an initial force,
//  then it will do dymaics until the maximum time is reached

#include "bomd_data.h"
#include <boost/mpi/communicator.hpp>

#define pout if( world.rank() == 0)cout

using namespace std;

namespace bomd {

int run_bomd( string input )
{

  boost::mpi::communicator world;
  int myid = world.rank();

  pout << " run_bomd(): starting BOMD " << endl;

//  bomd_data data( input );
//  data.run();

//  for( int itime = 0; itime < time_max; itime++ ){
//    data.read_in();
//    data.probagator( itime );
//    data.write_data( itime + 1 );
//    data.run();
//    data.read_in();
//  }


} // end of run_bomd()

} // end of bomd
