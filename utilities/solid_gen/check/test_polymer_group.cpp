#include <iostream>
#include <utilities/solid_gen/polymer_group_base.h>

using namespace std;
using namespace iquads::crystal;

int main( int argc, char* argv[] ){

  cout << "test polymer_group object" << endl;
  {
   cout << "implicit instantiation" << endl;
   polymer_group_base<2> dimer_group;
   polymer_group_base<3> trimer_group;
  }

}
