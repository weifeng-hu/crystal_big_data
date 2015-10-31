#ifndef MATRIX_H
#define MATRIX_H

#include "utilities/solid_gen/vector_matrix.h"
#include "utilities/solid_gen/array_matrix.h"

using namespace std;

namespace iquads {

namespace matrix {

  // typedef declaration
  typedef vector_matrix_base<int>     IMatrixHeap;
  typedef vector_matrix_base<float>   FMatrixHeap;
  typedef vector_matrix_base<double>  DMatrixHeap;

  typedef array_matrix_base<int>      IMatrixStack;
  typedef array_matrix_base<float>    FMatrixStack;
  typedef array_matrix_base<double>   DMatrixStack;

} // end of namespace matrix

} // end of namespace iquads

#endif
