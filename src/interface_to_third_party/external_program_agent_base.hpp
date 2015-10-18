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

#ifndef EXTERNAL_PROGRAM_AGENT_BASE_HPP
#define EXTERNAL_PROGRAM_AGENT_BASE_HPP

#include <stdlib.h>
#include <vector>
#include <string>
#include <memory>
#include <file_system/directory.hpp>
#include <file_system/filepath.hpp>
#include <iquads/sequence.hpp>
#include <electron_correlation/quantity.hpp>
#include <interface_to_third_party/external_program_request.hpp>
#include <interface_to_third_party/external_program_config_base.hpp>
#include <interface_to_third_party/external_program_report.hpp>

using std::string;

namespace iquads {

using namespace electron_correlation ;
using namespace electron_correlation :: quantity;

namespace interface_to_third_party {

class ExternalProgramAgent_Base {
public:
  typedef ExternalProgramRequest       request_type;
  typedef ExternalProgramReport        report_type;
  typedef ExternalProgramConfig_Base   base_config_type;
  typedef base_config_type*            base_config_ptr;
  typedef vector<base_config_ptr>      base_config_ptr_list;
  typedef bool     condition_type;
  typedef string   command_line_type;
  typedef string   program_name_type;
  typedef string   program_path_type;
  typedef string   file_extension_type;
  typedef request_type :: mode_type               mode_type;
  typedef iquads :: file_system :: Directory directory_type;
  typedef iquads :: file_system :: Filepath filepath_type;
  typedef base_config_type :: work_path_type      work_path_type;
  typedef base_config_type :: file_name_type      file_name_type;
  typedef report_type :: energy_bare_report_type       energy_report_type;
  typedef report_type :: gradient_bare_report_type     gradient_report_type;
  typedef report_type :: local_run_info_type           local_run_info_type;
  typedef base_config_type :: solution_tag_type        solution_tag_type;
  typedef base_config_type :: correlation_tag_type     correlation_tag_type;

public:
  ExternalProgramAgent_Base() {
    this->program_path_ = "not set";
    this->program_name_ = "not set";
    this->file_extension_ = "not set";
  };

public:
  virtual local_run_info_type run_external_program( filepath_type input_path, 
                                                    directory_type scratch_dir, 
                                                    directory_type output_dir ) = 0;
  virtual energy_report_type collect_energy_data_from_output( file_name_type output_filename ) = 0;
  virtual base_config_ptr_list generate_config_list_from_request( request_type request ) = 0;

public:
  virtual filepath_type write_input_hf_energy( base_config_ptr base_config_pointer ) = 0;
  virtual filepath_type write_input_mp2_energy( base_config_ptr base_config_pointer ) = 0;
  virtual filepath_type write_input_casscf_energy( base_config_ptr base_config_pointer ) = 0;

public:
  filepath_type write_energy_input( base_config_ptr base_config_pointer ) {
    try {
      correlation_tag_type energy_solution_tag = base_config_pointer->correlation_tag();
      switch( energy_solution_tag ) {
        case ( single_reference :: mean_field :: RHF ):
          return this->write_input_hf_energy( base_config_pointer );  // call derived class function
        case ( single_reference :: mollet_plesset :: MP2 ):
          return this->write_input_mp2_energy( base_config_pointer ); // call derived class function
        case ( multi_reference :: scf :: CASSCF ):
          return this->write_input_casscf_energy( base_config_pointer ); // call derived class function
        default:
          throw energy_solution_tag;
      }
    } catch ( correlation_tag_type unknown_energy_solution ) {
      using std::cout;
      using std::endl;
      cout << "unknown energy calculation type: " << unknown_energy_solution << endl;
      abort();
    }
  } // end of function write_energy_input()

