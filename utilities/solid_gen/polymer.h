#ifndef POLYMER_H
#define POLYMER_H

#include "utilities/solid_gen/"

namespace iquads {

namespace crystal {

  // explicit template instantiation
  template class polymer<2>;
  template class polymer<3>;
  template class polymer<4>;

  // self defined types
  typedef polymer<2> dimer;
  typedef polymer<3> trimer;
  typedef polymer<4> tetramer;

} // end of namespace crystal

} // end of namespace iquads

#endif
