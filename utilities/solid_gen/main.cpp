#include <stdio.h>
#include <string>

using namespace std;

int main( int argc, char* argv[] )
{

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
