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

#ifndef COMPUTE_EXPANSION_TERM_PERIODIC_FOR_SYM_NONEQ_TRAITS_HPP
#define COMPUTE_EXPANSION_TERM_PERIODIC_FOR_SYM_NONEQ_TRAITS_HPP

#include <manybody_expansion/config.hpp>
#include <manybody_expansion/report.hpp>
#include <manybody_expansion/compute_interaction_energy_traits.hpp>

namespace iquads {

namespace manybody_expansion {

typedef double energy_data_type;
typedef Config config_type;
typedef Report report_type;
typedef report_type& report_ref;

template < size_t Order > 
 inline energy_data_type compute_expansion_term_periodic_for_sym_noneq( config_type config, report_ref report )
{

  return 0.0e0;

}; // end of template function compute_expansion_term_periodic_for_sym_noneq<Order>()

template <>
 inline energy_data_type compute_expansion_term_periodic_for_sym_noneq<1>( config_type config, report_ref report )
{

  energy_data_type retval = 0.0e0;
  external_setting_type settings; settings.generate_from_config();

  unit_cell_type cell_zero = config.lattice().get_cell(0);
  for( size_t inode = 0; inode < cell_zero.n_node(); inode++ ){
    sym_noneq_monomer_list_type sym_noneq_list_for_center_inode = cell_zero.at(inode).identify_symmetry_equivalent_fragments_in_lattice<1>();
    if( sym_noneq_list_for_center_inode.has( cell_zero.at(inode)) ){
     double weight_factor = sym_noneq_list_for_center_inode.get_weight_factor( cell_zero.at(inode) );
     polymer_type<1> monomer_i( cell_zero.at(inode) );
     energy_data_type monomer_energy = compute_interaction_energy<1>( monomer_i, setting );
     report.add_monomer_data_to_sym_noneq_list( monomer_i, monomer_energy, weight_factor );
     retval += monomer_energy;
    }
  }

  return retval;

}; // end of template function compute_expansion_term_periodic_for_sym_noneq<1>()

template <>
 inline energy_data_type compute_expansion_term_periodic_for_sym_noneq<2>( config_type config, report_ref report )
{

  energy_data_type retval = 0.0e0;
  external_setting_type settings; settings.generate_from_config();

  unit_cell_type cell_zero = config.lattice().get_cell(0);
  for( size_t inode = 0; inode < cell_zero.n_node(); inode++ ){
    sym_noneq_dimer_list_type sym_noneq_list_for_center_inode = cell_zero.at(inode).identify_symmetry_equivalent_fragments_in_lattice<2>();

    for( size_t R = 0; R < config.lattice().n_cell(); i++ ){
      unit_cell_type cell_R = config.lattice().get_cell(R);
      for( size_t R_i = 0; R_i < cell_R.n_node(); R_i++ ){
        // This is a slow algorithm for the time beging
        // Loop over nodes will be improved to loop over dimer pairs
        if( sym_noneq_list_for_center_inode.has( cell_zero.at(inode), cell_R.at(R_i ) )
        {
          double weight_factor = sym_noneq_list_for_center_inode.get_weight_factor( cell_zero.at(inode), cell_R.at(R_i) );
          polymer_type<1> monomer_i( cell_zero.at(inode) );
          polymer_type<1> monomer_j( cell_R.at(R_i) );
          polymer_type<2> dimer_ij = monomer_i + monomer_j;
          energy_data_type dimer_interaction_energy = compute_interaction_energy<2>( dimer_ij, settings );
          report.add_dimer_data_to_sym_noneq_list( dimer_ij, dimer_interaction_energy, weight_factor );
          retval += dimer_energy * weight_factor;
        }
      }
    }
  }

  return 1.0e0/2.0e0 * retval;

}; // end of template function compute_expansion_term_periodic_for_sym_noneq<2>()

template <>
inline energy_data_type compute_expansion_term_periodic_for_sym_noneq<3>( config_type config, report_ref report )
{ 

  energy_data_type retval = 0.0e0;
  external_setting_type settings; settings.generate_from_config();

  unit_cell_type cell_zero = config.lattice().get_cell(0);
  for( size_t inode = 0; inode < cell_zero.n_node(); inode++ ){
    sym_noneq_trimer_list_type sym_noneq_list_for_center_inode = cell_zero.at(inode).identify_symmetry_equivalent_fragments_in_lattice<3>();
    for( size_t R_j = 0; R_j < config.lattice().n_cell(); R_j++ ){
      unit_cell_type cell_R_j = config.lattice().get_cell(R_j);
      for( size_t inode_R_j = 0; inode_R_j < cell_R_j.n_node(); inode_R_j++ ){
        for( size_t R_k = 0; R_k < config.lattice().n_cell(); R_k++ ){
          unit_cell_type cell_R_k = config.lattice().get_cell(R_k);
          for( size_t inode_R_k = 0; inode_R_k < cell_R_k.n_node(); inode_R_k++ ){
            if( sym_noneq_list_for_center_inode.has( cell_zero.at(inode), cell_R_j.at(inode_R_j), cell_R_k.at(inode_R_k) ) )
            {
              double weight_factor = sym_noneq_list_for_center_inode.get_weight_factor( cell_zero.at(inode), cell_R_j.at(inode_R_j), cell_R_k.at(inode_R_k) );
              polymer_type<1> monomer_i( cell_zero.at(inode) );
              polymer_type<1> monomer_j( cell_R_j.at(inode_R_j) );
              polymer_type<1> monomer_k( cell_R_k.at(inode_R_k) );
              polymer_type<3> trimer_ijk = monomer_i + monomer_j + monomer_k;
              energy_data_type trimer_interaction_energy = compute_interaction_energy<3> ( trimer_ijk, settings );
              report.add_trimer_data_to_sym_noneq_list( trimer_ijk, trimer_interaction_energy, weight_factor );
              retval += trimer_interaction_energy * weight_factor;
            }
          }
        }
      }
    }
  }

  return 1.0e0/6.0e0 * retval;

}; // end of template function compute_expansion_term_periodic_for_sym_noneq<3>()

template <>
 inline energy_data_type compute_expansion_term_periodic_for_sym_noneq<4> ( config_type config, report_ref report )
{

  energy_data_type retval;
  external_setting_type settings; settings.generate_from_config();

  unit_cell_type cell_zero = config.lattice().get_cell(0);
  for( size_t inode = 0; inode < cell_zero.n_node(); inode++ ){
    sym_noneq_tetramer_list_type sym_noneq_list_for_center_inode = cell_zero.at(inode).identify_symmetry_equivalent_fragments_in_lattice<4>();
    for( size_t R_j = 0; R_j < config.lattice().n_cell(); R_j++ ){
      unit_cell_type cell_R_j = config.lattice().get_cell(R_j);
      for( size_t inode_R_j = 0; inode_R_j < cell_R_j.n_node(); inode_R_j++ ){
        for( size_t R_k = 0; R_k < config.lattice().n_cell(); R_k++ ){
          unit_cell_type cell_R_k = config.lattice().get_cell(R_k);
          for( size_t inode_R_k = 0; inode_R_k < cell_R_k.n_node(); inode_R_k++ ){
            for( size_t R_l = 0; R_l < config.lattice().n_cell(); R_l++ ){
              unit_cell_type cell_R_l = config.lattice().get_cell(R_l);
               for( size_t inode_R_l = 0; inode_R_l < cell_R_l.n_node(); inode_R_l++ ){
                 if( sym_noneq_list_for_center_inode.has( cell_zero.at(inode), cell_R_j.at(inode_R_j), cell_R_k.at(inode_R_k) ), cell_R_l.at(inode_R_l) )
                 {
                   double weight_factor = sym_noneq_list_for_center_inode.get_weight_factor( cell_zero.at(inode), cell_R_j.at(inode_R_j), cell_R_k.at(inode_R_k), cell_R_l.at(inode_R_l );
                   polymer_type<1> monomer_i( cell_zero.at(inode) );
                   polymer_type<1> monomer_j( cell_R_j.at(inode_R_j) );
                   polymer_type<1> monomer_k( cell_R_k.at(inode_R_k) );
                   polymer_type<1> monomer_l( cell_R_l.at(inode_R_l));
                   polymer_type<4> tetramer_ijkl = monomer_i + monomer_j + monomer_k + monomer_l;
                   energy_data_type tetramer_interaction_energy = compute_interaction_energy<4> ( tetramer_ijkl, settings );
                   report.add_tetramer_data_to_sym_noneq_list( tetramer_ijkl, tetramer_interaction_energy, weight_factor );
                   retval += tetramer_interaction_energy * weight_factor;
                 }
              }
            }
          }
        }
      }
    }
  }

  return 1.0e0/24.0e0 * retval;

}; // end of template function compute_expansion_term_periodic_for_sym_noneq<4> ()

} // end of manybody_expansion

} // end of namespace iquads

#endif
