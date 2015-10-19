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
#include <structure/atom_list.hpp>
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
  local_run_info_type run_external_program( filepath_type input_path, directory_type scratch_dir, directory_type output_dir );
  filepath_type write_input_hf_energy( base_config_ptr base_config_pointer );
  filepath_type write_input_mp2_energy( base_config_ptr base_config_pointer );
  filepath_type write_input_casscf_energy( base_config_ptr base_config_pointer );
  energy_report_type collect_energy_data_from_output( correlation_tag_type correlation_tag, filepath_type output_path );
  iquads :: structure :: AtomList read_coordinate( filepath_type output_path );
  int    read_charge( filepath_type output_path );
  double read_energy( correlation_tag_type correlation_tag, filepath_type output_path );

}; // end of class MolproAgent

} // end of namespace interface_to_third_party

} // end of namespace iquads

#endif
