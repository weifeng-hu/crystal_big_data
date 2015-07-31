#include <stdlib.h>
#include <iostream>
#include <string>
#include "ithaca/cmd_options.h"

namespace ithaca { namespace interface {

void run_psi3( ithaca::cmd_options cmd_opt ){

  int retval = 0;
  std::string cmd = "psi3 " + cmd_opt.infile_path + " out.txt";
  char* _cmd = (char*) cmd.c_str();

  retval = system( _cmd );
  if( retval > 0 ){
   cout << " error: psi3 was not successfully executed --- abort" << endl;
   cout << " please check psi3 input file " << endl;
   exit(1);
  }


};

} }
