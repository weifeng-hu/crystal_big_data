#ifndef ELECTRONIC_STATE_INFO_H
#define ELECTRONIC_STATE_INFO_H

#include <particle_number.h>
#include <spin.h>
#include <irrep.h>

namespace iqauads {

class ElectronicStateInfo
{
public:
  // accessors and mutators
  ParticleNumber particle_number() const { return this->particle_number_; }
  ParticleNumber& set_particle_number() { return this->particle_number_; }
  Spin spin() const { return this->spin_; }
  Spin& set_spin(){ return this->spin_; }
  Irrep irrep() const { return this->irrep_; }
  Irrep& set_irrep() { return this->irrep_; }

private:
  ParticleNumber particle_number_;
  Spin spin_;
  Irrep irrep_;

}; // end of class ElectronStateInfo

} // end of namespace iquads

#endif
