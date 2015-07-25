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

namespace iquads {

namespace manybody_expansion {

template < class Unit >
class manybody_expansion_general
{
public:
  typedef double energy_data_type;

private:
  energy_type total_energy;

}; // end of class manybody_expansion_general

template < class Unit, size_t Order >
class ManyBodyExpansionPeriodic
{
public:
  typedef double energy_data_type;
  typedef bool condition_type;

public:
  energy_data_type compute_lattice_energy_per_unit_cell()
   {
    return this->energy_formula_.compute( shared_ptr< Lattice > lattice_ptr,  agent_ptr );
   } // end of compute_lattice_energy_per_unit_cell()

private:
  Lattice lattice_;
  ExpansionFormula< Order > expansion_formula_;
  ExternalProgramFactory factory_;

}; // end of class ManyBodyExpansionPeriodic

} // end of namespace manybody_expansion

} // end of namespace iquads

#endif
