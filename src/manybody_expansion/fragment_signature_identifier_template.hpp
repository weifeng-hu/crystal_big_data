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

#ifndef FRAGMENT_SIGNATURE_IDENTIFIER_TEMPLATE_HPP
#define FRAGMENT_SIGNATURE_IDENTIFIER_TEMPLATE_HPP

#include <omp.h>
#include <stdlib.h>
#include <array>
#include <vector>
#include <tuple>
#include <timer/progress_display.hpp>
#include <math/combination_computation.hpp>
#include <matrix/matrix_typedef.hpp>
#include <matrix/matrix_function.hpp>
#include <structure/molecule.hpp>
#include <structure/polymer_template.hpp>
#include <structure/bulk_instant.hpp>
#include <structure/lattice_instant.hpp>
#include <structure/euclidean_distance_matrix.hpp>
#include <electron_correlation/setting.hpp>
#include <electron_correlation/client.hpp>
#include <manybody_expansion/fragment_info_template.hpp>
#include <manybody_expansion/polymer_report_template.hpp>

namespace iquads {

namespace manybody_expansion {

template< size_t NUM > struct FragmentSignatureIdentifier {
public:
  typedef double distance_data_type;
  typedef iquads :: structure :: Molecule         molecule_type;
  typedef iquads :: structure :: MolecularLattice lattice_type;
  typedef iquads :: structure :: MolecularBulk    bulk_type;
  typedef iquads :: structure :: Polymer<NUM>     polymer_type;
  typedef std :: array< iquads :: structure :: Molecule, NUM >  molecule_list_type;
  typedef std :: vector< polymer_type >           polymer_list_type;

  typedef std :: array< int, NUM >                                 polymer_bulk_index_combination_type;
  typedef std :: vector< polymer_bulk_index_combination_type >     polymer_bulk_index_list_type;
  typedef std :: tuple< std :: tuple< int, int, int >, int >       lattice_node_index_type;
  typedef std :: array< lattice_node_index_type, NUM >             polymer_lattice_index_combination_type;
  typedef std :: vector< polymer_lattice_index_combination_type >  polymer_lattice_index_list_type;

  typedef iquads :: timer :: ProgressDisplay                 progress_display_type;
  typedef iquads :: electron_correlation :: Setting          electron_calc_setting_type;
  typedef iquads :: electron_correlation :: Client           molecular_energy_client_type;
  typedef iquads :: manybody_expansion :: FragmentInfo<NUM>  fragment_info_type;
  typedef std :: vector< fragment_info_type >                fragment_info_list_type;
  typedef iquads :: matrix :: DMatrixHeap                    matrix_type;
  typedef iquads :: structure :: EuclideanDistanceMatrix     euclidean_distance_matrix_type;
  enum SystemType { BULK,  LATTICE };

public:
  FragmentSignatureIdentifier() {
    this->polymer_list_.resize(0);
    this->polymer_bulk_index_list_.resize(0);
    this->polymer_lattice_index_list_.resize(0);
    this->is_initialized_ = false;
  }

public:
  std :: array< lattice_node_index_type, NUM > translate_index_to_lattice_node_index( std :: array< int, NUM > index, lattice_type lattice_obj ) {
    std :: array< lattice_node_index_type, NUM > retval;
    for( size_t i = 0; i < NUM; i++ ) {
      retval[i] = lattice_obj.translate_index_to_lattice_node_index( index[i] );
    }
    return retval;
  }
  molecule_list_type get_molecule_list_from_lattice( std :: array< lattice_node_index_type , NUM > comb, lattice_type lattice_obj ) {
    std :: array< molecule_type, NUM >  return_value;
    for( size_t i = 0; i < NUM; i++ ) {
      lattice_node_index_type node_index = comb[i];
      int a = std :: get <0> ( std :: get<0> ( node_index ) );
      int b = std :: get <1> ( std :: get<0> ( node_index ) );
      int c = std :: get <2> ( std :: get<0> ( node_index ) );
      lattice_type :: unit_cell_type unit_cell = lattice_obj.at( a, b, c );
      int j = std :: get <1> ( node_index );
      molecule_type molecule = unit_cell.at(j);
      return_value[i] = molecule;
    }
    return return_value;
  }

public:
  void initialize( const lattice_type& lattice_obj, distance_data_type radius ) {


    // cout << "Initializing polymer group from bulk... " << endl;
    // get a list of combination
    polymer_bulk_index_list_type polymer_combination_list_orig
      = iquads :: math :: get_combination<NUM>( lattice_obj.size() * lattice_obj.unit_cell().size() );

    std :: cout << "Combination done. Found " << polymer_combination_list_orig.size()  << " unique polymers of " << NUM << " in the molecular lattice " << std :: endl << std :: flush;

    omp_set_dynamic(0);
    const size_t num_thread = omp_get_num_procs();
    omp_set_num_threads( num_thread );
    const size_t total_num  = polymer_combination_list_orig.size();
    std :: vector< polymer_list_type* > sub_polymer_list_addresses;
    sub_polymer_list_addresses.resize( num_thread );
    std :: vector< polymer_lattice_index_list_type* > sub_polymer_lattice_index_list_addresses;
    sub_polymer_lattice_index_list_addresses.resize( num_thread );

    // std :: cout << polymer_combination_list_orig.size() << std :: endl;
    std :: string initialize_message = std :: string( "Initializing the identifier [ openmp, automatic, num_thread = " ) +
                                                                               std :: to_string( num_thread ) +
                                                                         std :: string( " ] for fragment [ polymer - " ) +
                                                                                                 std :: to_string( NUM ) +
                                       std :: string( " ] with total " + std :: to_string( total_num ) + " fragments to examine ..." );
    progress_display_type progress_display( initialize_message, total_num/num_thread );
 
    #pragma omp parallel 
    {
      const int thread_id = omp_get_thread_num();
                    polymer_list_type sub_polymer_list;
                                      sub_polymer_list.resize(0);
      polymer_lattice_index_list_type sub_polymer_lattice_index_list;
                                      sub_polymer_lattice_index_list.resize(0);
      #pragma omp for
      for( size_t icomb = 0; icomb < total_num; icomb++ ) {
        polymer_lattice_index_combination_type polymer_lattice_index_combination 
          = this->translate_index_to_lattice_node_index( polymer_combination_list_orig[icomb], lattice_obj );
        molecule_list_type molecule_list 
          = this->get_molecule_list_from_lattice( polymer_lattice_index_combination, lattice_obj );  // get the molecule list to construct a polymer
        polymer_type polymer( molecule_list );                                                       // initialize the polymer from molecule_list
        // if the center of mass in the polymer are within a radius of Radius from
        // each other, then to add the polymer to the group storage
        if( polymer.within_mean_distance_by_center_of_mass( radius ) == true ) {
          //this->polymer_list_.push_back( polymer );
          //this->polymer_lattice_index_list_.push_back( polymer_lattice_index_combination );
          sub_polymer_list.push_back( polymer );
          sub_polymer_lattice_index_list.push_back( polymer_lattice_index_combination );
        }
        if( thread_id == 0 ) { progress_display++; }
      } // end of loop icomb, all polymers

      sub_polymer_list_addresses[ thread_id ]               = &( sub_polymer_list );
      sub_polymer_lattice_index_list_addresses[ thread_id ] = &( sub_polymer_lattice_index_list );
      #pragma omp barrier

      #pragma omp single
      for( size_t i = 0; i < num_thread; i++ ) {
        this->polymer_list_.insert( this->polymer_list_.end(), sub_polymer_list_addresses[i]->begin(), sub_polymer_list_addresses[i]->end() );
        sub_polymer_list_addresses[i]->clear();
        sub_polymer_list_addresses[i]->shrink_to_fit();
        this->polymer_lattice_index_list_.insert( this->polymer_lattice_index_list_.end(), sub_polymer_lattice_index_list_addresses[i]->begin(), sub_polymer_lattice_index_list_addresses[i]->end() );
        sub_polymer_lattice_index_list_addresses[i]->clear();
        sub_polymer_lattice_index_list_addresses[i]->shrink_to_fit();
      }
    }
    //cout << "Obtained " 
    //     << this->group_storage.size() 
    //     << " unique polymers of " << NUM 
    //     << " within the averaged intermolecular distance of " << Radius << " Angstrom " << endl;
    std :: cout << "Total # of unsorted fragments = " << this->polymer_lattice_index_list_.size() << " with mean distance " << std :: setw(16) << std :: setprecision(11) << radius << std :: endl;
    this->is_initialized_ = true;
    this->system_type_ = LATTICE;
    this->lattice_ptr_ = &lattice_obj;
  }

  void initialize( const bulk_type& bulk_obj, distance_data_type radius ) {
    // cout << "Initializing polymer group from bulk... " << endl;
    // get a list of combination
    polymer_bulk_index_list_type polymer_combination_list_orig
      = iquads :: math :: get_combination<NUM>( bulk_obj.size() );
    // cout << "Found " << n_comb << " unique polymers of " << NUM << " in the molecule bulk " << endl;
    progress_display_type progress_display( "initialize the identifier...", polymer_combination_list_orig.size() );
    for( size_t icomb = 0; icomb < polymer_combination_list_orig.size(); icomb++ ) {
      molecule_list_type molecule_list 
        = this->get_molecule_list_from_bulk( polymer_combination_list_orig[icomb], bulk_obj );  // get the molecule list to construct a polymer
      polymer_type polymer( molecule_list );                                                    // initialize the polymer from molecule_list
      // if the center of mass in the polymer are within a radius of Radius from
      // each other, then to add the polymer to the group storage
      if( polymer.within_mean_distance_by_center_of_mass( radius ) == true ) {
        this->polymer_list_.push_back( polymer );
        this->polymer_bulk_index_list_.push_back( polymer_combination_list_orig[icomb] );
      }
      progress_display++;
    } // end of loop icomb, all polymers
    //cout << "Obtained " 
    //     << this->group_storage.size() 
    //     << " unique polymers of " << NUM 
    //     << " within the averaged intermolecular distance of " << Radius << " Angstrom " << endl;
    this->is_initialized_ = true;
    this->system_type_    = BULK;
    this->bulk_ptr_       = &bulk_obj;
  } // end of init_from_bulk()

  void evaluate_subgroups( fragment_info_list_type& fragment_info_list_ref, electron_calc_setting_type setting ) {
    // std :: cout << "Dividing subgroups by euclidean distance matrix ..." << std :: endl;
    try {
      if( this->is_initialized_ == false ) { throw 1; }

      std :: vector< std :: vector< int > > group_indices;
      group_indices.resize(0);
      {
        std :: vector< matrix_type > eigval_vectors = this->compute_dist_eigval();                     // compute euclidean distance matrix eigenvalues
        // iquads :: matrix :: IMatrixHeap eigpair_boolean_mat = iquads :: matrix :: compute_boolean_mat( eigval_vectors );   // get the ''eigenvalue boolean matrix''
        // group_indices = iquads :: matrix :: get_groups( eigpair_boolean_mat );                         // get the degeneracy structure of the boolean matrix
        std :: vector< std :: map<int, int> > bond_map = iquads :: matrix :: compute_boolean_map( eigval_vectors );
        group_indices = iquads :: matrix :: get_groups( bond_map );
      }
      this->fill_fragment_group( group_indices, fragment_info_list_ref, setting );
    } catch( int signal ) {
      std :: cout << " error: polymer_group object is not initialized " << std :: endl;
      abort();
    }
  }

private:
  std :: vector< matrix_type > compute_dist_eigval() {
    // cout << "Computing eigenvalues of euclidean distance matrices ... " << endl;
    // size_t count_interval = n_polymer_local/5;

    omp_set_dynamic(0);
    const size_t num_thread = omp_get_num_procs();
    omp_set_num_threads( num_thread );
    const size_t total_num = this->polymer_list_.size();
    std :: vector< matrix_type > retval;
    retval.resize( total_num );
    // vector parallizable
    std :: string display_message = std :: string( "Computing eigenvalues of all distance matrix [ openmp, automatic, num_thread = " ) +
                                    std :: to_string( num_thread ) + 
                                    std :: string( " ] ..." );
    progress_display_type progress_display( display_message, total_num/num_thread );
    #pragma omp parallel
    {
      const int thread_id = omp_get_thread_num();
      #pragma omp for
      for( size_t ipolymer = 0; ipolymer < total_num; ipolymer++ ) {
        euclidean_distance_matrix_type edm_local;
        edm_local.compose_from_atomlist( this->polymer_list_[ipolymer].atom_list() ); // construct a local euclidean distance matrix for the polymer
        //edm_local.print_eigval();
        edm_local.diagonalise();                                                      // diagonalise and get the eigenvalues
        retval[ipolymer] = edm_local.eigval();                                        // return the eigval vector for this polymer
        // if( (ipolymer+1) % count_interval == 0 ) {
        //   cout << (ipolymer*100/n_polymer_local + 1) << "%\tcompleted " << endl;
        // }
        if( thread_id == 0 ) { progress_display++; }
      } // end of loop ipolymer
      #pragma omp barrier
    }
    return retval;
  }

  void fill_fragment_group( const std :: vector< std :: vector<int> >& group_indices, fragment_info_list_type& fragment_info_list_obj, electron_calc_setting_type setting ) {
    // std :: cout << "Recording fragment group information ...";
    size_t n_group = group_indices.size();
    fragment_info_list_obj.resize( n_group );
    switch( this->system_type_ ) {
      case( BULK ): {
        progress_display_type progress_display( "Filling fragment group info...", n_group );
        for( size_t igroup = 0; igroup < n_group; igroup++ ) {
          std :: vector<int> polymer_indices_i = group_indices.at(igroup);
          fragment_info_type fragment_info_obj( this->get_signature_of_group_bulk( polymer_indices_i, setting ),
                                                this->extract_molecule_indices_for_group_set_bulk( polymer_indices_i ) );
          fragment_info_list_obj[igroup] = fragment_info_obj;
          progress_display++;
        }
        break;
      }
      case( LATTICE ): {
        omp_set_dynamic(0);
        const size_t num_thread = omp_get_num_procs();
        omp_set_num_threads( num_thread );
//        std :: string display_message = std :: string( "Filling fragment group info [ openmp, automatic, num_thread = " ) + 
//                                        std :: to_string( num_thread ) + 
//                                        std :: string( " ]  for " ) + 
//                                        std :: to_string( n_group ) + 
//                                        std :: string( " prototype fragments ... " );
        std :: string display_message = std :: string( "Filling fragment group info " ) +
                                        std :: string( "for " ) + 
                                        std :: to_string( n_group ) + 
                                        std :: string( " prototype fragments ... " );
        progress_display_type progress_display( display_message, n_group/num_thread );
        //#pragma omp parallel 
        {
          const int thread_id = omp_get_thread_num();
          //#pragma omp for
          for( size_t igroup = 0; igroup < n_group; igroup++ ) {
            std :: vector<int> polymer_indices_i = group_indices.at(igroup);
            fragment_info_type fragment_info_obj( this->get_signature_of_group_lattice( polymer_indices_i, setting ),
                                                  this->extract_molecule_indices_for_group_set_lattice( polymer_indices_i ) );
            fragment_info_list_obj[igroup] = fragment_info_obj;
            if( thread_id == 0 ) progress_display++;
          }
          //#pragma omp barrier
        }
        break;
      }
      default:
        break;
    }
    // std :: cout << " done";
  }

  std :: tuple < polymer_type, matrix_type, double, PolymerReport<NUM> > get_signature_of_group_bulk( std :: vector<int> group_set, electron_calc_setting_type setting ) {
    polymer_type mole_list;
    matrix_type eigval_edm;
    const int prim_index = group_set.at(0);
    polymer_type polymer_prim = this->polymer_list_.at( prim_index );
    double dist = polymer_prim.mean_distance_by_center_of_mass();
    {
      euclidean_distance_matrix_type edm_local;
      edm_local.compose_from_atomlist( polymer_prim.atom_list() );
      edm_local.diagonalise();
      eigval_edm = edm_local.eigval();
    }
    molecular_energy_client_type client;
    molecule_type molecule = iquads :: structure :: convert_polymer_to_molecule< NUM > ( polymer_prim );
    std :: array< int, NUM > prim_indices = this->polymer_bulk_index_list_.at( group_set.at(0) );
    std :: string indices_string = "" ;
    for( size_t i = 0; i < NUM; i++ )
      { indices_string += std :: string( std :: to_string( prim_indices[i] ) + std :: string( "_" ) ); }
    std :: string polymer_name = std :: string ( "fragment_prototype_polymer_bulk_" ) + indices_string; 
    client.driver( std :: make_tuple ( polymer_name, molecule ), setting );
    PolymerReport<NUM> report( client.report().molecule_name(), 
                               client.report().atom_list(),
                               client.report().geometry_unit(),
                               prim_indices,
                               client.report().energy(),
                               0.0e0,
                               client.report().raw(),
                               client.report().raw_external() );
    return std :: make_tuple( polymer_prim, eigval_edm, dist, report );
  }

  std :: tuple < polymer_type, matrix_type, double, PolymerReport<NUM> > get_signature_of_group_lattice( std :: vector<int> group_set, electron_calc_setting_type setting ) {
    polymer_type mole_list;
    matrix_type eigval_edm;
    const int prim_index = group_set.at(0);
    polymer_type polymer_prim = this->polymer_list_.at( prim_index );
    double dist = polymer_prim.mean_distance_by_center_of_mass();
    { 
      euclidean_distance_matrix_type edm_local;
      edm_local.compose_from_atomlist( polymer_prim.atom_list() );
      edm_local.diagonalise(); 
      eigval_edm = edm_local.eigval();
    }
    molecular_energy_client_type client;
    molecule_type molecule = iquads :: structure :: convert_polymer_to_molecule< NUM > ( polymer_prim );
    std :: array< lattice_node_index_type, NUM > prim_indices = this->polymer_lattice_index_list_.at( group_set.at(0) );
    std :: string indices_string = "" ;
    for( size_t i = 0; i < NUM; i++ ) { 
      indices_string += std :: to_string( std :: get<0> ( std :: get<0> ( prim_indices[i] ) ) ) + std :: string( "_" );
      indices_string += std :: to_string( std :: get<1> ( std :: get<0> ( prim_indices[i] ) ) ) + std :: string( "_" );
      indices_string += std :: to_string( std :: get<2> ( std :: get<0> ( prim_indices[i] ) ) ) + std :: string( "_" );
      indices_string += std :: to_string( std :: get<1> ( prim_indices[i] ) ) + std :: string( "__" );
    }
    std :: array< int, NUM > prim_indices_record;
    for( size_t i = 0; i < NUM; i++ ) {
      prim_indices_record[i] = this->lattice_ptr_->translate_lattice_node_index_to_index( prim_indices[i] );
    }
    std :: string polymer_name = std :: string ( "fragment_prototype_polymer_latt_" ) + indices_string;
    client.driver( std :: make_tuple ( polymer_name, molecule ), setting );
    PolymerReport<NUM> report( client.report().molecule_name(), 
                               client.report().atom_list(),
                               client.report().geometry_unit(),
                               prim_indices_record,
                               client.report().energy(),
                               0.0e0,
                               client.report().raw(),
                               client.report().raw_external() );
    // std :: cout << client.report().raw_external().energy_local_run_report_list().size() << std :: endl << std :: flush;
    return std :: make_tuple( polymer_prim, eigval_edm, dist, report );
  }

  std :: vector< std :: array< int, NUM > > extract_molecule_indices_for_group_set_bulk( std :: vector<int> group_set ) {
    std :: vector< std :: array< int, NUM > > retval;
    const size_t n_polymer = group_set.size();
    retval.resize( n_polymer );
    for( size_t ipolymer = 0; ipolymer < n_polymer; ipolymer++ ) {
      std :: array< int, NUM > molecule_indices_orig
        = this->polymer_bulk_index_list_.at( group_set.at(ipolymer) );
      retval[ipolymer] = molecule_indices_orig;
    }
    return retval;
  }

  std :: vector< std :: array< lattice_node_index_type, NUM > > extract_molecule_indices_for_group_set_lattice( std :: vector<int> group_set ) {
    std :: vector< std :: array< lattice_node_index_type, NUM > > retval;
    const size_t n_polymer = group_set.size();
    retval.resize( n_polymer );
    for( size_t ipolymer = 0; ipolymer < n_polymer; ipolymer++ ) {
      std :: array< lattice_node_index_type, NUM > molecule_indices_orig
        = this->polymer_lattice_index_list_.at( group_set.at(ipolymer) );
      retval[ipolymer] = molecule_indices_orig;
    }
    return retval;
  }

private:
  // storage of all the molecular groups with the 
  // same number of molecule within each group
  polymer_list_type polymer_list_;

  // storage of molecule lists for all polymers
  polymer_bulk_index_list_type     polymer_bulk_index_list_;
  polymer_lattice_index_list_type  polymer_lattice_index_list_;

  // whether the object is initialized from the bulk
  bool is_initialized_;
  SystemType system_type_;

  const lattice_type* lattice_ptr_;
  const bulk_type*    bulk_ptr_;

}; // end of struct polymer_group_base

} // end of namespace manybody_expansion

} // end of namespace iquads

#endif
