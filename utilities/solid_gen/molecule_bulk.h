#ifndef MOLECULE_BULK_H
#define MOLECULE_BULK_H

#include <vector>
#include <tuple>
#include "utilities/solid_gen/molecule.h"
#include "utilities/solid_gen/lattice.h"

namespace iquads{

namespace crystal{

struct molecule_bulk
{
public:
  mole_bulk(){
   this->bulk.resize(0);
   this->n_molecule_ = 0;
  }
  molecule_bulk( molecular_lattice* ml ){
   this->init_from( ml );
  }

public:
  void init_from( molecular_lattice* ml ){

  }
  void cut( double Radius ){
   this->radius_ = Radius;
  }

public:
  size_t get_nmolecule() const { return this->n_molecule_; }

private:
  vector< molecule > bulk;
  double radius_;
  size_t n_molecule_;

};

} // end of crystal

} // end of iquads

#endif