  tuple< energy_report_type, local_run_info_type > run_energy_calculation( base_config_ptr base_config_pointer ) {
   /**
    *  We write it in this way, to assure the chain of responsibility. If a directory/filename is invalid (checked by the 
    *  actual function in () ), then this parent function won't run either.
    */
    local_run_info_type local_run_info = this->run_external_program( this->write_energy_input( base_config_pointer ),
                                                                     this->make_directory( base_config_pointer->scratch_path() ), 
                                                                     this->make_directory( base_config_pointer->output_path() ) );
    energy_report_type energy_report 
      = collect_energy_data_from_output( local_run_info.output_filename() ); // call derived class
    using std::make_tuple;
    return make_tuple( energy_report, local_run_info );
  } // end of function run_energy_calculation()

  file_name_type write_run_script( base_config_ptr base_config_pointer )
    { return string("");  } // end of function write_run_script()

  file_name_type collect_result( file_name_type output_filename )
    {   } // end of function collect_result()

  tuple< gradient_report_type, local_run_info_type > run_gradient_calculation( base_config_ptr base_config_pointer )
    {   } // end of function run_gradient_calculation()

public:
  /**
   *  + sequence_local_run()
   *    Perform calculation on the local machine, according different targeted quantity types
   *
   *    The method will build a "list" of config instances, and each config is for one step of 
   *    a calculation. The actual way to build the config list depends on the request, and 
   *    performed by virtual method generate_config_from_request(), since different external programs 
   *    have different derived config.
   */
  report_type sequence_local_run( request_type request ) {
    try {
      report_type report;
      base_config_ptr_list base_config_pointer_list = generate_config_list_from_request( request );
      for( size_t istep = 0; istep < base_config_pointer_list.size(); istep++ ) {
         solution_tag_type solution_tag = base_config_pointer_list[istep]->solution_tag();
         switch( solution_tag ) {
           case( ENERGY ):
             report.accept_new_step_data( run_energy_calculation( base_config_pointer_list[istep] ) );
             break;
           case( GRADIENT ):
             report.accept_new_step_data( run_gradient_calculation( base_config_pointer_list[istep] ) );
             break;
           default:
             throw solution_tag;
             break;
        } // end of switch case
      } // end of for loop

      // prevent memory leak
      for( size_t istep = 0; istep < base_config_pointer_list.size(); istep++ ){
        delete base_config_pointer_list[istep];
      }

      return report;
    } catch ( solution_tag_type unknown_solution_type ) {
      using std::cout;
      using std::endl;
      cout << "unknown solution type" << unknown_solution_type << endl;
      abort();
    }
  } // end of function sequence_local_run()

  report_type sequence_write_local_input( request_type request ) 
    {   } // end of function sequence_write_local_input()

  report_type sequence_write_pbs_input( request_type request )
    {   } // end of function sequence_write_pbs_input()

  report_type sequence_write_sbatch_input( request_type request )
    {   } // end of function sequence_write_sbatch_input()

  report_type sequence_collect_local_output( request_type request )
    {   } // end of function sequence_collect_local_output()

public:
  report_type accept_request_and_process( request_type request ) {
    try {
      switch( request.mode() ){
        case( mode :: LOCAL_RUN ):
          return sequence_local_run( request );
        case( mode :: WRITE_LOCAL_INPUT ):
          return sequence_write_local_input( request );
        case( mode :: WRITE_PBS_INPUT ):
          return sequence_write_pbs_input( request );
        case( mode :: WRITE_SBATCH_INPUT ):
          return sequence_write_sbatch_input( request );
        case( mode :: COLLECT_LOCAL_OUTPUT ):
          return sequence_collect_local_output( request );
        default:
          throw request.mode();
      }
    } catch ( mode_type unknown_mode ) {
      using std::cout;
      using std::endl;
      cout << "unknown sequence type: " << unknown_mode << endl;
      abort();
    }
  } // end of function accept_request_and_process()

public:
  directory_type make_directory( string directory_name ) {
    directory_type directory( directory_name );
    directory.create();
    return directory;
  }

protected:
  program_path_type program_path_;
  program_name_type program_name_;
  file_extension_type file_extension_;

}; // end of class ExternalProgramAgent_Base

} // end of namespace interface_to_third_party

} // end of namespace iquads

#endif
