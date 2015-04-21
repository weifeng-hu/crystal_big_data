#ifndef POLYMER_H
#define POLYMER_H

#include "utilities/solid_gen/polymer_base.h"

namespace iquads {

namespace crystal {

  // explicit template instantiation
  template class polymer_base<2>;
  template class polymer_base<3>;
  template class polymer_base<4>;

  // self defined types
  typedef polymer_base<2> dimer;
  typedef polymer_base<3> trimer;
  typedef polymer_base<4> tetramer;

} // end of namespace crystal

} // end of namespace iquads

#endif
