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

#include <unistd.h>
#include <bitset>
#include <iostream>
#include <boost/date_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <interface_to_third_party/program_mask.hpp>
#include <manybody_expansion/order_mask.hpp>
#include <manybody_expansion/request.hpp>
#include <manybody_expansion/config.hpp>
#include <manybody_expansion/agent.hpp>
#include <manybody_expansion/manybody_expansion_template.hpp>

namespace iquads {

namespace manybody_expansion {

typedef Agent mbe_agent_type;

  /**
   *  This function manipulates the data member in the config object
   */
mbe_agent_type :: config_type 
mbe_agent_type :: setup_config_from_request( request_type request ) {

  using std :: get;
  config_type config;
  /**
   *  Step 1
   *  + lattice info/bulk info
   *  + check whether periodic system has been requested
   */
  if( get<1> ( request.lattice_info() ).is_filled() == true ) {
    config.set_is_periodic() = true;
    config.set_lattice_info() = request.lattice_info();
  }
  else if( get<1> ( request.bulk_info() ).is_filled() == true ) {
    config.set_is_periodic() = false;
    config.set_bulk_info() = request.bulk_info();
  }

  /**
   *  Step 2
   *  + set expansion order 
   */
  using order :: return_order_mask;
  config.set_expansion_order() = return_order_mask( request.expansion_order() );

  /**
   *  Step 2
   *  + solver info
   *    Detailed solver/external solver interfaces will be instantiated by the agents in the 
   *    namespace of iquads :: interface_to_third_party. 
   *    For now, the MBE config needs to know the ''code name'' of the solver only.
   */
  using interface_to_third_party :: program :: return_program_mask;
  config.set_program() = return_program_mask( request.external_program_name() );

  /**
   *  Step 3
   *  + set electron correlation essential settings
   *    + basis set
   *    + method: HF? MP2?
   */
  config.set_basis_set_name() = request.basis_set_name();
  using electron_correlation :: return_level_mask;
  config.set_correlation_method() = return_level_mask( request.correlation_name() );

  /**
   *  Step 4
   *  + set runtime info
   *   + job name?
   *   + prefix? scratch?
   *   + run mode
   */
  if( request.job_name() == "not set" ) {
    // then we use date, time to set the job name
    string date_and_time;
    using boost :: gregorian :: date;
    using boost :: gregorian :: day_clock;
    using boost :: gregorian :: to_simple_string;
    date today = day_clock :: local_day();
    date_and_time = to_simple_string( today );

    using boost :: posix_time :: ptime;
    using boost :: posix_time :: second_clock;
    ptime now = second_clock :: universal_time();
    date_and_time = date_and_time + to_simple_string( now );
    config.set_job_name() = date_and_time;
  }
  else {
    config.set_job_name() = request.job_name();
  }

  if( request.scratch_name() == "not set" ) {
    char pwd_char[256];
    getcwd( pwd_char, 256 );
    string pwd_string = pwd_char;
    config.set_scratch_name() = pwd_string + "/scratch/";
  }
  else {
    config.set_scratch_name() = request.scratch_name();
  }

  using iquads :: sequence :: mode :: return_mode_mask;
  config.set_run_mode() = return_mode_mask( request.run_mode_name() );

} // end of function setup_config_from_request()


void mbe_agent_type :: execute_periodic( config_type config, report_ref report ) {

  using std :: cout;
  using std :: endl;
  cout << " Compute lattice energy using the periodic MBE formula" << endl;

  try {
    switch ( config.expansion_order() ) {
      /**
       *  The runtime choice of different orders of many body expansion
       *  relies on explicit instantiation of different orders of actual
       *  many body expansion formulism.
       */
      case ( order :: FIRST_ORDER ):
        {
          ManyBodyExpansionPeriodic<1> manybody_expansion_periodic;
          manybody_expansion_periodic.compute_lattice_energy_per_unit_cell( config, report );
        }
        break;
      case ( order :: SECOND_ORDER ):
        {
          ManyBodyExpansionPeriodic<2> manybody_expansion_periodic;
          manybody_expansion_periodic.compute_lattice_energy_per_unit_cell( config, report );
        }
        break;
      case ( order :: THIRD_ORDER ):
        {
          ManyBodyExpansionPeriodic<3> manybody_expansion_periodic;
          manybody_expansion_periodic.compute_lattice_energy_per_unit_cell( config, report );
        }
        break;
      case ( order :: FOURTH_ORDER ):
        {
          ManyBodyExpansionPeriodic<4> manybody_expansion_periodic;
          manybody_expansion_periodic.compute_lattice_energy_per_unit_cell( config, report );
        }
        break;
      default:
        throw( config.expansion_order() );
        break;
    }
  }
  catch ( config_type :: expansion_order_type order ) {
    using std :: bitset;
    cout << " execute_periodic():" << endl;
    cout << "  ManyBody Expansion terms of " << bitset<16> (order) << " order are not implemented! " << endl;
    exit(1);
  }

}; // end of function execute_periodic()


void mbe_agent_type :: execute_general( config_type config, report_ref report ) {

  using std::cout;
  using std::endl;
  cout << " Compute lattice energy using the general MBE formula" << endl;

  try {
    switch ( config.expansion_order() ) {
      /**
       *  The runtime choice of different orders of many body expansion
       *  relies on implicit instantiation of the MBE system object which 
       *  depends on explicit instantiation of different orders of actual
       *  many body expansion formulism.
       */
      case ( order :: FIRST_ORDER ):
        {
          ManyBodyExpansionGeneral<1> manybody_expansion_general;
          manybody_expansion_general.compute_bulk_energy( config, report );
        }
        break;
      case ( order :: SECOND_ORDER ):
        {
          ManyBodyExpansionGeneral<2> manybody_expansion_general;
          manybody_expansion_general.compute_bulk_energy( config, report );
        }
        break;
      case ( order :: THIRD_ORDER ):
        {
          ManyBodyExpansionGeneral<3> manybody_expansion_general;
          manybody_expansion_general.compute_bulk_energy( config, report );
        }
        break;
      case ( order :: FOURTH_ORDER ):
        {
          ManyBodyExpansionGeneral<4> manybody_expansion_general;
          manybody_expansion_general.compute_bulk_energy( config, report );
        }
        break;
      default:
        throw( config.expansion_order() );
        break;
    }
  }
  catch ( config_type :: expansion_order_type order ) {
    using std :: bitset;
    cout << " execute_periodic():" << endl;
    cout << "  ManyBody Expansion terms of " << bitset<16> (order) << " order are not implemented! " << endl;
    exit(1);
  }

}; // end of function execute_general()

} // end of namespace manybody_expansion

} // end of namespace iquads
