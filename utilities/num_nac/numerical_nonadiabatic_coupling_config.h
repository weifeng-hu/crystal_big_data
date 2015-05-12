#ifndef NUMERICAL_NONADIABATIC_COUPLING_CONFIG_H
#define NUMERICAL_NONADIABATIC_COUPLING_CONFIG_H

#include <fstream>
#include <molecule.h>
#include <electronic_state_info.h>

using namespace std;

namespace iquads {

namespace numerical_nonadiabatic_coupling {

class NumericalNonadabaticCoupling_Config
{
public:
  friend 
   ifstream& 
    operator>> ( ifstream& ifs, NumericalNonadabaticCoupling_Config& config )
  {
   ifs >> config.set_molecule();
   ifs >> config.set_electronic_state_info();
   ifs >> config.set_displacement(); 
  }

public:
  // Accessors and mutators
  Molecule molecule() const { return this->molecule_; }
  Molecule& set_molecule() { return this->molecule_; }
  ElectronicStateInfo electronic_state_info() const 
   { return this->electronic_state_info_; }
  ElectronicstateInfo& set_electronic_state_info()
   { return this->electronic_state_info_; }
  PositionDisplacement position_displacement() const 
   { return this->position_displacement_; }
  PositionDisplacement& set_position_displacement()
   { return this->position_displacement_; }

private:
  Molecule molecule_;
  ElectronicStateInfo electroic_state_info_;
  PositionDisplacement position_displacement_;

};

}

}

#endif
