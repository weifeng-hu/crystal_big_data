#ifndef ARRAY_MATRIX_H
#define ARRAY_MATRIX_H

#include "utilities/solid_gen/array_matrix_base.h"

namespace iquads{

namespace matrix{

  // explicit template instantiation
  template class array_matrix_base<int>;
  template class array_matrix_base<float>;
  template class array_matrix_base<double>;

} // end of namespace matrix

} // end of namespace iquads

#endif
