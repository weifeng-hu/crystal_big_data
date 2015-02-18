#ifndef MO_COEFFICIENTS_H
#define MO_COEFFICIENTS_H

#include <array>
#include <iostream>
#include <algorithm>
#include <cmath>
#include "parameters.h"
#include "blas_interface.h"
#include "overlap_matrix.h"

using namespace std;

namespace ph_analysis{

struct mo_coefficients
{
public:
  mo_coefficients(){};
  mo_coefficients( const int n_ao, const int n_mo ){
   this->nao = n_ao;
   this->nmo = n_mo;
   this->n_element = nao * nmo;
   if( n_element > NMO_THRESH * NMO_THRESH ){ 
    std::cout << " error: number of elements exceeds limit 1e6 " << std::endl;
    abort();
   }
   this->transposed = false;
   this->inverse_computed = false;
  };
  ~mo_coefficients(){};

public:
  const int get_nmo() const { return this->nmo; }
  const int get_nao() const { return this->nao; }
  int& set_nmo() { return this->nmo; }
  int& set_nao() { return this->nao; }

  const int get_n_element() const { return this->n_element; }
  int& set_n_element() { return this->n_element; }

  const bool& get_inverse_computed() const { return this->inverse_computed; }
  bool& set_inverse_computed() { return this->inverse_computed; }

  const double get_element( const int ind_i, const int ind_j ) const { return store.at( ind_j * nao + ind_i ); }
  const double operator() ( const int ind_i, const int ind_j ) const { return store.at( ind_j * nao + ind_i ); }
  double& set_element( const int ind_i, const int ind_j ) { return store.at( ind_j * nao + ind_i ); }
  double& operator() ( const int ind_i, const int ind_j ){ return store.at( ind_j * nao + ind_i ); }

/*
  mo_coefficients& operator= ( const mo_coefficients& rhs ){
   this->nmo = rhs.get_nmo();
   this->nao = rhs.get_nao();
   this->n_element = rhs.get_n_element();
   copy( rhs.set_store().begin(), rhs.set_store().end(), this->store.begin() );
   if( rhs.get_inverse_computed() ){
    copy( rhs.get_inverse().begin(), rhs.get_inverse().end(), this->inverse.begin() );
    this->inverse_computed = true;
   }
  }
*/
  const double get_inverse_element( const int ind_i, const int ind_j ) const { return inverse.at( ind_i * nmo + ind_j ); }
  double& set_inverse_element( const int ind_i, const int ind_j )     { return inverse.at( ind_i * nmo + ind_j); }

  const array< double, NMO_THRESH * NMO_THRESH > get_store() const { return this->store; }
  array< double, NMO_THRESH * NMO_THRESH > get_store() { return this->store; }
  const array< double, NMO_THRESH * NMO_THRESH >& set_store() const { return this->store; }
  array< double, NMO_THRESH * NMO_THRESH >& set_store() { return this->store; }

  const array< double, NMO_THRESH * NMO_THRESH >& get_inverse() const { return this->inverse; }
  array< double, NMO_THRESH * NMO_THRESH >& get_inverse()      { return this->inverse; }

  void compute_inverse(){

    cout << " computing inverse of a MO coefficients matrix is not implemented yet " << endl; abort();
    inverse_computed = true;
  }

  const bool get_transposed() const { return this->transposed; }
  bool& set_transposed() { return this->transposed; }
  friend mo_coefficients operator* ( const mo_coefficients& a, const overlap_matrix& b){
    mo_coefficients product;

    const double coeff = 1.0e0;
    const int nrow_a = a.get_nao();
    const int ncol_a = a.get_nmo();
    const int nrow_b = b.get_nao();
    const int ncol_b = b.get_nao();
    const bool transa = true;
    const bool transb = false;

    product.set_nao() = transa ? ncol_a : nrow_a;
    product.set_nmo() = transb ? nrow_b : ncol_b;
    product.set_n_element() = product.get_nao() * product.get_nmo();
    product.set_inverse_computed() = false;
    product.set_transposed() = false;

    mat_x_mat( a.set_store().data(), b.set_store().data(), product.set_store().data(), coeff, nrow_a, ncol_a, nrow_b, ncol_b, transa, transb );

    return product;
  }

