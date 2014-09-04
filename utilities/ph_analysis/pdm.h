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
  int norb;
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
  }
  ~twopdm(){};

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
  const double set_element( const int ind_i, const int ind_j, const int ind_k, const int ind_l )
    { return store.at( ind_i * norb * norb * norb + ind_j * norb * norb + ind_k * norb + ind_l ); }

  double& operator() ( const int ind_i, const int ind_j, const int ind_k, const int ind_l )
    { return store.at( ind_i * norb * norb * norb + ind_j * norb * norb + ind_k * norb + ind_l); }
  const double operator() ( const int ind_i, const int ind_j, const int ind_k, const int ind_l ) const 
    { return store.at( ind_i * norb * norb * norb + ind_j * norb * norb + ind_k * norb + ind_l ); }

private:
  std::array< double, NACT_THRESH * NACT_THRESH * NACT_THRESH * NACT_THRESH > store;
  int norb;
  int n_element;

};

#endif
