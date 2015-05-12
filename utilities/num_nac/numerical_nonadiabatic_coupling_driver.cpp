#include <vector>
#include <string>
#include <invoker_numerical_nonadiabatic_coupling.h>

namespace iquads {

using std::string;
using std::vector;

int numerical_nonadiabatic_coupling_driver( vector<string> args ){

  Invoker_NumericalNonAdiabaticCoupling invoker( args );

  while( true )
  {
   invoker.process_request();
   if( invoker.nomore_request() == true ) break;
  }

  return 0;

}; // end of driver function

} // end of namespace iquads
