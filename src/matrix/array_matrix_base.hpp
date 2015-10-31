/*
 *  This source code applies all the terms in 
 *  GNU GENERAL PUBLIC LICENSE (GPL), Version3, 29 June 2007.
 *
 *  Copyright (C) 2013-2015 Weifeng Hu, all rights reserved.
 *  
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef ARRAY_MATRIX_BASE_HPP
#define ARRAY_MATRIX_BASE_HPP

/*
####################################################

  A matrix class based on the std::array<T, N>

  array_matrix provides an API for the 
  stack storage for a matrix with type T

  the number of elements should not exceed 
  STACK_DOUBLE_LIMIT

  array_matrix storage is initialized from
  vector_matrix objects

  further functionalities will be provided to get 
  cache-based operations instead of in-memory
  operations

####################################################
*/

#include <stdlib.h>
#include <vector>
#include <array>
#include <algorithm>
#include <utility>
#include <cassert>
#include <manybody_expansion/fragment_identifier/iquads_limits.hpp>
#include <manybody_expansion/fragment_identifier/vector_matrix_base.hpp>

using namespace std;

namespace iquads{

namespace matrix{

template< class T >
struct array_matrix_base
{
public:
  array_matrix_base(){
   this->nrow_ = 0;
   this->ncol_ = 0;
  }
  array_matrix_base( vector_matrix_base<T>* obj ){
   this->copy_from( obj );
  }

public:
  void copy_from( vector_matrix_base<T>* obj ){
   try{
    const size_t obj_size = obj->get_nelement();
    if( ( obj_size < STACK_DOUBLE_LIMIT ) == false ){
     throw obj_size;
    }
    this->nrow_ = obj->get_nrow();
    this->ncol_ = obj->get_ncol();
    vector<T> temp_store = obj->get_store();
    copy_n( temp_store.begin(), obj_size, this->store.begin() );
   }
   catch( size_t n){
    cout << " array load exception: " << n << " >= " << STACK_DOUBLE_LIMIT << endl;
    abort();
   }
  }
  void copy_to( vector_matrix_base<T>* obj ){
   obj->resize( this->nrow_, this->ncol_ );
   const size_t length = this->nrow_ * this->ncol_;
   vector<T> temp_store;
   temp_store.resize(length);
   copy_n( this->store.begin(), length, temp_store.begin() );
   obj->set_store() = move( temp_store );
  }
 
public:
  size_t get_nrow() const { return this->nrow_; }
  size_t get_ncol() const { return this->ncol_; }
  T& set_element( size_t i, size_t j ) {
   const size_t pos = i * ncol_ + j;
   assert( ( pos < STACK_DOUBLE_LIMIT ) == true );
   return this->store.at( pos );
  }
  T  get_element( size_t i, size_t j ) {
   T retval;
   retval = this->set_element(i,j);
   return retval;
  };
  T& operator() ( size_t i, size_t j ) {
   return this->set_element(i,j);
  };
  array<T, STACK_DOUBLE_LIMIT > get_store() const { return this->store; }
  array<T, STACK_DOUBLE_LIMIT >& set_store() { return this->store; } 

  friend 
  ostream& operator<< ( ostream& os, array_matrix_base<T>& mat ){
   const size_t nrow_local = mat.get_nrow();
   const size_t ncol_local = mat.get_ncol();
   for( size_t irow = 0; irow < nrow_local; irow++ ){
    for( size_t icol = 0; icol < ncol_local; icol++ ){
     const T element = mat( irow, icol );
     os << "[" << (irow+1) << "," << (icol+1) << "]:" << element << "  ";
    }
   }
   return os;
  }

private:
  array< T, STACK_DOUBLE_LIMIT > store;
  size_t nrow_, ncol_;

};

} // end of namespace matrix

} // end of namespace iquads
#endif