  friend mo_coefficients operator* ( const overlap_matrix& a, const mo_coefficients& b ){
    mo_coefficients product;

    const double coeff = 1.0e0;
    const int nrow_a = a.get_nao();
    const int ncol_a = a.get_nao();
    const int nrow_b = b.get_nao();
    const int ncol_b = b.get_nmo();
    const bool transa = false;
    const bool transb = false;

    product.set_nao() = transa ? ncol_a : nrow_a;
    product.set_nmo() = transb ? nrow_b : ncol_b;
    product.set_n_element() = product.get_nao() * product.get_nmo();
    product.set_inverse_computed() = false;
    product.set_transposed() = false;

    mat_x_mat( a.set_store().data(), b.set_store().data(), product.set_store().data(), coeff, nrow_a, ncol_a, nrow_b, ncol_b, transa, transb );

    return product;
  }

  friend mo_coefficients operator* ( const mo_coefficients& a, const mo_coefficients& b ){

    mo_coefficients product;

    const double coeff = 1.0e0;
    const int nrow_a = a.get_nao();
    const int ncol_a = a.get_nmo();
    const int nrow_b = b.get_nao();
    const int ncol_b = b.get_nmo();
    const bool transa = a.get_transposed();
    const bool transb = b.get_transposed();

    product.set_nao() = transa ? ncol_a : nrow_a;
    product.set_nmo() = transb ? nrow_b : ncol_b;
    product.set_n_element() = product.get_nao() * product.get_nmo();
    product.set_inverse_computed() = false;
    product.set_transposed() = false;

    mat_x_mat( a.set_store().data(), b.set_store().data(), product.set_store().data(), coeff, nrow_a, ncol_a, nrow_b, ncol_b, transa, transb );

    return product;
  }

  void check_unity(){

     cout << "  check unity of the transformation matrix U" << endl;
     cout << "   print elements != 1 for diagonal and non-zero off-diagonal " << endl;
     mo_coefficients transpose = *this;
     transpose.set_transposed() = true;

     {
      mo_coefficients product_uut = (*this) * transpose;
      for( size_t i = 0; i < product_uut.get_nao(); i++ ){
       for( size_t j = 0; j < product_uut.get_nmo(); j++ ){
        const double val = product_uut( i, j );
        if( i != j ){
         if( fabs( val ) > 1.0e-8 ){ printf( "%d %d %20.16f\n", i, j, val ); }
        }
        else{
         if( fabs( val - 1.0e0 ) > 1.0e-8 ){ printf( "%d %d %20.16f\n", i, j, val ); }
        }
       }
      }
//      product_uut.print_matrix();
     }
     
     {
      mo_coefficients product_utu = transpose * (*this);
      for( size_t i = 0; i < product_utu.get_nao(); i++ ){
       for( size_t j = 0; j < product_utu.get_nmo(); j++ ){
        const double val = product_utu( i, j );
        if( i != j ){
         if( fabs( val ) > 1.0e-8 ){ printf( "%d %d %20.16f\n", i, j, val ); }
        }
        else{
         if( fabs( val - 1.0e0 ) > 1.0e-8 ){ printf( "%d %d %20.16f\n", i, j, val ); }
        }
       }
      }
//      product_utu.print_matrix();
     }

  };
  void print_matrix(){

    cout.precision(8);
    const int dim1 = this->nao;
    const int dim2 = this->nmo;
    cout << " printing all elements" << endl;
    for( int i = 0; i < dim1; i++ ){
     for( int j = 0; j < dim2; j++ ){

      const double val = this->get_element(j, i);
      if( fabs(val) >= 1.0e-7 ){
       cout << "A(" << j << ", " << i << " ) = " << this->get_element(j, i) << endl; 
      }
     }
    }
    cout << " END" << endl;

  };
  void print_diag(){

    cout.precision(8);
    const int dim = this->nmo;
    cout << " printing diagonal elements" << endl;
    for( int i = 0; i < nmo; i++ ){
     cout << "A(" << i << ", " << i << " ) = " << this->get_element(i, i) << endl; 
    }
    cout << " END" << endl;
  }

private:
  std::array< double, NMO_THRESH * NMO_THRESH > store;
  std::array< double, NMO_THRESH * NMO_THRESH > inverse;
  int nmo, nao;
  int n_element;
  bool inverse_computed;

  bool transposed;

};


}
#endif
