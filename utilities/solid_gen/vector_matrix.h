#ifndef VECTOR_MATRIX_H
#define VECTOR_MATRIX_H

#include "utilities/solid_gen/vector_matrix_base.h"

namespace iquads{

namespace matrix{

// explicit template instantiation
template class vector_matrix_base<int>;
template class vector_matrix_base<float>;
template class vector_matrix_base<double>;

} // end of namespace matrix

} // end of namespace iquads

#endif
