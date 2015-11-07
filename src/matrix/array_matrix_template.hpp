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

#ifndef ARRAY_MATRIX_TEMPLATE_HPP
#define ARRAY_MATRIX_TEMPLATE_HPP

#include <stdlib.h>
#include <vector>
#include <array>
#include <algorithm>
#include <utility>
#include <cassert>
#include <iquads/iquads_limits.hpp>
#include <matrix/vector_matrix_template.hpp>

namespace iquads {

namespace matrix {

/**
 *
 *  A matrix class based on the std::array<T, N>
 *
 *  array_matrix provides an API for the 
 *  stack storage for a matrix with type T
 *
 *  the number of elements should not exceed 
 *  STACK_DOUBLE_LIMIT
 *
 *  array_matrix storage is initialized from
 *  vector_matrix objects
 *
 *  further functionalities will be provided to get 
 *  cache-based operations instead of in-memory
 *  operations
 *
 */

template< class T > struct ArrayMatrix {
public:
  typedef std :: array< T, STACK_DOUBLE_LIMIT >  store_type;
  typedef typename store_type :: iterator                 iterator_type;

public:
  ArrayMatrix() {
    this->nrow_ = 0;
    this->ncol_ = 0;
  }
  ArrayMatrix( const VectorMatrix<T>& vector_matrix_obj ) {
    this->copy_from( vector_matrix_obj );
  }
  ArrayMatrix( size_t nrow, size_t ncol ) {
    if( nrow * ncol > STACK_DOUBLE_LIMIT ) {
      std :: cout << "cannot initialize array matrix by nrow = " << nrow << " and ncol = " << ncol << ". too big!" << std :: endl;
      abort();
    }
    this->nrow_ = nrow;
    this->ncol_ = ncol;
  }

public:
  void copy_from( const VectorMatrix<T>& vector_matrix_obj ) {
    try {
      const size_t obj_size = vector_matrix_obj.size();
      if( ( obj_size < STACK_DOUBLE_LIMIT ) == false ) {
        throw obj_size;
      }
      this->nrow_ = vector_matrix_obj.nrow();
      this->ncol_ = vector_matrix_obj.ncol();
      std :: vector<T> temp_store = vector_matrix_obj.store();
      std :: copy_n( temp_store.begin(), obj_size, this->store_.begin() );
    }
    catch( size_t n ) {
      std :: cout << " array load exception: " << n << " >= " << STACK_DOUBLE_LIMIT << std :: endl;
      abort();
    }
  }
  // must pass in a lvalue
  void copy_to( VectorMatrix<T>& vector_matrix_obj ) {
    vector_matrix_obj.resize( this->nrow_, this->ncol_ );
    const size_t length = this->nrow_ * this->ncol_;
    std :: vector<T> temp_store;
    temp_store.resize(length);
    std :: copy_n( this->store_.begin(), length, temp_store.begin() );
    vector_matrix_obj.set_store() = std :: move( temp_store );
  }
 
public:
  size_t nrow() const
    { return this->nrow_; }
  size_t ncol() const
    { return this->ncol_; }
  size_t size() const
    { return this->nrow_ * this->ncol_; }
  T& at( size_t i, size_t j ) {
    const size_t pos = i * ncol_ + j;
    assert( ( pos < STACK_DOUBLE_LIMIT ) == true );
    return this->store_.at( pos );
  }
  T& operator() ( size_t i, size_t j ) {
    const size_t pos = i * ncol_ + j;
    return this->store_.at( pos );
  }
  std :: array< T, STACK_DOUBLE_LIMIT >& set_store() 
    { return this->store_; } 

  friend 
  std :: ostream& operator<< ( std :: ostream& os, const ArrayMatrix<T>& matrix_obj ) {
    for( size_t irow = 0; irow < matrix_obj.nrow(); irow++ ) {
      for( size_t icol = 0; icol < matrix_obj.ncol(); icol++ ) {
        const T element = matrix_obj( irow, icol );
        os << "[" << (irow+1) << "," << (icol+1) << "]:" << element << "  ";
      }
    }
    return os;
  }

private:
  std :: array< T, STACK_DOUBLE_LIMIT > store_;
  size_t nrow_, ncol_;

}; // end of template struct ArrayMatrix

} // end of namespace matrix

} // end of namespace iquads

#endif
