#include <iostream>
#include <utilities/solid_gen/euclidean_distance_matrix.h>
#include <utilities/solid_gen/polymer.h>

using namespace std;
using namespace iquads::crystal;
using namespace iquads::basic;

int main( int argc, char* argv[] )
{

  cout << "testing polymer" << endl;
  {
   cout << "default constructor" << endl;
   cout << "dimer" << endl;
   dimer d2;
   cout << "trimer" << endl;
   trimer d3;
   cout << "tetramer" << endl;
   tetramer d4;

   molecule mole1;
   {
    atom atom1( "C", 1.0, 0.0, 0.0, 1 );
    atom atom2( "C", 2.0, 0.0, 0.0, 1 );
    mole1.add_atom( atom1 );
    mole1.add_atom( atom2 );
   }

   molecule mole2;
   {
    atom atom1( "C", 1.0, 0.0, 0.0, 1 );
    atom atom2( "C", 2.0, 0.0, 0.0, 1 );
    mole2.add_atom( atom1 );
    mole2.add_atom( atom2 );
    mole2 += array<double,3> { 1.0, 1.5, 1.0 };
   }

   MoleculeList molelist;
   molelist.push_back(mole1);
   molelist.push_back(mole2);

   cout << "init_from()" << endl;
   d2.init_from( molelist );
   cout << " natom = " << d2.get_natom() << endl;
   cout << " dimer within radius 1.0 ?" << d2.within_radius(1.0) << endl;
   cout << " dimer within radius 6.0 ?" << d2.within_radius(6.0) << endl;

   euclidean_distance_matrix edm;
   edm.compose_from_atomlist( d2.get_atom_list() );
  }


}
