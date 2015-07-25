#include <fstream>
#include <string>
#include <vector>
#include "matrix/general_matrix.h"
#include "matrix/functions.h"
//#include "mkl.h"

namespace iqs {

namespace matrix {

vector<int> read_vector( string filename )
{

  vector<int> v;
  ifstream file; 
  file.open( filename.c_str(), std::ios::in );
  string entry; int val;
  while( file >> val )
  {
    v.push_back( val );
  }
  return v;

}

int  A_x_B_x_C( bool transpose_A, bool transpose_B, bool transpose_C, general_matrix& A, general_matrix& B, general_matrix& C, general_matrix& D )
{

  MKL_INT lda, ldb;
  double* c;
  CBLAS_ORDER Order = CblasRowMajor;
  CBLAS_TRANSPOSE TransA, TransB;
  if( transpose_A == true ){ TransA = CblasTrans; }  else{ TransA = CblasNoTrans; }
  if( transpose_B == true ){ TransB = CblasTrans; }  else{ TransB = CblasNoTrans; }
  MKL_INT M = A.nrow();
  MKL_INT N = B.ncol();
  MKL_INT K = A.ncol();
  double alpha = 1.0e0;
  double* a = A.get_matrix().data();
  if( TransA == CblasNoTrans ){ lda = M; } else { lda = K; }
  double* b = B.get_matrix().data();
  if( TransB == CblasNoTrans ){ ldb = K; } else { ldb = N; }
  double beta = 1.0e0;
  iqs::matrix::general_matrix mtr1( A.nrow(), B.ncol() );
  c = mtr1.get_matrix().data();
  MKL_INT ldc = M;
  cblas_dgemm( Order, TransA, TransB, M, N, K, alpha, a, lda, b, ldb, beta, c, ldc );


  Order = CblasRowMajor;
  TransA = CblasNoTrans;
  if( transpose_C == true ){ TransB = CblasTrans; }  else{ TransB = CblasNoTrans; }
  M = mtr1.nrow();
  N = C.ncol();
  K = mtr1.ncol();
  alpha = 1.0e0;
  a = mtr1.get_matrix().data();
  if( TransA == CblasNoTrans ){ lda = M; } else { lda = K; }
  b = C.get_matrix().data();
  if( TransB == CblasNoTrans ){ ldb = K; } else { ldb = N; }
  beta = 1.0e0;
  c = D.get_matrix().data();
  ldc = M;
  cblas_dgemm( Order, TransA, TransB, M, N, K, alpha, a, lda, b, ldb, beta, c, ldc );

  return 0;
}

} // end of matrix

} // end of iqs
