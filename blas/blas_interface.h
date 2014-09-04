#ifndef BLAS_INTERFACE
#define BLAS_INTERFACE

void mat_x_mat( const double* a, const double* b, double* c, const double coeff, const int nrow_a, const int ncol_a, const int nrow_b, const int ncol_b, const bool transa, const bool transb );

void diag( const double* mat, double* eigvec, double* eigval, const int dim );

void a_x_b_x_at( double* newmat, const double* b, const double* a, const int nrow_a, const int ncol_a );

extern "C"
{

  void mat_x_mat_( const double* a, const double* b, double* c, const double* coeff, const int* nrow_a, const int* ncol_a, const int* nrow_b, const int* ncol_b, const int* _transa, const int* _transb );

  void symdiag_( double* eigvec, double* eigval, const int* n );

}

#endif
