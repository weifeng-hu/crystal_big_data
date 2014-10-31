
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
#include "iquads/cmd_options.h"

using namespace std;

int main( int argc, char* argv[] )
{

   string input;
   if( argc == 1 ){
     cout << endl;
     cout << "Command Error:  unknown input file" << endl;
     cout << "To run this program, a correct input file must always be specified." << endl;
     cout << endl;
     abort();
   }
   if( argc == 2 ){
     input = argv[1];
   }

   iquads::command cmd;
   cmd.read_input( input );
   cmd.setup_instructions();

   iquads::launch_sequence launch_seq;
   launch_seq.setup_seq( cmd );

   launch( launch_seq );

}
