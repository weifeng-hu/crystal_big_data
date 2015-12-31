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
 * the Free Software Foundation, either version 2 of the License, or
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

#ifndef EXTERNAL_PROGRAM_REPORT_HPP
#define EXTERNAL_PROGRAM_REPORT_HPP

#include <memory>
#include <tuple>
#include <vector>
#include <iquads/sequence.hpp>
#include <electron_correlation/quantity.hpp>
#include <structure/molecule.hpp>
#include <file_system/filepath.hpp>
#include <electron_correlation/quantity.hpp>
#include <electron_correlation/correlation_level.hpp>
#include <interface_to_third_party/external_program_config_base.hpp>

namespace iquads {

namespace interface_to_third_party {

  /**
   *  A report struct for third party results
   *
   *  There is no fixed way to design this report meta-data.
   *  In order to interface with other modules, e.g., the dynamics,
   *  MBE, etc., also considering command quantity types and runtime
   *  behaviors of external program, there are sub-report types are 
   *  included in this report type.
   *   + Energy data, contains the geometry and energies.
   *     the goal is, users can easily dump out the geometry and rerun a calcultion.
   *   + Gradient data, similar to energy data
   *   + Runtime info data
   *
   *  An additional design is each actual quantity report is accompanied with a runtime
   *  report. Each quantity is considered as a single run. This report can have an 
   *  arbitrary number of report pairs.
   *
   */

using std :: tuple;
using std :: vector;
using std :: shared_ptr;
using namespace electron_correlation;

struct ExternalProgramReport {
public:
  typedef ExternalProgramReport parent_report_type;
  typedef ExternalProgramConfig_Base :: GeometryConfig_Base :: atomic_coord_list_type  atom_list_type;
  typedef iquads :: structure :: Molecule molecule_obj_type;
  typedef std :: string molecule_name_type;
  typedef std :: tuple < molecule_name_type, molecule_obj_type >  molecule_info_type;
  typedef iquads :: electron_correlation :: quantity :: quantity_mask_type solution_tag_type;
  typedef iquads :: sequence :: mode :: mode_mask_type run_mode_type;

public:
  ExternalProgramReport() {
    this->energy_local_run_report_list_.resize(0);
    this->gradient_local_run_report_list_.resize(0);
  }

public:
  struct EnergyReport {
    public:
      typedef EnergyReport this_type;
      typedef double energy_data_type;
      typedef level_mask_type energy_solution_tag_type;
      typedef correlation_name_type energy_solution_name_type;
    public:
      EnergyReport() {
        molecule_obj_type molecule;
        this->molecule_info_ = std :: make_tuple( std :: string(""), molecule );
        this->energy_ = 0.0e0;
        this->energy_solution_tag_ = 0;
      }
      EnergyReport( molecule_info_type molecule_info_obj,
                    energy_data_type energy_data_value,
                    energy_solution_tag_type energy_solution_tag_value ) :
         molecule_info_( molecule_info_obj ),
         energy_( energy_data_value ), 
         energy_solution_tag_ ( energy_solution_tag_value ) { }
    public:
      molecule_info_type molecule_info() const
        { return this->molecule_info_; }
      molecule_obj_type molecule_obj() const 
        { return std :: get<1> ( this->molecule_info_ ); }
      molecule_name_type molecule_name() const
        { return std :: get<0> ( this->molecule_info_ ); }
      energy_data_type energy() const
        { return this->energy_; }
      energy_solution_tag_type energy_solution_tag() const
        { return this->energy_solution_tag_; }
      energy_solution_name_type return_energy_solution_name() const 
        { return iquads :: electron_correlation :: return_level_name_aka_list( this->energy_solution_tag_ ).at(0); }
    private:
      molecule_info_type molecule_info_;
      energy_data_type energy_;
      energy_solution_tag_type energy_solution_tag_;
  }; // end of struct ExternalProgramReport :: EnergyReport

  struct GradientReport { }; // end of struct ExternalProgramReport :: GradientReport

