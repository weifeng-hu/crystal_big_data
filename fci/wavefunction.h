#ifndef WAVEFUNCTION_H
#define WAVEFUNCTION_H

#include <random>
#include <array>
#include <algorithm>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cmath>

#include "tensor_product.h"
#include "fci.h"


using namespace std;

namespace fci {

struct wavefunction
{
public:
  wavefunction(){};
  wavefunction( const int _norb, const int _particle, const int _sz, const bool _rand ){
   this->nsite = norb;
   this->dim = pow( 4, norb );
   if( dim > DIM_THRESH ){
    cout << " error: number of sites is too larger " << endl;
    abort();
   }
   this->set_space();

   this->particle = _particle;
   this->sz = _sz;
   this->store.fill(0.0e0);
   if( _rand == true ) { 
    this->rand(); 
    this->_norm = norm();
    this->apply_state( particle, sz );
   }
  }
  wavefunction( const int _norb, const int _particle, const int _sz ){
   this->nsite = norb;
   this->dim = pow( 4, norb );
   if( dim > DIM_THRESH ){
     cout << " error: number of sites is too larger " << endl;
     abort();
   }
   this->particle = _particle;
   this->sz = _sz;
   this->store.fill(0.0e0);
  }
  ~wavefunction{}

public:
  template<> 
  array<int, DIM_THRESH>& tensor_product( array<int, DIM_THRESH/4>& sub_tensor, const array<int, 4>& unit_tensor , const int sub_length );
  template<>
  array<int, DIM_THRESH>& tensor_product( const array<int, 4>& unit, const int _nsite );

public:
  void apply_state_p(){ 
   for( int i = 0; i < this->dim; i++ ){
    const int value = this->store_p.at(i);
    if( value != particle ){
     this->store_d.at(i) = 0.0e0;
    }
   }
  };
  void apply_state_sz(){
   for( int i = 0; i < this->dim; i++ ){
    const int value = this->store_sz.at(i);
    if( value != sz ){
     this->store_d.at(i) = 0.0e0;
    }
   }
  }
  void apply_state(){ 
   this->apply_state_p();
   this->apply_state_sz();
  }

  void set_space(){
   this->store_p = tensor_product<int>( this->unit_p, this->nsite );
   this->store_sz = tensor_product<int>( this->unit_sz, this->nsite );
  }
 
  wavefunction& multiplyH( const int h_type );
  wavefunction& multiplyQC();
  wavefunction& multiplyPPP();
  wavefunction& multiplyHBD();

public:
  void rand(){
   default_random_engine generator;
   uniform_real_distribution<double> distribution(0.0e0, 1.0e0);
   for( int i = 0; i < dim; i++ ){
    double number = distribution(generator);
    store_d.at(i) = number;
   }
  }

  double norm(){

   double norm_ = vec_norm( this->store.data(), dim );
   this->_norm = norm_;
   return this->get_norm();

  }

  double operator* ( const wavefunction& w2 ){
   if( this->get_dim() != w2.get_dim() ){ cout << " assertion dim1 == dim2 failed in operator *" << endl; abort(); }
   double inner_prod = vec_p_vec( this->set_store_d().data(), w2.set_store_d().data(), w1.get_dim() );
   return inner_prod;
  }

  wavefunction& operator= ( const wavefunction& rhs ){
   std::copy( rhs.set_store_d().begin(), rhs.set_store_d().end(), this->set_store_d().begin());
   std::copy( rhs.set_store_p().begin(), rhs.set_store_p().end(), this->set_store_p().begin());
   std::copy( rhs.set_store_sz().begin(), rhs.set_store_sz().end(), this->set_store_sz().begin());
   this->_norm = rhs.get_norm();
   this->nsite = rhs.get_nsite();
   this->dim   = rhs.get_dim();
   this->partcile = rhs.get_particle();
   this->sz       = rhs.get_sz();
   return *this;
  }

  wavefunction& operator+= ( const wavefunction& rhs, const double a ){
   if( this->get_dim() != rhs.get_dim() ){ cout << " assertion dim1 == dim2 failed in operator += " << endl; abort(); }
   const int _dim = rhs.get_dim();
   vec_p_vec( this->set_store_d().data(), rhs.set_store_d(), a, _dim );
   return *this;
  }
  wavefunction& operator-= ( const wavefunction& rhs, const double a ){
   if( this->get_dim() != rhs.get_dim() ){ cout << " assertion dim1 == dim2 failed in operator += " << endl; abort(); }
   const int _dim = rhs.get_dim();
   const double _a = -1.0e0 * a;
   vec_p_vec( this->set_store_d().data(), rhs.set_store_d(), _a, _dim );
   return *this;
  }

public:
  array<double, DIM_THRESH>& set_store_d() { return this->store_d; }
  const array<double, DIM_THRESH>& get_store_d() const { return this->store_d; }
  array<double, DIM_THRESH>& get_store_p() { return this->store_p; }
  const array<double, DIM_THRESH>& get_store_p() const { return this->store_p; }
  array<double, DIM_THRESH>& get_store_sz() { return this->store_sz; }
  const array<double, DIM_THRESH>& get_store_sz() const { return this->store_sz; } 
  const double get_norm() const { return this->_norm; }
  const int get_nsite() const { return this->nsite; }
  int& set_nsite() { return this->nsite; } 

