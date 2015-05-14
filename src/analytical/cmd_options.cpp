#include <string>
#include <iostream>
#include "cmd_options.h"

namespace ithaca { namespace anaytical {

cmd_options::cmd_options( int argc, char* argv[] )
{
  exec_path_is_set = false;
  work_dir_is_set  = false;
  scratch_dir_is_set = false;
  dmrg_exec_is_set   = false;

  for( int iopt = 0; iopt < argc; iopt++ ){
    std::string current_arg = argv[ iopt ];

    if( iopt == 0 ){
     exec_path = argv[0];
     _exec_path = argv[0];
     exec_path_is_set = true;
    }
    else if( current_arg == "-w" ){
     work_dir = argv[iopt+1];
     _work_dir = argv[iopt+1];
     work_dir_is_set = true;
    }
    else if( current_arg == "-s" )
     scratch_dir = argv[iopt+1];
     _scratch_dir = argv[iopt+1];
     scratch_dir_is_set = true;
  }

  if( exec_path_is_set == false ){
    cout << "exec path is not set " << endl;
    exit(1);
  }
  else if( work_dir_is_set == false ){
    cout << "work dir is not set" << endl;
    exit(1);
  }
  else if( scratch_dir_is_set == false ){
    cout << "scratch dir is not set " << endl;
    exit(1);
  }

}

} }