  typedef EnergyReport    energy_bare_report_type;
  typedef GradientReport  gradient_bare_report_type;

public:
  struct RuntimeInfo_Base {
    public:
      typedef string program_name_type;
      typedef string file_name_type;
      typedef string dir_name_type;
      typedef string path_name_type;
      typedef iquads :: file_system :: Filepath file_path_type;
      typedef RuntimeInfo_Base base;
    public:
      RuntimeInfo_Base() {
        this->program_name_ = "";
        this->input_dir_ = "";
        this->input_filename_ = "";
        this->scratch_dir_ = "";
        this->output_dir_ = "";
        this->output_filename_ = "";
      }
      RuntimeInfo_Base( program_name_type program_name,
                        dir_name_type     input_directory,
                        file_name_type    input_filename,
                        dir_name_type     scratch_directory,
                        dir_name_type     output_directory,
                        file_name_type    output_filename ) :
         program_name_ ( program_name ), input_dir_ (input_directory), input_filename_ ( input_filename ),
         scratch_dir_ ( scratch_directory ), output_dir_ ( output_directory ), output_filename_ ( output_filename ) {}
    public:
      file_name_type  input_filename()   const { return this->input_filename_; }
      file_name_type  output_filename()  const { return this->output_filename_; }
      dir_name_type   input_dir()        const { return this->input_dir_; }
      dir_name_type   scratch_dir()      const { return this->scratch_dir_; }
      dir_name_type   output_dir()       const { return this->output_dir_; }
      path_name_type  input_path_name()  const { return std :: string( this->input_dir_ + std :: string( "/" ) + this->input_filename_ ); }
      path_name_type  output_path_name() const { return std :: string( this->output_dir_ + std :: string( "/" ) + this->output_filename_ ); }
      file_path_type  input_path()       const { return file_path_type( this->input_dir_, this->input_filename_ ); }
      file_path_type  output_path()      const { return file_path_type( this->output_dir_, this->output_filename_ ); }
    protected:
      program_name_type program_name_;
      path_name_type    input_dir_;
      file_name_type    input_filename_;
      path_name_type    scratch_dir_;
      path_name_type    output_dir_;
      file_name_type    output_filename_;
  }; // end of struct RuntimeInfo_Base

  struct LocalRunInfo : public RuntimeInfo_Base {
    LocalRunInfo() : RuntimeInfo_Base() {}
    LocalRunInfo( program_name_type program_name,
                        dir_name_type input_directory,
                        file_name_type input_filename,
                        dir_name_type scratch_directory,
                        dir_name_type output_directory, 
                        dir_name_type output_filename ) :
      RuntimeInfo_Base ( program_name, input_directory, input_filename,
                         scratch_directory, output_directory, output_filename ) 
      { }
    private:
  }; // end of struct LocalRunInfo

  struct DryRunInfo : public RuntimeInfo_Base {
    DryRunInfo() : RuntimeInfo_Base() {
      this->dry_run_script_name_ = "";
      this->dry_run_group_submission_script_name_ = "";
    }
    DryRunInfo( program_name_type program_name,
                dir_name_type input_directory,
                file_name_type input_filename,
                dir_name_type scratch_directory,
                dir_name_type output_directory, 
                dir_name_type output_filename,
                file_name_type dry_run_script_name,
                file_name_type dry_run_group_submission_script_name ) :
      RuntimeInfo_Base ( program_name, input_directory, input_filename,
                         scratch_directory, output_directory, output_filename ),
      dry_run_script_name_( dry_run_script_name ),
      dry_run_group_submission_script_name_( dry_run_group_submission_script_name )
      { }
    public:
      file_name_type dry_run_script_name()                  const { return this->dry_run_script_name_; }
      file_name_type dry_run_group_submission_script_name() const { return this->dry_run_group_submission_script_name_; }
      file_path_type dry_run_script_path()                  const { return file_path_type( this->input_dir_, this->dry_run_script_name_ ); }
      file_path_type dry_run_group_submission_script_path() const { return file_path_type( this->input_dir_, this->dry_run_group_submission_script_name_ ); }
    private:
      file_name_type dry_run_script_name_;
      file_name_type dry_run_group_submission_script_name_;
  }; // end of struct InputRunInfo

