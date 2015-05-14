#include <string>
#include "matrix/square_matrix.h"
#include "matrix/two_electron_integral.h"
#include "rcm_main.h"

using namespace std;

namespace iqs {

namespace rcm {

iqs::matrix::square_matrix calc_fock( const int dim , const int nocc, const string filename )
{

  iqs::matrix::square_matrix fock( dim );
  iqs::matrix::square_matrix h_mtr = input_matrix( filename, 'h' );
  iqs::matrix::two_electron_integral v_2( dim );
  v_2.read_integral( filename );

  for( int i = 0; i < dim; i++ ){
   for( int j = 0; j < dim; j++ ){
      fock( i, j ) +=  h_mtr( i, j );
    for( int k = 0; k < nocc; k++ ){
      fock( i, j ) += 2.0e0 * v_2( i,j,k,k ) - v_2( i, k, j ,k ) ;
    }
   }
  }

  cout.precision(10);
  for( int i = 0; i < dim; i++ ){ cout << i << " " << fock(i,i) << endl; }
//  cout.precision(16);
//  cout << v_2( 85,84,84,83 ) << endl;

}

}  // end of rcm

}  // end of iqs
