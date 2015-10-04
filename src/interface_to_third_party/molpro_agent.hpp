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
  void run_external_program( file_name_type input_filename, file_name_type output_filename ) {
    command_line_type command_line 
      = this->program_path_ + " " + input_filename;
    try {
      int res = system( command_line.c_str() );
      if( res != 0 ){ throw 1; }
    } catch ( int signal ) {
      using std::cout;
      using std::endl;
      cout << "molpro program returns an error" << endl;
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
