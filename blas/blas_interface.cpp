#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "blas_interface.h"

void mat_x_mat( const double* a, const double* b, double* c, const double coeff, const int nrow_a, const int ncol_a, const int nrow_b, const int ncol_b, const bool transa, const bool transb )
{

  const int _transa = transa ? 1 : 0;
  const int _transb = transb ? 1 : 0;
  mat_x_mat_( a, b, c, &coeff, &nrow_a, &ncol_a, &nrow_b, &ncol_b, &_transa, &_transb );

}

void diag( const double* mat, double* eigvec,  double* eigval, const int n ){

  const int n2 = n*n;
  for( int i = 0; i < n2; i++ ){
   eigvec[i] = mat[i];
  } 

  symdiag_( eigvec, eigval, &n );
//  for( int i = 0; i < n2; i++ ){
//   printf("%d %20.16f\n", i, eigvec[i] );
//  } 
//  exit(0);
}

void a_x_b_x_at( double* newmat, const double* b, const double* a, const int nrow_a, const int ncol_a ){


  // a x b
  const int lentmp = nrow_a * ncol_a;
  std::vector<double> tmp; tmp.resize( lentmp );
  {
   const double coeff = 1.0e0;
   const int rowa = nrow_a;
   const int cola = ncol_a;
   const int rowb = ncol_a;
   const int colb = rowb;
   const bool transa = false;
   const bool transb = false;
   mat_x_mat( a, b, tmp.data(), coeff, rowa, cola, rowb, colb, transa, transb );
  }

  // b x at
  {
   const double coeff = 1.0e0;
   const int rowb = ncol_a;
   const int colb = rowb;
   const int rowa = nrow_a;
   const int cola = ncol_a;
   const bool transb = false;
   const bool transa = true;
   mat_x_mat(  tmp.data(), a, newmat,  coeff, rowb, colb, rowa, cola, transb, transa );
  }

}
