#ifndef VECTOR_MATRIX_BASE_H
#define VECTOR_MATRIX_BASE_H

/*
##################################################

  A matrix class based on the std::vector<T>

  vector_matrix is an API for the heap storages 
  for matrix objects

  copying storage array_matrix objects are 
  strongly recommended when encounting front edge 
  matrix operations

##################################################
*/

#include <vector>
#include <algorithm>

namespace iquads{

namespace matrix{

template< class T >
struct vector_matrix_base
{
public:
  vector_matrix_base(){
   this->store_.resize(0);
   this->nrow_ = 0;
   this->ncol_ = 0;
   this->length_ = this->store_.size();
  }
  vector_matrix_base( size_t nrow, size_t ncol ){
   this->init( nrow, ncol );
  }

public:
  void resize( size_t new_nrow, size_t new_ncol ){
   const size_t new_length = new_nrow * new_ncol;
   this->length_ = new_length;
   this->nrow_   = new_nrow;
   this->ncol_   = new_ncol;
   this->store_.resize(length_);
  }
  void init( size_t new_nrow, size_t new_ncol ){
   this->resize( new_nrow, new_ncol );
   fill( this->store_.begin(), this->store_.end(), 0 );
  }

public:
  size_t get_nrow() const { return this->nrow_; };
  size_t get_ncol() const { return this->ncol_; };
  size_t get_nelement() const { return this->length_; };
  vector<T> get_store() const { return this->store_;  };
  vector<T>& set_store() {    return this->store_;  };
  T& set_element( size_t i, size_t j ) {
   const size_t pos = i * ncol_ + j;
   return this->store_.at( pos );
  }
  T  get_element( size_t i, size_t j ) {
   T retval;
   retval = this->set_element(i,j);
   return retval;
  };
  T& operator() ( size_t i, size_t j ) {
   return this->set_element(i,j);
  };

private:
  vector<T> store_;
  size_t nrow_, ncol_;
  size_t length_;

};

}

}

#endif
