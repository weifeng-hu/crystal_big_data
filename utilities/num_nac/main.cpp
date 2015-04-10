#include <string>
#include <vector>
#include "num_nac/num_nac.h"

int main( int argc, char* argv[] )
{

 using namespace std;
 vector<string> args;
 args.resize(argc);
 {
  const int istart = 0;
  const int iend = argc;
  for( size_t i = istart; i < iend; i++ ){
   args[i] = argv[i];
  }
 }

 numerical_nac_driver( args );

}
