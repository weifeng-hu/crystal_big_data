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

#ifndef MANYBODY_EXPANSION_POLYMER_REPORT_TEMPLATE_HPP
#define MANYBODY_EXPANSION_POLYMER_REPORT_TEMPLATE_HPP

#include <string>
#include <array>
#include <structure/atom_list.hpp>
#include <structure/geometry_unit.hpp>
#include <electron_correlation/quantity.hpp>
#include <electron_correlation/correlation_level.hpp>
#include <electron_correlation/report.hpp>
#include <interface_to_third_party/external_program_report.hpp>

using std::string;
using std::array;

  /*
   *  each piece of info must have( for each possible polymer )
   *    name: MUST BE UNIQUE in the lattice!
   *    geometry: coordinates, unit
   *    composition of molecules in lattice
   *    solution: energy, links to the highest correlation level in electron correlation method info
   *                      will be used to add up the total energy
   *    electron correlation method info and solution( detailed, can have multiple levels of solutions )
   *    external program info: name, input files path, output files path, pbs scrpts path, whether run locally
   *                           I suggest that we copy the input file to a scratch dir when running, and then get
   *                           the output back to a safe place
   */

namespace iquads {

using structure :: AtomList;
using namespace structure :: geometry_unit;
using namespace electron_correlation :: quantity;
using namespace electron_correlation;

namespace manybody_expansion {

template < size_t NUM  > struct PolymerReport {
public:
  typedef AtomList atom_list_type;
  typedef array< int, NUM > composition_list_type;
  typedef geometry_unit :: unit_mask_type geometry_unit_type;
  typedef geometry_unit :: unit_literal_type geometry_unit_name_type;
  typedef double energy_data_type;
  typedef level_mask_type correlation_level_type;
  typedef electron_correlation :: Report electron_correlation_report_type;
  typedef interface_to_third_party :: ExternalProgramReport external_program_report_type;
  typedef size_t mbe_order_type;
  typedef bool condition_type;
  typedef electron_correlation_report_type& electron_correlation_report_ref;
  typedef external_program_report_type& external_program_report_ref;
  typedef string fragment_name_type;

public:
  fragment_name_type fragment_name() const
    { return this->fragment_name_; }
  atom_list_type atom_list() const
    { return this->atom_list_; }
  geometry_unit_name_type geometry_unit_name() const 
    { 
      using iquads :: structure :: geometry_unit :: return_unit_name;
      return return_unit_name( this->geometry_unit_ );
    }
  geometry_unit_type geometry_unit() const
    { return this->geometry_unit_; }
  composition_list_type composition_list() const
    { return this->composition_list_; }
  energy_data_type fragment_energy() const
    { return this->fragment_energy_; }
  energy_data_type interaction_energy() const
    { return this->interaction_energy_; }
  electron_correlation_report_type electron_correlation_report() const 
    { return this->electron_correlation_report_; }
  external_program_report_type external_program_report() const 
    { return this->external_program_report_; }

protected:
  fragment_name_type fragment_name_;
  atom_list_type     atom_list_;
  geometry_unit_type geometry_unit_;
  composition_list_type  composition_list_;
  energy_data_type   fragment_energy_;
  energy_data_type   interaction_energy_;
  electron_correlation_report_type electron_correlation_report_;
  external_program_report_type     external_program_report_;

}; // end of templated struct PolymerReport

} // end of manybody_expansion

} // end of namespace 

#endif
