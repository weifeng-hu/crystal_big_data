#ifndef GENERAL_MATRIX_H
#define GENERAL_MATRIX_H

#include <vector>
#include <string>
#include <fstream>

using namespace std;

namespace iqs {

namespace matrix {

class general_matrix
{

private:
  int dim0, dim1;
  vector<double> matrix;
  vector<double> matrix_t;

public:
  general_matrix(){};
  general_matrix( int d0, int d1 );
  ~general_matrix(){};

public:
  int& nrow() { return this->dim0; }
  int& ncol() { return this->dim1; }

  double& element( int i0, int i1 ){ return this->matrix.at( i0 * dim1 + i1 ); }
  double& operator() ( int i0, int i1 ){ return this->element( i0, i1 ); }

  inline vector<double> row( int i );
  inline vector<double> col( int j );

  vector<double>& get_matrix() { return this->matrix; }

  void reorder_col( vector<int>& new_seq );
  void reorder_row( vector<int>& new_seq );

public:
  inline void zero();

public:
  void read_matrix( string filename );
  void print( int all, int decimal );

};

} // end of matrix

} // end of iqs

#endif
