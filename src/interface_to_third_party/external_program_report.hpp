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
    typename ExternalProgramConfig_Base :: GeometryConfig_Base :: atomic_cartesian_coord_type
      atomic_cartesian_coord_type;
  typedef 
    typename ExternalProgramConfig_Base :: GeometryConfig_Base :: cartesian_coord_list_type 
      cartesian_coord_list_type;

public:
  struct EnergyReport {
    public:
      typedef EnergyReport this_type;
      typedef double energy_data_type;
      typedef typename quantity :: energy :: energy_mask_type energy_solution_tag_type;
      typedef typename quantity :: energy :: energy_literal_type energy_solution_name_type;
    public:
      cartesian_coord_list_type& set_atom_list()
       { return this->atom_list_; }
      energy_data_type& set_energy()
       { return this->energy_; }
      energy_solution_tag_type& set_energy_solution_tag()
       { return this->energy_solution_tag_; }
      const energy_solution_name_type return_energy_solution_name() const 
       { return quantity :: energy :: return_energy_literal( this->energy_solution_tag_ ); }
    private:
      cartesian_coord_list_type atom_list_;
      energy_data_type energy_;
      energy_solution_tag_type energy_solution_tag_;
  }; // end of struct ExternalProgramReport :: EnergyReport

  struct GradientReport  {

  }; // end of struct ExternalProgramReport :: GradientReport

  struct ReportInterface {
    public:

    public:

    private:
  };

public:
  typedef ExternalProgramReport :: EnergyReport energy_report_type;
  typedef ExternalProgramReport :: GradientReport gradient_report_type;

public:
  void accept_new_step_data( energy_report_type energy_report )
   { /* to be defined */ }
  void accept_new_step_data( gradient_report_type gradient_report )
   { /* to be defined */ }

private:
  vector< shared_ptr< ReportInterface > > interface_to_step_reports_;
  vector< EnergyReport > energy_report_backups_;
  vector< GradientReport > gradient_report_backups_;

}; // end of struct ExternalProgramReport

} // end of namespace interface_to_third_party

} // end of namespace iquads

#endif
