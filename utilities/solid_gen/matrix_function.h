#ifndef MATRIX_FUNCTION_H
#define MATRIX_FUNCTION_H

#include <vector>
#include <tuple>
#include "utilities/solid_gen/matrix.h"

namespace iquads {

namespace matrix {

  void symmetric_diag( DMatrixHeap* a, DMatrixHeap* eigvec, DMatrixHeap* eigval );
  void symmetric_diag_big( DMatrixHeap* a, DMatrixHeap* eigvec, DMatrixHeap* eigval );
  double distance_of_two_matrices( DMatrixHeap* mat_a, DMatrixHeap* mat_b );
  bool is_the_same( DMatrixHeap* eigval_a, DMatrixHeap* eigval_b );
  IMatrixHeap compute_boolean_mat( vector<DMatrixHeap>* eigvals, double tol );
  IMatrixHeap compute_boolean_mat( vector<DMatrixHeap>* all_matrices );
  vector< tuple< double, int, int> > get_degeneracy_groups( DMatrixHeap* eigval );
  vector< vector<int> > get_degeneracy_group( DMatrixHeap* mat );
  vector< vector<int> > get_groups( IMatrixHeap* boolean_mat );

} // end of namespace matrix

} // end of namespace iquads

#endif
