#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "../matrix/square_matrix.h"
#include "star_matrix.h"

using namespace std;

namespace iqs {

namespace rcm {

void star_matrix::print_star_mat()
{

  cout << " Print star matrix: " << endl;
//  cout << endl;
  cout << " print threshold = " << threshold << endl;
//  cout << " " ; for( int i = 0; i < dim1; i++ ){ cout << i << " "; } cout << " +" << endl;

  cout << "+" ; for( int i = 0; i < dim1; i++ ){ cout << " -"; } cout << " +";
  cout << endl;

  for( int i = 0; i < dim0; i++ ){
    string line;
    line = "| " ; for( int j = 0; j < dim1; j++ ){ line = line + star_mat[i][j] + " "  ;}
    cout << line << "|" << endl;
  }
  cout << "+" ; for( int i = 0; i < dim1; i++ ){ cout << " -"; } cout << " +";

  cout << endl;

}

} // end of rcm

} // end of iqs
