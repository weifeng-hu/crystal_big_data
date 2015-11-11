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
  typedef int      charge_value_type;
  typedef int      number_value_type;
  typedef float    spin_value_type;
  typedef double   energy_value_type;
  typedef std :: string   command_line_type;
  typedef std :: string   program_name_type;
  typedef std :: string   program_path_type;
  typedef std :: string   file_extension_type;
  typedef base_config_type :: dir_name_type       dir_name_type;
  typedef base_config_type :: file_name_type      file_name_type;
  typedef base_config_type :: path_name_type      path_name_type;
  typedef iquads :: file_system :: Directory      directory_type;
  typedef iquads :: file_system :: Filepath       filepath_type;
  typedef request_type :: mode_type               mode_type;
  typedef iquads :: structure :: AtomList atom_list_type;
  typedef report_type :: energy_bare_report_type       energy_report_type;
  typedef report_type :: gradient_bare_report_type     gradient_report_type;
  typedef report_type :: local_run_info_type           local_run_info_type;
  typedef report_type :: dry_run_info_type             dry_run_info_type;
  typedef report_type :: harvest_run_info_type         harvest_run_info_type;
  typedef report_type :: pbs_run_info_type             pbs_run_info_type;
  typedef report_type :: sbatch_run_info_type          sbatch_run_info_type;
  typedef base_config_type :: solution_tag_type        solution_tag_type;
  typedef base_config_type :: correlation_tag_type     correlation_tag_type;

public:
  ExternalProgramAgent_Base() {
    this->program_path_ = "not set";
    this->program_name_ = "not set";
    this->file_extension_ = "not set";
  };

public:
  virtual atom_list_type read_atom_list( filepath_type output_path ) = 0;
  virtual atom_list_type read_atom_list_from_input( filepath_type input_path ) = 0;
  virtual charge_value_type read_nuclear_charge( filepath_type output_path ) = 0;
  virtual std :: tuple< number_value_type, number_value_type > read_na_nb( filepath_type output_path ) = 0;
  virtual number_value_type read_nelec( filepath_type output_path ) = 0;
  virtual spin_value_type read_spin( filepath_type output_path ) = 0;
  virtual energy_value_type read_energy( correlation_tag_type correlation_tag, filepath_type output_path ) = 0;

public:
  virtual local_run_info_type run_external_program( filepath_type input_path,
                                                    directory_type scratch_dir,
                                                    directory_type output_dir ) = 0;
  virtual dry_run_info_type write_dry_run_script( filepath_type input_path ) = 0;
  virtual pbs_run_info_type write_pbs_run_script( filepath_type input_path ) = 0;
  virtual sbatch_run_info_type write_sbatch_run_script( filepath_type input_path ) = 0;

  virtual energy_report_type collect_energy_data_from_output( correlation_tag_type correlation_tag, filepath_type output_path ) = 0;
  virtual energy_report_type return_energy_null_info() = 0;

  virtual std :: tuple < filepath_type, bool > locate_energy_input( base_config_ptr base_config_pointer ) = 0;
  virtual std :: tuple < filepath_type, bool > locate_energy_output( base_config_ptr base_config_pointer ) = 0;
  virtual harvest_run_info_type return_previous_run_status( std :: tuple < filepath_type, bool > input_status, std :: tuple< filepath_type, bool > output_status ) = 0;

  virtual base_config_ptr_list generate_config_list_from_request( request_type request ) = 0;

public:
  virtual filepath_type write_input_hf_energy( base_config_ptr base_config_pointer ) = 0;
  virtual filepath_type write_input_mp2_energy( base_config_ptr base_config_pointer ) = 0;
  virtual filepath_type write_input_casscf_energy( base_config_ptr base_config_pointer ) = 0;
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

