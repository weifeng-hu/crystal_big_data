#include <iostream>
#include "utilities/solid_gen/lattice.h"

using namespace std;
using namespace iquads::crystal;
using namespace iquads::basic;

int main( int argc, char* argv[] ){

  cout << "test lattice object" << endl;
  {
   cout << "default constructor" << endl;
   cout << "using print_info()" << endl;
   molecular_lattice ml;
   ml.print_info();

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
    = lattice_parameters( make_tuple( 3.0e0, 3.0e0, 3.0e0 ), make_tuple( 90.0, 90.0, 90.0) );
   mu.set_constants().compute_translational_vectors();
 
   ml.set_primitive( mu );
   ml.generate( make_tuple( 3, 3, 3) );
   ml.print_info();
  }


}
