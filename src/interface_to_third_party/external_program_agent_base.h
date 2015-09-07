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

#include <vector>
#include <string>
#include <memory>
#include <iquads/run_mode_bitmask.h>
#include <electron_correlation/quantity.h>
#include <interface_to_third_party/external_program_request.h>
#include <interface_to_third_party/external_program_config_base.h>
#include <interface_to_third_party/external_program_report.h>

using std::string;

namespace iquads {

using namespace electron_correlation :: quantity;
using namespace electron_correlation :: quantity :: energy;
using namespace electron_correlation :: quantity :: gradient;

namespace interface_to_third_party {

class ExternalProgramAgent_Base
{
public:
  typedef ExternalProgramRequest request_type;
  typedef ExternalProgramReport report_type;
  typedef ExternalProgramConfig_Base base_config_type;
  typedef base_config_type* base_config_ptr;
  typedef vector<base_config_ptr> base_config_ptr_list;
  typedef string program_name_type;
  typedef string program_path_type;
  typedef string work_path_type;
  typedef string file_name_type;
  typedef string command_line_type;
  typedef typename report_type :: energy_report_t energy_report_type;
  typedef bool condition_type;
  typedef typename quantity_mask_type solution_type;
  typedef typename energy_mask_type energy_solution_type;
  typedef typename gradient_mask_type gradient_solution_type;

public:
  virtual void run_external_program( file_name_type input_filename, file_name_type output_filename ) = 0;
  virtual energy_report_type collect_energy_data_from_output( file_name_type output_filename ) = 0;
  virtual base_config_ptr_list generate_config_list_from_request( request_type request ) = 0;

public:
  virtual file_name_type write_input_hf_energy( base_config_ptr base_config_pointer ) = 0;
  virtual file_name_type write_input_mp2_energy( base_config_ptr base_config_pointer ) = 0;
  virtual file_name_type write_input_casscf_energy( base_config_ptr base_config_pointer ) = 0;

public:
  file_name_type write_energy_input( base_config_ptr base_config_pointer )
   {
    try{
     energy_solution_type energy_solution_tag = base_config_pointer->return_energy_solution_tag();
     switch( energy_solution_tag ){
      case ( HF_ENERGY ):
       return this->write_input_hf_energy( base_config_pointer );  // call derived class
      case ( MP2_ENERGY ):
       return this->write_input_mp2_energy( base_config_pointer ); // call derived class
      case ( CASSCF_ENERGY ):
       return this->write_input_casscf_energy( base_config_pointer ); // call derived class
      default:
       throw energy_solution_tag;
     }
    }
    catch ( energy_solution_type unknown_energy_solution ){
     using std::cout;
     using std::endl;
     cout << "unknown energy calculation type: " << unknown_energy_solution << endl;
     abort();
    }
   } // end of function write_energy_input()

  energy_report_type run_energy_calculation( base_config_ptr base_config_pointer )
   {
     file_name_type input_filename = write_energy_input( base_config_pointer ); 
     file_name_type output_filename = base_config_pointer->molecule_name() + ".out";
     run_external_program( input_filename, output_filename ); // call derived class
     energy_report_type retval = collect_energy_data_from_output( output_filename ); // call derived class
     return retval;
   } // end of function run_energy_calculation()


  file_name_type write_run_script( base_config_ptr base_config_pointer )
   {
   } 

  file_name_type collect_result( file_name_type output_filename )
   {
   }

  gradient_report_type run_gradient_calculation( base_config_ptr base_config_pointer )
   {

   } // end of function run_gradient_calculation()

public:
  report_type sequence_local_run( request_type request )
   {
    try{
     report_type report;
     base_config_ptr_list base_config_pointer_list = generate_config_list_from_request( request );
     for( size_t istep = 0; istep < base_config_pointer_list.size(); istep++ ){
      solution_type solution_tag = base_config_pointer_list[istep]->return_solution_quantity_tag();
      switch( solution_tag ){
       case( energy :: return_nest_mask() ): 
        report.accept_new_step_data( run_energy_calculation( base_config_pointer_list[istep] ) );
        break;
       case( gradient :: return_nest_mask() ):
        report.accept_new_step_data( run_gradient_calculation( base_config_pointer_list[istep]) ); //p
        break;
       default:
        throw solution_tag;
        break;
      } // end of switch case
     } // end of for loop

     for( size_t istep = 0; istep < base_config_pointer_list.size(); istep++ ){
      delete base_config_pointer_list[istep];
     }

     return report;
    }
    catch ( solution_mask_type unknown_solution_tag ){
     using std::cout;
     using std::endl;
     cout << "unknown solution type" << unknown_solution_tag << endl;
     abort();
    }
   } // end of function sequence_local_run()

  report_type sequence_write_local_input( request_type request )
   {

   } // end of function sequence_write_local_input()

  report_type sequence_write_pbs_input()
   {

   } // end of function sequence_write_pbs_input()

  report_type sequence_write_sbatch_input()
   {

   } // end of function sequence_write_sbatch_input()

  report_type sequence_collect_local_output()
   {

   } // end of function sequence_collect_local_output()

public:
  report_type accept_request_and_process( request_type request )
   {
    try{
     using namespace iquads :: sequence_type;
     switch( request.sequence_type() ){
      case( LOCAL_RUN ):
        return sequence_local_run();
      case( WRITE_LOCAL_INPUT ):
        return sequence_write_local_input();
      case( WRITE_PBS_INPUT ):
        return sequence_write_pbs_input();
      case( WRITE_SBATCH_INPUT ):
        return sequence_write_sbatch_input();
      case( COLLECT_LOCAL_OUTPUT ):
        return sequence_collect_local_output();
      default:
        throw request.sequence_type();
     }
    } catch ( sequence_type_mask sequence_code ){
      using std::cout;
      using std::endl;
      cout << "unknown sequence type: " << sequence_code << endl;
      abort();
    }
   } // end of function accept_request_and_process()

protected:
  program_path_type program_path_;
  program_name_type program_name_;

}; // end of class ExternalProgramAgent_Base

} // end of namespace interface_to_third_party

} // end of namespace iquads

#endif
