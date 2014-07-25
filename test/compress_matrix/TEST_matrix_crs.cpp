//////////////////////////////////////////////////////////////////////
//
//  A test program for the Compressed Row Storage 
//
//  Compressed Row Storage:
//  Ref:
//  Templates for the Solution of Algebraic Eigenvalue Problems, SIAM
//  by ZJ. Bai etc.
//    Common issues --> Sparse Matrix Storage Formats 
//     --> Compressed Row Storage
//
//  main class:
//    matrix/compressed_matrix.h :     class matrix_crs
//  functions defined in
//    matrix/compressed_matrix.cpp
//
/////////////////////////////////////////////////////////////////////

#include <iostream>
#include "matrix/compressed_matrix.h"
#include "matrix/general_matrix.h"

using namespace std;

int main( int argc, char* argv[] )
{

// The matrix from the book is 
//    [ 10 0 0 0 -2  0 ]
//    [  3 9 0 0  0  3 ]   
//    [  0 7 8 7  0  0 ]
//    [  3 0 8 7  5  0 ]
//    [  0 8 0 9  9 13 ]
//    [  0 4 0 0  2 -1 ]
//
  cout << endl;
  iqs::matrix::general_matrix A(6,6);
  A(0,0) = 10.0e0; A(0,1) = 0.0e0; A(0,2) = 0.0e0; A(0,3) = 0.0e0; A(0,4) = -2.0e0; A(0,5) =  0.0e0;
//  A(0,0) =  0.0e0; A(0,1) = 0.0e0; A(0,2) = 0.0e0; A(0,3) = 0.0e0; A(0,4) =  0.0e0; A(0,5) =  0.0e0;
//  A(1,0) =  3.0e0; A(1,1) = 9.0e0; A(1,2) = 0.0e0; A(1,3) = 0.0e0; A(1,4) =  0.0e0; A(1,5) =  3.0e0;
  A(1,0) =  0.0e0; A(1,1) = 0.0e0; A(1,2) = 0.0e0; A(1,3) = 0.0e0; A(1,4) =  0.0e0; A(1,5) =  0.0e0;
//  A(2,0) =  0.0e0; A(2,1) = 7.0e0; A(2,2) = 8.0e0; A(2,3) = 7.0e0; A(2,4) =  0.0e0; A(2,5) =  0.0e0;
  A(2,0) =  0.0e0; A(2,1) = 0.0e0; A(2,2) = 0.0e0; A(2,3) = 0.0e0; A(2,4) =  0.0e0; A(2,5) =  0.0e0;
  A(3,0) =  3.0e0; A(3,1) = 0.0e0; A(3,2) = 8.0e0; A(3,3) = 7.0e0; A(3,4) =  5.0e0; A(3,5) =  0.0e0;
//  A(3,0) =  0.0e0; A(3,1) = 0.0e0; A(3,2) = 0.0e0; A(3,3) = 0.0e0; A(3,4) =  0.0e0; A(3,5) =  0.0e0;
//  A(4,0) =  0.0e0; A(4,1) = 8.0e0; A(4,2) = 0.0e0; A(4,3) = 9.0e0; A(4,4) =  9.0e0; A(4,5) = 13.0e0;
  A(4,0) =  0.0e0; A(4,1) = 0.0e0; A(4,2) = 0.0e0; A(4,3) = 0.0e0; A(4,4) =  0.0e0; A(4,5) = 0.0e0;
  A(5,0) =  0.0e0; A(5,1) = 4.0e0; A(5,2) = 0.0e0; A(5,3) = 0.0e0; A(5,4) =  2.0e0; A(5,5) = -1.0e0;
//  A(5,0) =  0.0e0; A(5,1) = 0.0e0; A(5,2) = 0.0e0; A(5,3) = 0.0e0; A(5,4) =  0.0e0; A(5,5) = -0.0e0;
  A.print( 4, 1 );

  iqs::matrix::matrix_crs B( A, 1.0e-15 );
  cout << endl;
  B.print( 4, 1 );
  cout << endl;

}
