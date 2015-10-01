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

#ifndef COMPUTE_EXPANSION_TERM_PERIODIC_TRAITS_HPP
#define COMPUTE_EXPANSION_TERM_PERIODIC_TRAITS_HPP

#include <electron_correlation/setting.hpp>
#include <manybody_expansion/config.hpp>
#include <manybody_expansion/report.hpp>
#include <manybody_expansion/compute_interaction_energy_traits.hpp>

namespace iquads {

namespace manybody_expansion {

  /**
   *  Templated methods to calculate individual orders of total interaction energies
   *  for periodic systems, coded using explicit instantiation.
   *
   *  These methods here do not use symmetry equilivant fragment identification, so
   *  the actual report object to use the the one for non-periodic case
   */
  typedef double energy_data_type;
  typedef Config config_type;
  typedef Report report_type;
  typedef report_type& report_ref;
  typedef electron_correlation :: Setting  external_setting_type;
  typedef config_type :: lattice_type :: unit_cell_type unit_cell_type;

  /**
   *  Default instantiation
   *  returns zero for energy, since no method can be defined.
   */
  template < size_t Order > inline energy_data_type compute_expansion_term_periodic( config_type config, report_ref report )
    { return 0.0e0; }

  /**
   *  Explicit instantiation for order 1, to calculate total monomer energy
   */
  template <> inline energy_data_type compute_expansion_term_periodic<1>( config_type config, report_ref report ) {
 
    energy_data_type retval = 0.0e0;
    external_setting_type settings; settings.generate_from_config( config );
 
    unit_cell_type cell_zero = config.lattice().at(0, 0, 0);
    for( size_t inode = 0; inode < cell_zero.size(); inode++ ) {
      MoleculeList monomer_molecule_list = { cell_zero.at(inode) };
      Polymer<1>  monomer_i( monomer_molecule_list );
      PolymerOmniReportGeneral<1>  monomer_report;
      energy_data_type monomer_energy = compute_interaction_energy<1>( monomer_i, setting, monomer_report );
      report.attach_new_monomer_report( monomer_report );
      retval += monomer_energy;
    }
 
    return retval;
 
  }; // end of template function compute_expansion_term_periodic<1>()
 
  /**
   *  Explicit instantiation for order 2, to calculate total dimer interaction energy
   */
  template <> inline energy_data_type compute_expansion_term_periodic<2>( config_type config, report_ref report ) {
 
    energy_data_type retval = 0.0e0;
    external_setting_type settings; settings.generate_from_config();
 
    unit_cell_type cell_zero = config.lattice().at(0, 0, 0);
    for( size_t inode = 0; inode < cell_zero.size(); inode++ ) {
      polymer_type<1> monomer_i( cell_zero.at(inode) );
      for( size_t R = 0; R < config.lattice().size(); i++ ){
        unit_cell_type cell_R = config.lattice().get_cell(R);
        for( size_t R_i = 0; R_i < cell_R.n_node(); R_i++ ){
          polymer_type<1> monomer_j( cell_R.at(R_i) );
          {
            polymer_type<2> dimer_ij = monomer_i + monomer_j;
            PolymerOmniReportGeneral<2> dimer_report;
            energy_data_type dimer_interaction_energy = compute_interaction_energy<2>( dimer_ij, settings, dimer_report );
            report.attach_new_dimer_report( dimer_report );
            retval += dimer_interaction_energy;
          }
        }
      }
    }
 
    return 1.0e0/2.0e0 * retval;
 
  }; // end of template function compute_expansion_term_periodic<2>()
 
  /**
   *  Explicit instantiation for order 3, to calculate total trimer interaction energy
   */
  template <> inline energy_data_type compute_expansion_term_periodic<3>( config_type config, report_ref report ) { 
 
    energy_data_type retval = 0.0e0;
    external_setting_type settings; settings.generate_from_config();
  
    unit_cell_type cell_zero = config.lattice().get_cell(0);
    for( size_t inode = 0; inode < cell_zero.n_node(); inode++ ){
      polymer_type<1> monomer_i( cell_zero.at(inode) );
      for( size_t R_j = 0; R_j < config.lattice().n_cell(); R_j++ ){
        unit_cell_type cell_R_j = config.lattice().get_cell(R_j);
        for( size_t inode_R_j = 0; inode_R_j < cell_R_j.n_node(); inode_R_j++ ){
          polymer_type<1> monomer_j( cell_R_j.at(inode_R_j) );
          for( size_t R_k = 0; R_k < config.lattice().n_cell(); R_k++ ){
            unit_cell_type cell_R_k = config.lattice().get_cell(R_k);
            for( size_t inode_R_k = 0; inode_R_k < cell_R_k.n_node(); inode_R_k++ ){
              polymer_type<1> monomer_k( cell_R_k.at(inode_R_k) );
              {
                polymer_type<3> trimer_ijk = monomer_i + monomer_j + monomer_k;
                PolymerOmniReportGeneral<3> trimer_report;
                energy_data_type trimer_interaction_energy = compute_interaction_energy<3> ( trimer_ijk, settings, trimer_report );
                report.attach_new_trimer_report( trimer_report );
                retval += trimer_interaction_energy;
              }
            }
          }
        }
      }
    }
 
    return 1.0e0/6.0e0 * retval;
 
  }; // end of template function compute_expansion_term_periodic<3>()
 
  /**
   *  Explicit instantiation for order 4, to calculate total tetramer interaction energy
   */
  template <> inline energy_data_type compute_expansion_term_periodic<4> ( config_type config, report_ref report ) {
 
    energy_data_type retval;
    external_setting_type settings; settings.generate_from_config();
 
    unit_cell_type cell_zero = config.lattice().get_cell(0);
    for( size_t inode = 0; inode < cell_zero.n_node(); inode++ ){
      polymer_type<1> monomer_i( cell_zero.at(inode) );
      for( size_t R_j = 0; R_j < config.lattice().n_cell(); R_j++ ){
        unit_cell_type cell_R_j = config.lattice().get_cell(R_j);
        for( size_t inode_R_j = 0; inode_R_j < cell_R_j.n_node(); inode_R_j++ ){
          polymer_type<1> monomer_j( cell_R_j.at(inode_R_j) );
          for( size_t R_k = 0; R_k < config.lattice().n_cell(); R_k++ ){
            unit_cell_type cell_R_k = config.lattice().get_cell(R_k);
            for( size_t inode_R_k = 0; inode_R_k < cell_R_k.n_node(); inode_R_k++ ){
              polymer_type<1> monomer_k( cell_R_k.at(inode_R_k) );
              for( size_t R_l = 0; R_l < config.lattice().n_cell(); R_l++ ){
                unit_cell_type cell_R_l = config.lattice().get_cell(R_l);
                 for( size_t inode_R_l = 0; inode_R_l < cell_R_l.n_node(); inode_R_l++ ){
                   polymer_type<1> monomer_l( cell_R_l.at(inode_R_l));
                   {
                     polymer_type<4> tetramer_ijkl = monomer_i + monomer_j + monomer_k + monomer_l;
                     PolymerOmniReportGeneral<4> tetramer_report;
                     energy_data_type tetramer_interaction_energy = compute_interaction_energy<4> ( tetramer_ijkl, settings, tetramer_report );
                     report.attach_new_tetramer_report( tetramer_report );
                     retval += tetramer_interaction_energy;
                   }
                }
              }
            }
          }
        }
      }
    }
 
    return 1.0e0/24.0e0 * retval;
 
  }; // end of template function compute_expansion_term_periodic<4> ()

} // end of manybody_expansion

} // end of namespace iquads

#endif
