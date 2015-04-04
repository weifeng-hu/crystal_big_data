#ifndef MATRIX_FUNCTION_H
#define MATRIX_FUNCTION_H

#include <vector>
#include <tuple>
#include "utilities/solid_gen/matrix.h"

namespace iquads {

namespace matrix {

  void symmetrix_diag( DMatrixHeap* a, DMatrixHeap* eigvec, DMatrixHeap* eigval );
  bool is_the_same( DMatrixHeap* eigval_a, DMatrixHeap* eigval_b );
  vector< tuple<double, int, int> > get_degeneracy_struct( DMatrixHeap* eigval )

} // end of namespace matrix

} // end of namespace iquads

#endif
