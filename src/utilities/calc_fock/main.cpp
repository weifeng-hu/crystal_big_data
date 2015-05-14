#include <stdlib.h>
#include <string>
#include <vector>
#include "matrix/fc_fortran.h"
#include "matrix/general_matrix.h"
#include "matrix/one_electron_integral.h"
#include "matrix/two_electron_integral.h"

using namespace std;

int main( int argc, char* argv[] )
{

  string one_file = argv[1];
  string two_file = argv[2];
  int norb = atoi( argv[3] );
  int nocc = atoi( argv[4] );

  cout << one_file << endl;
  cout << two_file << endl;
  cout << norb << endl;
  cout << nocc << endl;

 // exit(0);

  iqs::matrix::one_electron_integral v1_mo( norb );
  v1_mo.read( one_file );

  iqs::matrix::two_electron_integral v2_mo( norb );
  v2_mo.read( two_file );

//exit(0);
  iqs::matrix::general_matrix fock_mo( norb, norb );

  for( int i = 0; i < norb; i++ ){
   for( int j = 0; j < norb; j++ ){
    fock_mo( i, j ) += v1_mo( i, j );
    for( int k = 0; k < nocc; k++ ){
     fock_mo( i, j ) += 2.0e0 * v2_mo( i, j, k, k ) - v2_mo( i, k, j, k );
    }
   }
  }

  vector<double> eigval; eigval.resize(norb);
  vector<double> eigvec = fock_mo.get_matrix();
  iqs::matrix::eigtql2_( &norb, (eigvec.data()), (eigval.data()) );

  cout.precision(16);
  for( int i = 0; i < norb; ++i ){
    cout << eigval.at(i) << endl;
  }

}
