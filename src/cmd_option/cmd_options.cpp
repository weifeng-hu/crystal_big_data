#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "dmrgclass_cmd_option.h"

namespace ithaca  { namespace dmrg {

cmd_option::cmd_option( int argc, char* argv[] )
{
  exec_dir = "";
  work_dir = "";
  input_file = "";
  oei_file = "";
  tei_file = "";
  scratch_dir = "";
  output_file = "";

/*
 _____________________________________________________________________________

    1. Get information from command line
        including:
        a. -e      dmrg executable directory (this option should be set 
                   as system default value in future version
     
        b. -i      input file
           -oeint
           -teint  integral file(directory)
           -w      the directory of above files(they should be put in the
                 same directory)
        c. -s      scratch directory
        d. -o      output file
 
        The array of character are transformed into strings
        There should be a command line class to handle this

 _____________________________________________________________________________

*/

  for( int iopt = 0; iopt < argc; iopt++ )
  {
    std::string current_arg = argv[iopt];
    if( iopt == 0 )
    {
      exec_dir = argv[iopt];
//      cout << " dmrg (directory)executable = " << exec_dir << endl;
    }
    else if( current_arg == "-w" )
    {
      work_dir = argv[iopt+1];
//      cout << " working directory = " << work_dir << endl;
    }
    else if( current_arg == "-i" )
    {
      input_file = argv[iopt+1];
//      cout << " input file = " << input_file << endl;
    }
    else if( current_arg == "-oeint" )
    {
      oei_file = argv[iopt+1];
//      cout << " one-electron integral file name = " << oei_file << endl;
    }
    else if( current_arg == "-teint" )
    {
      tei_file = argv[iopt+1];
//      cout << " two-electron repulsion integral file name = " << tei_file << endl;
    }
    else if( current_arg == "-s" )
    {
      scratch_dir = argv[iopt+1];
//      cout << " scratch directory = " << scratch_dir << endl;
    } 
    else if( current_arg == "-o" )
    {
      output_file = argv[iopt+1];
//      cout << " output file = " << output_file << endl;
    }
    else if( current_arg == "--help" )
    {
      cout << endl;
      cout << " Density Matrix Renormalization(DMRG) Theory Module" << endl;
      cout << endl;
      cout << endl;
      cout << " Command line to run this program:" << endl;
      cout << " <executable directory>/dmrg -w /home/dmrg/  -i a.inp -oeint a.oei -teint b.tei -s /home/scratch -o a.out" << endl;
      cout << endl;
      cout << " Required options: " << endl;
      cout << "       -w        Working directory, containing the input file and integral files" << endl;
      cout << endl;
      cout << "       -i        Input file name" << endl;
      cout << "       -oeint    One-electron integral file name" << endl;
      cout << "       -teint    Two-electron integral file name" << endl;
      cout << endl;
      cout << "       -s        Scratch directory, all the intermediate files will be stored in it " << endl;
      cout << endl;
      cout << "       -o        Output file name" << endl;
      cout << endl;
      cout << endl;
      cout << " For more information or reporting bugs, please feel free to contact hulakui@gmail.com " << endl;
      cout << endl;

    }
  }
} // end of cmd_opt::cmd_opt

} } // namespace ithaca::dmrg
