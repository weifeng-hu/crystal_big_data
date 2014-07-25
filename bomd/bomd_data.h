// BOMD_DATA_H

#include <vector>
#include <string>
#include "timeframe_class.h"

namespace bomd {

class bomd_data
{
public:
  std::string basename;
  int natom, ncoord;
  int time_max;
  double t;
  std::vector< timeframe > data;

  std::string method;

  int nel, norb, mult;
  int nroots;
  std::vector<int> weights;
  int cistep;
  int maxiter;
  double etol;
  bool scfgrad_debug, scf_zvector;

  bool do_dmrg;
  double sweeptol;
  bool new_version;
  int nroots_dmrg;
  std::vector<double> weights_dmrg;
  int irrep;
  bool use_mpi, use_host;
  int np;
  std::string pathname;
  int nschedule;
  std::vector<int> m;
  std::vector<int> iteration;
  std::vector<double> david_tol;
  std::vector<double> noise;
  int two_to_one;
  int maxiter_dmrg;
  bool restart, reset_iter, savetransf, mom;
  std::string prefix;
  std::string hostfile;

public:
  bomd_data();
  ~bomd_data();

public:
  int run( std::string orca_input );
  int read_in();
  int probagator();
  int write_data();

}; // end of class

} // end of bomd