  struct HarvestRunInfo : public RuntimeInfo_Base {
    HarvestRunInfo() : RuntimeInfo_Base() {
      this->input_matches_output_ = false;
      this->input_is_found_ = false;
      this->output_is_found_ = false;
    }
    HarvestRunInfo( program_name_type program_name,
                dir_name_type input_directory,
                file_name_type input_filename,
                dir_name_type scratch_directory,
                dir_name_type output_directory, 
                dir_name_type output_filename,
                bool input_matches_output,
                bool input_is_found,
                bool output_is_found ) :
      RuntimeInfo_Base ( program_name, input_directory, input_filename,
                         scratch_directory, output_directory, output_filename ),
      input_matches_output_ ( input_matches_output ),
      input_is_found_ ( input_is_found ),
      output_is_found_ ( output_is_found )
      { }
    public:
      bool input_matches_output() const { return this->input_matches_output_; }
      bool input_is_found()       const { return this->input_is_found_; }
      bool output_is_found()      const { return this->output_is_found_; }
    private:
      bool input_matches_output_;
      bool input_is_found_;
      bool output_is_found_;
  }; // end of struct OutputRunInfo

  struct PBSRunInfo : public RuntimeInfo_Base {
    PBSRunInfo() : RuntimeInfo_Base() {
      this->pbs_run_script_name_ = "";
      this->pbs_run_group_submission_script_name_ = "";
    }
    PBSRunInfo( program_name_type program_name,
                dir_name_type input_directory,
                file_name_type input_filename,
                dir_name_type scratch_directory,
                dir_name_type output_directory, 
                dir_name_type output_filename,
                file_name_type pbs_run_script_name,
                file_name_type pbs_run_group_submission_script_name ) :
      RuntimeInfo_Base ( program_name, input_directory, input_filename,
                         scratch_directory, output_directory, output_filename ),
      pbs_run_script_name_( pbs_run_script_name ),
      pbs_run_group_submission_script_name_( pbs_run_group_submission_script_name )
      { }
    public:
      file_name_type pbs_run_script_name()                      const { return this->pbs_run_script_name_; }
      file_name_type pbs_run_group_submission_script_name()     const { return this->pbs_run_group_submission_script_name_; }
      file_path_type pbs_run_script_path()                  const { return file_path_type( this->input_dir_, this->pbs_run_script_name_ ); }
      file_path_type pbs_run_group_submission_script_path() const { return file_path_type( this->input_dir_, this->pbs_run_group_submission_script_name_ ); }
    private:
      file_name_type pbs_run_script_name_;
      file_name_type pbs_run_group_submission_script_name_;
  }; // end of PBSRunInfo

