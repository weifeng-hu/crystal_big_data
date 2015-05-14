#ifndef COMPRESSED_MATRIX_H
#define COMPRESSED_MATRIX_H

#include <vector>
#include <utility>
#include "matrix/general_matrix.h"

using namespace std;

namespace iqs { namespace matrix {

// Matrix stored in the Compressed Row Storage(CRS) form

class matrix_crs
{
private:
  int ncol_ ;
  int nrow_ ;
  double thresh_;

private:
  vector<double> val_ ;
  vector<int> col_ind_ ;
  vector<int> row_nnz_ ;
  vector<int> row_ptr_ ;

public:
  // class member access
  int& ncol() { return this->ncol_; }
  int& nrow() { return this->nrow_; }
  const int get_ncol() const { return this->ncol_; }
  const int get_nrow() const { return this->nrow_; }
  
  double& thresh() { return this->thresh_; }
  double get_thresh() { return this->thresh_; }

  vector<double>& val() { return this->val_; }
  vector<int>&    col_ind() { return this->col_ind_; }
  vector<int>&    row_ptr() { return this->row_ptr_; }

  vector<double> get_val() { return this->val_; }
  vector<int>    get_col_ind() { return this->col_ind_; }
  vector<int>    get_row_ptr() { return this->row_ptr_; }

public:
 // element access
  double& element( const int i, const int j );
  double& operator() ( const int i, const int j ) { return this->element(i, j); }

//  void operator= ( const int i, const int j, const double val ) {}

public:
  void print( int all, int decimal );

public:
 // constructors
  matrix_crs( const int dim );
  matrix_crs( general_matrix& A, double threshold );
  ~matrix_crs(){};

};


} } // iqs :: matrix

#endif
