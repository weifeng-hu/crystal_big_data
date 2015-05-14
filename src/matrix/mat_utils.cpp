#include <math.h>
#include "mat_utils.h"

double* diag_matrix_( int dim, double* eigval, double* diag_matrix )
{
  int dim2 = dim*dim;

  diag_matrix = new double [dim2];
  for( int i = 0; i < dim2; i++ ){ diag_matrix[i] = 0.0e0; }

  for( int i = 0; i < dim ; i++ ){
   diag_matrix[ i * dim + i ] = eigval[i];
  }
  return diag_matrix;
}

double* non_zero_diag( int dim, double* m1, double* m2 )
{
  int icount = 0;
  double val;

  for( int i = 0; i < dim; i++ ){
   val = m1 [ i * dim + i ];
   if( fabs( val - 1.0e-16 ) <= 1.0e-10 ) icount++;
  }

  int icount2 = icount*icount;

  m2 = new double [icount2];
  for( int i = 0 ; i < icount2; i++ ){ m2[i] = 0.0e0;  }
  for( int i = 0 ; i < icount ; i++ ){
     int j = dim - icount + i;
   m2[ i * icount + i ] = m1[ j * dim + j ];
  }

  return m2;
}
