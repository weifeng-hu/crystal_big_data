#ifndef PDM_H
#define PDM_H

#include <array>
#include <iostream>
#include "parameters.h"

using namespace std;

struct onepdm
{
public:
  onepdm(){};
  onepdm( const int n_orb ){
   this->norb = n_orb;
   this->n_element = norb * norb;
   if( n_element > NACT_THRESH * NACT_THRESH ){
    std::cout << " error: number of elements exceeds limit 1e4 " << std::endl;
    abort();
   }
  }
  ~onepdm(){};

public:
  void set_type_vo()
  {
    cout << "  setting onepdm type to vo " << endl;
    for( size_t i = 0; i < norb; i++ ){
     for( size_t j = 0; j < norb; j++ ){
      if( i < nocc ) this->set_element( i, j ) = 0.0e0;
      if( j >= nocc ) this->set_element( i, j ) = 0.0e0;
     }
    }
  }

public:
  const int get_norb() const { return this->norb; }
  int& set_norb() { return this->norb; }

  const int get_n_element() const { return this->n_element; }
  int& set_n_element() { return this->n_element; }
 
  const array<double, NACT_THRESH * NACT_THRESH > get_store() const { return this->store; }
  array<double, NACT_THRESH * NACT_THRESH > get_store(){ return this->store; }
  const array<double, NACT_THRESH * NACT_THRESH >& set_store() const { return this->store; }
  array<double, NACT_THRESH * NACT_THRESH >& set_store() { return this->store; }

  const double get_element( const int ind_i, const int ind_j ){ return store.at( ind_i * norb + ind_j ); }
  double& set_element( const int ind_i, const int ind_j ){ return store.at( ind_i * norb + ind_j ); }

  double& operator() ( const int ind_i, const int ind_j ){ return store.at( ind_i * norb + ind_j ); }
  const double operator() ( const int ind_i, const int ind_j ) const { return store.at( ind_i * norb + ind_j ); }

private:
  array< double, NACT_THRESH * NACT_THRESH > store;
  int norb, nocc;
  int n_element;

};

struct twopdm
{
public:
  twopdm(){};
  twopdm( const int n_orb ){
   this->norb = n_orb;
   this->n_element = norb * norb * norb * norb;
   if( n_element > NACT_THRESH * NACT_THRESH * NACT_THRESH * NACT_THRESH ){
    std::cout << " error: number of elements exceeds limit 1e8 " << std::endl;
    abort();
   }
   this->store.fill(0.0e0);
  }
  ~twopdm(){};

public:
  void set_type_vvoo()
  {
   cout << "  setting twopdm type to vvoo " << endl;
   for( size_t i = 0; i < norb; i++ ){
    for( size_t j = 0; j < norb; j++ ){
     for( size_t k = 0; k < norb; k++ ){
      for( size_t l = 0; l < norb; l++ ){
       if( i < nocc ) this->set_element( i, j, k, l ) = 0.0e0;
       if( j < nocc ) this->set_element( i, j, k, l ) = 0.0e0;
       if( k >= nocc ) this->set_element( i, j, k, l ) = 0.0e0;
       if( l >= nocc ) this->set_element( i, j, k, l ) = 0.0e0;
      }
     }
    }
   }

  }

public:
  const int get_norb() const { return this->norb; }
  int& set_norb() { return this->norb; }

  const int get_n_element() const { return this->n_element; }
  int& set_n_element() { return this->n_element; }

  const array<double, NACT_THRESH * NACT_THRESH * NACT_THRESH * NACT_THRESH > get_store() const { return this->store; }
  array<double, NACT_THRESH * NACT_THRESH * NACT_THRESH * NACT_THRESH > get_store(){ return this->store; }
  const array<double, NACT_THRESH * NACT_THRESH * NACT_THRESH * NACT_THRESH >& set_store() const { return this->store; }
  array<double, NACT_THRESH * NACT_THRESH * NACT_THRESH * NACT_THRESH >& set_store() { return this->store; }

  const double get_element( const int ind_i, const int ind_j, const int ind_k, const int ind_l ) const 
    { return store.at( ind_i * norb * norb * norb + ind_j * norb * norb + ind_k * norb + ind_l ); }
  double& set_element( const int ind_i, const int ind_j, const int ind_k, const int ind_l )
    { return store.at( ind_i * norb * norb * norb + ind_j * norb * norb + ind_k * norb + ind_l ); }

  double& operator() ( const int ind_i, const int ind_j, const int ind_k, const int ind_l )
    { return store.at( ind_i * norb * norb * norb + ind_j * norb * norb + ind_k * norb + ind_l); }
  const double operator() ( const int ind_i, const int ind_j, const int ind_k, const int ind_l ) const 
    { return store.at( ind_i * norb * norb * norb + ind_j * norb * norb + ind_k * norb + ind_l ); }

  twopdm& operator+ ( const twopdm& to_be_added ){
   const int norb_a = to_be_added.get_norb();
   if( norb_a != this->norb ){ cout << " error: two pdms with different norbs cannot be added"; abort(); }
   for( int i = 0; i < norb; i++ ){
    for( int j = 0; j < norb; j++ ){
     for( int k = 0; k < norb; k++ ){
      for( int l = 0; l < norb; l++ ){
       this->set_element( i, j, k, l ) = this->get_element( i, j, k, l ) + to_be_added( i, j, k, l );
      }
     }
    }
   }
   return *this;
  }

private:
  std::array< double, NACT_THRESH * NACT_THRESH * NACT_THRESH * NACT_THRESH > store;
  int norb;
  int nocc;
  int n_element;

};

#endif
