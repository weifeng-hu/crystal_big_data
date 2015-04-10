#include <iostream>
#include "utilities/solid_gen/molecule.h"

using namespace std;
using namespace iquads::basic;

int main( int argc, char* argv[] ){

  cout << "test molecule object" << endl;
  cout << endl;
  {
   cout << "test default constructor" << endl;
   cout << "using print_info()" << endl;
   {
    molecule new_mole;
    new_mole.print_info();
   }

   molecule new_mole;
   {
    cout << "test add_atom()" << endl;
    atom new_atom1( "C", 1.0, 1.0, 1.0, 6 );
    atom new_atom2( "H", 0.5, 1.0, 0.5, 1 );
    new_mole.add_atom( new_atom1 );
    new_mole.add_atom( new_atom2 );
   }
   new_mole.print_info();

   cout << "test within_radius() " << endl;
   cout << " within radius of 1.0e0 ? " << new_mole.within_radius(1.0e0) << endl;
   cout << " within radius of 3.0e0 ? " << new_mole.within_radius(3.0e0) << endl;

   cout << " test operator += " << endl;
   {
    cout << " adding vector [ 1.0 1.0 1.0 ]" << endl;
    array<double, 3> vec = { 1.0e0, 1.0e0, 1.0e0 };
    new_mole += vec;
    new_mole.print_info();
   }

   cout << " test get_edges() " << endl;
   {
    array< array<double, 2>, 3 > edges = new_mole.get_edges();
    cout << "x max = " << edges.at(0).at(0) << " x min = " << edges.at(0).at(1) << endl;
    cout << "y max = " << edges.at(1).at(0) << " y min = " << edges.at(1).at(1) << endl;
    cout << "z max = " << edges.at(2).at(0) << " z min = " << edges.at(2).at(1) << endl;
   }

  }

}
