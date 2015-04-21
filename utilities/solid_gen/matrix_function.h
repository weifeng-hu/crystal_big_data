#ifndef MATRIX_FUNCTION_H
#define MATRIX_FUNCTION_H

#include <vector>
#include <tuple>
#include "utilities/solid_gen/matrix.h"

namespace iquads {

namespace matrix {

  void symmetric_diag( DMatrixHeap* a, DMatrixHeap* eigvec, DMatrixHeap* eigval );
  void symmetric_diag_big( DMatrixHeap* a, DMatrixHeap* eigvec, DMatrixHeap* eigval );
  bool is_the_same( DMatrixHeap* eigval_a, DMatrixHeap* eigval_b );
  DMatrixHeap compute_boolean_mat( vector<DMatrixHeap>* eigvals );
  vector< tuple< double, int, int> > get_degeneracy_groups( DMatrixHeap* eigval );
  vector< vector<int> > get_degeneracy_group( DMatrixHeap* mat );

} // end of namespace matrix

} // end of namespace iquads

#endif
