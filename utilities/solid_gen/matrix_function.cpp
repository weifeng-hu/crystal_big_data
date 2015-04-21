#include <stdlib.h>
#include <math.h>
#include <vector>
#include <array>
#include <tuple>
#include <utility>
#include <algorithm>
#include <iostream>
#include "blas/blas_interface.h"
#include "utilities/solid_gen/iquads_limits.h"
#include "utilities/solid_gen/matrix.h"
#include "utilities/solid_gen/matrix_function.h"
#include <boost/graph/adjacency_matrix.hpp>

using namespace std;

namespace iquads {

namespace matrix {

void symmetric_diag( DMatrixHeap* a, DMatrixHeap* eigvec, DMatrixHeap* eigval )
{

  // Heap -> Stack
  DMatrixStack a_local( a );
  DMatrixStack eigvec_local( eigvec );
  DMatrixStack eigval_local( eigval );
  int dimension = a_local.get_nrow();

  // blas call
  diag( a_local.set_store().data(), eigvec_local.set_store().data(), eigval_local.set_store().data(), dimension );

  // Stack -> Heap
  eigvec_local.copy_to( eigvec );
  eigval_local.copy_to( eigval );
//  cout << eigvec->get_element(0,0) << " " << eigvec->get_element(1,0) << " " << eigvec->get_element(2,0) << endl;
//  cout << eigvec->get_element(1,0) << " " << eigvec->get_element(1,1) << " " << eigvec->get_element(2,1) << endl;
//  cout << eigvec->get_element(2,0) << " " << eigvec->get_element(2,1) << " " << eigvec->get_element(2,2) << endl;
//  cout << eigval->get_element(0,0) << " " << eigval->get_element(1,0) << " " << eigval->get_element(2,0) << endl;

};

void symmetric_diag_big( DMatrixHeap* a, DMatrixHeap* eigvec, DMatrixHeap* eigval )
{

  int dimension = a->get_nrow();
  // blas call
  diag( a->set_store().data(), eigvec->set_store().data(), eigval->set_store().data(), dimension );

}

bool is_the_same( DMatrixHeap* eigval_a, DMatrixHeap* eigval_b )
{

  bool retval = true;
  try{
   const size_t nrow_a = eigval_a->get_nrow();
   const size_t nrow_b = eigval_b->get_nrow();

//  cout << nrow_a << " " << nrow_b << endl;
   tuple< size_t, size_t > nrow_pair = make_pair( nrow_a, nrow_b );
   if( nrow_a != nrow_b ) throw nrow_pair;

   DMatrixStack eigval_a_local( eigval_a );
   DMatrixStack eigval_b_local( eigval_b );
   for( size_t ival = 0; ival < nrow_a; ival++ ){
    // no range check
    const double val_a = eigval_a_local(ival,0);
    const double val_b = eigval_b_local(ival,0);
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

  vector<int> vertex;

  size_t n_matrix = eigvals->size();
  vertex.resize(n_matrix);

  boost::adjacency_matrix<boost::undirectedS, property<int> > Matrix(n_matrix, vertex);

  DMatrixHeap retval( n_matrix, n_matrix );
  for( size_t imatrix = 0; imatrix < n_matrix; imatrix++ ){
   DMatrixHeap matrix_i = eigvals->at(imatrix);
   for( size_t jmatrix = 0; jmatrix < n_matrix; jmatrix++ ){
    DMatrixHeap matrix_j = eigvals->at(jmatrix);
    retval( imatrix, jmatrix ) = is_the_same( &matrix_i, &matrix_j ) ? 1.0e0 : 0.0e0;
//    cout << " boolean_mat [ " << imatrix << ", " << jmatrix << " ] = " << retval(imatrix, jmatrix) << endl;;
   }
  }
  return retval;

}

vector< tuple< double, int, int> > get_degeneracy_groups( DMatrixHeap* eigval )
{

  vector< tuple<double, int, int> > retval;
  retval.resize(0);

  DMatrixStack eigval_local( eigval );
  const size_t nrow_local = eigval_local.get_nrow();

  size_t start = 0;
  size_t end = start;
  while( true ){

   if( end != nrow_local ){
    const double this_value = eigval_local(start,0);
    const double next_value = eigval_local(end,0);
    const double difference = fabs( this_value - next_value );
    if( difference < 1.0e-12 ){
     end = end + 1;
    }
    else if( fabs( this_value - next_value) > 1.0e-12 ){
     tuple<double, int, int> this_set = make_tuple( this_value, start, end-1 );
     retval.push_back( this_set );
     start = end;
     end = start;
    }
   }
   else{
    const double this_value = eigval_local(start,0);
    tuple<double, int, int> this_set = make_tuple( this_value, start, end-1 );
    retval.push_back( this_set );
    break;
   }
  }

  return retval;

}

vector< vector<int> > get_degeneracy_group( DMatrixHeap* mat )
{

  vector< vector<int> > retval;

  int dimension = mat->get_nrow();
  DMatrixHeap eigvec( dimension, dimension );
  DMatrixHeap eigval( dimension, 1 );
  symmetric_diag_big( mat, &eigvec, &eigval );

  for( size_t i = 0; i < dimension; i++ ){
   cout << i << " " << eigval(i,0) << " " << endl;
  }

  vector< tuple< double, int, int> > degen_groups = get_degeneracy_groups( &eigval );
  const size_t n_groups = degen_groups.size();
  cout << "The eigenvalues have " << n_groups << " different groups" << endl;

  for( size_t igroup = 0; igroup < n_groups; igroup++ ){
   vector<int> this_indices;
   const tuple<double, int, int> degen_group = degen_groups.at(igroup);
   const double eigenvalue = get<0> ( degen_group );
   if( fabs( eigenvalue ) > 1.0e-11 ){
    const int startdim = get<1> ( degen_group );
    const int enddim   = get<2> ( degen_group );
    cout << "group " << igroup << " eigval = " << eigenvalue; 
    cout << " [ " << startdim << "<-->" << enddim << " ]" << endl;
//    for( size_t j = startdim; j <= enddim; j++ ){
     for( size_t i = 0; i < dimension; i++ ){
      const double value = eigvec( startdim, i );
      if( fabs( value) > 1.0e-5 ){
//       cout << i << " " << value << "|";
       this_indices.push_back(i);
      }
     }
//     cout << " || ";
    }
//    cout << endl;
    retval.push_back( this_indices );
   }
//  }

//  exit(0);
  return retval;

} // end of get_degeneracy_stuct()

} // end of namespace matrix

} // end of namespace iquads
