#ifndef UNIT_CELL_H
#define UNIT_CELL_H

#include "utilities/solid_gen/atom.h"
#include "utilities/solid_gen/molecule.h"
#include "utilities/solid_gen/unit_cell_base.h"

using namespace std;

namespace iquads{

using namespace basic;

namespace crystal{

  template class unit_cell_base<atom>;
  template class unit_cell_base<molecule>;

  typedef unit_cell_base<atom> atomic_ucell;
  typedef unit_cell_base<molecule> molecular_ucell;

} // end of namespace crystal 

} // end of namespace iquads

#endif
