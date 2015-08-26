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


#ifndef MOLPRO_AGENT_H
#define MOLPRO_AGENT_H

#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <interface_to_third_party/molpro_config.h>
#include <interface_to_third_party/external_program_report.h>
#include <interface_to_third_party/external_program_agent_base.h>

namespace iquads {

namespace interface_to_third_party {

class MolproAgent 
  : public ExternalProgramAgent_Base
{
public:
  typedef MolproConfig config_type;
  typedef ExternalProgramReport report_type;

public:
  MolproAgent()
   {
     {
      using std::getenv;
      const char* program_path = getenv("MOLPRO_PATH");
      if( program_path == nullptr ){
        using std::cout;
        using std::endl;
        cout << "Environment Variable $MOLPRO_PATH not set" << endl;
        exit(1);
      }
      else{
       this->program_path_ = program_path;
      }
     }
     this->program_name_ = "molpro";
   }

public:
  void run_calculation( file_name_type input_filename, file_name_type output_filename )
   {
     command_line_type command_line 
       = this->program_path_ + " " + input_filename;
     int res = system( command_line.c_str() );
   }
  file_name_type write_input( base_config_ptr base_config_pointer, 
                              work_path_type work_path  ){};
  file_name_type write_run_script( base_config_ptr base_config_pointer ) {};
  file_name_type collect_result( file_name_type output_filename ){};

public:
  report_type sequence_local_run();
  report_type sequence_write_local_input(){}
  report_type sequence_write_pbs_input(){}
  report_type sequence_write_sbatch_input(){}
  report_type sequence_collect_local_output(){}

private:
  config_type config_;

}; // end of class MolproAgent

} // end of namespace interface_to_third_party

} // end of namespace iquads

#endif
