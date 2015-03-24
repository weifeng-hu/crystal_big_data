#include <stdio.h>
#include <string>
#include <vector>
#include "fragment_gen.h"

int main( int argc, char* argv[] )
{
 
  using namespace std;
 
  vector<string> args;
  args.resize(argc);
  {
   const int istart = 0;
   const int iend   = argc;
   for( size_t i = istart; i < iend; i++ ){ 
    args[i] = argv[i]; 
   }
  }
 
  fragment_gen_driver( args );

}
