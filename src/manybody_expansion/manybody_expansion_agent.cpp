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

#include <iostream>
#include <manybody_expansion/manybody_expansion_agent.h>
//#include <manybody_expansion/manybody_expansion_template.h>
#include <manybody_expansion/manybody_expansion_order_bitmask.h>

namespace iquads {

namespace manybody_expansion {

void ManyBodyExpansionAgent :: execute()
{

  using std::cout;
  using std::endl;
  using order_bitmask :: bitmask_type;

  try {
   switch ( this->order_ ){
    case ( order_bitmask :: FIRST_ORDER ):
//     ManyBodyExpansionPeriodic<1> manybody_expansion_periodic;
//     manybody_expansion_periodic.compute_lattice_energy_per_unit_cell();
     break;
    case ( order_bitmask :: SECOND_ORDER ):
//     ManyBodyExpansionPeriodic<2> manybody_expansion_periodic;
//     manybody_expansion_periodic.compute_lattice_energy_per_unit_cell();
     break;
    case ( order_bitmask :: THIRD_ORDER ):
//     ManyBodyExpansionPeriodic<3> manybody_expansion_periodic;
//     manybody_expansion_periodic.compute_lattice_energy_per_unit_cell();
     break;
    case ( order_bitmask :: FOURTH_ORDER ):
//     ManyBodyExpansionPeriodic<4> manybody_expansion_periodic;
//     manybody_expansion_periodic.compute_lattice_energy_per_unit_cell();
     break;
    default:
     throw( this->order_ );
     cout << " ManyBody Expansion terms higher than 4th order are not implemented! " << endl;
     abort();
     break;
   }
  }
  catch ( bitmask_type order ) {
    cout << " ManyBody Expansion terms of " << this->order_ << " order are not implemented! " << endl;
    abort();
  }

};

} // end of namespace manybody_expansion

} // end of namespace iquads
