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

#ifndef COMPUTE_INTERACTION_ENERGY_TRAITS_H
#define COMPUTE_INTERACTION_ENERGY_TRAITS_H

namespace iquads {

namespace manybody_expansion {

template < size_t Order >
inline energy_data_type compute_interaction_energy( polymer<Order> x, energy_calc_req_type request )
{

};

template <>
inline energy_data_type compute_interaction_energy( polymer<1> x, energy_calc_req_type request )
{

  ExternalProgramClient<energy_calc_req_type > client_request_energy_calc;
  client_request_energy_calc.set_request() = request;
  report_type report = client_request_energy_calc.driver();
  return report.return_total_energy();

}

template <>
inline energy_data_type compute_interaction_energy( polymer<3> x, energy_calc_req_type request )
{

  energy_data_type energy_monomer_0 = compute_interaction_energy<1> ( x.at(0) );
  energy_data_type energy_monomer_1 = compute_interaction_energy<1> ( x.at(1) );
  energy_data_type energy_monomer_2 = compute_interaction_energy<1> ( x.at(2) );

  energy_data_type interaction_energy_dimer_01 = compute_interaction_energy<2>( x.at(0) + x.at(1) );
  energy_data_type interaction_energy_dimer_02 = compute_interaction_energy<2>( x.at(0) + x.at(2) );
  energy_data_type interaction_energy_dimer_12 = compute_interaction_energy<2>( x.at(1) + x.at(2) );

  ExternalProgramAgentFactory factory;
  ExternalProgramAgent_Base* agent_ptr = factory.get_agent();
  energy_data_type energy_trimer_012 = agent_ptr->sequence_full( x );

  return energy_trimer_012 - 
         energy_monomer_0 - energy_monomer_1 - energy_monomer_2 - 
         interaction_energy_dimer_01 - interaction_energy_dimer_02 - interaction_energy_dimer_12;

};

} // end of namespace manybody_expansion

} // end of namespace iquads

#endif