  struct SBATCHRunInfo : public RuntimeInfo_Base {
    SBATCHRunInfo() : RuntimeInfo_Base() {
      this->sbatch_run_script_name_ = "";
      this->sbatch_run_group_submission_script_name_ = "";
    }
    SBATCHRunInfo( program_name_type program_name,
                dir_name_type input_directory,
                file_name_type input_filename,
                dir_name_type scratch_directory,
                dir_name_type output_directory, 
                dir_name_type output_filename,
                file_name_type sbatch_run_script_name,
                file_name_type sbatch_run_group_submission_script_name,
                int num_node,
                int num_procs_per_node,
                int memory,
                std :: string runtime ) :
      RuntimeInfo_Base ( program_name, input_directory, input_filename,
                         scratch_directory, output_directory, output_filename ),
      sbatch_run_script_name_( sbatch_run_script_name ),
      sbatch_run_group_submission_script_name_( sbatch_run_group_submission_script_name ),
      num_node_( num_node ),
      num_procs_per_node_( num_procs_per_node ),
      memory_( memory ),
      runtime_( runtime ) 
      { }
    public:
      file_name_type sbatch_run_script_name()                      const { return this->sbatch_run_script_name_; }
      file_name_type sbatch_run_group_submission_script_name()     const { return this->sbatch_run_group_submission_script_name_; }
      file_path_type sbatch_run_script_path()                  const { return file_path_type( this->input_dir_, this->sbatch_run_script_name_ ); }
      file_path_type sbatch_run_group_submission_script_path() const { return file_path_type( this->input_dir_, this->sbatch_run_group_submission_script_name_ ); }
      int num_node() const { return this->num_node_; }
      int num_procs_per_node() const { return this->num_procs_per_node_; }
      int memory() const { return this->memory_; }
      std :: string runtime() const { return this->runtime_; }
    private:
      file_name_type sbatch_run_script_name_;
      file_name_type sbatch_run_group_submission_script_name_;
      int num_node_;
      int num_procs_per_node_;
      int memory_;
      std :: string runtime_;
  }; // end of SBATCHRunInfo

  typedef LocalRunInfo local_run_info_type;
  typedef DryRunInfo dry_run_info_type;
  typedef HarvestRunInfo harvest_run_info_type;
  typedef PBSRunInfo pbs_run_info_type;
  typedef SBATCHRunInfo sbatch_run_info_type;

public:
  typedef tuple< energy_bare_report_type, local_run_info_type >   energy_local_run_report_type;
  typedef tuple< energy_bare_report_type, harvest_run_info_type > energy_harvest_run_report_type;
  typedef tuple< energy_bare_report_type, dry_run_info_type >     energy_dry_run_report_type;
  typedef tuple< energy_bare_report_type, pbs_run_info_type >     energy_pbs_run_report_type;
  typedef tuple< energy_bare_report_type, sbatch_run_info_type >  energy_sbatch_run_report_type;
  
  typedef vector< energy_local_run_report_type >    energy_local_run_report_list_type;
  typedef vector< energy_harvest_run_report_type >  energy_harvest_run_report_list_type;
  typedef vector< energy_dry_run_report_type >      energy_dry_run_report_list_type;
  typedef vector< energy_pbs_run_report_type >      energy_pbs_run_report_list_type;
  typedef vector< energy_sbatch_run_report_type >   energy_sbatch_run_report_list_type;

  typedef tuple< gradient_bare_report_type, local_run_info_type >    gradient_local_run_report_type;
  typedef tuple< gradient_bare_report_type, harvest_run_info_type >  gradient_harvest_run_report_type;
  typedef tuple< gradient_bare_report_type, dry_run_info_type >      gradient_dry_run_report_type;
  typedef tuple< gradient_bare_report_type, pbs_run_info_type >      gradient_pbs_run_report_type;
  typedef tuple< gradient_bare_report_type, sbatch_run_info_type >   gradient_sbatch_run_report_type;
 
  typedef vector< gradient_local_run_report_type >    gradient_local_run_report_list_type;
  typedef vector< gradient_harvest_run_report_type >  gradient_harvest_run_report_list_type;
  typedef vector< gradient_dry_run_report_type >      gradient_dry_run_report_list_type;
  typedef vector< gradient_pbs_run_report_type >      gradient_pbs_run_report_list_type;
  typedef vector< gradient_sbatch_run_report_type >   gradient_sbatch_run_report_list_type;

public:
  void initialize() {
    this->energy_local_run_report_list_.resize(0);
    this->energy_dry_run_report_list_.resize(0);
    this->energy_pbs_run_report_list_.resize(0);
    this->energy_sbatch_run_report_list_.resize(0);
    this->energy_harvest_run_report_list_.resize(0);

    this->gradient_local_run_report_list_.resize(0);
    this->gradient_dry_run_report_list_.resize(0);
    this->gradient_pbs_run_report_list_.resize(0);
    this->gradient_sbatch_run_report_list_.resize(0);
    this->gradient_harvest_run_report_list_.resize(0);
  }