public:
  tuple< energy_report_type, local_run_info_type > run_energy_calculation( base_config_ptr base_config_pointer ) {
   /**
    *  We write it in this way, to assure the chain of responsibility. If a directory/filename is invalid (checked by the 
    *  actual function in () ), then this parent function won't run either.
    */
    local_run_info_type local_run_info = this->run_external_program( this->write_energy_input( base_config_pointer ),
                                                                     this->make_directory( base_config_pointer->scratch_dir() ), 
                                                                     this->make_directory( base_config_pointer->output_dir() ) );
    energy_report_type energy_report 
      = collect_energy_data_from_output( base_config_pointer->correlation_tag(), local_run_info.output_path() ); // call derived class
    return std :: make_tuple( energy_report, local_run_info );
  } // end of function run_energy_calculation()

  tuple< gradient_report_type, local_run_info_type > run_gradient_calculation( base_config_ptr base_config_pointer ) {
    // do not use this function yet!
  } // end of function run_gradient_calculation()

  tuple< energy_report_type, dry_run_info_type > write_local_energy_input( base_config_ptr base_config_pointer ) {
    dry_run_info_type dry_run_info = this->write_dry_run_script( this->write_energy_input( base_config_pointer ) );
    energy_report_type energy_report = this->return_energy_null_info();
    return std :: make_tuple( energy_report, dry_run_info );
  } // end of write_local_energy_input()

  tuple< gradient_report_type, dry_run_info_type > write_local_gradient_input( base_config_ptr base_config_pointer ) {

  } // end of write_local_gradient_input()

  tuple< energy_report_type, pbs_run_info_type > write_pbs_energy_input( base_config_ptr base_config_pointer ) {
    pbs_run_info_type pbs_run_info = this->write_pbs_run_script( this->write_energy_input( base_config_pointer ) );
    energy_report_type energy_report = this->return_energy_null_info();
    return std :: make_tuple( energy_report, pbs_run_info );
  } // end of write_pbs_energy_input()

  tuple< gradient_report_type, pbs_run_info_type > write_pbs_gradient_input( base_config_ptr base_config_pointer ) {
    // do not use this function yet!
  } // end of write_pbs_gradient_input()

  tuple< energy_report_type, sbatch_run_info_type > write_sbatch_energy_input( base_config_ptr base_config_pointer ) {
    sbatch_run_info_type sbatch_run_info = this->write_sbatch_run_script( this->write_energy_input( base_config_pointer ) ); 
    energy_report_type energy_report       = this->return_energy_null_info();
    return std :: make_tuple( energy_report, sbatch_run_info );
  } // end of write_pbs_energy_input()

  tuple< gradient_report_type, sbatch_run_info_type > write_sbatch_gradient_input( base_config_ptr base_config_pointer ) {
    // do not use this function yet!
  } // end of write_sbatch_energy_input()

  tuple< energy_report_type, harvest_run_info_type > collect_local_energy_output( base_config_ptr base_config_pointer ) {
    harvest_run_info_type harvest_run_info = this->return_previous_run_status( this->locate_energy_input( base_config_pointer ), 
                                                                                 this->locate_energy_output( base_config_pointer ) );
    energy_report_type energy_report;
    if( harvest_run_info.input_matches_output() == true ) {
      energy_report = this->collect_energy_data_from_output( base_config_pointer->correlation_tag(), harvest_run_info.output_path() );
    }
    else {
      std :: cout << "error: detected mismatching between input [ " << harvest_run_info.input_path_name();
      std :: cout <<                                " ] and output [ " << harvest_run_info.output_path_name();
      std :: cout <<                                " ] " << std :: endl;
      if( harvest_run_info.input_is_found() == false ) {
        std :: cout << "info: input [ " << harvest_run_info.input_path_name() << " ] not found " << std :: endl;
      }
      if( harvest_run_info.output_is_found() == false ) {
        std :: cout << "info: output [ " << harvest_run_info.output_path_name() << " ] not found " << std :: endl;
      }
      abort();
    }

    return std :: make_tuple( energy_report, harvest_run_info );
  } // end of write_pbs_energy_input()

  tuple< gradient_report_type, harvest_run_info_type > collect_local_gradient_output( base_config_ptr base_config_pointer ) {
    // do not use this function yet!
  } // end of write_sbatch_energy_input()


  file_name_type write_run_script( base_config_ptr base_config_pointer )
    { return string("");  } // end of function write_run_script()

  file_name_type collect_result( file_name_type output_filename )
    {   } // end of function collect_result()

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
      report.initialize();
      report.set_run_mode() = iquads :: sequence :: mode :: LOCAL_RUN;
      base_config_ptr_list base_config_pointer_list = generate_config_list_from_request( request );
      for( size_t istep = 0; istep < base_config_pointer_list.size(); istep++ ) {
         solution_tag_type solution_tag = base_config_pointer_list[istep]->solution_tag();
         switch( solution_tag ) {
           case( ENERGY ):
             report.set_solution_tag() = iquads :: electron_correlation :: quantity :: ENERGY;
             report.accept_new_step_data( run_energy_calculation( base_config_pointer_list[istep] ) );
             break;
           case( GRADIENT ):
             report.set_solution_tag() = iquads :: electron_correlation :: quantity :: GRADIENT;
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

  report_type sequence_write_local_input( request_type request ) {
    try {
      report_type report;
      report.initialize();
      report.set_run_mode() = iquads :: sequence :: mode :: WRITE_LOCAL_INPUT;
      base_config_ptr_list base_config_pointer_list = generate_config_list_from_request( request );
      for( size_t istep = 0; istep < base_config_pointer_list.size(); istep++ ) {
         solution_tag_type solution_tag = base_config_pointer_list[istep]->solution_tag();
         switch( solution_tag ) {
           case( ENERGY ):
             report.set_solution_tag() = iquads :: electron_correlation :: quantity :: ENERGY;
             report.accept_new_step_data( write_local_energy_input( base_config_pointer_list[istep] ) );
             break;
           case( GRADIENT ):
             report.set_solution_tag() = iquads :: electron_correlation :: quantity :: GRADIENT;
             report.accept_new_step_data( write_local_gradient_input( base_config_pointer_list[istep] ) );
             break;
           default:
             throw solution_tag;
             break;
         }
      }

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
 } // end of function sequence_write_local_input()

  report_type sequence_write_pbs_input( request_type request ) {
    try {
      report_type report;
      report.initialize();
      report.set_run_mode() = iquads :: sequence :: mode :: WRITE_PBS_INPUT;
      base_config_ptr_list base_config_pointer_list = generate_config_list_from_request( request );
      for( size_t istep = 0; istep < base_config_pointer_list.size(); istep++ ) {
         solution_tag_type solution_tag = base_config_pointer_list[istep]->solution_tag();
         switch( solution_tag ) {
           case( ENERGY ):
             report.set_solution_tag() = iquads :: electron_correlation :: quantity :: ENERGY;
             report.accept_new_step_data( write_pbs_energy_input( base_config_pointer_list[istep] ) );
             break;
           case( GRADIENT ):
             report.set_solution_tag() = iquads :: electron_correlation :: quantity :: GRADIENT;
             report.accept_new_step_data( write_pbs_gradient_input( base_config_pointer_list[istep] ) );
             break;
           default:
             throw solution_tag;
             break;
         }
      }

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
  } // end of function sequence_write_pbs_input()

  report_type sequence_write_sbatch_input( request_type request ) {
    try {
      report_type report;
      report.initialize();
      report.set_run_mode() = iquads :: sequence :: mode :: WRITE_SBATCH_INPUT;
      base_config_ptr_list base_config_pointer_list = generate_config_list_from_request( request );
      for( size_t istep = 0; istep < base_config_pointer_list.size(); istep++ ) {
         solution_tag_type solution_tag = base_config_pointer_list[istep]->solution_tag();
         switch( solution_tag ) {
           case( ENERGY ):
             report.set_solution_tag() = iquads :: electron_correlation :: quantity :: ENERGY;
             report.accept_new_step_data( write_sbatch_energy_input( base_config_pointer_list[istep] ) );
             break;
           case( GRADIENT ):
             report.set_solution_tag() = iquads :: electron_correlation :: quantity :: GRADIENT;
             report.accept_new_step_data( write_sbatch_gradient_input( base_config_pointer_list[istep] ) );
             break;
           default:
             throw solution_tag;
             break;
         }
      }

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
  } // end of function sequence_write_sbatch_input()

  report_type sequence_collect_local_output( request_type request ) {
    try {
      report_type report;
      report.initialize();
      report.set_run_mode() = iquads :: sequence :: mode :: COLLECT_LOCAL_OUTPUT;
      base_config_ptr_list base_config_pointer_list = generate_config_list_from_request( request );
      for( size_t istep = 0; istep < base_config_pointer_list.size(); istep++ ) {
         solution_tag_type solution_tag = base_config_pointer_list[istep]->solution_tag();
         switch( solution_tag ) {
           case( ENERGY ):
             report.set_solution_tag() = iquads :: electron_correlation :: quantity :: ENERGY;
             report.accept_new_step_data( collect_local_energy_output( base_config_pointer_list[istep] ) );
             break;
           case( GRADIENT ):
             report.set_solution_tag() = iquads :: electron_correlation :: quantity :: GRADIENT;
             report.accept_new_step_data( collect_local_gradient_output( base_config_pointer_list[istep] ) );
             break;
           default:
             throw solution_tag;
             break;
         }
      }

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

  } // end of function sequence_collect_local_output()

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
  directory_type make_directory( dir_name_type directory_name ) {
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
