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
#include <manybody_expansion/expansion_formula_periodic_traits.h>
#include <manybody_expansion/config.h>
#include <manybody_expansion/report.h>

namespace iquads {

namespace manybody_expansion {

template < size_t Order >
class ManyBodyExpansionGeneral 
{
public:
  typedef iquads :: manybody_expansion :: Config config_type;
  typedef iquads :: manybody_expansion :: Report report_type;
  typedef double energy_data_type;
  typedef energy_data_type& energy_data_reference;
  typedef bool condition_type;

  typedef report_type& report_ref;

}; // end of template class manybody_expansion_general

template < size_t Order >
class ManyBodyExpansionPeriodic
{
public:
  typedef iquads :: manybody_expansion :: ExpansionFormulaPeriodic< Order > expansion_formula_type;
  typedef iquads :: manybody_expansion :: Config config_type;
  typedef iquads :: manybody_expansion :: Report report_type;
  typedef double energy_data_type;
  typedef bool condition_type;

  typedef report_type& report_ref;

public:
  energy_data_type 
   compute_lattice_energy_per_unit_cell( config_type config, report_ref report )
   {
     this->expansion_formula_.compute( config, report );
   } // end of compute_lattice_energy_per_unit_cell()

private:
  expansion_formula_type expansion_formula_;

};// end of template class ManyBodyExpansionPeriodic

} // end of namespace manybody_expansion

} // end of namespace iquads

#endif
