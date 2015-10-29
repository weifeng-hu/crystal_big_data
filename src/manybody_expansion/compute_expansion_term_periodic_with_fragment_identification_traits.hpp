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

#ifndef COMPUTE_EXPANSION_TERM_PERIODIC_TRAITS_HPP
#define COMPUTE_EXPANSION_TERM_PERIODIC_TRAITS_HPP

#include <string>
#include <structure/polymer_template.hpp>
#include <electron_correlation/setting.hpp>
#include <manybody_expansion/config.hpp>
#include <manybody_expansion/report.hpp>
#include <manybody_expansion/fragment_signature_database_template.hpp>
#include <manybody_expansion/compute_interaction_energy_with_fragment_identification_traits.hpp>

namespace iquads {

namespace manybody_expansion {

  /**
   *  Templated methods to calculate individual orders of total interaction energies
   *  for periodic systems, coded using explicit instantiation.
   *
   *  These methods here use symmetry equilivant fragment identification, so
   *  the actual report object to use can either be periodic or non-periodic ones.
   */
  using structure :: Polymer;
  typedef double energy_data_type;
  typedef Config config_type;
  typedef Report report_type;
  typedef report_type& report_ref;
  typedef FragmentSignatureDataBase database_template;
  typedef electron_correlation :: Setting  external_setting_type;
  typedef config_type :: lattice_type :: unit_cell_type unit_cell_type;

  /**
   *  Default instantiation
   *  returns zero for energy, since no method can be defined.
   */
  template < size_t Order > inline energy_data_type compute_expansion_term_periodic_with_fragment_identification( config_type config, const database_template<Order>& database, report_ref report )
    { return 0.0e0; }

  /**
   *  Explicit instantiation for order 1, to calculate total monomer energy
   */
  template <> inline energy_data_type compute_expansion_term_periodic_with_fragment_identification<1>( config_type config, const database_template<1>& database, report_ref report ) {

    energy_data_type retval = 0.0e0;
    external_setting_type settings; settings.generate_from( config );
 
    unit_cell_type cell_R0 = config.lattice().at(0, 0, 0);
    for( size_t i_R0 = 0; i_R0 < cell_R0.size(); i_R0++ ) {
      Polymer<1>  monomer_i( array< Molecule, 1 > { cell_R0[i_R0] } );
      {
        double weight_factor = mbe_system_pointer->retrieve_weight_factor_for( monomer_i );
        double weight_factor = mbe_system_pointer->retrieve_identical_polymer_list_for( monomer_i );
        PolymerOmniReportPeriodic<1>  monomer_report;
        std :: string monomer_name( "monomer_" );
                      monomer_name += std :: string( "R_" ) + std :: string( "0_0_0_" );
                      monomer_name += std :: string( "i_" ) + std :: to_string( i_R0 ) + std :: string( "_" );
        energy_data_type monomer_energy
          = compute_interaction_energy<1>( monomer_i, std :: string( monomer_name ) , settings, monomer_report );
        report.attach_new_monomer_report( monomer_report );
        retval += monomer_energy * weight_factor;
      }
    }
 
    return retval;
 
  }; // end of template function compute_expansion_term_periodic<1>()
 
  /**
   *  Explicit instantiation for order 2, to calculate total dimer interaction energy
   */
  template <> inline energy_data_type compute_expansion_term_periodic_with_fragment_identification<2>( config_type config, const database_template<2>& database, report_ref report ) {
 
    energy_data_type retval = 0.0e0;
    external_setting_type settings; settings.generate_from( config );
 
    unit_cell_type cell_R0 = config.lattice().at(0, 0, 0);
    for( size_t i_R0 = 0; i_R0 < cell_R0.size(); i_R0++ ) {
      Polymer<1> monomer_i( array<Molecule, 1> { cell_R0[i_R0] } );
      for( int R_a = config.lattice().a_min(); R_a <= config.lattice().a_max(); R_a++ ) {
        for( int R_b = config.lattice().b_min(); R_b <= config.lattice().b_max(); R_b++ ) {
          for( int R_c = config.lattice().c_min(); R_c <= config.lattice().c_max(); R_c++ ) {
            unit_cell_type cell_R = config.lattice().at( R_a, R_b, R_c );
            for( size_t i_R = 0; i_R < cell_R.size(); i_R++ ) {

              if( ( cell_R0 == cell_R ) && ( i_R0 == i_R ) ) continue;
              Polymer<1> monomer_j( array< Molecule, 1 > { cell_R[i_R] } );
              {
                Polymer<2> dimer_ij = monomer_i + monomer_j;
                PolymerOmniReportGeneral<2> dimer_report;
                std :: string dimer_name( "dimer_" );
                              dimer_name += std :: string( "R_" ) + std :: string( "0_0_0_" );
                              dimer_name += std :: string( "i_" ) + std :: to_string( i_R0  ) + std :: string( "_" );
                              dimer_name += std :: string( "R_" ) + std :: to_string( R_a ) + std :: string( "_" ) + 
                                                                    std :: to_string( R_b ) + std :: string( "_" ) + 
                                                                    std :: to_string( R_c ) + std :: string( "_" );
                              dimer_name += std :: string( "j_" ) + std :: to_string( i_R ) + std :: string( "_" );
                energy_data_type dimer_interaction_energy = compute_interaction_energy<2> ( dimer_ij, std :: string( dimer_name ), settings, dimer_report );
                report.attach_new_dimer_report( dimer_report );
                retval += dimer_interaction_energy;
              }
            }
      } } }
    }
 
    return 1.0e0/2.0e0 * retval;
 
  }; // end of template function compute_expansion_term_periodic<2>()
 
