#ifndef LATTICE_H
#define LATTICE_H

#include <string>
#include <vector>
#include "utilities/solid_gen/unit_cell.h"
#include "utilities/solid_gen/lattice_base.h"

namespace iquads {

namespace crystal {

  template class < atomic_cell > lattice_base;
  template class < molecular_cell > lattice_base;

  typedef lattice_base<atomic_cell> atomic_lattice;
  typedef lattice_base<molecular_cell> molecular_lattice;

} // end of namespace crystal

} // end of namespace iquads

#endif
