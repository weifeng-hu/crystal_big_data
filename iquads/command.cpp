
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "iquads/cmd_options.h"

using namespace std;

namespace iquads {

// prints a brief help script
void print_little_help( int iopt )
{
     cout << endl;
     cout << " Unknown number " << iopt << " argument in command" << endl;
     cout << endl;
     cout << " The minimum correct command line is " << endl;
     cout << endl;
     cout << " <EXEC_DIR>/ithaca <input file name> <output file name> " << endl;
     cout << "    OR " << endl;
     cout << " <EXEC_DIR>/ithaca -i <input file name> -o <output file name> " << endl;
     cout << endl;
     cout << " Be advised that if you only want to use the above simplest command lines, please " << endl;
     cout << " first enter into a directory that you wish to work in, and the both of the file " << endl;
     cout << " names should NOT include the file paths of them. " << endl;
     cout << endl;
     cout << " If need further help, type -h or --help for more information. " << endl;
     cout << endl;
}

// prints the whole help document of the current program
void print_help()
{
       cout << endl;
       cout << " Program of Intergrated THeoretical and Advanced Computational Applications(ITHACA): " << endl;
       cout << endl;
       cout << " Basic execution command line: " << endl;
       cout << endl;
       cout << " <EXEC_DIR>/ithaca <input file name> <output file name> " << endl;
       cout << "    OR " << endl;
       cout << " <EXEC_DIR>/ithaca -i <input file name> -o <output file name> " << endl;
       cout << endl;
       cout << " Be advised that if you only want to use the above simplest command lines, please " << endl;
       cout << " first enter into a directory that you wish to work in, and the both of the file names  " << endl;
       cout << " should NOT include the file paths of them. " << endl;
       cout << endl;
       cout << " Extended options: " << endl;
       cout << endl;
       cout << " 1. Directory:" << endl;
       cout << endl;
       cout << "    This program chooses the current directory as the working and scratching directory " << endl;
       cout << "    if no other options are given. " << endl;
       cout << endl;
       cout << "    Working directory contains the input file and output file; " << endl;
       cout << "    Scratching directory contains all the intermediated files generated during the " << endl;
       cout << "    execution of the program package. " << endl;
       cout << endl;
       cout << "    To specify these directories, use options below: " << endl;
       cout << endl;
       cout << "    -w or --work_dir <full path of working directory> " << endl;
       cout << "    -s or --scratch_dir <full path of scratch directory> " << endl;
       cout << endl;
       cout << endl;
       cout << " 2. Input and Output:" << endl;
       cout << endl;
       cout << "    THE INPUT FILE NAME(PATH) MUST BE SPECIFIED ALL THE TIME." << endl;
       cout << "    If output file is not given, then the default output file is output.txt which will be written under " << endl;
       cout << "    the current directory. " << endl;
       cout << endl;
       cout << "    To specify input and output file name and path, use the following options: " << endl;
       cout << endl;
       cout << "    -i or --input_file <input file name> " << endl;
       cout << "    -o or --output_file <output file name> " << endl;

       cout << endl;
       cout << "3. SCF:" << endl;
       cout << endl;
       cout << "    If the user sets no additional options other than input and output paths, the SCF program will " << endl;
       cout << "    automatically set the options. However, the users can use the following options." << endl;
       cout << endl;
       cout << "    --diis        enable DIIS. DIIS is off by default. " << endl;
       cout << "    --scf_tol     set the scf convergence tolerance. This tolerance is 1.0e-7 by default."    << endl;
       cout << "    --init_guess  set the initial guess method. The Default method is Core Hamiltonian."      << endl;
       cout << endl;



       cout << endl;
       cout << " End of Help Script. " << endl;
       cout << endl;

};

std::string cmd_options::get_workdir() { return this->dir_work; }

// constructor for class ithaca::cmd_options
cmd_options::cmd_options( int argc, char* argv[] )
{
// Initialize all the bool parameters
   this->input_is_set       = false;
   this->output_is_set      = false;
   this->dir_work_is_set    = false;
   this->dir_scratch_is_set = false;

// first argument is the file path of executable.
   this->path_exec = argv[0];

// Case for no options -- stop execution
   if( argc == 1 )
   {
     cout << endl;
     cout << "Command Error:  unknown input file" << endl;
     cout << "To execute this program, a correct input file must always be specified." << endl;
     cout << "type -h or --help and see the section of 'Input and Output' for more information. " << endl;
     cout << endl;
     exit(1);
   }

// Case for having a single additional option -- see whether containing correct input file.
   if( (argc == 2 || argc == 3) )
   {
     std::string current_arg;

     int iopt = 1;
     {
     current_arg = argv[iopt];

//   if the second options is just for asking help
     if( current_arg == "-h" || current_arg == "--help"){
        ithaca::print_help();
        exit(1);
     }
//   if not asking for help check the good status of input file
     else{
        ifstream infile; 
        infile.open( argv[iopt] );
        int ch = infile.get();
        if( infile.good() == false ){
        cout << endl;
        cout << "File Error:  Input file '" << argv[iopt] << "'  is empty or do not exist. Please check. " << endl;
        cout << endl;
        exit(1);
        }
        else if( infile.good() == true ){
//      set default values for parameters in this case
        this->input_filename = current_arg;
        this->dir_work        = "./"; 
        this->dir_scratch     = "./"; 
        this->output_filename = "out.txt";

        this->_input_filename  = ( char* ) this->input_filename.c_str();
        this->_dir_work        = ( char* ) this->dir_work.c_str();
        this->_dir_scratch     = ( char* ) this->dir_scratch.c_str();
        this->_output_filename = ( char* ) this->output_filename.c_str();

        this->input_is_set       = true;
        this->output_is_set      = true;
        this->dir_work_is_set    = true;
        this->dir_scratch_is_set = true;
        }
       }
     } // end of the scope for iopt = 1;

//  if output file is also given in command line
     if( argc == 3 )
     {
       iopt = 2;
       current_arg = argv[iopt];
       this->output_filename  = current_arg;
       this->_output_filename = ( char* ) this->output_filename.c_str();
       this->output_is_set    = true;
     }

   } // end of argc = 2 or 3

// if a more detailed command line is given
   if( argc > 3 && argv[1][0] == '-' ){
   for( int iopt = 1; iopt < argc ; iopt = iopt + 2 )
   {
     std::string current_arg = argv[iopt];
     if( current_arg == "-w" || current_arg == "--work_dir" )
     {
       char cmd[500];
       sprintf( cmd, "cd %s", argv[iopt+1] );
       if( system( cmd ) ){
          cout << endl;
          cout << "Command Error:  Invalid working directory " << endl;
          cout << "                Expecting a complete command line input with " << endl;
          cout << "                -w/--work_dir <full path of working directory> " << endl;
          cout << endl;
          exit(1); 
       }
       else if( system( cmd ) == 0 ){
         this->dir_work        = argv[iopt+1];
         this->_dir_work       = ( char* ) dir_work.c_str();
         this->dir_work_is_set = true; 
       }
     }

     else if( current_arg == "-s" || current_arg == "--scratch_dir" ) 
     {
       char cmd[500];
       sprintf( cmd, "cd %s", argv[iopt+1] );
       if( system( cmd ) ){
          cout << endl;
          cout << "Command Error:  Invalid scratch directory" << endl;
          cout << "                Expecting a complete command line input with " << endl;
          cout << "                -s/--scratch_dir <full path of scratch directory>" << endl;
          cout << endl;
          exit(1);
       }
       else if( system( cmd ) == 0 ){
          this->dir_scratch        = argv[iopt+1];
          this->_dir_scratch       = ( char* ) dir_scratch.c_str();
          this->dir_scratch_is_set = true;
       }
     }

     else if( current_arg == "-i" || current_arg == "--input_file" )
     {
        fstream infile;
        this->infile_path = this->dir_work + argv[iopt+1];
        this->_infile_path = ( char* ) infile_path.c_str();
        infile.open( _infile_path );
        int ch = infile.get();
        if( infile.good() == false ){
           cout << endl;
           cout << "File Error:  Input file '" << infile_path << "'  is empty or do not exist. Please check. " << endl;
           cout << endl;
           exit(1);
        }
        else if( infile.good() == true ){
           this->input_filename     = argv[ iopt + 1 ];
           this->_input_filename    = ( char* ) this->input_filename.c_str();
           this->input_is_set       = true;
        }
     }
     else if( current_arg == "-o" || current_arg == "--output_file" )
     {
        this->output_filename  = argv[ iopt + 1 ];
        this->_output_filename = ( char* ) this->input_filename.c_str();
        this->output_is_set    = true;
     }
     else
     {  
        cout << endl;
        cout << "Command Error:  Unknow command option " << argv[iopt] << endl;
        cout << "Type -h or --help for detailed command options" << endl;
        cout << endl;
     }
   }

  }

// check whether all the parameters in this class have been set
  if( this->input_is_set == false )
  {
    cout << endl;
    cout << "Exit:  Input file name is not set. Please check. " << endl;
    cout << endl;
    exit(1);
  }
  else if( this->output_is_set == false ) 
  {
    cout << endl;
    cout << "Exit:  Output file name is not set. Please check. " << endl;
    cout << endl;
    exit(1);
  }
  else if( this->dir_work_is_set == false )
  {
    cout << endl;
    cout << "Exit:  Working directory is not set. Please check. " << endl;
    cout << endl;
    exit(1);
  }
  else if( this->dir_scratch_is_set == false )
  {
    cout << endl;
    cout << "Exit:  Scratch directory is not set. Please check. " << endl;
    cout << endl;
    exit(1);
  }


};  // end of cmd_options::cmd_options




} // end of namespace ithaca
