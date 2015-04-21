#ifndef LATTICE_H
#define LATTICE_H

#include <string>
#include <vector>
#include "utilities/solid_gen/unit_cell.h"
#include "utilities/solid_gen/lattice_base.h"

namespace iquads {

using namespace basic;

namespace crystal {

  template class lattice_base<atomic_ucell>;
  template class lattice_base<molecular_ucell>;

  typedef lattice_base<atomic_ucell> atomic_lattice;
  typedef lattice_base<molecular_ucell> molecular_lattice;

} // end of namespace crystal

} // end of namespace iquads

#endif
