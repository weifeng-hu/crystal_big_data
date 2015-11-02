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

#include <stdlib.h>
#include <array>
#include <vector>
#include <tuple>
#include <math/combination_computation.hpp>
#include <matrix/matrix_instant.hpp>
#include <matrix/matrix_function.hpp>
#include <structure/molecule.hpp>
#include <structure/polymer_template.h>
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

  typedef iquads :: electron_correlation :: Setting          energy_calc_setting_type;
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
  void initialize( const lattice_type& lattice_obj, distance_data_type radius ) {
    // cout << "Initializing polymer group from bulk... " << endl;
    // get a list of combination
    polymer_bulk_index_list_type polymer_combination_list_orig; 
      = iquads :: math :: get_combination<NUM>( lattice_obj.size() );
    // cout << "Found " << n_comb << " unique polymers of " << NUM << " in the molecule bulk " << endl;
    for( size_t icomb = 0; icomb < polymer_combination_list_orig.size(); icomb++ ) {
      molecule_list_type molecule_list 
        = this->get_molecule_list_from_lattice( polymer_combination_list_orig[icomb], lattice_obj );  // get the molecule list to construct a polymer
      polymer_lattice_index_combination_type polymer_lattice_index_combination 
        = this->get_polymer_index_list_from_lattice( polymer_combination_list_orig[icomb], lattice_obj );
      polymer_type polymer( molecule_list );                                                          // initialize the polymer from molecule_list
      // if the center of mass in the polymer are within a radius of Radius from
      // each other, then to add the polymer to the group storage
      if( polymer.within_mean_radius_by_center_of_mass( Radius ) == true ) {
        this->polymer_list_.push_back( polymer );
        this->polymer_lattice_index_list_.push_back( polymer_lattice_index_combination );
      }
    } // end of loop icomb, all polymers
    //cout << "Obtained " 
    //     << this->group_storage.size() 
    //     << " unique polymers of " << NUM 
    //     << " within the averaged intermolecular distance of " << Radius << " Angstrom " << endl;
    this->is_initialized_ = true;
    this->system_type_ = LATTICE;
  }

  void initialize( const bulk_type& bulk_obj, distance_data_type radius ) {
    // cout << "Initializing polymer group from bulk... " << endl;
    // get a list of combination
    polymer_bulk_index_list_type polymer_combination_list_orig;
      = iquads :: math :: get_combination<NUM>( bulk_obj.size() );
    // cout << "Found " << n_comb << " unique polymers of " << NUM << " in the molecule bulk " << endl;
    for( size_t icomb = 0; icomb < polymer_combination_list_orig.size(); icomb++ ) {
      molecule_list_type molecule_list 
        = this->get_molecule_list_from_bulk( polymer_combination_list_orig[icomb], bulk_obj );  // get the molecule list to construct a polymer
      polymer_type polymer( molecule_list );                                                    // initialize the polymer from molecule_list
      // if the center of mass in the polymer are within a radius of Radius from
      // each other, then to add the polymer to the group storage
      if( polymer.within_mean_radius_by_center_of_mass( Radius ) == true ) {
        this->polymer_list_.push_back( polymer );
        this->polymer_bulk_index_list_.push_back( polymer_combination_list_orig[icomb] );
      }
    } // end of loop icomb, all polymers
    //cout << "Obtained " 
    //     << this->group_storage.size() 
    //     << " unique polymers of " << NUM 
    //     << " within the averaged intermolecular distance of " << Radius << " Angstrom " << endl;
    this->is_initialized_ = true;
    this->system_type_    = BULK;
  } // end of init_from_bulk()

  void evaluate_subgroups( fragment_info_list_type& fragment_info_list_ref, electron_calc_setting_type setting ) {
    // std :: cout << "Dividing subgroups by euclidean distance matrix ..." << std :: endl;
    try {
      if( this->is_initialized_ == false ) { throw 1; }

      std :: vector< std :: vector< int > > group_indices;
      group_indices.resize(0);
      double energy;
      {
        std :: vector< matrix_type > eigval_vectors = this->compute_dist_eigval();                     // compute euclidean distance matrix eigenvalues
        IMatrixHeap eigpair_boolean_mat = iquads :: matrix :: compute_boolean_mat( eigval_vectors );   // get the ''eigenvalue boolean matrix''
        group_indices = iquads :: matrix :: get_groups( eigpair_boolean_mat );                         // get the degeneracy structure of the boolean matrix
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
    std :: vector< matrix_type > retval;
    retval.resize( this->polymer_list_.size() );
    // vector parallizible
    for( size_t ipolymer = 0; ipolymer < this->polymer_list_.size(); ipolymer++ ) {
      euclidean_distance_matrix_type edm_local;
      edm_local.compose_from_atomlist( this->polymer_list_[ipolymer].atom_list() ); // construct a local euclidean distance matrix for the polymer
      edm_local.diagonalise();                                                      // diagonalise and get the eigenvalues
      retval[ipolymer] = edm_local.eigval();                                        // return the eigval vector for this polymer
      // if( (ipolymer+1) % count_interval == 0 ) {
      //   cout << (ipolymer*100/n_polymer_local + 1) << "%\tcompleted " << endl;
      // }
    } // end of loop ipolymer
    return retval;
  }

  void fill_fragment_group( const std :: vector< std :: vector<int> >& group_indices, fragment_info_list_type& fragment_info_list_obj, electron_calc_setting_type setting ) {
    // std :: cout << "Recording fragment group information ..." ;
    size_t n_group = group_indices.size();
    fragment_info_list_obj.resize( n_group );
    switch( this->system_type_ ) {
      case( BULK ):
        for( size_t igroup = 0; igroup < n_group; igroup++ ) {
          std :: vector<int> polymer_indices_i = group_indices.at(igroup);
          fragment_info_type fragment_info_obj( this->get_signature_of_group( polymer_indices_i, setting ),
                                                this->extract_molecule_indices_for_group_set_bulk( polymer_indices_i ) );
          fragment_info_list_obj[igroup] = fragment_info_obj;
        }
        break;
      case( LATTICE ):
        for( size_t igroup = 0; igroup < n_group; igroup++ ) {
          std :: vector<int> polymer_indices_i = group_indices.at(igroup);
          fragment_info_type fragment_info_obj( this->get_signature_of_group( polymer_indices_i, setting ),
                                                this->extract_molecule_indices_for_group_set_lattice( polymer_indices_i ) );
          fragment_info_list_obj[igroup] = fragment_info_obj;
        }
        break;
      default:
        break;
    }
    // std :: cout << " done";
  }

  std :: tuple < polymer_type, matrix_type, double, PolymerReport<NUM> > get_signature_of_group( std :: vector<int> group_set, energy_calc_setting_type setting ) {
    polymer_type mole_list;
    matrix_type eigval_edm;
    double dist;
    {
      const int prim_index = group_set.at(0);
      polymer_type polymer_prim = this->polymer_list_.at( prim_index );
      dist = polymer_x.mean_distance_by_center_of_mass();
      {
        euclidean_distance_matrix_type edm_local;
        edm_local.compose_from_atomlist( polymer_prim.atom_list() );
        edm_local.diagonalise();
        eigval_edm = edm_local.eigval();
      }
    }
    molecular_energy_client_type client;
    molecule_type molecule = iquads :: structure :: convert_polymer_to_molecule< NUM > ( polymer_prim );
    std :: array< int, NUM > prim_indices = array<int, NUM> { 0, 0, 0 }; //this->polymer_bulk_index_list_.at( group_set.at(0) );
    std :: string indices_string = "";
    for( size_t i = 0; i < NUM; i++ )
      { indices_string += ( std :: string( prim_indices[i] ) + std :: string( "_" ) ); }
    std :: string polymer_name = std :: string ( "fragment_prototype_polymer_" ) + indices_string; 
    client.driver( std :: make_tuple ( polymer_name, molecule ), settings );
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

  std :: vector< std :: array< int, NUM > > extract_mole_indices_for_group_set_bulk( std :: vector<int> group_set ) {
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

  std :: vector< std :: array< lattice_node_index_type, NUM > > extract_mole_indices_for_group_set_lattice( std :: vector<int> group_set ) {
    std :: vector< std :: array< int, NUM > > retval;
    const size_t n_polymer = group_set.size();
    retval.resize( n_polymer );
    for( size_t ipolymer = 0; ipolymer < n_polymer; ipolymer++ ) {
      std :: array< lattice_node_index_type, NUM > molecule_indices_orig
        = this->polymer_bulk_index_list_.at( group_set.at(ipolymer) );
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

}; // end of struct polymer_group_base

} // end of namespace manybody_expansion

} // end of namespace iquads

#endif
