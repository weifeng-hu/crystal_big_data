#include "scf_class_input_ao.h"
#include "scf.h"
//#include "qcread.h"
//#include "scf_class_input_ao.h"
//#include "scf_class_SCF.h"

using namespace std;

int main( int argc, char* argv[] )
{

// get the command options
   ithaca::scf::cmd_options cmd_opt( argc, argv );

// set the scf parameters: 
// nele, basis, norb, etc.
   ithaca::scf::Input_AO input_ao( cmd_opt );

// we may need to calculate the ao integrals.
   
// ok, all the data is here, it's time to execute the scf iteration
   ithaca::scf::rhf_main( input_ao );


//  ithaca::qcread::psiread psird( cmd_opt.dir_work, cmd_opt.input_filename, cmd_opt.output_filename );
//  ithaca::scf::SCF scf_data( cmd_opt, psird );

}
