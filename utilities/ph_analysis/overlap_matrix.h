#ifndef OVERLAP_MATRIX_H
#define OVERLAP_MATRIX_H

#include <array>
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include "parameters.h"
#include "blas_interface.h"

using namespace std;

namespace ph_analysis{

struct overlap_matrix
{
public:
 overlap_matrix(){};
 overlap_matrix( const int n_ao ){
  this->nao = n_ao;
  this->n_element = nao * nao;
  if( n_element > NMO_THRESH * NMO_THRESH ){
   std::cout << " error: number of elements exceeds limit 1e6" << std::endl;
   abort();
   this->inverse_computed = false;
   this->inversehalf_computed = false;
   this->half_computed = false;
  }
 }
 ~overlap_matrix(){};

public:
 const array< double, NMO_THRESH * NMO_THRESH > get_store() const { return this->store; }
 array< double, NMO_THRESH * NMO_THRESH > get_store() { return this->store; }
 const array< double, NMO_THRESH * NMO_THRESH >& set_store() const { return this->store; }
 array< double, NMO_THRESH * NMO_THRESH >& set_store() { return this->store; }

 const array< double, NMO_THRESH * NMO_THRESH > get_inverse() const { return this->inverse; }
 array< double, NMO_THRESH * NMO_THRESH > get_inverse() { return this->inverse; }
 const array< double, NMO_THRESH * NMO_THRESH >& set_inverse() const { return this->inverse; }
 array< double, NMO_THRESH * NMO_THRESH >& set_inverse() { return this->inverse; }

 const array< double, NMO_THRESH * NMO_THRESH > get_half() const { return this->half; }
 array< double, NMO_THRESH * NMO_THRESH > get_half() { return this->half; }
 const array< double, NMO_THRESH * NMO_THRESH >& set_half() const { return this->half; }
 array< double, NMO_THRESH * NMO_THRESH >& set_half() { return this->half; }

 const array< double, NMO_THRESH * NMO_THRESH > get_inverse_half() const { return this->inverse_half; }
 array< double, NMO_THRESH * NMO_THRESH > get_inverse_half() { return this->inverse_half; }
 const array< double, NMO_THRESH * NMO_THRESH >& set_inverse_half() const { return this->inverse_half; }
 array< double, NMO_THRESH * NMO_THRESH >& set_inverse_half() { return this->inverse_half; }

 const array< double, NMO_THRESH * NMO_THRESH > get_eigvec() const { return this->eigvec; }
 array< double, NMO_THRESH * NMO_THRESH > get_eigvec() { return this->eigvec; }
 const array< double, NMO_THRESH * NMO_THRESH >& set_eigvec() const { return this->eigvec; }
 array< double, NMO_THRESH * NMO_THRESH >& set_eigvec() { return this->eigvec; }

 const array< double, NMO_THRESH > get_eigval() const { return this->eigval; }
 array< double, NMO_THRESH > get_eigval() { return this->eigval; }
 const array< double, NMO_THRESH >& set_eigval() const { return this->eigval; }
 array< double, NMO_THRESH >& set_eigval() { return this->eigval; }

 const int get_nao() const { return this->nao; }
 int& set_nao() { return this->nao; }

 const int get_n_element() const { return this->n_element; }
 int& set_n_element(){ return this->n_element; }

 const bool& get_inverse_computed() const { return this->inverse_computed; }
 bool& set_inverse_computed() { return this->inverse_computed; }
 
 const bool& get_inversehalf_computed() const { return this->inversehalf_computed; }
 bool& set_inversehalf_computed() { return this->inversehalf_computed; }

 const bool& get_half_computed() const { return this->half_computed; }
 bool& set_half_computed() { return this->half_computed; }

 const bool& get_auxiliary_computed() const { return this->auxiliary_computed; }
 bool& auiliary_computed() { return this->auxiliary_computed; }

public:
 const double get_element( const int ind_i, const int ind_j ) const { return store.at( ind_j * nao + ind_i ); }
 const double operator() ( const int ind_i, const int ind_j ) const { return store.at( ind_j * nao + ind_i ); }
 double& set_element( const int ind_i, const int ind_j ) { return store.at( ind_j * nao + ind_i ); }
 double& operator() ( const int ind_i, const int ind_j ) { return store.at( ind_j * nao + ind_i ); }

public:

