#include "dmrg/dmrg_config_class.h"
#include "matrix/integral.h"
#include "dmrg/dmrg_quantum_num_class.h"
#include "dmrg/dmrg_block_class.h"
#include "dmrg/dmrg_density_mtr_class.h"
#include "dmrg/dmrg_wavefunction_class.h"
#include <vector>

#ifndef DMRG_UNIVERSE_H
#define DMRG_UNIVERSE_H

using namespace std;

namespace iqs { namespace dmrg {

class universe
{
// data
private:
  iqs::matrix::one_electron_integral h_;
  iqs::matrix::two_electron_integral v_;

private:
  quantum_number qm_sys_;
  quantum_number qm_env_;
  quantum_number qm_d_sys_;
  quantum_number qm_d_env_;

private:
  block system_;
  block environment_;
  block dot_sys_;
  block dot_env_;
  block new_system_;
  block new_environment_;

private:
  density_matrix dm_sys_;
  density_matrix dm_env_;

private:
  vector<wavefunction> wf_;
  vector<double> energy_;

// constructor & destructor
public:
  dmrg_step(){};
 ~dmrg_step(){};

public:
  void calc_wavefunction();
  void renormalize();

public:
  // we don't pass the values back since the value of blocks can be gigantic
  // so only returning the references here
  quantum_number& qm_sys() { return this->qm_sys_; }
  quantum_number& qm_env() { return this->qm_env_; }
  quantum_number& qm_d_sys() { return this->qm_d_sys_; }
  quantum_number& qm_d_env() { return this->qm_d_env_; }

  block& system() { return this->system_; }
  block& environment() { return this->environment_; }
  block& dot_sys() { return this-> dot_sys_; }
  block& dot_env() { return this-> dot_env_; }
  block& new_system() { return this-> new_system_; }
  block& new_environment() { return this-> new_environment_; }

  density_matrix& dm_sys() { return this->dm_sys_; }
  density_matrix& dm_env() { return this->dm_env_; }

  vector<wavefunction>& wf() { return this->wf_; }
  vector<double> energy(){ return this->energy_; }

};

} } // end of iqs::dmrg

#endif
