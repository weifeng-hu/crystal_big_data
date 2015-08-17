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

#ifndef EXTERNAL_PROGRAM_AGENT_BASE_H
#define EXTERNAL_PROGRAM_AGENT_BASE_H

#include <string>
#include <memory>
#include <iquads/run_mode_bitmask.h>
#include <iquads/report.h>
#include <electron_correlation/electron_correlation_config.h>
#include <electron_correlation/electron_correlation_report.h>
#include <interface_to_third_party/external_program_config_base.h>

using std::string;

namespace iquads {

namespace interface_to_third_party {

class ExternalProgramAgent_Base
{
public:
  typedef ExternalProgramConfig_Base base_config_type;
  typedef base_config_type* base_config_ptr;
  typedef Report report_type;
  typedef string program_name_type;
  typedef string program_path_type;
  typedef string work_path_type;
  typedef string file_name_type;
  typedef string command_line_type;
  typedef double energy_data_type;
  typedef bool condition_type;

public:
  virtual void run_calculation( file_name_type input_filename, 
                                file_name_type output_filename ) = 0;
  virtual file_name_type write_input( base_config_ptr base_config_pointer, 
                                      work_path_type work_path ) = 0;
  virtual file_name_type write_run_script( base_config_ptr base_config_pointer )
  virtual file_name_type collect_result( file_name_type output_filename ) = 0;

public:
  virtual void sequence_local_run() = 0;
  virtual void sequence_write_local_input() = 0;
  virtual void sequence_write_pbs_input() = 0;
  virtual void sequence_write_sbatch_input() = 0;
  virtual void sequence_collect_local_result() = 0;

public:
  report_type accept_request_and_process( request_type request )
   {
     using namespace iquads :: rum_mode;
     switch( request.run_mode() ){
      case( LOCAL_RUN ):
        return sequence_run( request );
      case( WRITE_LOCAL_INPUT ):
        return sequence_write_local_input();
      case( WRITE_PBS_INPUT ):
        return sequence_write_pbs_input();
      case( WRITE_SBATCH_INPUT ):
        return sequence_write_sbatch_input();
      case( COLLECT_LOCAL_OUTPUT ):
        return sequence_collect_local_output();
     }
   } // end of accept_request_and_process()

protected:
  program_path_type program_path_;
  program_name_type program_name_;

}; // end of class ExternalProgramAgent_Base

} // end of namespace interface_to_third_party

} // end of namespace iquads

#endif
