#include <tuple>
#include <iostream>
#include "utilities/solid_gen/lattice_parameters.h"

using namespace std;
using namespace iquads::crystal;

int main( int argc, char* argv[] )
{

  cout << "test lattice parameters object" << endl;
  {
   cout << "default constructor" << endl;
   cout << "using print_info()" << endl;
   lattice_parameters lp;
   lp.print_info();
  }

  {
   cout << "explicit constructor" << endl;
   cout << "using print_info()" << endl;
   tuple<double, double, double> edge_lengths
    = make_tuple( 1.0, 2.0, 3.0);
   tuple<double, double, double> angles
    = make_tuple( 90.0, 90.0, 90.0 );
   lattice_parameters lp( edge_lengths, angles );
   lp.print_info();

   cout << "test compute_translational_vectors()" << endl;
   lp.compute_translational_vectors();
   lp.print_info();
  }

}
