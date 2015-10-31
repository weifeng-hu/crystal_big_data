/*
 *  This source code applies all the terms in 
 *  GNU GENERAL PUBLIC LICENSE (GPL), Version3, 29 June 2007.
 *
 *  Copyright (C) 2013-2015 Weifeng Hu, all rights reserved.
 *  
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef POLYMER_GROUP_TEMPLATE_HPP
#define POLYMER_GROUP_TEMPLATE_HPP

#include <stdlib.h>
#include <array>
#include <manybody_expansion/fragment_identifer/math_function.h>
#include <manybody_expansion/fragment_identifer/matrix_function.h>
#include <structure/molecule.h>
#include <structure/molecule_bulk.h>
#include <manybody_expansion/fragment_identifer/euclidean_distance_matrix.h>
#include <structure/polymer_template.h>
#include <manybody_expansion/fragment_identifer/fragment_group_info.h>

using namespace std;

namespace iquads {

using namespace iquads :: math;
using namespace iquads :: matrix;
using namespace iquads :: basic;

namespace manybody_expansion {

template< size_t NUM > struct FragmentSignatureIdentifier {
public:
  typedef double distance_data_type;
  typedef iquads :: structure :: MolecularLattice lattice_type;
  typedef iquads :: structure :: MolecularBulk    bulk_type;
  typedef iquads :: structure :: Polymer<NUM>     polymer_type;
  typedef std :: array< Molecule >                molecule_list_type;
  typedef std :: vector< polymer_type >           polymer_list_type;

  typedef std :: array< int, NUM >                polymer_bulk_index_combination_type;
  typedef std :: vector< polymer_bulk_index_combination_type >   polymer_bulk_index_list_type;
  typedef std :: tuple< std :: tuple< int, int, int >, int >     lattice_node_index_type;
  typedef std :: array< lattice_node_index_type, NUM >  polymer_lattice_index_combination_type;
  typedef std :: vector< polymer_lattice_index_combination_type >  polymer_lattice_index_list_type;

  typedef iquads :: manybody_expansion :: FragmentInfo fragment_info_type;
  typedef std :: vector< fragment_info_type > fragment_info_list_type;

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
      // get the molecule list to construct a polymer
      molecule_list_type molecule_list 
        = this->get_molecule_list_from_lattice( polymer_combination_list_orig[icomb], lattice_obj );
      polymer_lattice_index_combination_type polymer_lattice_index_combination 
        = this->get_polymer_index_list_from_lattice( polymer_combination_list_orig[icomb], lattice_obj );
      // initialize the polymer from molecule_list
      polymer_type polymer( molecule_list );
      // if the center of mass in the polymer are within a radius of Radius from
      // each other, then to add the polymer to the group storage
      if( polymer.within_mean_radius_by_center_of_mass( Radius ) == true ){
        this->polymer_list_.push_back( polymer );
        this->polymer_lattice_index_list_.push_back( polymer_lattice_index_combination );
      }
    } // end of loop icomb, all polymers
    //cout << "Obtained " 
    //     << this->group_storage.size() 
    //     << " unique polymers of " << NUM 
    //     << " within the averaged intermolecular distance of " << Radius << " Angstrom " << endl;
    this->is_initialized_ = true;
  }

  void initialize( const bulk_type& bulk_obj, distance_data_type radius ) {
    // cout << "Initializing polymer group from bulk... " << endl;
    // get a list of combination
    polymer_bulk_index_list_type polymer_combination_list_orig;
      = iquads :: math :: get_combination<NUM>( bulk_obj.size() );
    // cout << "Found " << n_comb << " unique polymers of " << NUM << " in the molecule bulk " << endl;
    for( size_t icomb = 0; icomb < polymer_combination_list_orig.size(); icomb++ ) {
      // get the molecule list to construct a polymer
      molecule_list_type molecule_list 
        = this->get_molecule_list_from_bulk( polymer_combination_list_orig[icomb], bulk_obj );
      // initialize the polymer from molecule_list
      polymer_type polymer( molecule_list );
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
  } // end of init_from_bulk()

  void evaluate_subgroups( fragment_info_list_type& fragment_info_list_ref ) {
    // cout << "Dividing subgroups by euclidean distance matrix ..." << endl;
    try {
      if( this->is_initialized_ == false ) { throw 1; }

      vector< vector<int> > group_indices;
      group_indices.resize(0);
      {
        // compute euclidean distance matrix eigenvalues
        vector< DMatrixHeap > eigval_vectors = this->compute_dist_eigval();
        // get the ''eigenvalue boolean matrix''
        IMatrixHeap eigpair_boolean_mat = iquads :: math :: compute_boolean_mat( &eigval_vectors );
        // get the degeneracy structure of the boolean matrix
        group_indices = get_groups( &eigpair_boolean_mat );
      }
      this->fill_frag_group( group_indices );
    } catch( int signal ) {
      std :: cout << " error: polymer_group object is not initialized " << std :: endl;
      abort();
    }
  }

public:
  fragment_group_info get_fragment_group_info() const 
    { return this->frag_group; }

private:
  vector< DMatrixHeap > compute_dist_eigval() {
    // cout << "Computing eigenvalues of euclidean distance matrices ... " << endl;
    // size_t count_interval = n_polymer_local/5;
    vector< DMatrixHeap > retval;
    retval.resize( this->polymer_list_.size() );
    // vector parallizible
    for( size_t ipolymer = 0; ipolymer < this->polymer_list_.size(); ipolymer++ ) {
      euclidean_distance_matrix edm_local;
      edm_local.compose_from_atomlist( this->polymer_list_[ipolymer].atom_list() ); // construct a local euclidean distance matrix for the polymer
      edm_local.diagonalise();                                                      // diagonalise and get the eigenvalues
      retval[ipolymer] = edm_local.get_eigval();                                    // return the eigval vector for this polymer
      // if( (ipolymer+1) % count_interval == 0 ) {
      //   cout << (ipolymer*100/n_polymer_local + 1) << "%\tcompleted " << endl;
      // }
    } // end of loop ipolymer
    return retval;
  }

  tuple<MoleculeList, DMatrixHeap, double> get_primitive_info_for_groupset( vector<int> group_set ){
   MoleculeList mole_list;
   DMatrixHeap eigval_edm;
   double dist;
   {
    const size_t prim_index = group_set.at(0);
    polymer_base<NUM> polymer_x = this->group_storage.at( prim_index );
    mole_list = polymer_x.get_group();
    dist = polymer_x.compute_mean_distance_by_center_of_mass();
    {
     euclidean_distance_matrix edm_local;
     AtomList atomlist_i = polymer_x.get_atom_list();
     edm_local.compose_from_atomlist( atomlist_i );
     edm_local.diagonalise();
     eigval_edm = edm_local.get_eigval();
    }
   }
   return make_tuple( mole_list, eigval_edm, dist );
  }

  vector< tuple< vector<int>, int > > extract_mole_indices_for_groupset( vector<int> group_set ){
   vector< tuple< vector<int>, int > > retval;
   const size_t n_polymer = group_set.size();
   for( size_t ipolymer = 0; ipolymer < n_polymer; ipolymer++ ){
    vector<int> molecule_indices_polymer;
    molecule_indices_polymer.resize( this->n_molecule_per_unit_ );
    array<int, NUM> molecule_indices_orig
      = this->polymer_combination.at(group_set.at(ipolymer) );
    copy_n( molecule_indices_orig.begin(), 
            this->n_molecule_per_unit_, 
            molecule_indices_polymer.begin() );
    retval.push_back( make_tuple( molecule_indices_polymer, group_set.at(ipolymer) ) );
   }
   return retval;
  }

  void fill_frag_group( vector< vector<int> > group_indices ){
   cout << "Recording fragment group information ..." ;
   size_t n_group = group_indices.size();
   for( size_t igroup = 0; igroup < n_group; igroup++ ){
    vector<int> polymer_indices_i = group_indices.at(igroup);
    fragment_info fraginfo_local;
    fraginfo_local.set_n_mole_per_frag() = this->n_molecule_per_unit_;
    fraginfo_local.set_bulk_ptr() = this->bulk_ptr;
    fraginfo_local.set_primitive_info() 
      = this->get_primitive_info_for_groupset( polymer_indices_i );
    fraginfo_local.set_fragment_list()
      = this->extract_mole_indices_for_groupset( polymer_indices_i );
    this->frag_group.add_fragment_info( fraginfo_local );
   }
   cout << " done";
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

}; // end of struct polymer_group_base

} // end of namespace manybody_expansion

} // end of namespace iquads

#endif
