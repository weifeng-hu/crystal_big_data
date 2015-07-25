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

namespace iquads {

namespace manybody_expansion {

template < size_t Order > 
inline double compute_expansion_term()
{
  return 0.0e0;
};

template <>
inline double compute_expansion_term<1>()
{
  double retval = 0.0e0;
  for( size_t i = 0; i < n_in_cell_zero; i++ ){
//  a_monomer = ?;
   retval += compute_interaction_energy<1>( a_monomer );
  }
};

template <>
inline double compute_expansion_term<2>()
{

// a mess!
  double retval = 0.0e0;
  for( size_t R = 0; R < n_cell; i++ ){
   for( size_t i_0 = 0; i_0 < n_per_cell; i_0++ ){
//    a_dimer = ?;
    retval += compute_interaction_energy<2>( a_dimer );
   }
  }
  return 1.0e0/2.0e0 * retval;
};

template <>
inline double compute_expansion_term<3>()
{ 

// a mess!
  double retval = 0.0e0;
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
  return 1.0e0/6.0e0 * retval;
}

} // end of manybody_expansion

} // end of namespace iquads