  void set_nsite( const int _nsite ){
   this->nsite = _nsite;
   this->dim = pow( 4, nsite );
   if( dim > DIM_THRESH ){
    cout << " error: number of sites is too larger " << endl;
    abort();
   }
   this->set_space(); 
  }

  const int get_dim() const { return this->dim; }

  const int get_particle() const { return this->particle; }
  int& set_particle() { return this->particle; }
  const int get_sz() const { return this->sz; }
  int& set_sz() { return this->sz; }

  const double get_element( const int ind ){ return this->store.at(ind); }
  double& operator( const int ind ){ return this->store.at(ind); }

  wavefunction operator* ( const virtual_op op, const wavefunction v){
   

  }

private:
  array<double, DIM_THRESH> store_d;
  array<int, DIM_THRESH > store_p;
  array<int, DIM_THRESH > store_sz;
  const array<int, 4> unit_p = { 0, 1, 1, 2 };
  const array<int, 4> unit_sz = { 0, 1, -1, 0 };
  double _norm;
  int nsite;
  int dim;
  int particle;
  int sz;

}

struct wf_buffer
{
public:
  wf_buffer(){}
  wf_buffer( const wavefunction& wf ){
   this->nsite = wf.get_nsite();
   this->nstore = 1;
   this->dim = wf.get_dim();
   this->particle = wf.get_particle();
   this->sz = wf.get_sz();
   std::copy( wf.set_store_d().begin(), wf.set_store_d().end(), this->store_d.begin() );
   std::copy( wf.set_store_p().begin(), wf.set_store_p().end(), this->store_p.begin() );
   std::copy( wf.set_store_sz().begin(), wf.set_store_sz().end(), this->store_sz.begin() );
   this->pos_last += nstore * dim; 
  }
  ~wf_buffer(){};

public:
  void append( wavefunction& wf ){ 
   *this | wf;
  };

  wf_buffer& operator| ( wavefunction& wf ){
   if( this->get_dim() != wf.get_dim() ){ cout << " assertion dim1 == dim2 failed in operator | " << endl; abort(); }
   if( this->get_particle() != wf.get_particle() ){ cout << " assertion particle1 == particle2 failed in operator | " << endl; abort(); }
   if( this->get_sz() != wf.get_sz() ){ cout << " assertion sz1 == sz2 failed in operator | " << endl; abort(); }

   std::copy( wf.set_store_d(), wf.set_store_d()+dim, this->pos_last );
   this->pos_last += dim;

   return *this;
  }

  wavefunction& get_element( const int i ){
   wavefunction wf( this->nsite, this->particle, this->sz );
   array<double, DIM_THRESH * MAXITER > :: iterator pos = this->store_d.begin();
   this->pos += dim * i;
   std::copy( pos, pos + dim, wf.begin() );
   return std::move( wf );
  }

  wavefunction& operator[] ( const int i ){
   wavefunction wf( this->nsite, this->particle, this->sz );
   wf = this->get_element(i);
   return std::move( wf );
  }

public:
  array<double, DIM_THRESH * MAXITER>& set_store_d() { return this->store_d; }
  const array<double, DIM_THRESH * MAXITER>& get_store_d() const { return this->store_d; }
  array<double, DIM_THRESH>& set_store_p(){ return this->store_p; }
  const array<double, DIM_THRESH * MAXITER>& get_store_p() const { return this->store_p; }
  array<double, DIM_THRESH>& set_store_sz(){ return this->store_sz; }
  const array<double, DIM_THRESH * MAXITER>& get_store_sz() const { return this->store_sz; }

  const int get_nsite() const { return this->nsite; }
  int& set_nsite() const { return this->nsite; }

  const int get_nstore() const { return this->nstore; }
  int& set_nstore() { return this->nstore; }
  const int get_dim() const { return this->dim; }
  int* set_dim() { return this->dim; }
  const int get_particle() const { return this->particle; }
  int& set_particle(){ return this->particle; }
  const int get_sz() const { return this->sz; }
  int& set_sz() { return this->sz; }

private:
  array<double, DIM_THRESH * MAXITER> store_d;
  array<int, DIM_THRESH> store_p;
  array<int, DIM_THRESH> store_sz;

  array<double, DIM_THRESH * MAXITER> :: iterator pos_last = store_d.begin();
  int nsite;
  int nstore;
  int dim;
  int particle;
  int sz;
  

};

}

#endif
