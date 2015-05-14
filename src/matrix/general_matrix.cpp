#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <string>
#include "matrix/general_matrix.h"

namespace iqs {

namespace matrix {

void general_matrix :: reorder_row( vector<int>& new_seq )
{

  vector<int> org_seq; for( int i = 0; i < nrow(); i++ ){ org_seq.push_back(i); }
  vector<double> row; row.resize( ncol() );
  for( int i = 0; i < nrow(); i++ ){
   for( int j = 0; j < ncol(); j++ ){ row.at(j) = element( org_seq.at(i), j ); }
   for( int j = 0; j < ncol(); j++ ){ element( org_seq.at(i), j ) = element( new_seq.at(i), j ); }
   for( int j = 0; j < ncol(); j++ ){ element( new_seq.at(i), j ) = row.at(j); }
  }

}

void general_matrix :: reorder_col( vector<int>& new_seq )
{

  vector<int> org_seq; for( int j = 0; j < ncol(); j++ ){ org_seq.push_back(j); }
  vector<double> col; col.resize( nrow() );
  for( int j = 0; j < ncol(); j++ ){
   for( int i = 0; i < nrow(); i++ ){ col.at(i) = element( i, org_seq.at(j) ); }
   for( int i = 0; i < nrow(); i++ ){ element( i, org_seq.at(j) ) = element( i, new_seq.at(j) ); }
   for( int i = 0; i < nrow(); i++ ){ element( i, new_seq.at(j) ) = col.at(i); }
  }

}

inline vector<double> general_matrix :: row( int i )
{
  vector<double> v;
  for( int j = 0; j < ncol(); j++ ){ v.push_back( matrix.at( i * dim0 + j ) ); }
  return v;
}

inline vector<double> general_matrix :: col( int j )
{
  vector<double> v;
  for( int i = 0; i < nrow(); i++ ){ v.push_back( matrix.at( i * dim0 + j ) ); }
  return v;
}

inline void general_matrix :: zero()
{
  for( int i = 0; i < nrow() * ncol(); i++ ){
    matrix.at(i) = 0.0e0;
  }
} // end of zero()

void general_matrix :: read_matrix( string filename )
{

  ifstream file;
  file.open( filename.c_str(), std::ios::in );
  file.precision(16);
  int p1, p2; double val;
  while( file.good() ){
    file >> p1 >> p2 >> val;
    this->element( p1, p2 ) = val;
  }
  file.close();

} // end of read_matrix

void general_matrix :: print( int all, int decimal )
{

  char format[100];
  const char presenta = '%';
  sprintf( format, "%c%i.%if ", presenta, all, decimal );

  printf( "Print general matrix\n" );
  for( int i = 0; i < nrow(); i++ ){
   for( int j = 0; j < ncol(); j++ ){
    printf( format, this->element( i, j ) );
   }
   printf( "\n" );
  }

}

general_matrix :: general_matrix( int d0, int d1 )
{

  this->dim0 = d0;
  this->dim1 = d1;
  this->matrix.resize( dim0 * dim1 );
  this->zero();

} // end of general_matrix()

} // end of matrix

} // end of iqs
