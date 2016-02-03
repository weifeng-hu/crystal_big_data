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

#ifndef VECTOR_MATRIX_TEMPLATE_HPP
#define VECTOR_MATRIX_TEMPLATE_HPP

#include <vector>
#include <algorithm>

namespace iquads {

namespace matrix {

/**
 *
 *  A matrix class based on the std::vector<T>
 *
 *  vector_matrix is an API for the heap storages 
 *  for matrix objects
 *
 *  copying storage array_matrix objects are 
 *  strongly recommended when encounting front edge 
 *  matrix operations
 *
 */

template < class T > struct VectorMatrix {
public:
  VectorMatrix() {
    this->store_.resize(0);
    this->nrow_ = 0;
    this->ncol_ = 0;
  }
  VectorMatrix( size_t nrow, size_t ncol ) {
    this->resize( nrow, ncol );
    std :: fill( this->store_.begin(), this->store_.end(), 0.0 );
  }

public:
  void resize( size_t new_nrow, size_t new_ncol ) {
    this->nrow_   = new_nrow;
    this->ncol_   = new_ncol;
    this->store_.resize( new_nrow * new_ncol );
  }
  size_t nrow() const 
    { return this->nrow_; }
  size_t ncol() const 
    { return this->ncol_; }
  size_t size() const 
    { return this->store_.size(); }
  std :: vector<T>& set_store()
    { return this->store_; }
  T& at( size_t i, size_t j ) {
    const size_t pos = i * ncol_ + j;
    return this->store_.at( pos );
  }
  T& operator() ( size_t i, size_t j ) {
    return this->at( i, j );
  }
  friend 
  std :: ostream& operator<< ( std :: ostream& os, VectorMatrix<T>& matrix_obj ){
    for( size_t irow = 0; irow < matrix_obj.nrow(); irow++ ) {
      for( size_t icol = 0; icol < matrix_obj.ncol(); icol++ ) {
        const T element = matrix_obj( irow, icol );
        os << "[" << (irow+1) << "," << (icol+1) << "]:" << element << "  " << std :: endl;
      }
    }
    return os;
  }
  std :: vector<T> store() const 
    { return this->store_; }

private:
  std :: vector<T> store_;
  size_t nrow_, ncol_;

}; // end of template struct VectorMatrix

} // end of namespace matrix

} // end of namespace iquads

#endif