  /**
   *  Explicit instantiation for order 3, to calculate total trimer interaction energy
   */
  template <> inline energy_data_type compute_expansion_term_periodic_with_fragment_identification<3>( config_type config, const database_template<3>& database, report_ref report ) {
 
    energy_data_type retval = 0.0e0;
    external_setting_type settings; settings.generate_from(config);
  
    unit_cell_type cell_R0 = config.lattice().at(0, 0, 0);
    for( size_t i_R0 = 0; i_R0 < cell_R0.size(); i_R0++ ) {
      Polymer<1> monomer_i( array< Molecule, 1 > { cell_R0[ i_R0 ] } );
      for( int R_j_a = config.lattice().a_min(); R_j_a <= config.lattice().a_max(); R_j_a++ ) {
        for( int R_j_b = config.lattice().b_min(); R_j_b <= config.lattice().b_max(); R_j_b++ ) {
          for( int R_j_c = config.lattice().c_min(); R_j_c <= config.lattice().c_max(); R_j_c++ ) {
            unit_cell_type cell_Rj = config.lattice().at( R_j_a, R_j_b, R_j_c );
            for( size_t i_Rj = 0; i_Rj < cell_Rj.size(); i_Rj++ ) {
              Polymer<1> monomer_j( array< Molecule, 1 > { cell_Rj[i_Rj] } );
              for( int R_k_a = config.lattice().a_min(); R_k_a <= config.lattice().a_max(); R_k_a++ ) {
                for( int R_k_b = config.lattice().b_min(); R_k_b <= config.lattice().b_max(); R_k_b++ ) {
                  for( int R_k_c = config.lattice().c_min(); R_k_c <= config.lattice().c_max(); R_k_c++ ) {
                    unit_cell_type cell_Rk = config.lattice().at( R_k_a, R_k_b, R_k_c );
                    for( size_t i_Rk = 0; i_Rk < cell_Rk.size(); i_Rk++ ){

                      if( ( ( cell_Rj == cell_R0 ) && ( i_Rj == i_R0 ) ) ||
                          ( ( cell_Rk == cell_R0 ) && ( i_Rk == i_R0 ) ) ||
                          ( ( cell_Rk == cell_Rj ) && ( i_Rk == i_Rj ) ) ) continue;

                      Polymer<1> monomer_k( array< Molecule, 1 > { cell_Rk[ i_Rk ] } );

                      {
                        Polymer<3> trimer_ijk = monomer_i + monomer_j + monomer_k;
                        PolymerOmniReportGeneral<3> trimer_report;
                        std :: string trimer_name( "trimer_" );
                                      trimer_name += std :: string( "R_" ) + std :: string( "0_0_0_" );
                                      trimer_name += std :: string( "i_" ) + std :: to_string( i_R0 ) + std :: string( "_" );
                                      trimer_name += std :: string( "R_" ) + std :: to_string( R_j_a ) + std :: string( "_" ) + 
                                                                             std :: to_string( R_j_b ) + std :: string( "_" ) + 
                                                                             std :: to_string( R_j_c ) + std :: string( "_" );
                                      trimer_name += std :: string( "j_" ) + std :: to_string( i_Rj ) + std :: string( "_" );
                                      trimer_name += std :: string( "R_" ) + std :: to_string( R_k_a ) + std :: string( "_" ) + 
                                                                             std :: to_string( R_k_b ) + std :: string( "_" ) + 
                                                                             std :: to_string( R_k_c ) + std :: string( "_" );
                                      trimer_name += std :: string( "k_" ) + std :: to_string( i_Rk ) + std :: string( "_" );
                        energy_data_type trimer_interaction_energy = compute_interaction_energy<3> ( trimer_ijk, std :: string( trimer_name ), settings, trimer_report );
                        report.attach_new_trimer_report( trimer_report );
                        retval += trimer_interaction_energy;
                      }
                    }
              } } }
            }
      } } }
    }
 
    return 1.0e0/6.0e0 * retval;
 
  }; // end of template function compute_expansion_term_periodic<3>()
 
