#include "dmrg/dmrg_define.h"
#include "dmrg/cmd_option.h"
#include "dmrg/dmrg_config_class.h"
//#include "dmrg/dmrg_class.h"
#include "boost/mpi/environment.hpp"

using namespace iqs::dmrg;

int main( int argc, char* argv[] )
{

  boost::mpi::environment env( argc, argv );
  boost::mpi::communicator world;

  iqs::dmrg::dmrg_world = world;
  iqs::dmrg::cmd_option cmd_opt( argc, argv );
  iqs::dmrg::config dmrg_conf(cmd_opt);

  if( cmd_opt.run_mode() == CPP ){
//    dmrg_cpp( dmrg_conf );  // iqs::dmrg::dmrg_cpp()
  }
  else if( cmd_opt.run_mode() == FORTRAN ){
//    dmrg_f( dmrg_conf );    // iqs::dmrg::dmrg_f()
  }


}
