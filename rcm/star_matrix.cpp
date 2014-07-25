#include <iostream>
#include <stdlib.h>
#include <cmath>
#include "../matrix/square_matrix.h"
#include "star_matrix.h"

using namespace std;

namespace iqs {

namespace rcm {

void star_matrix::generate_star_mat()
{

  this->nstar_ = 0;
  for( int i = 0; i < dim0; i++ ){
   for( int j = 0; j < dim1; j++ ){
    if( fabs( orig_mat[i][j]) >= threshold  ){
      star_mat[i][j] = '*';
      ++nstar_;
    }
    else{
      star_mat[i][j] = ' ';
    }
   }
  }
}

star_matrix::star_matrix( double thres, iqs::matrix::square_matrix matrix )
{

  this->dim0 = matrix.get_dim();
  this->dim1 = matrix.get_dim();

//  cout << dim0 << " " << dim1 << endl;

  this->orig_mat = new double* [dim0];
  for( int i = 0; i < dim0; i++ ){ this->orig_mat[i] = new double [dim1]; }

  for( int i = 0; i < dim0; i++ ){ 
   for( int j = 0; j < dim1; j++ ){ 
//    cout << i << " " << j << endl; 
    orig_mat[i][j] = matrix(i,j); 
   } 
  }


  this->threshold = thres;
  this->star_mat = new char* [dim0];
  for( int i = 0; i < dim0; i++ ){ this->star_mat[i] = new char [dim1]; }
  this->generate_star_mat();

} // end of star_matrix()

} // end of rcm

} // end of iqs
