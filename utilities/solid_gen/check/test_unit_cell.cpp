#include <iostream>
#include <utilities/solid_gen/unit_cell.h>

using namespace std;
using namespace iquads::basic;
using namespace iquads::crystal;

int main( int argc, char* argv[] )
{

  cout << "test unit_cell objects" << endl;
  cout << endl;

  cout << "unit_cell = atom" << endl;
  {
   cout << "default constructor" << endl;
   atomic_ucell au;
   cout << "using print_info()" << endl;
   au.print_info();

   cout << "adding node" << endl;
   atom new_atom1( "Au", 1.0, 1.0, 0.0, 92 );
   atom new_atom2( "Au", 0.0, 1.0, 0.0, 92 );
   atom new_atom3( "Au", 0.0, 0.0, 0.0, 92 );
   atom new_atom4( "Au", 1.0, 0.0, 0.0, 92 );
   au.add_node( new_atom1 );
   au.add_node( new_atom2 );
   au.add_node( new_atom3 );
   au.add_node( new_atom4 );
   au.set_constants() 
    = lattice_parameters( make_tuple( 2.0, 2.0, 2.0 ), make_tuple( 90.0, 90.0, 90.0) );
   au.set_constants().compute_translational_vectors();
   au.print_info();

   cout << "do displacement" << endl;
   au += array<double, 3 > {0.1, 0.1, 0.1};
   au.print_info();
   cout << "duplicate unit cell to a new cell" << endl;
   atomic_ucell new_cell 
    = au.translational_duplicate( make_tuple( 3, 5, 7) );
   new_cell.print_info();

   cout << "test within_radius()" << endl;

   cout << "original cell is within a radius of 6.0e0 ?" << au.within_radius(6.0e0) << endl;
   cout << "new cell is within a radius of 6.0e0?" << new_cell.within_radius(6.0e0) << endl;

  }

  {
   cout << "unit_cell = molecule" << endl;
   cout << "adding molecule" << endl;
   molecule new_molecule1( "o2.1" );
   {
    new_molecule1.add_atom( atom( "O", 0.0e0, 0.0e0, 0.0e0, 8) );
    new_molecule1.add_atom( atom( "O", 0.0e0, 1.0e0, 0.0e0, 8) );
   }
   molecule new_molecule2( "o2.2" );
   {
    new_molecule2.add_atom( atom( "O", 0.0e0, 1.0e0, 0.0e0, 8) );
    new_molecule2.add_atom( atom( "O", 0.0e0, 1.0e0, 1.0e0, 8) );
   }
   molecular_ucell mu;
   mu.add_node( new_molecule1 );
   mu.add_node( new_molecule2 );
   mu.set_constants()
    = lattice_parameters( make_tuple( 3.0e0, 3.0e0, 3.0e0 ), make_tuple( 120.0, 120.0, 120.0) );
   mu.set_constants().compute_translational_vectors();
   mu.print_info();

   cout << "do displacement" << endl;
   mu += array<double, 3> { 0.1, 0.2, 0.3};
   mu.print_info();

   cout << "duplicate unit cell to a new cell" << endl;
   molecular_ucell new_mu
    = mu.translational_duplicate( make_tuple( 3, 5, 7) );
   new_mu.print_info();

   cout << "test within_radius()" << endl;
   cout << "original cell is within a radius of 10.0e0?" << mu.within_radius(10.0e0) << endl;
   cout << "new cell is within a radius of 10.0e0?" << new_mu.within_radius(10.0e0) << endl;
  }

}
