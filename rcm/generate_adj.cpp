#include <vector>
#include <iostream>
#include <cmath>
#include "../matrix/square_matrix.h"
#include "star_matrix.h"

using namespace std;

namespace iqs {

namespace rcm {

void star_matrix::generate_adj( vector<int>& xadj, vector<int>& adj )
{

   xadj.push_back(0);
   int count = 0;
   for( int i = 0; i < dim0; i++ ){
    for( int j = 0; j < dim1; j++ ){
      if( fabs( star_mat[i][j] == '*' ) ){ 
       if( i != j ){
         adj.push_back(j);
//         cout << j << " " ;
         count = count + 1;
       }
      }
    }
    xadj.push_back(count); //cout << "  indice = " << count << endl;
   }

}

}

}
