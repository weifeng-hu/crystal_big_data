/**
 * @file
 * @author Weifeng Hu
 *
 * @section LICENSE
 *
 * Copyright (C) 2013, 2014, 2015  Weifeng Hu
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @section DESCRIPTION
 *
 *
 */


#ifndef MOLPRO_AGENT_HPP
#define MOLPRO_AGENT_HPP

#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <interface_to_third_party/molpro_config.hpp>
#include <interface_to_third_party/external_program_report.hpp>
#include <interface_to_third_party/external_program_agent_base.hpp>

namespace iquads {

namespace interface_to_third_party {

class MolproAgent : public ExternalProgramAgent_Base {
public:
  typedef MolproConfig this_config_type;
  typedef this_config_type* this_config_ptr;
  typedef ExternalProgramReport report_type;

public:
  MolproAgent() {
    try {
      using std::getenv;
      const char* program_path = getenv("MOLPRO_PATH");
      if( program_path == nullptr ) {
       throw 1;
      }
      this->program_path_ = program_path;
      this->program_name_ = "molpro";
      this->file_extension_ = ".com";
    } catch ( int signal ) {
      using std::cout;
      using std::endl;
      cout << "Environment Variable $MOLPRO_PATH not set" << endl;
      abort();
    }
  } // end of default constructor

public:
  base_config_ptr_list generate_config_list_from_request( request_type request );
  local_run_info_type run_external_program( filepath_type input_path, directory_type scratch_dir, directory_type output_dir ) {
    try {
      // check whether input_file exists;
      if( input_path.exists() == true ) {
        // copy input file to scratch
        if( input_path.directory() == scratch_dir ) {
          std :: cout << "warning: input file path and scratch path are the same! suggest to have a different scratch path " << std :: endl;
        }
        else {
          input_path.copy_to( scratch_dir );
        }

        // get the file name + path for scratch run
        filepath_type scratch_input_path = filepath_type( scratch_dir, input_path.filename() );
        filepath_type :: filename_type output_filename( input_path.filename().name() , std :: string( ".out" ) );
        filepath_type scratch_output_path = filepath_type( scratch_dir, output_filename );

        // RUN, for molpro, we don't need to tell the run-time output filename
        command_line_type command_line 
          = this->program_path_ + "/" + program_name_ + " " + scratch_input_path.absolute();
        int retval_run = system( command_line.c_str() );
        if( retval_run != 0 ) { throw 2; }

        // after a successful run we copy the output file from scratch to output path
        // we should check whether this output file is there
        if( scratch_output_path.exists() == false ) {
          throw 3;
        }
        if( scratch_dir == output_dir ) {
          // do nothing;
          std :: cout << " scratch path and output path are the same; suggest to have a different output path" << std :: endl;
        }
        else {
          if( input_path.directory() == output_dir ) {
            std :: cout << " input path and output path are the same; suggest to have a different output path" << std :: endl;
          }
          scratch_output_path.copy_to( output_dir );
        } 
        return local_run_info_type( this->program_name_, 
                                    input_path.directory().absolute(),
                                    input_path.filename().value(),
                                    scratch_dir.absolute(),
                                    output_dir.absolute(),
                                    output_filename.value() );

      }
      else {
        throw 0;
      }
    } catch ( int signal ) {
      switch ( signal ) {
        case( 0 ):
          std :: cout << " cannot find input file " << input_path.absolute() << std :: endl;
          break;
        case( 1 ):
          std :: cout << " cannot copy input file to the scratch file " << std :: endl;
          break;
        case( 2 ):
          std :: cout << " molpro program returns an error" << std :: endl;
          break;
        case( 3 ):
          std :: cout << " cannot find the output file in scratch" << std :: endl;
          break;
        case( 4 ):
          std :: cout << " cannot copy output file from scratch to output dir" << std :: endl;
          break;
        default:
          std :: cout << " unknown error in run external program" << std :: endl;
          break;
      }
      abort();
    }
  }

  filepath_type write_input_hf_energy( base_config_ptr base_config_pointer );
  filepath_type write_input_mp2_energy( base_config_ptr base_config_pointer );
  filepath_type write_input_casscf_energy( base_config_ptr base_config_pointer );
  energy_report_type collect_energy_data_from_output( file_name_type output_filename );

}; // end of class MolproAgent

} // end of namespace interface_to_third_party

} // end of namespace iquads

#endif
