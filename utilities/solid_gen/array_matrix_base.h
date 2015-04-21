#ifndef ARRAY_MATRIX_BASE_H
#define ARRAY_MATRIX_BASE_H

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
#include "utilities/solid_gen/iquads_limits.h"
#include "utilities/solid_gen/vector_matrix_base.h"

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

private:
  array< T, STACK_DOUBLE_LIMIT > store;
  size_t nrow_, ncol_;

};

} // end of namespace matrix

} // end of namespace iquads
#endif
