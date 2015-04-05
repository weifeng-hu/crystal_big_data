#include <stdlib.h>
#include <math.h>
#include <vector>
#include <array>
#include <tuple>
#include <utilitiy>
#include <algorithm>
#include <iostream>
#include "matrix/blas_interface.h"
#include "utilities/solid_gen/iquads_limit.h"
#include "utilities/solid_gen/matrix.h"
#include "utilities/solid_gen/matrix_function.h"

using namespace std;

namespace iquads {

namespace matrix {

void symmetrix_diag( DMatrixHeap* a, DMatrixHeap* eigvec, DMatrixHeap* eigval )
{

  // Heap -> Stack
  DMatrixStack a_local( a );
  DMatrixStack eigvec_local( eigvec );
  DMatrixStack eigval_local( eigval );
  int dimension = a_local.get_nrow();

  // blas call
  diag( a_local.get_store().data(), eigvec_local.get_store().data(), eigval_local.get_store().data(), dimension );

  // Stack -> Heap
  eigvec_local.copy_to( eigvec );
  eigval_local.copy_to( eigval );

};

bool is_the_same( DMatrixHeap* eigval_a, DMatrixHeap* eigval_b )
{
  bool retval = true;
  try{
   const size_t nrow_a = eigval_a->get_nrow();
   const size_t nrow_b = eigval_b->get_nrow();
   tuple< size_t, size_t > nrow_pair = make_pair( nrow_a, nrow_b );
   if( nrow_a != nrow_b ) throw nrow_pair;

   DMatrixStack eigval_a_local( eigval_a );
   DMatrixStack eigval_b_local( eigval_b );
   for( size_t ival = 0; ival < nrow_a; ival++ ){
    // no range check
    const double val_a = eigval_a_local[ival];
    const double val_b = eigval_b_local[ival];
    if( fabs( val_a - val_b ) >= 1.0e-11 ){
     retval = false;
     break;
    }
   }
  }
  catch ( tuple< size_t, size_t > conflict_nrows ){
   cout << " matrix exception: compare_eigval_pair() " << endl;
   cout << "   lengths of eigen value vectors are unequal " << endl;
   cout << "   length a = " << get<0>( conflict_nrows );
   cout << "   length b = " << get<1>( conflict_nrows );
   cout << endl;
   abort();
  }

  return retval;

};

DMatrixHeap compute_boolean_mat( vector<DMatrixHeap>* eigvals )
{

  size_t n_matrix = eigvals.size();
  DMatrixHeap retval( n_matrix, n_matrix );
  for( size_t imatrix = 0; imatrix < n_matrix; imatrix++ ){
   DMatrixHeap matrix_i = eigvals.at(imatrix);
   for( size_t jmatrix = 0; jmatrix < n_matrix; jmatrix++ ){
    DMatrixHeap matrix_j = eigvals.at(jmatrix);
    retval( imatrix, jmatrix ) = is_the_same( &matrix_i, &matrix_j ) ? 1.0e0 : 0.0e0;
   }
  }
  return retval;

}

vector< tuple< double, int, int> > get_degeneracy_struct( DMatrixHeap* eigval )
{

  vector< tuple<double, int, int> > retval;
  retval.resize(0);

  DMatrixStack eigval_local( eigval );
  const size_t nrow_local = eigval_local.get_nrow();

  size_t start = 0;
  size_t end = start;
  while( true ){

   if( end != nrow_local ){
    const double this_value = eigval_local.at(start);
    const double next_value = eigval_local.at(end);
    const double difference = fabs( this_value - next_value );
    if( difference < 1.0e-10 ){
     end = end + 1;
    }
    else if( fabs( this_value - next_value) > 1.0e-10 ){
     tuple<double, int, int> this_set = make_tuple( this_value, start, end-1 );
     retval.push_back( this_set );
     start = end;
     end = start;
    }
   }
   else{
    const double this_value = eigval_local.at(start);
    tuple<double, int, int> this_set = make_tuple( this_value, start, end-1 );
    retval.push_back( this_set );
    break;
   }
  }

  return retval;
}

vector< vector<int> > get_degeneracy_struct( DMatrixHeap* eigval )
{

  

}

} // end of namespace matrix

} // end of namespace iquads