  void accept_new_step_data( energy_local_run_report_type report )
    { this->energy_local_run_report_list_.push_back( report ); }
  void accept_new_step_data( energy_dry_run_report_type report )
    { this->energy_dry_run_report_list_.push_back( report ); }
  void accept_new_step_data( energy_pbs_run_report_type report )
    { this->energy_pbs_run_report_list_.push_back( report ); }
  void accept_new_step_data( energy_sbatch_run_report_type report )
    { this->energy_sbatch_run_report_list_.push_back( report ); }
  void accept_new_step_data( energy_harvest_run_report_type report )
    { this->energy_harvest_run_report_list_.push_back( report ); }


  void accept_new_step_data( gradient_local_run_report_type report )
    { this->gradient_local_run_report_list_.push_back( report ); }
  void accept_new_step_data( gradient_dry_run_report_type report )
    { this->gradient_dry_run_report_list_.push_back( report ); }
  void accept_new_step_data( gradient_pbs_run_report_type report )
    { this->gradient_pbs_run_report_list_.push_back( report ); }
  void accept_new_step_data( gradient_sbatch_run_report_type report )
    { this->gradient_sbatch_run_report_list_.push_back( report ); }
  void accept_new_step_data( gradient_harvest_run_report_type report )
    { this->gradient_harvest_run_report_list_.push_back( report ); }

  energy_local_run_report_list_type energy_local_run_report_list() const
    { return this->energy_local_run_report_list_; }
  energy_dry_run_report_list_type energy_dry_run_report_list() const
    { return this->energy_dry_run_report_list_; }
  energy_pbs_run_report_list_type energy_pbs_run_report_list() const
    { return this->energy_pbs_run_report_list_; }
  energy_sbatch_run_report_list_type energy_sbatch_run_report_list() const
    { return this->energy_sbatch_run_report_list_; }
  energy_harvest_run_report_list_type energy_harvest_run_report_list() const
    { return this->energy_harvest_run_report_list_; }

  gradient_local_run_report_list_type gradient_local_run_report_list() const
    { return this->gradient_local_run_report_list_; }
  gradient_dry_run_report_list_type gradient_dry_run_report_list() const
    { return this->gradient_dry_run_report_list_; }
  gradient_pbs_run_report_list_type gradient_pbs_run_report_list() const
    { return this->gradient_pbs_run_report_list_; }
  gradient_sbatch_run_report_list_type gradient_sbatch_run_report_list() const
    { return this->gradient_sbatch_run_report_list_; }
  gradient_harvest_run_report_list_type gradient_harvest_run_report_list() const
    { return this->gradient_harvest_run_report_list_; }

  run_mode_type run_mode() const 
    { return this->run_mode_; }
  solution_tag_type solution_tag() const
    { return this->solution_tag_; }

  run_mode_type& set_run_mode()
    { return this->run_mode_; }
  solution_tag_type& set_solution_tag()
    { return this->solution_tag_; }

private:
  energy_local_run_report_list_type    energy_local_run_report_list_;
  energy_dry_run_report_list_type      energy_dry_run_report_list_;
  energy_pbs_run_report_list_type      energy_pbs_run_report_list_;
  energy_sbatch_run_report_list_type   energy_sbatch_run_report_list_;
  energy_harvest_run_report_list_type  energy_harvest_run_report_list_;

  gradient_local_run_report_list_type    gradient_local_run_report_list_;
  gradient_dry_run_report_list_type      gradient_dry_run_report_list_;
  gradient_pbs_run_report_list_type      gradient_pbs_run_report_list_;
  gradient_sbatch_run_report_list_type   gradient_sbatch_run_report_list_;
  gradient_harvest_run_report_list_type  gradient_harvest_run_report_list_;

  run_mode_type run_mode_;
  solution_tag_type solution_tag_;

}; // end of struct ExternalProgramReport

} // end of namespace interface_to_third_party

} // end of namespace iquads

#endif
