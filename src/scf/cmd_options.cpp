#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "scf/cmd_options.h"

namespace ithaca { namespace scf {

cmd_options::cmd_options( int argc, char* argv[] )
: ithaca::cmd_options( argc, argv )
{

  this->diis_is_set       = false;
  this->scf_tol_is_set    = false;
  this->init_guess_is_set = false;

  std::string current_arg;
  for( int i = 0; i < argc; i++ )
  {
    current_arg = argv[i];

    if( current_arg == "--diis" ){
     this->diis = true;
     this->diis_is_set = true;
    }

    if( current_arg == "--scf_tol" ){
     this->scf_tol = argv[i+1];
     this->scf_tol_is_set = true;
    }

    if( current_arg == "--init_guess" ){
     this->init_guess = argv[i+1];
     this->init_guess_is_set = true;
    }

  }

};

} } // end of ithaca::scf
