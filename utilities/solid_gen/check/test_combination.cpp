#include <iostream>
#include <utilities/solid_gen/combination.h>
#include <utilities/solid_gen/math_function.h>

using namespace std;
using namespace iquads::math;

template< size_t k >
vector< array<int, k> > get_x( size_t n )
{

  vector<array<int, k > > retval = get_combination<k>(n);
  return retval;

}

int main( int argc, char* argv[] ){

  cout << "test combination" << endl;
  {
//   cout << "get a list of combination of (5,3)" << endl;
   size_t n = 5;
   vector< array< int, 2> > retval = get_combination<2>(n);
  }

}