  /**
   *  Explicit instantiation for order 4, to calculate total tetramer interaction energy
   */
  template <> inline energy_data_type compute_expansion_term_periodic_with_fragment_identification<4> ( config_type config, const database_template<4>& database, report_ref report ) {
 
    energy_data_type retval = 0.0e0;
    external_setting_type settings; settings.generate_from( config );
 
    unit_cell_type cell_R0 = config.lattice().at(0, 0, 0);
    for( size_t i_R0 = 0; i_R0 < cell_R0.size(); i_R0++ ) {
      Polymer<1> monomer_i( array< Molecule, 1 > { cell_R0[ i_R0 ] } );
      for( int R_j_a = config.lattice().a_min(); R_j_a <= config.lattice().a_max(); R_j_a++ ) {
        for( int R_j_b = config.lattice().b_min(); R_j_b <= config.lattice().b_max(); R_j_b++ ) {
          for( int R_j_c = config.lattice().c_min(); R_j_c <= config.lattice().c_max(); R_j_c++ ) {
            unit_cell_type cell_Rj = config.lattice().at( R_j_a, R_j_b, R_j_c );
            for( size_t i_Rj = 0; i_Rj < cell_Rj.size(); i_Rj++ ) {
              Polymer<1> monomer_j( array< Molecule, 1 > { cell_Rj[ i_Rj ] } );
              for( int R_k_a = config.lattice().a_min(); R_k_a <= config.lattice().a_max(); R_k_a++ ) {
                for( int R_k_b = config.lattice().b_min(); R_k_b <= config.lattice().b_max(); R_k_b++ ) {
                  for( int R_k_c = config.lattice().c_min(); R_k_c <= config.lattice().c_max(); R_k_c++ ) {
                    unit_cell_type cell_Rk = config.lattice().at( R_k_a, R_k_b, R_k_c );
                    for( size_t i_Rk = 0; i_Rk < cell_Rk.size(); i_Rk++ ){
                      Polymer<1> monomer_k( array< Molecule, 1 > { cell_Rk[ i_Rk ] } );
                        for( int R_l_a = config.lattice().a_min(); R_l_a <= config.lattice().a_max(); R_l_a++ ){
                          for( int R_l_b = config.lattice().b_min(); R_l_b <= config.lattice().b_max(); R_l_b++ ){
                            for( int R_l_c = config.lattice().c_min(); R_l_c <= config.lattice().c_max(); R_l_c++ ){
                              unit_cell_type cell_Rl = config.lattice().at( R_l_a, R_l_b, R_l_c );
                              for( size_t i_Rl = 0; i_Rl < cell_Rl.size(); i_Rl++ ){
                                Polymer<1> monomer_l( array< Molecule, 1 > { cell_Rl[ i_Rl ] } );

                                if( ( ( cell_Rj == cell_R0 ) && ( i_Rj == i_R0 ) ) || 
                                    ( ( cell_Rk == cell_R0 ) && ( i_Rk == i_R0 ) ) ||
                                    ( ( cell_Rl == cell_R0 ) && ( i_Rl == i_R0 ) ) ||
                                    ( ( cell_Rj == cell_Rk ) && ( i_Rj == i_Rk ) ) ||
                                    ( ( cell_Rj == cell_Rl ) && ( i_Rj == i_Rl ) ) ||
                                    ( ( cell_Rk == cell_Rl ) && ( i_Rk == i_Rl ) ) ) continue;

                                {
                                  Polymer<4> tetramer_ijkl = monomer_i + monomer_j + monomer_k + monomer_l;
                                  PolymerOmniReportGeneral<4> tetramer_report;
                                  std :: string tetramer_name;
                                                tetramer_name += std :: string( "R_" ) + std :: string( "0_0_0_" );
                                                tetramer_name += std :: string( "i_" ) + std :: to_string( i_R0 ) + std :: string( "_" );
                                                tetramer_name += std :: string( "R_" ) + std :: to_string( R_j_a ) + std :: string( "_" ) + 
                                                                                         std :: to_string( R_j_b ) + std :: string( "_" ) + 
                                                                                         std :: to_string( R_j_c ) + std :: string( "_" );
                                                tetramer_name += std :: string( "j_" ) + std :: to_string( i_Rj ) + std :: string( "_" );
                                                tetramer_name += std :: string( "R_" ) + std :: to_string( R_k_a ) + std :: string( "_" ) + 
                                                                                         std :: to_string( R_k_b ) + std :: string( "_" ) + 
                                                                                         std :: to_string( R_k_c ) + std :: string( "_" );
                                                tetramer_name += std :: string( "k_" ) + std :: to_string( i_Rk ) + std :: string( "_" );
                                                tetramer_name += std :: string( "R_" ) + std :: to_string( R_l_a ) + std :: string( "_" ) + 
                                                                                         std :: to_string( R_l_b ) + std :: string( "_" ) + 
                                                                                         std :: to_string( R_l_c ) + std :: string( "_" );
                                                tetramer_name += std :: string( "l_" ) + std :: to_string( i_Rl ) + std :: string( "_" );
                                  energy_data_type tetramer_interaction_energy = compute_interaction_energy<4> ( tetramer_ijkl, std :: string( tetramer_name ), settings, tetramer_report );
                                  report.attach_new_tetramer_report( tetramer_report );
                                  retval += tetramer_interaction_energy;
                                }
                              }
                        } } }
                    }
              } } }
            }
      } } }
    }
 
    return 1.0e0/24.0e0 * retval;
 
  }; // end of template function compute_expansion_term_periodic<4> ()

} // end of manybody_expansion

} // end of namespace iquads

#endif