 void diagonalize(){
  this->eigvec.fill(0.0e0);
  this->eigval.fill(0.0e0);
  diag( this->store.data(), this->eigvec.data(), this->eigval.data(), this->nao );
 }

 void compute_half(){

  this->eigval_half.fill(0.0e0);
  for( int i = 0; i < this->nao; i++ ){
   this->eigval_half.at(i) = sqrt( this->eigval.at(i) );
  }

  // U S^1/2 U+
  array< double, NMO_THRESH * NMO_THRESH > diag_half; diag_half.fill(0.0e0);
  for( int i = 0; i < this->nao; i++ ){
   const int ind_mat = i * nao + i;
   diag_half.at( ind_mat ) = this->eigval_half.at(i);
  }

  this->half.fill(0.0e0);
  a_x_b_x_at( this->half.data(), diag_half.data(), this->eigvec.data(), this->nao, this->nao );

  this->half_computed = true;
 }

 void compute_inverse(){

  this->eigval_inverse.fill(0.0e0);
  for( int i = 0; i < this->nao; i++ ){
   this->eigval_inverse.at(i) = 1.0e0/( this->eigval.at(i) );
  }

  // U S^(-1) U+
  array< double, NMO_THRESH * NMO_THRESH > diag_inverse; diag_inverse.fill( 0.0e0 );
  for( int i = 0; i < this->nao; i++ ){
   const int ind_mat = i * nao + i; 
   diag_inverse.at( ind_mat ) = this->eigval_inverse.at(i);
  }

  this->inverse.fill(0.0e0);
  a_x_b_x_at( this->inverse.data(), diag_inverse.data(), this->eigvec.data(), this->nao, this->nao );

  this->inverse_computed = true;
 }

 void compute_inversehalf(){

  this->eigval_inversehalf.fill(0.0e0);
  for( int i = 0; i < this->nao; i++ ){
   this->eigval_inversehalf.at(i) = 1.0e0/( sqrt( this->eigval.at(i) ) );
  }

  // U S^(-1/2) U+
  array< double, NMO_THRESH * NMO_THRESH > diag_inversehalf; diag_inversehalf.fill(0.0e0);
  for( int i = 0; i < this->nao; i++ ){
   const int ind_mat = i * nao + i;
   diag_inversehalf.at( ind_mat ) = this->eigval_inversehalf.at(i);
  }

  this->inverse_half.fill(0.0e0);
  a_x_b_x_at( this->inverse_half.data(), diag_inversehalf.data(), this->eigvec.data(), this->nao, this->nao );

  // check symmetry
  cout << " check the symmetry of S^(-1/2)" << endl;
  for( int i = 0; i < nao; i++ ){
   for( int j = 0; j < nao; j++ ){
    const int ind1 = i * nao + j;
    const int ind2 = j * nao + i;
    const double val = inverse_half.at(ind1) - inverse_half.at(ind2);
    if( fabs(val) >= 1.0e-10 ){
     printf( "%d %d - %d %d = %20.16f\n", i, j, j, i, val );
    }
   }
  }

  this->inversehalf_computed = true;
 }

 void print_inversehalf( const string prefix, const string basename ){
  string filename = prefix + basename + ".s_inversehalf.txt"; 
  cout << "ph filename = "<< filename << endl;
  FILE* fov = fopen( filename.c_str() , "wt" );
  cout << "ph filename = "<< filename << endl;
  for( int i = 0; i < nao; i++ ){
   for( int j = 0; j < nao; j++ ){
    const int ind = i * nao + j;
    const double value = inverse_half.at( ind );
    fprintf( fov, "%d  %d  %20.16f\n", i, j, value );
   }
  }
  fclose( fov );
 }

