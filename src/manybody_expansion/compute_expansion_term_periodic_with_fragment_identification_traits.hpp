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

#ifndef COMPUTE_EXPANSION_TERM_PERIODIC_WITH_FRAGMENT_IDENTIFICATION_TRAITS_HPP
#define COMPUTE_EXPANSION_TERM_PERIODIC_WITH_FRAGMENT_IDENTIFICATION_TRAITS_HPP

#include <string>
#include <timer/progress_display.hpp>
#include <structure/polymer_template.hpp>
#include <electron_correlation/setting.hpp>
#include <manybody_expansion/config.hpp>
#include <manybody_expansion/report.hpp>
#include <manybody_expansion/fragment_signature_database.hpp>
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
  typedef FragmentSignatureDataBase database_type;
  typedef config_type :: lattice_type :: unit_cell_type unit_cell_type;

  /**
   *  Default instantiation
   *  returns zero for energy, since no method can be defined.
   */
  template < size_t Order > inline energy_data_type compute_expansion_term_periodic_with_fragment_identification( config_type config, const database_type& database, report_ref report )
    { return 0.0e0; }

  /**
   *  Explicit instantiation for order 1, to calculate total monomer energy
   */
  template <> inline energy_data_type compute_expansion_term_periodic_with_fragment_identification<1>( config_type config, const database_type& database, report_ref report ) {

    energy_data_type retval = 0.0e0;
    unit_cell_type cell_R0 = config.lattice().at(0, 0, 0);
    iquads :: timer :: ProgressDisplay progress_display( "Computing first order energy ...", cell_R0.size() );
    for( size_t i_R0 = 0; i_R0 < cell_R0.size(); i_R0++ ) {
      
      Polymer<1>  monomer_i( array< Molecule, 1 > { cell_R0[i_R0] } );
      {
        PolymerOmniReportGeneral<1>  monomer_report;
        std :: string monomer_name( "monomer_" );
                      monomer_name += std :: string( "R_" ) + std :: string( "0_0_0_" );
                      monomer_name += std :: string( "i_" ) + std :: to_string( i_R0 ) + std :: string( "_" );
        std :: array< lattice_index_type, 1 > index = { std :: make_tuple( std :: make_tuple( 0, 0, 0 ), i_R0 ) };
        energy_data_type monomer_energy
          = compute_interaction_energy_with_fragment_identification<1>( index, std :: string( monomer_name ), database, monomer_report );
        /*
        report.attach_new_monomer_report( monomer_report );
        */
        retval += monomer_energy;
      }
      progress_display++;
    }
 
    std :: cout << "First order energy: " << std :: setprecision(12) << std :: setw(16) << retval << std :: endl;
    return retval;
 
  }; // end of template function compute_expansion_term_periodic<1>()
 
  /**
   *  Explicit instantiation for order 2, to calculate total dimer interaction energy
   */
  template <> inline energy_data_type compute_expansion_term_periodic_with_fragment_identification<2>( config_type config, const database_type& database, report_ref report ) {
 
    energy_data_type retval = 0.0e0;
    size_t number_of_effective_terms = 0;
    unit_cell_type cell_R0 = config.lattice().at(0, 0, 0);

    const size_t unit_size = cell_R0.size();
    const size_t na = config.lattice().na(); 
    const size_t nb = config.lattice().nb(); 
    const size_t nc = config.lattice().nc(); 

    omp_set_dynamic(0);
    const int num_thread = omp_get_num_procs();
    omp_set_num_threads( num_thread );
    const size_t loop_size = unit_size * na * nb * nc;
    std :: string display_message = std :: string( "Computing second order interaction energy [ openmp, automatic, num_thread = " ) +
                                    std :: to_string( num_thread ) +
                                    std :: string( " ] with total number of terms [ " ) + 
                                    std :: to_string( unit_size * na * nb * nc ) + 
                                    std :: string( " ] ... " );
    iquads :: timer :: ProgressDisplay progress_display( display_message, loop_size/num_thread );

    std :: vector< energy_data_type > retval_set;
    retval_set.resize( num_thread );
    std :: vector< size_t > number_of_effective_terms_set;
    number_of_effective_terms_set.resize( num_thread );

    #pragma omp parallel
    {
      const int thread_id = omp_get_thread_num();
      energy_data_type retval_local = 0.0e0;
      size_t number_of_effective_terms_local = 0;

      #pragma omp for
      for( size_t i = 0; i < loop_size; i++ ) {
        const size_t i_R0  = i / ( na * nb * nc );
        const size_t i_R_a = ( i - i_R0 * na * nb * nc ) / ( nb * nc );
        const size_t i_R_b = ( i - i_R0 * na * nb * nc - i_R_a * nb * nc ) / nc;
        const size_t i_R_c = ( i - i_R0 * na * nb * nc - i_R_a * nb * nc - i_R_b * nc );
        const int R_a = config.lattice().a_min() + i_R_a;
        const int R_b = config.lattice().b_min() + i_R_b;
        const int R_c = config.lattice().c_min() + i_R_c;
 

    // iquads :: timer :: ProgressDisplay progress_display( "Computing second order interaction energy ...", cell_R0.size() * config.lattice().na() * config.lattice().nb() * config.lattice().nc() );

       // for( size_t i_R0 = 0; i_R0 < cell_R0.size(); i_R0++ ) {
          Polymer<1> monomer_i( array<Molecule, 1> { cell_R0[i_R0] } );
        // for( int R_a = config.lattice().a_min(); R_a <= config.lattice().a_max(); R_a++ ) {
          // for( int R_b = config.lattice().b_min(); R_b <= config.lattice().b_max(); R_b++ ) {
            // for( int R_c = config.lattice().c_min(); R_c <= config.lattice().c_max(); R_c++ ) {
                unit_cell_type cell_R = config.lattice().at( R_a, R_b, R_c );
                for( size_t i_R = 0; i_R < cell_R.size(); i_R++ ) {

                  if( ( cell_R0 == cell_R ) && ( i_R0 == i_R ) ) continue;
                  Polymer<1> monomer_j( array< Molecule, 1 > { cell_R[i_R] } );

                  {
                    Polymer<2> dimer_ij = monomer_i + monomer_j;
                      if( dimer_ij.within_mean_distance_by_center_of_mass( config.radius() ) == true ) {
                      PolymerOmniReportGeneral<2> dimer_report;
                      std :: string dimer_name( "dimer_" );
                                    dimer_name += std :: string( "R_" ) + std :: string( "0_0_0_" );
                                    dimer_name += std :: string( "i_" ) + std :: to_string( i_R0  ) + std :: string( "_" );
                                    dimer_name += std :: string( "R_" ) + std :: to_string( R_a ) + std :: string( "_" ) + 
                                                                          std :: to_string( R_b ) + std :: string( "_" ) + 
                                                                          std :: to_string( R_c ) + std :: string( "_" );
                                    dimer_name += std :: string( "j_" ) + std :: to_string( i_R ) + std :: string( "_" );
                      std :: array< lattice_index_type, 2 > index = { std :: make_tuple( std :: make_tuple( 0, 0, 0 ), i_R0 ), 
                                                                      std :: make_tuple( std :: make_tuple( R_a, R_b, R_c ), i_R ) };
                      energy_data_type dimer_interaction_energy = compute_interaction_energy_with_fragment_identification<2> ( index, std :: string( dimer_name ), database, dimer_report );
                      //std :: cout << dimer_interaction_energy << std :: endl;
                      /*
                      report.attach_new_dimer_report( dimer_report );
                      */
                      number_of_effective_terms_local += 1;
                      retval_local += dimer_interaction_energy;
                    }
                  }
                }
          if( thread_id == 0 ) { progress_display++; }
          // } } }
        //}
      }

      retval_set[ thread_id ] = retval_local;
      number_of_effective_terms_set[ thread_id ] = number_of_effective_terms_local;
      #pragma omp barrier

      #pragma omp single
      for( size_t j = 0; j < retval_set.size(); j++ ) {
        retval+= retval_set[j];
        number_of_effective_terms += number_of_effective_terms_set[j];
      }

    }

    std :: cout << "Second order interaction energy: " << std :: setprecision(12) << std :: setw(16) << retval/2.0e0 << std :: endl;
    std :: cout << "Number of effective terms: " << number_of_effective_terms << std :: endl;

    return 1.0e0/2.0e0 * retval;
 
  }; // end of template function compute_expansion_term_periodic<2>()
 
  /**
   *  Explicit instantiation for order 3, to calculate total trimer interaction energy
   */
  template <> inline energy_data_type compute_expansion_term_periodic_with_fragment_identification<3>( config_type config, const database_type& database, report_ref report ) {

    energy_data_type retval = 0.0e0;
    size_t number_of_effective_terms = 0;
    unit_cell_type cell_R0 = config.lattice().at(0, 0, 0);

    const size_t unit_size = cell_R0.size();
    const size_t na = config.lattice().na(); 
    const size_t nb = config.lattice().nb(); 
    const size_t nc = config.lattice().nc(); 
 
    omp_set_dynamic(0);
    const int num_thread = omp_get_num_procs();
    omp_set_num_threads( num_thread );
    const size_t loop_size = unit_size * na * nb * nc;
    std :: string display_message = std :: string( "Computing third order interaction energy [ openmp, automatic, num_thread = " ) +
                                    std :: to_string( num_thread ) +
                                    std :: string( " ] with total number of terms [ " ) + 
                                    std :: to_string( unit_size * na * nb * nc * na * nb * nc ) + 
                                    std :: string( " ] ... " );
    iquads :: timer :: ProgressDisplay progress_display( display_message, loop_size/num_thread );

    //iquads :: timer :: ProgressDisplay progress_display( "Computing third order interaction energy ...", cell_R0.size() * config.lattice().na() * config.lattice().nb() * config.lattice().nc() );

    std :: vector< energy_data_type > retval_set;
    retval_set.resize( num_thread );
    std :: vector< size_t > number_of_effective_terms_set;
    number_of_effective_terms_set.resize( num_thread );

    #pragma omp parallel
    {
      const int thread_id = omp_get_thread_num();
      energy_data_type retval_local = 0.0e0;
      size_t number_of_effective_terms_local = 0;

      #pragma omp for
      for( size_t i = 0; i < loop_size; i++ ) {
        const size_t i_R0  = i / ( na * nb * nc );
        const size_t i_R_a = ( i - i_R0 * na * nb * nc ) / ( nb * nc );
        const size_t i_R_b = ( i - i_R0 * na * nb * nc - i_R_a * nb * nc ) / nc;
        const size_t i_R_c = ( i - i_R0 * na * nb * nc - i_R_a * nb * nc - i_R_b * nc );
        const int R_j_a = config.lattice().a_min() + i_R_a;
        const int R_j_b = config.lattice().b_min() + i_R_b;
        const int R_j_c = config.lattice().c_min() + i_R_c;

        //for( size_t i_R0 = 0; i_R0 < cell_R0.size(); i_R0++ ) {
          Polymer<1> monomer_i( array< Molecule, 1 > { cell_R0[ i_R0 ] } );
         // for( int R_j_a = config.lattice().a_min(); R_j_a <= config.lattice().a_max(); R_j_a++ ) {
          //  for( int R_j_b = config.lattice().b_min(); R_j_b <= config.lattice().b_max(); R_j_b++ ) {
           //   for( int R_j_c = config.lattice().c_min(); R_j_c <= config.lattice().c_max(); R_j_c++ ) {
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
                            if( trimer_ijk.within_mean_distance_by_center_of_mass( config.radius() ) == true ) { 
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
                              std :: array< lattice_index_type, 3 > index 
                                = { std :: make_tuple( std :: make_tuple( 0, 0, 0 ), i_R0 ), 
                                    std :: make_tuple( std :: make_tuple( R_j_a, R_j_b, R_j_c ), i_Rj ), 
                                    std :: make_tuple( std :: make_tuple( R_k_a, R_k_b, R_k_c ), i_Rk ) };
                              energy_data_type trimer_interaction_energy = compute_interaction_energy_with_fragment_identification<3> ( index, std :: string( trimer_name ), database, trimer_report );
                              /*
                              report.attach_new_trimer_report( trimer_report );
                              */
                              // retval += trimer_interaction_energy;
                              number_of_effective_terms_local += 1;
                              retval_local += trimer_interaction_energy;
                            }
                          }
                        }
                  } } }
                }
         if( thread_id == 0 ) {  progress_display++; }
        //  } } }
       // }
      }

      retval_set[ thread_id ] = retval_local;
      number_of_effective_terms_set[ thread_id ] = number_of_effective_terms_local;
      #pragma omp barrier

      #pragma omp single
      for( size_t j = 0; j < retval_set.size(); j++ ) {
        retval+= retval_set[j];
        number_of_effective_terms += number_of_effective_terms_set[j];
      }

    }

    std :: cout << "Third order interaction energy: " << std :: setprecision(12) << std :: setw(16) << retval/6.0e0 << std :: endl;
    std :: cout << "Number of effective terms: " << number_of_effective_terms << std :: endl;

    return 1.0e0/6.0e0 * retval;
 
  }; // end of template function compute_expansion_term_periodic<3>()
 
  /**
   *  Explicit instantiation for order 4, to calculate total tetramer interaction energy
   */
  template <> inline energy_data_type compute_expansion_term_periodic_with_fragment_identification<4> ( config_type config, const database_type& database, report_ref report ) { 

    energy_data_type retval = 0.0e0;
    size_t number_of_effective_terms = 0;
    unit_cell_type cell_R0 = config.lattice().at(0, 0, 0);

    const size_t unit_size = cell_R0.size();
    const size_t na = config.lattice().na(); 
    const size_t nb = config.lattice().nb(); 
    const size_t nc = config.lattice().nc(); 

    omp_set_dynamic(0);
    const int num_thread = omp_get_num_procs();
    omp_set_num_threads( num_thread );
    const size_t loop_size = unit_size * na * nb * nc;
    std :: string display_message = std :: string( "Computing fourth order interaction energy [ openmp, automatic, num_thread = " ) +
                                    std :: to_string( num_thread ) +
                                    std :: string( " ] with total number of terms [ " ) + 
                                    std :: to_string( unit_size * na * nb * nc * na * nb * nc * na * nb * nc ) + 
                                    std :: string( " ] ... " );
    iquads :: timer :: ProgressDisplay progress_display( display_message, loop_size/num_thread );

// Former code
//    unit_cell_type cell_R0 = config.lattice().at(0, 0, 0);
//    iquads :: timer :: ProgressDisplay progress_display( "Computing fourth order interaction energy ...", cell_R0.size() * config.lattice().na() * config.lattice().nb() * config.lattice().nc() );

    std :: vector< energy_data_type > retval_set;
    retval_set.resize( num_thread );
    std :: vector< size_t > number_of_effective_terms_set;
    number_of_effective_terms_set.resize( num_thread );

    #pragma omp parallel
    {
      const int thread_id = omp_get_thread_num();
      energy_data_type retval_local = 0.0e0;
      size_t number_of_effective_terms_local = 0;

      #pragma omp for
      for( size_t i = 0; i < loop_size; i++ ) {
        const size_t i_R0  = i / ( na * nb * nc );
        const size_t i_R_a = ( i - i_R0 * na * nb * nc ) / ( nb * nc );
        const size_t i_R_b = ( i - i_R0 * na * nb * nc - i_R_a * nb * nc ) / nc;
        const size_t i_R_c = ( i - i_R0 * na * nb * nc - i_R_a * nb * nc - i_R_b * nc );
        const int R_j_a = config.lattice().a_min() + i_R_a;
        const int R_j_b = config.lattice().b_min() + i_R_b;
        const int R_j_c = config.lattice().c_min() + i_R_c;
        // std :: cout << i_R0 << " " << R_j_a << " " << R_j_b << " " << R_j_c << std :: endl;
 
      //for( size_t i_R0 = 0; i_R0 < cell_R0.size(); i_R0++ ) {
        Polymer<1> monomer_i( array< Molecule, 1 > { cell_R0[ i_R0 ] } );
       // for( int R_j_a = config.lattice().a_min(); R_j_a <= config.lattice().a_max(); R_j_a++ ) {
         // for( int R_j_b = config.lattice().b_min(); R_j_b <= config.lattice().b_max(); R_j_b++ ) {
           // for( int R_j_c = config.lattice().c_min(); R_j_c <= config.lattice().c_max(); R_j_c++ ) {
        unit_cell_type cell_Rj = config.lattice().at( R_j_a, R_j_b, R_j_c );
              for( size_t i_Rj = 0; i_Rj < cell_Rj.size(); i_Rj++ ) {
                Polymer<1> monomer_j( array< Molecule, 1 > { cell_Rj[ i_Rj ] } );
                for( int R_k_a = config.lattice().a_min(); R_k_a <= config.lattice().a_max(); R_k_a++ ) {
                  for( int R_k_b = config.lattice().b_min(); R_k_b <= config.lattice().b_max(); R_k_b++ ) {
                    for( int R_k_c = config.lattice().c_min(); R_k_c <= config.lattice().c_max(); R_k_c++ ) {
                      unit_cell_type cell_Rk = config.lattice().at( R_k_a, R_k_b, R_k_c );
                      for( size_t i_Rk = 0; i_Rk < cell_Rk.size(); i_Rk++ ){
                        Polymer<1> monomer_k( array< Molecule, 1 > { cell_Rk[ i_Rk ] } );
                          for( int R_l_a = config.lattice().a_min(); R_l_a <= config.lattice().a_max(); R_l_a++ ) {
                            for( int R_l_b = config.lattice().b_min(); R_l_b <= config.lattice().b_max(); R_l_b++ ) {
                              for( int R_l_c = config.lattice().c_min(); R_l_c <= config.lattice().c_max(); R_l_c++ ) {
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
                                    if( tetramer_ijkl.within_mean_distance_by_center_of_mass( config.radius() ) == true ) {
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
                                      std :: array< lattice_index_type, 4 > index 
                                        = { std :: make_tuple( std :: make_tuple( 0, 0, 0 ), i_R0 ), 
                                            std :: make_tuple( std :: make_tuple( R_j_a, R_j_b, R_j_c ), i_Rj ),
                                            std :: make_tuple( std :: make_tuple( R_k_a, R_k_b, R_k_c ), i_Rk ),
                                            std :: make_tuple( std :: make_tuple( R_l_a, R_l_b, R_l_c ), i_Rl ) };
                                      energy_data_type tetramer_interaction_energy = compute_interaction_energy_with_fragment_identification<4> ( index, std :: string( tetramer_name ), database, tetramer_report );
                                      //  For save the memory we temporarily disable this reporting
                                      //  report.attach_new_tetramer_report( tetramer_report );
                                      //
                                      // retval += tetramer_interaction_energy;
                                       number_of_effective_terms_local += 1;
                                       retval_local += tetramer_interaction_energy;
                                    }
                                  }
                                }
                          } } }
                      }
                } } }
              }
        if( thread_id == 0 ) { progress_display++; }
        // Former code
       // } } }
      //}
      }

      retval_set[ thread_id ] = retval_local;
      number_of_effective_terms_set[ thread_id ] = number_of_effective_terms_local;
      #pragma omp barrier

      #pragma omp single
      for( size_t j = 0; j < retval_set.size(); j++ ) {
        retval+= retval_set[j];
        number_of_effective_terms += number_of_effective_terms_set[j];
      }

    }

    std :: cout << "Fourth order interaction energy: " << std :: setprecision(12) << std :: setw(16) << retval/24.0e0 << std :: endl;
    std :: cout << "Number of effective terms: " << number_of_effective_terms << std :: endl;

    return 1.0e0/24.0e0 * retval;
 
  }; // end of template function compute_expansion_term_periodic<4> ()

} // end of manybody_expansion

} // end of namespace iquads

#endif
