#include <iostream>
#include <utilities/solid_gen/euclidean_distance_matrix.h>

using namespace std;
using namespace iquads::crystal;
using namespace iquads::basic;
using namespace iquads::matrix;

int main( int argc, char* argv[] )
{

  cout << "test euclidean distance matrix" << endl;
  {
   cout << "test constructor" << endl;
   euclidean_distance_matrix edm;
  }

  cout << "test explicit constructor" << endl;
  {
   atom atom1( "C", 1.0,  0.0, 0.0 , 6 );
   atom atom2( "H", 0.5,  1.0, 0.0 , 1 );
   atom atom3( "H", 0.3, -1.0, 1.0 , 1 );
   euclidean_distance_matrix edm(2);
   cout << "test construct from atomlist" << endl;
   AtomList new_atomlist;
   new_atomlist.push_back( atom1 );
   new_atomlist.push_back( atom2 );
   new_atomlist.push_back( atom3 );
   edm.compose_from_atomlist( new_atomlist );
   cout << edm(0,0) << " " << edm(0,1) << " " << edm(0,2) << endl;
   cout << edm(1,0) << " " << edm(1,1) << " " << edm(1,2) << endl;
   cout << edm(2,0) << " " << edm(2,1) << " " << edm(2,2) << endl;
   cout << "test diagonalise" << endl;
   edm.diagonalise();
   DMatrixHeap eigval = edm.get_eigval();

   array<double,3> x = { 1.0, 1.0, 1.0 };
   AtomList new_atomlist_x;
   atom1 += x;
   atom2 += x;
   atom3 += x;
   new_atomlist_x.push_back( atom1 );
   new_atomlist_x.push_back( atom2 );
   new_atomlist_x.push_back( atom3 );
   euclidean_distance_matrix edm_x;
   edm_x.compose_from_atomlist( new_atomlist_x );
//   cout << edm_x(0,0) << " " << edm_x(0,1) << " " << edm_x(0,2) << endl;
//   cout << edm_x(1,0) << " " << edm_x(1,1) << " " << edm_x(1,2) << endl;
//   cout << edm_x(2,0) << " " << edm_x(2,1) << " " << edm_x(2,2) << endl;
   edm_x.diagonalise();

   DMatrixHeap eigval_x = edm_x.get_eigval();
   cout << " is the same? " << is_the_same( &eigval, &eigval_x ) << endl;

  }

}
