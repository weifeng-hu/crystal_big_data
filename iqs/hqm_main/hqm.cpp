

//  ----------------------------------------------------------------------------------------
//
//      Integrated THeoretical and Applied Computational Chemistry Applications(ITHACCA)
//
//                                       Main Driver
//
//  ----------------------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "ithaca/cmd_options.h"
//#include "interface/psi3/psi3.h"
//#include "interface/qcdmrg/qcdmrg.h"
//#include "interface/qcdmrg/qcdmrg_class.h"

using namespace std;

int main( int argc, char* argv[] )
{

// command options setup
    ithaca::cmd_options cmd_opt( argc, argv );

//  run psi3 scf and cphf
//    ithaca::interface::run_psi3( cmd_opt );

//  get data from psi3 output
//    ithaca::interface::qcread::psiread psi_data();

// call dmrg and get pdms
//    ithaca::interface::qcdmrg_class dmrg_data( cmd_opt );
//    ithaca::interface::run_dmrg( dmrg_data );

// call gradient module
//    ithaca::analytical::gradient_class gradient_data();

// call geometry step in orca
//    ithaca::analytical::run_orca_geo_step();
  
}
