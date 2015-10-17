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
  local_run_info_type run_external_program( work_path_type input_path, file_name_type input_filename, work_path_type scratch_path, work_path_type output_path ) {
    try {
      // check whether input_file exists;
      if( boost :: filesystem :: exists( boost :: filesystem :: path ( input_filename ) ) == true ) {
        // copy input file to scratch
        if( input_path != scratch_path ) {
          command_line_type command = "cp ";
                            command += input_filename;
                            command += " ";
                            command += scratch_path;
          int retval = system( command.c_str() );
          if( retval != 0 ) throw 1;
        }
        else {
          std :: cout << "warning: input file path and scratch path are the same! suggest to have a different scratch path " << std :: endl;
        }

        // let's get the actual filename of the input file, this filename does not include the path information
        file_name_type filename = input_filename;
        size_t len_input_path = input_path.length();
        filename.erase(0, len_input_path);
        // now we get the file name + path for scratch run
        file_name_type scratch_input_file = scratch_path;
                       scratch_input_file += filename;
        // almost there, now deduce the output filename, no path info
        file_name_type output_name = filename;
        size_t len_filename = filename.length();
        // we want to erase the ".com" for molpro input extension
        output_name.erase( len_filename - 4, 4 );
        output_name += ".out";

        // now we can run the calculation
        command_line_type command_line 
          = this->program_path_ + "/" + program_name_ + " " + scratch_input_file;
        int retval_run = system( command_line.c_str() );
        if( retval_run != 0 ) { throw 2; }

        // after a successful run we copy the output file from scratch to output path
        // first to figure out the original output path
        file_name_type scratch_output_file = scratch_path;
        scratch_output_file += output_name;
        // we probably should check whether this output file is there
        if( boost :: filesystem :: exists( boost :: filesystem :: path( scratch_output_file ) ) == false ) {
          throw 3;
        }
        if( scratch_path != output_path ) {
          command_line_type command_copy_out = "cp ";
                            command_copy_out += scratch_output_file;
                            command_copy_out += " ";
          // check whether output_path is ok
          if( input_path == output_path ) {
            std :: cout << " input path and output path are the same; suggest to have a different output path" << std :: endl;
          }
          command_copy_out += output_path;
          int retval_out = system( command_copy_out.c_str() );
          if( retval_out != 0 ) { throw 4; }
        } else {
          // do nothing;
          std :: cout << " scratch path and output path are the same; suggest to have a different output path" << std :: endl;
        }
        return local_run_info_type( this->program_name_, 
                                    input_path,
                                    input_filename,
                                    scratch_path,
                                    output_path,
                                    output_path + output_name );

      }
      else {
        throw 0;
      }
    } catch ( int signal ) {
      switch ( signal ) {
        case( 0 ):
          std :: cout << " cannot find input file " << input_filename << std :: endl;
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

  file_name_type write_input_hf_energy( base_config_ptr base_config_pointer );
  file_name_type write_input_mp2_energy( base_config_ptr base_config_pointer );
  file_name_type write_input_casscf_energy( base_config_ptr base_config_pointer );
  energy_report_type collect_energy_data_from_output( file_name_type output_filename );

}; // end of class MolproAgent

} // end of namespace interface_to_third_party

} // end of namespace iquads

#endif
