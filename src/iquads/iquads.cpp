
//  ---------------------------------------------------------------
//
//      Integrated QUAntum Dynamics Solver(IQUADS)
//
//                      Main Entry
//
//  ---------------------------------------------------------------

// Weifeng Hu, 2014
// hulakui@gmail.com

#include <stdlib.h>
#include <string>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include "iquads/command.h"

using namespace std;

int main( int argc, char* argv[] )
{

   string input;
   if( argc != 2 ){
     cout << endl;
     cout << "Command line error:  incorrect command line" << endl;
     cout << endl;
     cout << " Command line:" << endl;
     cout << "  <exec_dir>/iquads <input>" << endl;
     cout << endl;
     cout << " For detailed usage, type -h or --help. " << endl;
     cout << endl;
     abort();
   }
   else
   {
     input = argv[1];
     if( boost::iequals( input, "-h" ) || boost::iequals( input, "--help" ) ){
      iquads::print_help();
      exit(0);
     }
     else{
      continue;
     }
   }

   iquads::command cmd;
   cmd.read_input( input );
   if( cmd.coordination_is_set() == true && cmd.instruction_key_is_set() == true ){
     cmd.setup_instructions();
   }
   else
   {
     cout << "error: either coordination or instruction is not roundly set" << endl;
     abort();
   }

   iquads::sequence seq( cmd );
   seq.setup_stage();
   seq.launch();

}
