// PROGRAM: 
// A fragment generator for molecular crystals
//
// DESCRPTION:
// This program identifies unique types of
// fragments, e.g., dimers, trimers, in 
// a big molecular crystal lattice.
//
// AUTHOR: 
// Weifeng Hu
//

#include <stdio.h>
#include <string>
#include <vector>
#include "utilities/solid_gen/fragment_gen.h"

int main( int argc, char* argv[] )
{

  using namespace std;

  // transfer arguments to strings
  vector<string> args;
  args.resize(argc);
  for( size_t iarg = 0; iarg < argv; iarg++ ){ 
   args[i] = argv[i]; 
  }

  // enter the main driver
  fragment_gen_driver( args );

  return 0;
}
