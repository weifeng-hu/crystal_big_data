#include <cmath>
#include <iostream>
#include "matrix/general_matrix.h"
#include "matrix/compressed_matrix.h"

#define DBG 0

using namespace std;

namespace iqs { namespace matrix {

double& matrix_crs :: element( const int i, const int j )
{

  int nnz = row_nnz_.at(i);
  if( nnz == 0 ){ return *val_.end(); }
  else{
    int m = row_ptr_.at(i);
    int n = m + nnz;
    for( int k = m; k <= n; k++ ){
      if( k == n ){ return *val_.end(); }
      if( col_ind_.at(k-1) == j )return val_.at(k-1);
    }
  }

}

void matrix_crs :: print( int all, int decimal )
{

  char format[100];
  char presenta = '%';
  sprintf( format, "%c%i.%if ", presenta, all, decimal );

  printf( "Print matrix in CRS \n" );
  for( int i = 0; i < nrow(); i++ ){
   for( int j = 0; j < ncol(); j++ ){
    printf( format, this->element( i, j ) );
   }
   printf( "\n" );
  }

}

matrix_crs :: matrix_crs( const int dim )
{
}


#define _SCAN_ROW_ \
        nnz_inrow = 0; nz_start = -1; \
        for( int j = 0; j < ncol(); j++ ){  \
             value = A( i, j );             \
             if( fabs(value) >= thresh() ){ \
                nnz_inrow = nnz_inrow + 1;              \
                val_.push_back( value );    \
                col_ind_.push_back( j );    \
                if( nz_start == -1 ) nz_start = val_.size(); \
             }                              \
             if( DBG )cout << "A[ " << i << ", "  << j << " ] = " <<  value << "  nnz_inrow = " << nnz_inrow << endl; \
        }                                   \
        row_nnz_.push_back(nnz_inrow);            \
        if( nnz_inrow == 0 ){ row_ptr_.push_back(0); }     \
        else{ row_ptr_.push_back( nz_start ); }   
 
matrix_crs :: matrix_crs( general_matrix& A, double threshold )
{

  this->thresh_ = threshold;
  this->ncol_ = A.ncol();
  this->nrow_ = A.nrow();

  int nnz_inrow, nz_start;
  double value;

  val_.resize(0);
  col_ind_.resize(0);
  row_nnz_.resize(0);
  row_ptr_.resize(0);

  cout.precision(8);

  if( nrow() == 1 ){
      int i = 0;
      _SCAN_ROW_

  } // end of nrow == 1
  else if( nrow() == 2 ){
      int i = 0;
      _SCAN_ROW_

       i = 1;
      _SCAN_ROW_ 
  } // end of nrow() == 2
  else if( nrow() >= 3 ){
      int i = 0;
      _SCAN_ROW_

      for( int i = 1; i < nrow()-1; i++ ){
        _SCAN_ROW_ 
      }
  
      i = nrow() - 1;
      _SCAN_ROW_
  
  } // if nrow > 3
  
  row_ptr_.push_back( val_.size() + 1 );
  val_.push_back(0.0e0);
  col_ind_.push_back(-1);

#ifdef USE_DBG  
  cout << "val: "; for( int i = 0; i < val_.size(); i++ ){ cout << val_.at(i) << " " ; } cout << endl;
  cout << "col_ind: "; for( int i = 0; i < col_ind_.size(); i++ ){ cout << col_ind_.at(i) << " " ; } cout << endl;
  cout << "row_ptr: "; for( int i = 0; i < row_ptr_.size(); i++ ){ cout << row_ptr_.at(i) << " " ; } cout << endl;
  cout << "row_nnz: "; for( int i = 0; i < row_nnz_.size(); i++ ){ cout << row_nnz_.at(i) << " " ; } cout << endl;
#endif


// //  A do-while version of the constructor
// //  for illustration
//
//  int i = 0;
//  int j = 0;
//  int countnz;
//  while( true )
//  {
//    countnz = 0;
//    double value = A(i,j);
//    if( fabs(val) >= thresh ){
//      val_.push_back( value );
//      col_ind_.push_back(j);
//      ++countnz;
//    }
//    ++j;
//    if( j == ncol ){
//      if( countnz == 0 && i == 0 ){
//        row_ptr_.push_back(0);
//      }
//      else if( countnz == 0 && i > 0 ){
//        row_ptr_.push_back( row_ptr_.at( row_ptr_.size() - 1 ) );
//      }
//      else{
//        row_ptr_.push_back( val_.size() + 1 );
//      }
//
//      j = 0;
//      countnz = 0;
//      ++i;
//    }
//  }
//

} // emd of matrix_crs :: matrix_crs( general_matrix&, double )

} } // iqs::matrix
