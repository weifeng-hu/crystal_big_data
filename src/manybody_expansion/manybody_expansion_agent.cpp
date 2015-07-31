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
#include <manybody_expansion/manybody_expansion_template.h>
#include <manybody_expansion/manybody_expansion_order_bitmask.h>

namespace iquads {

namespace manybody_expansion {

int ManyBodyExpansion_Agent :: execute_periodic()
{

  using std::cout;
  using std::endl;
  using order_bitmask :: bitmask_type;

  cout << " Compute lattice energy using the periodic MBE formula" << endl;

  try {
   switch ( this->order_ ) {
    case ( order_bitmask :: FIRST_ORDER ):
     ManyBodyExpansionPeriodic<1> manybody_expansion_periodic;
//     manybody_expansion_periodic.compute_lattice_energy_per_unit_cell( this->config_shared_pointer(), this->lattice_shared_pointer() );
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
     break;
   }
  }
  catch ( bitmask_type order ) {
    cout << " execute_periodic():" << endl;
    cout << "  ManyBody Expansion terms of " << this->order_ << " order are not implemented! " << endl;
    exit(1);
  }

  return 0;

}; // end of function execute_periodic()

int ManyBodyExpansion_Agent :: execute_general()
{

  using std::cout;
  using std::endl;

  cout << " Compute lattice energy using the general MBE formula " << endl;

  return 0;

}; // end of function execute_general()

int ManyBodyExpansion_Agent :: execute()
{

  using std::cout;
  using std::endl;

  if( config_shared_pointer() -> is_periodic() == true ){
    cout << " PERIODIC flag detected; " << endl;
    this->execute_periodic();
  }
  else{
    cout << " no PERIODIC flag detected; " << endl;
    this->execute_general();
  }

  return 0;

};

} // end of namespace manybody_expansion

} // end of namespace iquads
