#include <string>
#include <iostream>
#include <vector>
#include "scf_class_rhf.h"

using namespace std;

namespace ithaca { namespace scf  {

int rhf_main( Input_AO scf_inp )
{

  cout << ">>> rhf_main() " << endl;

  int  max_iter = 1;

  std::vector< ithaca::scf::rhf > scf_tuple;

  for( int i = 0; i < max_iter ; i++ ){
    cout << "      rhf iteration " << i << " : " << endl;
    ithaca::scf::rhf scf_data( scf_inp );

    scf_tuple.push_back( scf_data );

  }


}

} }