 void compute_auxiliary( ){
  this->diagonalize();
  this->compute_half();
  this->compute_inverse();
  this->compute_inversehalf();

  /*
  // tests
  std::array< double, NMO_THRESH * NMO_THRESH > tmp;

  // S S-1 = 1
  {
   cout << "  testing S . S^-1 = 1 " << endl;
   tmp.fill(0.0e0);
   mat_x_mat( store.data(), inverse.data(), tmp.data(), 1.0e0, nao, nao, nao, nao, false, false);
   for( int i = 0; i < nao; i++ ){
    for( int j = 0; j < nao; j++ ){
     const int ind = i * nao + j;
     const double val = tmp.at(ind);
     if( val >1.0e-7 ){
      printf( "%d %d %20.16f\n", i, j, val );
     }
    }
   }

  }

  // S-1 S = 1
  {
   cout << "  testing S^-1 . S = 1 " << endl;
   tmp.fill(0.0e0);
   mat_x_mat( inverse.data(), store.data(), tmp.data(), 1.0e0, nao, nao, nao, nao, false, false);
   for( int i = 0; i < nao; i++ ){
    for( int j = 0; j < nao; j++ ){
     const int ind = i * nao + j;
     const double val = tmp.at(ind);
     if( val >1.0e-7 ){
      printf( "%d %d %20.16f\n", i, j, val );
     }
    }
   }

  }

  // S^(-1/2) S S^(-1/2) = 1
  {
   cout << "  testing S^-1/2 . S . S^(-1/2) = 1 " << endl;
   tmp.fill(0.0e0);
   a_x_b_x_at( tmp.data(), this->store.data(), this->inverse_half.data(), nao, nao );
   for( int i = 0; i < nao; i++ ){
    for( int j = 0; j < nao; j++ ){
     const int ind = i * nao + j;
     const double val = tmp.at(ind);
     if( val >1.0e-7 ){
      printf( "%d %d %20.16f\n", i, j, val );
     }
    }
   }

  }

  // S^(1/2) S^(-1) S^(1/2) = 1
  {
   cout << "  testing S^1/2 . S^-1 . S^(1/2) = 1 " << endl;
   tmp.fill(0.0e0);
   a_x_b_x_at( tmp.data(), this->inverse.data(), this->half.data(), nao, nao );
   for( int i = 0; i < nao; i++ ){
    for( int j = 0; j < nao; j++ ){
     const int ind = i * nao + j;
     const double val = tmp.at(ind);
     if( val >1.0e-7 ){
      printf( "%d %d %20.16f\n", i, j, val );
     }
    }
   }

  }

  // S^(1/2) * S(1/2) - S = 0
  {
   cout << "  testing S^1/2 S^(1/2) - S = 0 " << endl;
   tmp.fill(0.0e0);
   mat_x_mat( half.data(), half.data(), tmp.data(), 1.0e0, nao, nao, nao, nao, false, false);
   for( int i = 0; i < nao; i++ ){
    for( int j = 0; j < nao; j++ ){
     const int ind = i * nao + j;
     const double val = tmp.at(ind) - store.at(ind);
     if( fabs( val ) > 1.0e-7 ){
      printf( "%d %d %20.16f\n", i, j, val );
     }
    }
   }

  }

  */

  this->auxiliary_computed = true;
 }

private:
 std::array< double, NMO_THRESH * NMO_THRESH > store;
 std::array< double, NMO_THRESH * NMO_THRESH > eigvec;
 std::array< double, NMO_THRESH * NMO_THRESH > inverse;
 std::array< double, NMO_THRESH * NMO_THRESH > half;
 std::array< double, NMO_THRESH * NMO_THRESH > inverse_half;
 std::array< double, NMO_THRESH > eigval;
 std::array< double, NMO_THRESH > eigval_inverse;
 std::array< double, NMO_THRESH > eigval_half;
 std::array< double, NMO_THRESH > eigval_inversehalf;
 int nao;
 int n_element;
 bool inverse_computed;
 bool inversehalf_computed;
 bool half_computed;
 bool auxiliary_computed;

};

}

#endif
