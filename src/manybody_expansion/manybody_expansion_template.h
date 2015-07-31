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

#ifndef MANYBODY_EXPANSION_TEMPLATE_H
#define MANYBODY_EXPANSION_TEMPLATE_H

#include <memory>
#include <manybody_expansion/lattice.h>
#include <manybody_expansion/expansion_formula_periodic_traits.h>
#include <manybody_expansion/external_program_agent_base.h>
#include <manybody_expansion/external_program_agent_factory.h>

namespace iquads {

namespace manybody_expansion {

template < size_t Order >
class ManyBodyExpansionGeneral 
{
public:
  typedef double energy_data_type;
  typedef energy_data_type& energy_data_reference;
  typedef bool condition_type;

private:

}; // end of class manybody_expansion_general

template < size_t Order >
class ManyBodyExpansionPeriodic
{
public:
  typedef Lattice lattice_type;
  typedef shared_ptr< Lattice > lattice_shared_pointer_type;
  typedef ExpansionFormulaPeriodic< Order > expansion_formula_type;
  typedef ExternalProgramAgent_Factory external_program_factory_type;
  typedef ExternalProgramAgent_Base agent_base_type;
  typedef ManyBodyExpansionConfig config_type;
  typedef shared_ptr<config_type> config_shared_pointer_type;
  typedef agent_base_type* agent_pointer_type;
  typedef double energy_data_type;
  typedef energy_data_type& energy_data_reference;
  typedef bool condition_type;

public:
  energy_data_type 
   compute_lattice_energy_per_unit_cell( config_shared_pointer_type config_shared_pointer, 
                                         lattice_shared_pointer_type lattice_shared_pointer )
    // Here the config and lattice shared_ptr as function parameters rather than class members
    // since they are not necessary elements to make the class ManyBodyExpansionPeriodic valid
    // The objects they point to are in nature volatile at run-time
   {
     agent_pointer_type agent_pointer 
      = this->external_program_factory_.get_agent( config_shared_pointer->external_program_mask() );
     agent_pointer->set_essential_data();
     this->expansion_formula_.compute( lattice_shared_pointer,  agent_pointer );
   } // end of compute_lattice_energy_per_unit_cell()

public:
  const expansion_formula_type expansion_formula() const 
   { return this->expansion_formula_; }
  const external_program_factory_type external_program_factory() const 
   { return this->external_program_factory_; }

private:
  expansion_formula_type expansion_formula_;
  external_program_factory_type external_program_factory_;

};// end of class ManyBodyExpansionPeriodic

} // end of namespace manybody_expansion

} // end of namespace iquads

#endif
