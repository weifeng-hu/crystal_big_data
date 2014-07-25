#include <string>
#include "boost/mpi/communicator.hpp"

#ifndef DMRG_DEFINE_H
#define DMRG_DEFINE_H

namespace iqs { namespace dmrg {

static boost::mpi::communicator dmrg_world;

static std::string UNDEFINED_STR = "undefined"; 

enum para_status_int { UNDEFINED = -1000 };
enum RUN_MODE { CPP, FORTRAN };

#define sout if( dmrg_world.rank() == 0 )cout

} } // end of iqs::dmrg

#endif
