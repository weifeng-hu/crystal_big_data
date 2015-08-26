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
#include <manybody_expansion/order_mask.h>
#include <manybody_expansion/request.h>
#include <manybody_expansion/config.h>
#include <manybody_expansion/agent.h>
#include <manybody_expansion/manybody_expansion_template.h>

namespace iquads {

namespace manybody_expansion {

typedef Agent mbe_agent_type;

mbe_agent_type :: config_type 
 mbe_agent_type :: setup_config_from_request( request_type request )
{

} // end of function setup_config_from_request()

mbe_agent_type :: report_type
 mbe_agent_type :: execute_periodic( config_type config, report_ref report ) 
{

  using std::cout;
  using std::endl;
  using order_bitmask :: bitmask_type;

  cout << " Compute lattice energy using the periodic MBE formula" << endl;

  try {
   switch ( config.order() ) {
    case ( order_bitmask :: FIRST_ORDER ):
     ManyBodyExpansionPeriodic<1> manybody_expansion_periodic;
     manybody_expansion_periodic.compute_lattice_energy_per_unit_cell( config, report );
     break;
    default:
     throw( config.order() );
     break;
   }
  }
  catch ( bitmask_type order ) {
    cout << " execute_periodic():" << endl;
    cout << "  ManyBody Expansion terms of " << order << " order are not implemented! " << endl;
    exit(1);
  }

}; // end of function execute_periodic()

mbe_agent_type :: report_type 
 mbe_agent_type :: execute_general( config_type config, report_ref report )
{

  using std::cout;
  using std::endl;

  cout << " Compute lattice energy using the general MBE formula " << endl;
  cout << " general MBE formula algorithm not implemented "  << endl;
  exit(1);


}; // end of function execute_general()

} // end of namespace manybody_expansion

} // end of namespace iquads
