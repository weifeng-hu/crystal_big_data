//#include <Python.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include "boost/algorithm/string.hpp"              // for split()
#include "boost/algorithm/string/predicate.hpp"    // for iequals()
#include "dmrg/dmrg_define.h"
#include "dmrg/dmrg_config_class.h"

using namespace std;

namespace iqs  {  namespace dmrg  {

config::config( cmd_option cmd_opt )
{

  set_default();

  // Judge whether the file is a python script
  bool use_python = false;
  {
   string tmp = cmd_opt.get_dmrg_conf();
   vector<string> splitv;
   boost::algorithm::split( splitv, tmp, boost::algorithm::is_any_of("."), boost::algorithm::token_compress_on );
   vector<string> :: iterator it_str = splitv.begin();
   if( std::equal( it_str->begin(), it_str->end(), "py" ) ) use_python = true;
  }

  if( use_python = true ){
    input_python( cmd_opt.get_dmrg_conf() );
  }
  else{
    input( cmd_opt.get_dmrg_conf() );
  }

  check_conf();

}

void config :: set_default()
{

  nsite() = UNDEFINED;
  np() = UNDEFINED;
  na() = UNDEFINED;
  nb() = UNDEFINED;
  ns() = UNDEFINED;

  integral_file() = UNDEFINED_STR ;

  nroot() = 1;
  weights().push_back(1.0e0);

  nschedule() = 4;
  schedule().resize( nschedule() );
  for( int i = 0; i < schedule().size(); i++ ){
   schedule()[i].sweep()     = i * 4;
   schedule()[i].m()         = pow( 4, i+3 );
   schedule()[i].david_tol() = 1.0e-5;
   schedule()[i].noise()     = 1.0e-4 / pow( 10, i );
  }

  max_sweep() = 24;
  twodot() = true;
  two_to_one() = 20;

}

void config :: input( string conf_file )
{

  ifstream file;
  file.open( conf_file.c_str(), ios::in );
  string entry;
  while( file >> entry ){

   if( boost::algorithm::iequals( entry, "orbitals" ) || boost::algorithm::iequals( entry, "orb") ){ file >> nsite(); }
   else if( boost::algorithm::iequals( entry, "nele")){ file >> np(); }
   else if( boost::algorithm::iequals( entry, "spin") ){ file >> ns(); }
   else if( boost::algorithm::iequals( entry, "twodot" ) ){ file >> twodot(); }
   else if( boost::algorithm::iequals( entry, "two_to_one" ) ){ file >> two_to_one(); }
   else if( boost::algorithm::iequals( entry, "max_sweep" ) ){ file >> max_sweep(); }
   else if( boost::algorithm::iequals( entry, "integral" ) ){ file >> integral_file(); }
   else if( boost::algorithm::iequals( entry, "root") ){ 
      file >> nroot();
      weights().resize( nroot() );
      for( int i = 0; i < nroot(); i++ ){ weights().push_back( 1.0e0/nroot() ); }
   }
   else if( boost::algorithm::iequals( entry, "schedule" ) ){
     sweep_schedule tmp_schedule;
     char line[256];
     int count = 0;
     while( file.getline( line, 256 ) ){
       entry = line;
       if( boost::algorithm::iequals( "end", entry ) ){
        vector<string> fields;
        boost::algorithm::split( fields, entry, boost::algorithm::is_any_of(","), boost::algorithm::token_compress_on );
        if( fields.size() != 4 ){ cout << " schedule line " << entry << " is incomplete " << endl; exit(1); }
        tmp_schedule.sweep()     = atoi( fields.at(0).c_str() );
        tmp_schedule.m()         = atoi( fields.at(1).c_str() );
        tmp_schedule.david_tol() = atof( fields.at(2).c_str() );
        tmp_schedule.noise()     = atof( fields.at(3).c_str() );

        schedule().at(count) = tmp_schedule;
        ++count;
       }
     }
     schedule().resize(count);
     nschedule() = schedule().size();
   }

  }

}

void config :: input_python( string conf_file )
{
  // Initialize Python Environment and ScriptFile
//    Py_Initialize();
//    iqs::py::interface PY( filename );

  //   ^ ^
  // (=   =)
  // (  u  )
  // 
  // read dmrg parameters
  // essential
//    nsite() = iqs::py::get_value<int>( "dmrg.nsite", PY);
//    np()    = iqs::py::get_value<int>( "dmrg.np", PY );
//    ns()    = iqs::py::get_value<int>( "dmrg.ns", PY );

//    Py_Finalize();

}

void config :: check_conf()
{

  if( get_nsite() == UNDEFINED ){ }
  if( get_np()    == UNDEFINED ){ }
  if( get_ns()    == UNDEFINED ){ }
  if( get_na()    == UNDEFINED ){ }
  if( get_nb()    == UNDEFINED ){ }

  if( boost::algorithm::iequals( get_integral_file(), UNDEFINED_STR ) ){ }

  cout << " config.nsite = " << get_nsite() << endl;
  cout << " config.np    = " << get_np()    << endl;
  cout << " config.ns    = " << get_ns()    << endl;
  cout << " config.na    = " << get_na()    << endl;
  cout << " config.nb    = " << get_nb()    << endl;
  cout << " config.integral_file = " << get_integral_file() << endl;
  cout << " config.max_sweep     = " << get_max_sweep()     << endl;
  cout << " config.two_dot       = " << get_twodot()        << endl;
  cout << " config.two_to_one    = " << get_two_to_one()    << endl;
  cout << " config.schedule: " << endl;

  cout << "\tsweep\tM\tDavidson tolerance\tnoise" << endl;
  for( int i; i < schedule().size(); ++i ){
   cout << "\t" << schedule().at(i).get_sweep() << "\t" << schedule().at(i).get_m() << "\t" << schedule().at(i).get_david_tol() << "\t" << schedule().at(i).get_noise() << endl;
  }


}

} }  // end of iqs::dmrg
