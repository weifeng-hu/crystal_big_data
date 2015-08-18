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

#include <electron_correlation/electron_correlation_client.h>

namespace iquads {

namespace manybody_expansion {

typedef double energy_data_type;
typedef iquads :: electron_correlation :: Client molecular_energy_client_type;
typedef iquads :: electron_correlation :: Setting energy_calc_setting_type;

template < size_t Order >
inline energy_data_type compute_interaction_energy( polymer<Order> x, energy_calc_setting_type guildlines )
{

  return 0.0e0;

}; // end of function compute_interaction_energy<Order>

template <>
inline energy_data_type compute_interaction_energy<1> ( polymer<1> x, energy_calc_setting_type guildlines )
{

  molecular_energy_client_type client;
  client.driver( Molecule(x), guilelines );
  return client.report().energy();

}; // end of function compute_interaction_energy<1>

template <>
inline energy_data_type compute_interaction_energy<2>( polymer<2> x )
{

  energy_data_type energy_dimer_01;
  {
   molecular_energy_client_type client;
   client.driver( Molecule(x), guidelines );
   energy_dimer_01 = client.report().energy();
  }

  energy_data_type energy_monomer_0 = compute_interaction_energy<1> ( x.at(0) );
  energy_data_type energy_monomer_1 = compute_interaction_energy<1> ( x.at(1) );

  return energy_dimer_01 - energy_monomer_0 - energy_monomer_1;

}; // end of function compute_interaction_energy<2>

template <>
inline energy_data_type compute_interaction_energy<3>( polymer<3> x )
{

  energy_data_type energy_trimer_012;
  {
   molecular_energy_client_type client;
   client.driver( Molecule(x), guidelines );
   energy_trimer_012 = client.report().energy();
  }

  energy_data_type energy_monomer_0 = compute_interaction_energy<1> ( x.at(0) );
  energy_data_type energy_monomer_1 = compute_interaction_energy<1> ( x.at(1) );
  energy_data_type energy_monomer_2 = compute_interaction_energy<1> ( x.at(2) );

  energy_data_type interaction_energy_dimer_01 = compute_interaction_energy<2>( x.at(0) + x.at(1) );
  energy_data_type interaction_energy_dimer_02 = compute_interaction_energy<2>( x.at(0) + x.at(2) );
  energy_data_type interaction_energy_dimer_12 = compute_interaction_energy<2>( x.at(1) + x.at(2) );

  return energy_trimer_012 - 
         energy_monomer_0 - energy_monomer_1 - energy_monomer_2 - 
         interaction_energy_dimer_01 - interaction_energy_dimer_02 - interaction_energy_dimer_12;

}; // end of function compute_interaction_energy<3>

} // end of namespace manybody_expansion

} // end of namespace iquads

#endif
