/**
 * @file
 * @author Weifeng Hu
 *
 * @section LICENSE
 *
 * Copyright (C) 2013, 2014, 2015  Weifeng Hu
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @section DESCRIPTION
 *
 *
 */

//#include <emmintrin.h>
#include <omp.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <map>
#include <array>
#include <tuple>
#include <utility>
#include <algorithm>
#include <iostream>
#include <blas/blas_interface.h>
#include <iquads/iquads_limits.hpp>
#include <timer/progress_display.hpp>
#include <matrix/matrix_typedef.hpp>
#include <matrix/matrix_function.hpp>
//#include <boost/graph/adjacency_matrix.hpp>
//#include <boost/graph/adjacency_list.hpp>
//#include <boost/graph/graphviz.hpp>
//#include <boost/graph/graph_utility.hpp>

namespace iquads {

namespace matrix {

void symmetric_diag( DMatrixHeap& a, DMatrixHeap& eigvec, DMatrixHeap& eigval ) {

  // Heap -> Stack
  DMatrixStack a_local( a );
  DMatrixStack eigvec_local( eigvec );
  DMatrixStack eigval_local( eigval );
  int dimension = a_local.nrow();

  // blas call
  diag( a_local.set_store().data(), eigvec_local.set_store().data(), eigval_local.set_store().data(), dimension );

  // Stack -> Heap
  eigvec_local.copy_to( eigvec );
  eigval_local.copy_to( eigval );

}

void symmetric_diag_big( DMatrixHeap& a, DMatrixHeap& eigvec, DMatrixHeap& eigval ) {

  int dimension = a.nrow();
  // blas call
  diag( a.set_store().data(), eigvec.set_store().data(), eigval.set_store().data(), dimension );

}

double distance_of_two_matrices( DMatrixStack& mat_a, DMatrixStack& mat_b ) {
  try {
    double retval = 0.0e0;
    const size_t nrow_a = mat_a.nrow();
    const size_t nrow_b = mat_b.nrow();
    const size_t ncol_a = mat_a.ncol();
    const size_t ncol_b = mat_b.ncol();
    std :: tuple< size_t, size_t > nrow_pair = std :: make_pair( nrow_a, nrow_b );
    std :: tuple< int, size_t, size_t > ncol_pair = std :: make_tuple( 1, ncol_a, ncol_b );
    if( nrow_a != nrow_b ) throw nrow_pair;
    if( ncol_a != ncol_b ) throw ncol_pair;
    for( size_t irow = 0; irow < nrow_a; irow++ ) {
      for( size_t icol = 0; icol < ncol_a; icol++ ) {
//        double a = mat_a( irow, icol );
//        double b = mat_b( irow, icol );
//        __m128d x = _mm_load_sd( &a );
//        __m128d y = _mm_load_sd( &b );
//        __m128d z = _mm_sub_sd( x, y );
//        double diff[2];   // why here the assembly always not use xmm0 as the first register? not like the code about " difference < 1.0e-12 " below... 
//                        // OK we have to force to use intrinsics ...
//        _mm_store_sd( diff, z );
//        retval += fabs( diff[0] );
        retval += fabs( ( mat_a(irow, icol) - mat_b( irow, icol ) ) );
      }
    }
    return retval;
  } catch( std :: tuple< size_t, size_t > conflict_nrows ) {
    std :: cout << " matrix exception: distance_of_two_matrices() " << std :: endl;
    std :: cout << "   nrows are unequal " << std :: endl;
    std :: cout << "   nrows a = " << std :: get<0>( conflict_nrows );
    std :: cout << "   nrows b = " << std :: get<1>( conflict_nrows );
    std :: cout << std :: endl;
   abort();
  } catch( std :: tuple< int, size_t, size_t > conflict_ncols ) {
    std :: cout << " matrix exception: distance_of_two_matrices() " << std :: endl;
    std :: cout << "   ncols are unequal " << std :: endl;
    std :: cout << "   ncols a = " << std :: get<1>( conflict_ncols );
    std :: cout << "   ncols b = " << std :: get<2>( conflict_ncols );
    std :: cout << std :: endl;
    abort();
  }
}


double distance_of_two_matrices( const DMatrixHeap& mat_a, const DMatrixHeap& mat_b ) {
  try {
    double retval = 0.0e0;
    DMatrixStack mat_a_local( mat_a );
    DMatrixStack mat_b_local( mat_b );
    const size_t nrow_a = mat_a_local.nrow();
    const size_t nrow_b = mat_b_local.nrow();
    const size_t ncol_a = mat_a_local.ncol();
    const size_t ncol_b = mat_b_local.ncol();
    std :: tuple< size_t, size_t > nrow_pair = std :: make_pair( nrow_a, nrow_b );
    std :: tuple< int, size_t, size_t > ncol_pair = std :: make_tuple( 1, ncol_a, ncol_b );
    if( nrow_a != nrow_b ) throw nrow_pair;
    if( ncol_a != ncol_b ) throw ncol_pair;
    for( size_t irow = 0; irow < nrow_a; irow++ ) {
      for( size_t icol = 0; icol < ncol_a; icol++ ) {
         retval += fabs( ( mat_a_local(irow, icol) - mat_b_local( irow, icol ) ) );
      }
    }
    return retval;
  } catch( std :: tuple< size_t, size_t > conflict_nrows ) {
    std :: cout << " matrix exception: distance_of_two_matrices() " << std :: endl;
    std :: cout << "   nrows are unequal " << std :: endl;
    std :: cout << "   nrows a = " << std :: get<0>( conflict_nrows );
    std :: cout << "   nrows b = " << std :: get<1>( conflict_nrows );
    std :: cout << std :: endl;
   abort();
  } catch( std :: tuple< int, size_t, size_t > conflict_ncols ) {
    std :: cout << " matrix exception: distance_of_two_matrices() " << std :: endl;
    std :: cout << "   ncols are unequal " << std :: endl;
    std :: cout << "   ncols a = " << std :: get<1>( conflict_ncols );
    std :: cout << "   ncols b = " << std :: get<2>( conflict_ncols );
    std :: cout << std :: endl;
    abort();
  }
}

bool is_the_same( DMatrixStack& eigval_a, DMatrixStack& eigval_b ) {

  bool retval = true;
  try{
    retval = distance_of_two_matrices( eigval_a, eigval_b ) <= 1.0e-4 ? true : false;
//   const size_t nrow_a = eigval_a.nrow();
//   const size_t nrow_b = eigval_b.nrow();

//  cout << nrow_a << " " << nrow_b << endl;
//   tuple< size_t, size_t > nrow_pair = make_pair( nrow_a, nrow_b );
//   if( nrow_a != nrow_b ) throw nrow_pair;

//   DMatrixStack eigval_a_local( eigval_a );
//   DMatrixStack eigval_b_local( eigval_b );
//   for( size_t ival = 0; ival < nrow_a; ival++ ){
//    // no range check
//    const double val_a = eigval_a_local(ival,0);
//    const double val_b = eigval_b_local(ival,0);
//    if( fabs( val_a - val_b ) >= 1.0e0 ){
//     retval = false;
//     break;
//    }
//   }
  } catch ( std :: tuple< size_t, size_t > conflict_nrows ) {
    std :: cout << " matrix exception: is_the_same() " << std :: endl;
    std :: cout << "   lengths of eigen value vectors are unequal " << std :: endl;
    std :: cout << "   length a = " << std :: get<0>( conflict_nrows );
    std :: cout << "   length b = " << std :: get<1>( conflict_nrows );
    std :: cout << std :: endl;
    abort();
  }
  return retval;
}

bool is_the_same( const DMatrixHeap& eigval_a, const DMatrixHeap& eigval_b ) {

  bool retval = true;
  try{
    retval = distance_of_two_matrices( eigval_a, eigval_b ) <= 1.0e-4 ? true : false;
//   const size_t nrow_a = eigval_a.nrow();
//   const size_t nrow_b = eigval_b.nrow();

//  cout << nrow_a << " " << nrow_b << endl;
//   tuple< size_t, size_t > nrow_pair = make_pair( nrow_a, nrow_b );
//   if( nrow_a != nrow_b ) throw nrow_pair;

//   DMatrixStack eigval_a_local( eigval_a );
//   DMatrixStack eigval_b_local( eigval_b );
//   for( size_t ival = 0; ival < nrow_a; ival++ ){
//    // no range check
//    const double val_a = eigval_a_local(ival,0);
//    const double val_b = eigval_b_local(ival,0);
//    if( fabs( val_a - val_b ) >= 1.0e0 ){
//     retval = false;
//     break;
//    }
//   }
  } catch ( std :: tuple< size_t, size_t > conflict_nrows ) {
    std :: cout << " matrix exception: is_the_same() " << std :: endl;
    std :: cout << "   lengths of eigen value vectors are unequal " << std :: endl;
    std :: cout << "   length a = " << std :: get<0>( conflict_nrows );
    std :: cout << "   length b = " << std :: get<1>( conflict_nrows );
    std :: cout << std :: endl;
    abort();
  }
  return retval;
}

IMatrixHeap compute_boolean_mat( const std :: vector<DMatrixHeap>& all_matrices, double tol ){

  size_t n_matrix = all_matrices.size();
  IMatrixHeap retval( n_matrix, n_matrix );
  for( size_t imatrix = 0; imatrix < n_matrix; imatrix++ ) {
    DMatrixHeap matrix_i = all_matrices.at(imatrix);
    for( size_t jmatrix = 0; jmatrix < n_matrix; jmatrix++ ){
      DMatrixHeap matrix_j = all_matrices.at(jmatrix);
      const double distance = distance_of_two_matrices( matrix_i, matrix_j );
//    cout << " distance of matrices between " << imatrix << " " << jmatrix << " = " << distance << endl;
      retval( imatrix, jmatrix ) = ( distance <= tol ? 1 : 0);
    }
  }
  return retval;

}

IMatrixHeap compute_boolean_mat( std :: vector<DMatrixHeap>& eigvals ) {

  // std :: cout << "Compute boolean matrix ... " << std :: endl;
//  vector<int> vertex;

  size_t n_matrix = eigvals.size();
//  vertex.resize(n_matrix);
  size_t n_element_per_vector = eigvals[0].size();
  size_t n_element_total = n_matrix * n_element_per_vector;
  size_t n_element_cache_size = STACK_DOUBLE_LIMIT;
  size_t n_vector_every_time = n_element_cache_size / n_element_per_vector;
  size_t n_normal      = n_matrix / n_vector_every_time;
  size_t n_vector_tail = n_matrix % n_vector_every_time;
  // std :: cout << n_vector_every_time << std :: endl;
  // std :: cout << n_vector_tail << std :: endl;

  size_t n_block_main = n_normal;
  size_t n_block_tail = ( n_vector_tail == 0 ) ? 0 : 1;
  size_t n_block = n_block_main + n_block_tail;
  size_t n_element_main_every_time = n_vector_every_time * n_element_per_vector;
  size_t n_element_tail_every_time = n_vector_tail       * n_element_per_vector;
  // std :: cout << "n_block_main " << n_block_main << std :: endl;
  // std :: cout << "n_block_tail " << n_block_tail << std :: endl;

  IMatrixHeap retval( n_matrix, n_matrix );

  DMatrixHeap big_matrix( 1, n_matrix * n_element_per_vector );
  std :: vector< double > :: iterator it_big = big_matrix.set_store().begin();
  for( size_t i = 0; i < n_matrix; i++ ) {
    std :: copy_n( eigvals[i].set_store().begin(), n_element_per_vector, it_big );
    it_big += n_element_per_vector;
  }

  iquads :: timer :: ProgressDisplay progress_display_x( "Comparing eivenvalue to get a boolean matrix [ cache hierached ]...", ( n_block_main * n_block_main + 2 * n_block_main * n_block_tail + n_block_tail * n_block_tail ) );
  for( size_t iblock = 0; iblock < n_block_main; iblock++ ) {
    DMatrixStack iblock_matrix( n_vector_every_time, n_element_per_vector );
    std :: vector< double > :: iterator iterator_big_iblock =  big_matrix.set_store().begin();
                                        iterator_big_iblock += iblock * n_element_main_every_time;
    std :: copy_n( iterator_big_iblock, n_element_main_every_time, iblock_matrix.set_store().begin() );

    for( size_t jblock = 0; jblock < n_block_main; jblock++ ) {
      DMatrixStack jblock_matrix( n_vector_every_time,  n_element_per_vector );
      std :: vector< double > :: iterator iterator_big_jblock =  big_matrix.set_store().begin();
                                          iterator_big_jblock += jblock * n_element_main_every_time;
      std :: copy_n( iterator_big_jblock, n_element_main_every_time, jblock_matrix.set_store().begin() );

      for( size_t ivector = 0; ivector < n_vector_every_time; ivector++ ) {
        DMatrixStack matrix_i( 1, n_element_per_vector );
        DMatrixStack :: iterator_type ismall =  iblock_matrix.set_store().begin();
                                      ismall += ivector * n_element_per_vector; 
        std :: copy_n( ismall, n_element_per_vector, matrix_i.set_store().begin() );

        for( size_t jvector = 0; jvector < n_vector_every_time; jvector++ ) {
          DMatrixStack matrix_j( 1, n_element_per_vector );
          DMatrixStack :: iterator_type jsmall =  jblock_matrix.set_store().begin();
                                        jsmall += jvector * n_element_per_vector;
          std :: copy_n( jsmall, n_element_per_vector, matrix_j.set_store().begin() );
          retval( iblock * n_vector_every_time + ivector, jblock * n_vector_every_time + jvector ) = is_the_same( matrix_i, matrix_j ) ? 1 : 0;
        }
      }
      progress_display_x++;
    }
  }

  for( size_t iblock = 0; iblock < n_block_main; iblock++ ) {
    DMatrixStack iblock_matrix( n_vector_every_time, n_element_per_vector );
    std :: vector< double > :: iterator iterator_big_iblock =  big_matrix.set_store().begin();
                                        iterator_big_iblock += iblock * n_element_main_every_time;
    std :: copy_n( iterator_big_iblock, n_element_main_every_time, iblock_matrix.set_store().begin() );

    for( size_t jblock = n_block_main; jblock < n_block_main + n_block_tail; jblock++ ) {
      DMatrixStack jblock_matrix( n_vector_tail,  n_element_per_vector );
      std :: vector< double > :: iterator iterator_big_jblock =  big_matrix.set_store().begin();
                                          iterator_big_jblock += n_block_main * n_element_main_every_time + ( jblock - n_block_main ) * n_element_tail_every_time;
      std :: copy_n( iterator_big_jblock, n_element_tail_every_time, jblock_matrix.set_store().begin() );

      for( size_t ivector = 0; ivector < n_vector_every_time; ivector++ ) {
        DMatrixStack matrix_i( 1, n_element_per_vector );
        DMatrixStack :: iterator_type ismall =  iblock_matrix.set_store().begin();
                                      ismall += ivector * n_element_per_vector; 
        std :: copy_n( ismall, n_element_per_vector, matrix_i.set_store().begin() );

        for( size_t jvector = 0; jvector < n_vector_tail; jvector++ ) {
          DMatrixStack matrix_j( 1, n_element_per_vector );
          DMatrixStack :: iterator_type jsmall =  jblock_matrix.set_store().begin();
                                        jsmall += jvector * n_element_per_vector;
          std :: copy_n( jsmall, n_element_per_vector, matrix_j.set_store().begin() );
          retval( iblock * n_vector_every_time + ivector, n_block_main * n_vector_every_time + ( jblock - n_block_main) * n_vector_tail + jvector ) = is_the_same( matrix_i, matrix_j ) ? 1 : 0;
        }
      }
      progress_display_x++;
    }
  }

  for( size_t iblock = n_block_main; iblock < n_block_main + n_block_tail; iblock++ ) {
    DMatrixStack iblock_matrix( n_vector_tail, n_element_per_vector );
    std :: vector< double > :: iterator iterator_big_iblock =  big_matrix.set_store().begin();
                                        iterator_big_iblock += n_block_main * n_element_main_every_time + ( iblock - n_block_main ) * n_element_tail_every_time;
    std :: copy_n( iterator_big_iblock, n_element_tail_every_time, iblock_matrix.set_store().begin() );

    for( size_t jblock = 0; jblock < n_block_main; jblock++ ) {
      DMatrixStack jblock_matrix( n_vector_every_time,  n_element_per_vector );
      std :: vector< double > :: iterator iterator_big_jblock =  big_matrix.set_store().begin();
                                          iterator_big_jblock += jblock * n_element_main_every_time;
      std :: copy_n( iterator_big_jblock, n_element_main_every_time, jblock_matrix.set_store().begin() );

      for( size_t ivector = 0; ivector < n_vector_tail; ivector++ ) {
        DMatrixStack matrix_i( 1, n_element_per_vector );
        DMatrixStack :: iterator_type ismall =  iblock_matrix.set_store().begin();
                                      ismall += ivector * n_element_per_vector; 
        std :: copy_n( ismall, n_element_per_vector, matrix_i.set_store().begin() );

        for( size_t jvector = 0; jvector < n_vector_every_time; jvector++ ) {
          DMatrixStack matrix_j( 1, n_element_per_vector );
          DMatrixStack :: iterator_type jsmall =  jblock_matrix.set_store().begin();
                                        jsmall += jvector * n_element_per_vector;
          std :: copy_n( jsmall, n_element_per_vector, matrix_j.set_store().begin() );
          retval( n_block_main * n_vector_every_time + ( iblock - n_block_main ) * n_vector_tail + ivector, jblock * n_vector_every_time + jvector ) = is_the_same( matrix_i, matrix_j ) ? 1 : 0;
        }
      }
      progress_display_x++;
    }
  }

  for( size_t iblock = n_block_main; iblock < n_block_main + n_block_tail; iblock++ ) {
    DMatrixStack iblock_matrix( n_vector_every_time, n_element_per_vector );
    std :: vector< double > :: iterator iterator_big_iblock =  big_matrix.set_store().begin();
                                        iterator_big_iblock += n_block_main * n_element_main_every_time + ( iblock - n_block_main ) * n_element_tail_every_time;
    std :: copy_n( iterator_big_iblock, n_element_tail_every_time, iblock_matrix.set_store().begin() );

    for( size_t jblock = n_block_main; jblock < n_block_main + n_block_tail; jblock++ ) {
      DMatrixStack jblock_matrix( n_vector_every_time,  n_element_per_vector );
      std :: vector< double > :: iterator iterator_big_jblock =  big_matrix.set_store().begin();
                                          iterator_big_jblock += n_block_main * n_element_main_every_time + ( jblock - n_block_main ) * n_element_tail_every_time;
      std :: copy_n( iterator_big_jblock, n_element_tail_every_time, jblock_matrix.set_store().begin() );

      for( size_t ivector = 0; ivector < n_vector_tail; ivector++ ) {
        DMatrixStack matrix_i( 1, n_element_per_vector );
        DMatrixStack :: iterator_type ismall =  iblock_matrix.set_store().begin();
                                      ismall += ivector * n_element_per_vector; 
        std :: copy_n( ismall, n_element_per_vector, matrix_i.set_store().begin() );

        for( size_t jvector = 0; jvector < n_vector_tail; jvector++ ) {
          DMatrixStack matrix_j( 1, n_element_per_vector );
          DMatrixStack :: iterator_type jsmall =  jblock_matrix.set_store().begin();
                                        jsmall += jvector * n_element_per_vector;
          std :: copy_n( jsmall, n_element_per_vector, matrix_j.set_store().begin() );
          retval( n_block_main * n_vector_every_time + ( iblock - n_block_main ) * n_vector_tail + ivector, n_block_main * n_vector_every_time + ( jblock - n_block_main ) * n_vector_tail + jvector ) = is_the_same( matrix_i, matrix_j ) ? 1 : 0;
        }
      }
      progress_display_x++;
    }
  }


/*
  if( n_element_per_vector == 4 ) return retval;

//  boost::adjacency_matrix<boost::undirectedS, property<int> > Matrix(n_matrix, vertex);
//  boost::adjacency_matrix<boost::undirectedS> Matrix(n_matrix);
//  int n = n_matrix;
//  boost::adjacency_list< boost::setS, boost::vecS, boost::undirectedS > List(n_matrix);

  size_t num_of_comp = n_matrix * n_matrix;
  iquads :: timer :: ProgressDisplay progress_display( "Comparing eigenvalues to get a boolean matrix...", num_of_comp );
  // std :: cout  << num_of_comp << " matrix pairs to compare:" << std :: endl;
  // size_t count_interval = num_of_comp/5;

  for( size_t imatrix = 0; imatrix < n_matrix; imatrix++ ) {
//    DMatrixHeap matrix_i = eigvals.at(imatrix);
//    DMatrixStack matrix_i( eigvals[imatrix] );
    DMatrixStack matrix_i( 1, n_element_per_vector );
    std :: vector<double> :: iterator it_big_i =  big_matrix.set_store().begin();
                                      it_big_i += imatrix * n_element_per_vector;
    std :: copy_n( it_big_i, n_element_per_vector, matrix_i.set_store().begin() );
    for( size_t jmatrix = 0; jmatrix < n_matrix; jmatrix++ ) {
//      DMatrixHeap matrix_j = eigvals.at(jmatrix);
//      DMatrixStack matrix_j( eigvals[jmatrix] );
      DMatrixStack matrix_j( 1, n_element_per_vector );
      std :: vector<double> :: iterator it_big_j =  big_matrix.set_store().begin();
                                        it_big_j += jmatrix * n_element_per_vector;
      std :: copy_n( it_big_j, n_element_per_vector, matrix_j.set_store().begin() );
      retval( imatrix, jmatrix ) = is_the_same( matrix_i, matrix_j ) ? 1: 0;
//    if( is_the_same( &matrix_i, &matrix_j) ){
//     boost::add_edge(imatrix,jmatrix, List);
//    }
//    cout << " boolean_mat [ " << imatrix << ", " << jmatrix << " ] = " << retval(imatrix, jmatrix) << endl;
      //size_t current_count = imatrix * n_matrix + jmatrix;
//    if( (current_count+1) % count_interval == 0 ){
//     cout << (current_count*100/num_of_comp + 1 ) << "%\tcompleted" << endl;
//    }
      progress_display++;
    }
  }
//  boost::write_graphviz(cout, List );
//  boost::print_graph(List);
*/
  return retval;
//  exit(0);
}

std :: vector< std :: map< int, int > > compute_boolean_map( std :: vector<DMatrixHeap>& eigvals ) {

  omp_set_dynamic(0);
  const size_t num_thread = omp_get_num_procs();
  omp_set_num_threads( num_thread );

  size_t n_matrix = eigvals.size();
  size_t n_element_per_vector = eigvals[0].size();
  size_t n_element_total = n_matrix * n_element_per_vector;
  size_t n_element_cache_size = STACK_DOUBLE_LIMIT/num_thread;
  size_t n_vector_every_time = n_element_cache_size / n_element_per_vector;
  size_t n_normal      = n_matrix / n_vector_every_time;
  size_t n_vector_tail = n_matrix % n_vector_every_time;
//  std :: cout << n_vector_every_time << std :: endl;
//  std :: cout << n_vector_tail << std :: endl;

  size_t n_block_main = n_normal;
  size_t n_block_tail = ( n_vector_tail == 0 ) ? 0 : 1;
  size_t n_block = n_block_main + n_block_tail;
  size_t n_element_main_every_time = n_vector_every_time * n_element_per_vector;
  size_t n_element_tail_every_time = n_vector_tail       * n_element_per_vector;
//  std :: cout << "n_block_main " << n_block_main << std :: endl;
//  std :: cout << "n_block_tail " << n_block_tail << std :: endl;

  std :: vector< std :: map< int, int > > retval;
  retval.resize( n_matrix );

  DMatrixHeap big_matrix( 1, n_matrix * n_element_per_vector );
  std :: vector< double > :: iterator it_big = big_matrix.set_store().begin();
  for( size_t i = 0; i < n_matrix; i++ ) {
    std :: copy_n( eigvals[i].set_store().begin(), n_element_per_vector, it_big );
    it_big += n_element_per_vector;
  }

//  omp_set_dynamic(0);
//  const size_t num_thread = omp_get_num_procs();
//  omp_set_num_threads( num_thread );

  std :: string display_message = std :: string( "Comparing eivenvalue to get a boolean matrix [ cache hierached, compressed, openmp, automatic, num_thread = " ) +
                                  std :: to_string( num_thread ) + 
                                  std :: string( " ], step 1 ...");

  iquads :: timer :: ProgressDisplay progress_display_step_1( display_message, n_block_main/num_thread );

  #pragma omp parallel
  {
    const int thread_id = omp_get_thread_num();

    #pragma omp for
    for( size_t iblock = 0; iblock < n_block_main; iblock++ ) {
     // std :: cout << iblock << std :: endl << std :: flush;
      DMatrixStack iblock_matrix( n_vector_every_time, n_element_per_vector );
      std :: vector< double > :: iterator iterator_big_iblock =  big_matrix.set_store().begin();
                                          iterator_big_iblock += iblock * n_element_main_every_time;
      std :: copy_n( iterator_big_iblock, n_element_main_every_time, iblock_matrix.set_store().begin() );
  
      for( size_t ivector = 0; ivector < n_vector_every_time; ivector++ ) {
        std :: map< int, int > map_local;
  
        DMatrixStack matrix_i( 1, n_element_per_vector );
        DMatrixStack :: iterator_type ismall =  iblock_matrix.set_store().begin();
                                      ismall += ivector * n_element_per_vector; 
        std :: copy_n( ismall, n_element_per_vector, matrix_i.set_store().begin() );
  
        for( size_t jblock = 0; jblock < n_block_main; jblock++ ) {
          DMatrixStack jblock_matrix( n_vector_every_time,  n_element_per_vector );
          std :: vector< double > :: iterator iterator_big_jblock =  big_matrix.set_store().begin();
                                              iterator_big_jblock += jblock * n_element_main_every_time;
          std :: copy_n( iterator_big_jblock, n_element_main_every_time, jblock_matrix.set_store().begin() );
  
          for( size_t jvector = 0; jvector < n_vector_every_time; jvector++ ) {
            DMatrixStack matrix_j( 1, n_element_per_vector );
            DMatrixStack :: iterator_type jsmall =  jblock_matrix.set_store().begin();
                                          jsmall += jvector * n_element_per_vector;
            std :: copy_n( jsmall, n_element_per_vector, matrix_j.set_store().begin() );
            if( is_the_same( matrix_i, matrix_j ) == true ) {
              map_local.insert( std :: pair< int, int > ( jblock * n_vector_every_time + jvector, 1 ) );
            }
            // retval( iblock * n_vector_every_time + ivector, jblock * n_vector_every_time + jvector ) = is_the_same( matrix_i, matrix_j ) ? 1 : 0;
          }
        }
  
        for( size_t jblock = n_block_main; jblock < n_block_main + n_block_tail; jblock++ ) {
          DMatrixStack jblock_matrix( n_vector_tail,  n_element_per_vector );
          std :: vector< double > :: iterator iterator_big_jblock =  big_matrix.set_store().begin();
                                              iterator_big_jblock += n_block_main * n_element_main_every_time + ( jblock - n_block_main ) * n_element_tail_every_time;
          std :: copy_n( iterator_big_jblock, n_element_tail_every_time, jblock_matrix.set_store().begin() );
        
          for( size_t jvector = 0; jvector < n_vector_tail; jvector++ ) {
            DMatrixStack matrix_j( 1, n_element_per_vector );
            DMatrixStack :: iterator_type jsmall =  jblock_matrix.set_store().begin();
                                          jsmall += jvector * n_element_per_vector;
            std :: copy_n( jsmall, n_element_per_vector, matrix_j.set_store().begin() );
            if( is_the_same( matrix_i, matrix_j ) == true ) {
              map_local.insert( std :: pair< int, int > ( n_block_main * n_vector_every_time + ( jblock - n_block_main ) * n_vector_tail + jvector, 1 ) );
            }
            //retval( iblock * n_vector_every_time + ivector, n_block_main * n_vector_every_time + ( jblock - n_block_main) * n_vector_tail + jvector ) = is_the_same( matrix_i, matrix_j ) ? 1 : 0;
          }
        }
        retval[ iblock * n_vector_every_time + ivector ] = map_local;
        // progress_display++;
      }
      if( thread_id == 0 ) { progress_display_step_1++; }
    }
    #pragma omp barrier
  }

  for( size_t iblock = n_block_main; iblock < n_block_main + n_block_tail; iblock++ ) {
    DMatrixStack iblock_matrix( n_vector_tail, n_element_per_vector );
    std :: vector< double > :: iterator iterator_big_iblock =  big_matrix.set_store().begin();
                                        iterator_big_iblock += n_block_main * n_element_main_every_time + ( iblock - n_block_main ) * n_element_tail_every_time;
    std :: copy_n( iterator_big_iblock, n_element_tail_every_time, iblock_matrix.set_store().begin() );

    std :: string display_message = std :: string( "Comparing eivenvalue to get a boolean matrix [ cache hierached, compressed, openmp, automatic, num_thread = " ) +
                                    std :: to_string( num_thread ) + 
                                    std :: string( " ], step 2,  phase ") +
                                    std :: to_string( iblock - n_block_main ) +
                                    std :: string( " ... " );
    iquads :: timer :: ProgressDisplay progress_display_step_2( display_message, n_vector_tail/num_thread );
    
    #pragma omp parallel
    {
      const int thread_id = omp_get_thread_num();

      #pragma omp for
      for( size_t ivector = 0; ivector < n_vector_tail; ivector++ ) {
  
        std :: map< int, int > map_local;
  
        DMatrixStack matrix_i( 1, n_element_per_vector );
        DMatrixStack :: iterator_type ismall =  iblock_matrix.set_store().begin();
                                      ismall += ivector * n_element_per_vector; 
        std :: copy_n( ismall, n_element_per_vector, matrix_i.set_store().begin() );
  
        for( size_t jblock = 0; jblock < n_block_main; jblock++ ) {
          DMatrixStack jblock_matrix( n_vector_every_time,  n_element_per_vector );
          std :: vector< double > :: iterator iterator_big_jblock =  big_matrix.set_store().begin();
                                              iterator_big_jblock += jblock * n_element_main_every_time;
          std :: copy_n( iterator_big_jblock, n_element_main_every_time, jblock_matrix.set_store().begin() );
  
          for( size_t jvector = 0; jvector < n_vector_every_time; jvector++ ) {
            DMatrixStack matrix_j( 1, n_element_per_vector );
            DMatrixStack :: iterator_type jsmall =  jblock_matrix.set_store().begin();
                                          jsmall += jvector * n_element_per_vector;
            std :: copy_n( jsmall, n_element_per_vector, matrix_j.set_store().begin() );
            if( is_the_same( matrix_i, matrix_j ) == true ) {
              map_local.insert( std :: pair< int, int > ( jblock * n_vector_every_time + jvector, 1 ) );
            }
            //retval( n_block_main * n_vector_every_time + ( iblock - n_block_main ) * n_vector_tail + ivector, jblock * n_vector_every_time + jvector ) = is_the_same( matrix_i, matrix_j ) ? 1 : 0;
          }
        }
  
        for( size_t jblock = n_block_main; jblock < n_block_main + n_block_tail; jblock++ ) {
          DMatrixStack jblock_matrix( n_vector_every_time,  n_element_per_vector );
          std :: vector< double > :: iterator iterator_big_jblock =  big_matrix.set_store().begin();
                                              iterator_big_jblock += n_block_main * n_element_main_every_time + ( jblock - n_block_main ) * n_element_tail_every_time;
          std :: copy_n( iterator_big_jblock, n_element_tail_every_time, jblock_matrix.set_store().begin() );
  
          for( size_t jvector = 0; jvector < n_vector_tail; jvector++ ) {
            DMatrixStack matrix_j( 1, n_element_per_vector );
            DMatrixStack :: iterator_type jsmall =  jblock_matrix.set_store().begin();
                                          jsmall += jvector * n_element_per_vector;
            std :: copy_n( jsmall, n_element_per_vector, matrix_j.set_store().begin() );
            if( is_the_same( matrix_i, matrix_j ) == true ) {
              map_local.insert( std :: pair< int, int > ( n_block_main * n_vector_every_time + ( jblock - n_block_main ) * n_vector_tail + jvector, 1 ) );
            }
            // retval( n_block_main * n_vector_every_time + ( iblock - n_block_main ) * n_vector_tail + ivector, n_block_main * n_vector_every_time + ( jblock - n_block_main ) * n_vector_tail + jvector ) = is_the_same( matrix_i, matrix_j ) ? 1 : 0;
          }
        }
        retval[ n_block_main * n_vector_every_time + ( iblock - n_block_main ) * n_vector_tail + ivector ] = map_local;
        // progress_display++;
        if( thread_id == 0 ) { progress_display_step_2++ ; }
      }
      #pragma omp barrier
    }
  }

  return retval;

}


std :: vector< std :: vector< int > > get_groups( std :: vector< std :: map< int, int > >& bond_maps ) {

  std :: vector< std :: vector< int > > bond_vecs;
  size_t nvec = bond_maps.size();
  iquads :: timer :: ProgressDisplay progress_display_a( "Initializing bond map ...", nvec );
  for( size_t ivec = 0; ivec < nvec; ivec++ ) {
    std :: map<int, int> bond_map = bond_maps.at(ivec);
    std :: vector<int> vec_local;
    for( std :: map< int, int >::iterator it = bond_map.begin(); it != bond_map.end(); ++it ) {
      const int value = it->first;
      vec_local.push_back(value);
    }
    bond_vecs.push_back(vec_local);
    progress_display_a++;
  }

  iquads :: timer :: ProgressDisplay progress_display_b( "Analyzing subgroups from bond map ...", nvec );
  for( size_t ivec = 0; ivec < bond_vecs.size(); ivec++ ) {
    std :: vector<int> vec_i = bond_vecs.at(ivec);
    const size_t size_i = vec_i.size();
    if( size_i != 0 ) {
      for( size_t jvec = ivec + 1; jvec < bond_vecs.size(); jvec++ ) {
        std :: vector<int> vec_j = bond_vecs.at(jvec);
        const size_t size_j = vec_j.size();
        if( size_j != 0 ) {
          if( size_i != size_j ) {
            continue;
          }
          else {
            bool the_same = true;
            for( size_t i = 0; i < size_i; i++ ) {
              const int value_i = vec_i.at(i);
              const int value_j = vec_j.at(i);
              if( value_i != value_j ) {
                the_same = false;
                break;
              }
            }
            if( the_same == true ) {
              bond_vecs.at(jvec).resize(0);
              bond_vecs.at(jvec).clear();
              bond_vecs.at(jvec).shrink_to_fit();
            }
          } // end of else
 
        }
      }
    }
    progress_display_b++;
  }

  iquads :: timer :: ProgressDisplay progress_display_c( "Finalizing subgroup analysis ...", nvec );
  for( std :: vector< std :: vector<int> > :: iterator ivec = bond_vecs.begin(); ivec != bond_vecs.end(); ) {
    if( ivec->size() == 0 ) {
      bond_vecs.erase(ivec);
    }
    else {
      ivec++;
    }
    progress_display_c++;
  }

  // std :: cout << " done" << std :: endl;
  return bond_vecs;


}

std :: vector< std :: vector< int > > get_groups( IMatrixHeap& boolean_mat ){

  std :: cout << "Analyzing subgroups from boolean matrix ...";
  std :: vector< std :: map< int, int > > bond_maps;
  size_t nvec = boolean_mat.ncol();
  for( size_t ivec = 0; ivec < nvec; ivec++ ) {
    std :: map< int, int > bond_map;
    for( size_t jvec = 0; jvec < nvec; jvec++ ) {
      const int value = boolean_mat( ivec, jvec );
      if( value == 1 ){
        bond_map.insert( std :: pair<int, int>( jvec, value ) );
      }
    }
    bond_maps.push_back( bond_map );
  }

  std :: vector< std :: vector< int > > bond_vecs;
  for( size_t ivec = 0; ivec < nvec; ivec++ ) {
    std :: map<int, int> bond_map = bond_maps.at(ivec);
    std :: vector<int> vec_local;
    for( std :: map< int, int >::iterator it = bond_map.begin(); it != bond_map.end(); ++it ) {
      const int value = it->first;
      vec_local.push_back(value);
    }
    bond_vecs.push_back(vec_local);
  }

  for( size_t ivec = 0; ivec < bond_vecs.size(); ivec++ ) {
    std :: vector<int> vec_i = bond_vecs.at(ivec);
    const size_t size_i = vec_i.size();
    if( size_i != 0 ) {
      for( size_t jvec = ivec + 1; jvec < bond_vecs.size(); jvec++ ) {
        std :: vector<int> vec_j = bond_vecs.at(jvec);
        const size_t size_j = vec_j.size();
        if( size_j != 0 ) {
          if( size_i != size_j ) {
            continue;
          }
          else {
            bool the_same = true;
            for( size_t i = 0; i < size_i; i++ ) {
              const int value_i = vec_i.at(i);
              const int value_j = vec_j.at(i);
              if( value_i != value_j ) {
                the_same = false;
                break;
              }
            }
            if( the_same == true ) {
              bond_vecs.at(jvec).resize(0);
              bond_vecs.at(jvec).clear();
              bond_vecs.at(jvec).shrink_to_fit();
            }
          } // end of else
 
        }
      }
    }
  }

  for( std :: vector< std :: vector<int> > :: iterator ivec = bond_vecs.begin(); ivec != bond_vecs.end(); ) {
    if( ivec->size() == 0 ) {
      bond_vecs.erase(ivec);
    }
    else {
      ivec++;
    }
  }

  std :: cout << " done" << std :: endl;
  return bond_vecs;
}

std :: vector< std :: tuple< double, int, int> > get_degeneracy_groups( iquads :: matrix :: DMatrixHeap& eigval ) {

  std :: vector< std :: tuple<double, int, int> > retval;
  retval.resize(0);

  DMatrixStack eigval_local( eigval );
  const size_t nrow_local = eigval_local.nrow();

  size_t start = 0;
  size_t end = start;
  while( true ) {

    if( end != nrow_local ) {
      const double this_value = eigval_local(start,0);
      const double next_value = eigval_local(end,0);
      const double difference = fabs( this_value - next_value );
      if( difference < 1.0e-12 ) {
        end = end + 1;
      }
      else if( fabs( this_value - next_value) > 1.0e-12 ) {
        std :: tuple<double, int, int> this_set = std :: make_tuple( this_value, start, end-1 );
        retval.push_back( this_set );
        start = end;
        end = start;
      }
    }
    else {
      const double this_value = eigval_local(start,0);
      std :: tuple<double, int, int> this_set = std :: make_tuple( this_value, start, end-1 );
      retval.push_back( this_set );
      break;
    }
  }
  return retval;

}

std :: vector< std :: vector< int > > get_degeneracy_group( DMatrixHeap& mat ) {

  std :: vector< std :: vector< int > > retval;

  int dimension = mat.nrow();
  DMatrixHeap eigvec( dimension, dimension );
  DMatrixHeap eigval( dimension, 1 );
  symmetric_diag_big( mat, eigvec, eigval );

  for( size_t i = 0; i < dimension; i++ ) {
    std :: cout << i << " " << eigval(i,0) << " " << std :: endl;
  }

  std :: vector< std :: tuple< double, int, int> > degen_groups = get_degeneracy_groups( eigval );
  const size_t n_groups = degen_groups.size();
  std ::cout << "The eigenvalues have " << n_groups << " different groups" << std :: endl;

  for( size_t igroup = 0; igroup < n_groups; igroup++ ) {
    std :: vector<int> this_indices;
    const std :: tuple<double, int, int> degen_group = degen_groups.at(igroup);
    const double eigenvalue = std :: get<0> ( degen_group );
    if( fabs( eigenvalue ) > 1.0e-11 ){
      const int startdim = std :: get<1> ( degen_group );
      const int enddim   = std :: get<2> ( degen_group );
      std :: cout << "group " << igroup << " eigval = " << eigenvalue; 
      std :: cout << " [ " << startdim << "<-->" << enddim << " ]" << std :: endl;
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
