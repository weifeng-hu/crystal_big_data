#include <stdlib.h>
#include <iostream>
#include "../../ithaca/cmd_options.h"
#include "../qcdmrg/cmd_options.h"

using namespace ithaca;
using namespace std;

namespace ithaca { namespace interface { namespace qcdmrg {

cmd_options::cmd_options( int argc, char* argv[] )
 : ithaca::cmd_options( argc, argv )
{
// check whether the parent class is fine 
  if( this->input_is_set       == false || 
      this->output_is_set      == false || 
      this->dir_work_is_set    == false ||
      this->dir_scratch_is_set == false   )
  {
    cout << endl;
    cout << "Some command options in ithaca::cmd_options are not set. Please check. " << endl;
    cout << endl;
    exit(1);
  }

// Initialize the bool members of this class
  this->dmrg_input_is_set  = false;
  this->dmrg_output_is_set = false;

  for( int iopt = 0; iopt < argc ; iopt = iopt +2 )
  {


  }

};

} } } // end of ithaca::interface::qcdmrg
