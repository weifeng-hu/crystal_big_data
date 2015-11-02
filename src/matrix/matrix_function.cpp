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
#include <iquads/iquads_limits.h>
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

bool is_the_same( const DMatrixHeap& eigval_a, const DMatrixHeap& eigval_b ) {

  bool retval = true;
  try{
    retval = distance_of_two_matrices( eigval_a, eigval_b ) <= 1.0e-2 ? true : false;
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
  } catch ( tuple< size_t, size_t > conflict_nrows ) {
    std :: cout << " matrix exception: is_the_same() " << std :: endl;
    std :: cout << "   lengths of eigen value vectors are unequal " << std :: endl;
    std :: cout << "   length a = " << std :: get<0>( conflict_nrows );
    std :: cout << "   length b = " << std :: get<1>( conflict_nrows );
    std :: cout << endl;
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

IMatrixHeap compute_boolean_mat( const std :: vector<DMatrixHeap>& eigvals ) {

  // std :: cout << "Compute boolean matrix ... " << std :: endl;
//  vector<int> vertex;

  size_t n_matrix = eigvals.size();
//  vertex.resize(n_matrix);

//  boost::adjacency_matrix<boost::undirectedS, property<int> > Matrix(n_matrix, vertex);
//  boost::adjacency_matrix<boost::undirectedS> Matrix(n_matrix);
//  int n = n_matrix;
//  boost::adjacency_list< boost::setS, boost::vecS, boost::undirectedS > List(n_matrix);

  size_t num_of_comp = n_matrix * n_matrix;
  // std :: cout  << num_of_comp << " matrix pairs to compare:" << std :: endl;
  size_t count_interval = num_of_comp/5;

  IMatrixHeap retval( n_matrix, n_matrix );
  for( size_t imatrix = 0; imatrix < n_matrix; imatrix++ ) {
    DMatrixHeap matrix_i = eigvals.at(imatrix);
    for( size_t jmatrix = 0; jmatrix < n_matrix; jmatrix++ ) {
      DMatrixHeap matrix_j = eigvals.at(jmatrix);
      retval( imatrix, jmatrix ) = is_the_same( matrix_i, matrix_j ) ? 1: 0;
//    if( is_the_same( &matrix_i, &matrix_j) ){
//     boost::add_edge(imatrix,jmatrix, List);
//    }
//    cout << " boolean_mat [ " << imatrix << ", " << jmatrix << " ] = " << retval(imatrix, jmatrix) << endl;;
      size_t current_count = imatrix * n_matrix + jmatrix;
//    if( (current_count+1) % count_interval == 0 ){
//     cout << (current_count*100/num_of_comp + 1 ) << "%\tcompleted" << endl;
//    }
    }
  }
//  boost::write_graphviz(cout, List );
//  boost::print_graph(List);

  return retval;
//  exit(0);
}

std :: vector< std :: vector< int > > get_groups( const IMatrixHeap& boolean_mat ){

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

std :: vector< std :: tuple< double, int, int> > get_degeneracy_groups( std :: DMatrixHeap& eigval ) {

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

std :: vector< std :: vector< int > > get_degeneracy_group( const DMatrixHeap& mat ) {

  std :: vector< std :: vector< int > > retval;

  int dimension = mat.nrow();
  DMatrixHeap eigvec( dimension, dimension );
  DMatrixHeap eigval( dimension, 1 );
  symmetric_diag_big( mat, &eigvec, &eigval );

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
