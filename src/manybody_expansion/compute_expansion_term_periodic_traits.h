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
 * the Free Software Foundation, either version 3 of the License, or
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

#ifndef COMPUTE_EXPANSION_TERM_PERIODIC_TRAITS_H
#define COMPUTE_EXPANSION_TERM_PERIODIC_TRAITS_H

#include <manybody_expansion/config.h>
#include <manybody_expansion/report.h>
#include <manybody_expansion/compute_interaction_energy_traits.h>

namespace iquads {

namespace manybody_expansion {

typedef double energy_data_type;
typedef Config config_type;
typedef Report report_type;
typedef report_type& report_ref;

template < size_t Order > 
inline energy_data_type compute_expansion_term_periodic( config_type config, report_ref report )
{

  return 0.0e0;

}; // end of template function compute_expansion_term_periodic<Order>()

template <>
inline energy_data_type compute_expansion_term_periodic<1>( config_type config, report_ref report )
{

  double retval = 0.0e0;
/*
  for( size_t i = 0; i < n_in_cell_zero; i++ ){
//  a_monomer = ?;
   retval += compute_interaction_energy<1>( a_monomer );
  }
*/

}; // end of template function compute_expansion_term_periodic<1>()

template <>
inline energy_data_type compute_expansion_term_periodic<2>( config_type config, report_ref report )
{

// a mess!
  double retval = 0.0e0;
/*
  for( size_t R = 0; R < n_cell; i++ ){
   for( size_t i_0 = 0; i_0 < n_per_cell; i_0++ ){
//    a_dimer = ?;
    retval += compute_interaction_energy<2>( a_dimer );
   }
  }
*/

  return 1.0e0/2.0e0 * retval;

}; // end of template function compute_expansion_term_periodic<2>()

template <>
inline energy_data_type compute_expansion_term_periodic<3>( config_type config, report_ref report )
{ 

// a mess!
  double retval = 0.0e0;
/*
  for( size_t i_0 = 0; i_0 < n_per_cell; i_0++ ){
   for( size_t R_j = 0; R_j < n_cell; R_j++ ){
    for( size_t R_k = 0; R_k < n_cell; R_k++ ){
     for( size_t j_R = 0; j_R < n_per_cell; j_R++ ){
      for( size_t k_R = 0; j_R < n_per_cell; j_R++ ){
//    a_trimer = ?;
        retval += compute_interaction_energy<3>( a_trimer );
      }
     }
    }
   }
  }
*/

  return 1.0e0/6.0e0 * retval;

}; // end of template function compute_expansion_term_periodic<3>()

} // end of manybody_expansion

} // end of namespace iquads

#endif
