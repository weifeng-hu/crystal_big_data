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
#include <electron_correlation/quantity.hpp>
#include <interface_to_third_party/external_program_config_base.hpp>

using std::tuple;
using std::vector;
using std::shared_ptr;

namespace iquads {

namespace interface_to_third_party {

struct ExternalProgramReport {
public:
  typedef ExternalProgramReport parent_report_type;
  typedef
  typedef 
    typename ExternalProgramConfig_Base :: GeometryConfig_Base :: atom_list_type 
      atom_list_type;

public:
  struct EnergyReport {
    public:
      typedef EnergyReport this_type;
      typedef double energy_data_type;
      typedef typename quantity :: energy :: energy_mask_type energy_solution_tag_type;
      typedef typename quantity :: energy :: energy_literal_type energy_solution_name_type;
    public:
      atom_list_type& set_atom_list()
       { return this->atom_list_; }
      energy_data_type& set_energy()
       { return this->energy_; }
      energy_solution_tag_type& set_energy_solution_tag()
       { return this->energy_solution_tag_; }
      const energy_solution_name_type return_energy_solution_name() const 
       { return quantity :: energy :: return_energy_literal( this->energy_solution_tag_ ); }
    private:
      atom_list_type atom_list_;
      energy_data_type energy_;
      energy_solution_tag_type energy_solution_tag_;
  }; // end of struct ExternalProgramReport :: EnergyReport

  struct GradientReport {

  }; // end of struct ExternalProgramReport :: GradientReport

  typedef EnergyReport    energy_bare_report_type;
  typedef GradientReport  gradient_bare_report_type;

public:
  struct ReportInterface {
    public:

    public:

    private:
  };

public:
  struct RuntimeInfo_Base {
    public:
      typedef string program_name_type;
      typedef string file_name_type;
      typedef string path_name_type;
    public:

    protected:
      program_name_type program_name_;
      file_name_type input_filename_;
      file_name_type output_filename_;
      path_name_type input_path_;
      path_name_type scratch_path_;
      path_name_type output_path_;
  }; // end of struct RuntimeInfo_Base
  struct LocalRunInfo : public RuntimeInfo_Base {
    LocalRunInfo( program_name_type program_name,
                  file_name_type input_filename,
                  file_name_type output_filename,
                  path_name_type input_directory,
                  path_name_type scratch_directory,
                  path_name_type output_directory ):
      program_name_( program_name ), input_filename_( input_filename ), output_filename_( output_filename ),
      input_path_( input_directory ), scratch_path_ ( scratch_directory ), output_path_ ( output_directory ) { }
    private:
  }; // end of struct LocalRunInfo
  struct DryRunInfo : public RuntimeInfo_Base {
    private:
      file_name_type run_script_filename_;
  }; // end of struct InputRunInfo
  struct HarvestRunInfo : public RuntimeInfo_Base {
    private:
  }; // end of struct OutputRunInfo
  struct PBSRunInfo {
    private:
      file_name_type pbs_script_name_;
      file_name_type pbs_group_submission_script_name_;
  }; // end of PBSRunInfo
  struct SBATCHRunInfo {
    private:
      file_name_type sbatch_script_name_;
      file_name_type sbatch_group_submission_script_name_;
  }; // end of SBATCHRunInfo

  typedef LocalRunInfo local_run_info_type;
  typedef DryRunInfo dry_run_info_type;
  typedef HarvestRunInfo harvest_run_info_type;
  typedef PBSRunInfo pbsrun_info_type;
  typedef SBATCHRunInfo sbatchrun_info_type;

public:
  typedef tuple< energy_bare_report_type, local_run_info_type > energy_local_run_report_type;
  typedef tuple< energy_bare_report_type, harvest_run_info_type > energy_report_harvest_run_type;
  typedef vector< energy_report_type > energy_report_list_type;

  typedef tuple< gradient_bare_report_type, local_run_info_type > gradient_local_run_report_type;
  typedef vector< energy_report_type > energy_local_run_report_list_type;

public
  void accept_new_step_data( energy_local_run_report_type report )
    { this->energy_local_run_report_list_.push_back( report ); }
  void accept_new_step_data( gradient_local_run_report_type gradient_report )
    { this->gradient_local_run_report_list_.push_back( report); }

private:
  vector< shared_ptr< ReportInterface > > interface_to_step_reports_;
  energy_local_run_report_list_type energy_local_run_report_list_;
  vector< gradient_local_run_report_type > gradient_local_run_report_list_;

}; // end of struct ExternalProgramReport

} // end of namespace interface_to_third_party

} // end of namespace iquads

#endif
