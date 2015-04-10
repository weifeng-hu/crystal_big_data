#include "utilities/solid_gen/atom.h"

using namespace std;
using namespace iquads::basic;

int main( int argc, char* argv[] ){

  cout << "test iquads::basic::atom object" << endl;
  cout << endl;
  cout << "default constructor" << endl;
  {
   atom new_atom;
   cout << "using atom::print_info()" << endl;
   new_atom.print_info();
  }

  cout << endl;

  cout << "explicit constructor" << endl;
  {
   atom new_atom( "C", 1.0e0, 2.0e0, 3.0e0, 6 );
   cout << "using atom::print_info()" << endl;
   new_atom.print_info();
  }

  cout << "test within_radius()" << endl;
  {
   cout << " atom1 at [ 5.0, 7.0, 9.0 ] " << endl;
   atom new_atom1( "H", 5.0, 7.0, 9.0, 1 );
   cout << " atom within radius 6.0 is " << new_atom1.within_radius(6.0e0) << endl;

   cout << " atom2 at [ 1.0, 1.0, 1.0 ] " << endl;
   atom new_atom2( "H", 1.0, 1.0, 1.0, 1 );
   cout << " atom within radius 6.0 is " << new_atom2.within_radius(6.0e0) << endl;
  }

  cout << "test operator+= " << endl;
  {
   cout << " atom1 at [ 5.0, 7.0, 9.0 ] " << endl;
   atom new_atom( "H", 5.0e0, 7.0e0, 9.0e0, 1 );
   cout << " moving vector is [ 1.0, 1.0, 1.0 ] " << endl;
   array< double, 3 > vec = { 1.0e0, 1.0e0, 1.0e0 };
   new_atom += vec;
   new_atom.print_info();
  }

}
