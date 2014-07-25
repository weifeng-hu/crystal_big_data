#include <iostream>
#include <fstream>
#include "boost/algorithm/string/predicate.hpp"
#include "dmrg/dmrg_define.h"
#include "dmrg/cmd_option.h"

using namespace std;

namespace iqs { namespace dmrg {

void cmd_option :: help()
{
      sout << endl;
      sout << " Density Matrix Renormalization(DMRG) Module" << endl;
      sout << endl;
      sout << endl;
      sout << " usage: dmrg <dmrg_conf>" << endl;
      sout << "    -i        Input file name" << endl;
      sout << "    -o        Output file name" << endl;
      sout << endl;
}

void cmd_option :: set_default()
{

   dmrg_conf() = UNDEFINED_STR;
   output()    = UNDEFINED_STR;
   run_mode()  = CPP;

}

void cmd_option :: check_cmd()
{

   if( boost::algorithm::iequals( dmrg_conf(), UNDEFINED_STR ) ){
     sout << " command error: dmrg_conf is not defined " << endl;
     exit(1);
   }
   ifstream file;
   file.open( get_dmrg_conf().c_str(), std::ios::in );
   if( file.good() == false ){ 
     sout << " error: cannot open the input file " << endl;
     exit(1);
   }

   if( boost::algorithm::iequals( output(), UNDEFINED_STR ) ){
     output() = "dmrg.out";
   }

   sout << "  input file        = " << dmrg_conf()      << endl;
   sout << "  output file       = " << output()         << endl;
   sout << "  running mode      = " << int(run_mode())  << endl;
}

cmd_option::cmd_option( int argc, char* argv[] )
{

   set_default();

/*
  Get information from command line
    including:
    a. -i      input file
    b. -o      output file
*/
   if( argc < 2 ){ 
     sout << " error: dmrg needs at least one argument " << endl;
     exit(1);
   }

   if( argc == 2 ){
     string current_arg = argv[1];
     dmrg_conf() = current_arg;
   }

   for( int iopt = 0; iopt < argc; iopt++ )
   {
    std::string current_arg = argv[iopt];
    if( current_arg == "-i" )
    {
      this->dmrg_conf() = argv[iopt+1];
    }
    else if( current_arg == "-o" )
    {
      this->output() = argv[iopt+1];
    }
    else if( current_arg == "--help" || current_arg == "-h" )
    {
      help();
    }
    else
    {
      sout << " unknown argument " << current_arg << endl;
      exit(1);
    }
  }

  check_cmd();

} // end of cmd_opt::cmd_opt

} } // namespace iqs::dmrg
