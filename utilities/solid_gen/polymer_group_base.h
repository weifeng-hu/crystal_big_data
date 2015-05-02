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

#ifndef POLYMER_GROUP_BASE_H
#define POLYMER_GROUP_BASE_H

#include <stdlib.h>
#include <array>
#include "utilities/solid_gen/math_function.h"
#include "utilities/solid_gen/matrix_function.h"
#include "utilities/solid_gen/molecule.h"
#include "utilities/solid_gen/molecule_bulk.h"
#include "utilities/solid_gen/euclidean_distance_matrix.h"
#include "utilities/solid_gen/polymer_base.h"
#include "utilities/solid_gen/fragment_group_info.h"

using namespace std;

namespace iquads {

using namespace iquads :: math;
using namespace iquads :: matrix;
using namespace iquads :: basic;

namespace crystal {

template< size_t NUM >
struct polymer_group_base{
public:
  polymer_group_base(){
   this->group_storage.resize(0);
   this->polymer_combination.resize(0);
   this->frag_group.reset();
   this->n_molecule_per_unit_ = NUM;
   this->bulk_ptr.reset();
   this->is_initialized_ = false;
  }

public:
  void init_from_bulk( shared_ptr< molecule_bulk > new_bulk, double Radius )
  {
   cout << "Initializing polymer group ... " << endl;
   size_t n_mole_local = new_bulk->get_nmolecule();
   // set the local bulk pointer
   this->bulk_ptr = new_bulk;
   // get a list of combination
   vector<array<int, NUM> > polymer_combination_orig = get_combination<NUM>( n_mole_local );
   size_t n_comb = polymer_combination_orig.size();
   cout << "Found " << n_comb << " unique polymers of " << NUM << " in the molecule bulk " << endl;
   for( size_t icomb = 0; icomb < n_comb; icomb++ ){
    // get the molecule list to construct a polymer
    array<int, NUM> list_local = polymer_combination_orig.at(icomb);
    vector<int> list_vec( list_local.begin(), list_local.end() );
    MoleculeList molecule_list = new_bulk->get_molelist_from_list( list_vec );
    // initialize the polymer from molecule_list
    polymer_base<NUM> polymer_x;
    polymer_x.init_from( molecule_list );
    // if the center of mass in the polymer are within a radius of Radius from
    // each other, then to add the polymer to the group storage
    if( polymer_x.within_mean_radius_by_center_of_mass( Radius ) == true ){
     this->group_storage.push_back( polymer_x );
     this->polymer_combination.push_back(list_local);
    }
   } // end of loop icomb, all polymers

   cout << "Obtained " 
        << this->group_storage.size() 
        << " unique polymers of " << NUM 
        << " within the averaged intermolecular distance of " << Radius << " Angstrom " << endl;

   this->is_initialized_ = true;
  } // end of init_from_bulk()

  void evaluate_subgroups()
  {
    cout << "Dividing subgroups by euclidean distance matrix ..." << endl;
    if( this->is_initialized_ == false ){
     cout << " error: polymer_group object is not initialized " << endl;
     abort();
    }

    vector< vector<int> > group_indices;
    group_indices.resize(0);
    {
     // compute euclidean distance matrix eigenvalues
     vector< DMatrixHeap > eigval_vectors = compute_dist_eigval();
     // get the ''eigenvalue boolean matrix''
     IMatrixHeap eigpair_boolean_mat = compute_boolean_mat( &eigval_vectors );
     // get the degeneracy structure of the boolean matrix
     group_indices = get_groups( &eigpair_boolean_mat );
    }
    this->fill_frag_group( group_indices );
  }

public:
  fragment_group_info get_fragment_group_info() const 
   { return this->frag_group; }

private:
  vector< DMatrixHeap > compute_all_edm()
  {
   vector< DMatrixHeap > retval;
   size_t n_polymer_local = this->group_storage.size();
   for( size_t ipolymer = 0; ipolymer < n_polymer_local; ipolymer++ ){
    polymer_base<NUM> polymer_i = group_storage.at(ipolymer);
    euclidean_distance_matrix edm_local;
    {
     AtomList atomlist_i = polymer_i.get_atom_list();
     edm_local.compose_from_atomlist( atomlist_i );
    }
    retval.push_back( edm_local.get_dist_mat() );
   }
   return retval;
  }

  vector< DMatrixHeap > compute_dist_eigval()
  {
   cout << "Computing eigenvalues of euclidean distance matrices ... " << endl;
   vector< DMatrixHeap > retval;
   size_t n_polymer_local = this->group_storage.size();

   size_t count_interval = n_polymer_local/5;

   for( size_t ipolymer = 0; ipolymer < n_polymer_local; ipolymer++ ){
    polymer_base<NUM> polymer_i = group_storage.at(ipolymer);
    // construct a local euclidean distance matrix for the polymer
    euclidean_distance_matrix edm_local;
    {
     // get the atom list for the polymer
     AtomList atomlist_i = polymer_i.get_atom_list();
     // construct a local euclidean distance matrix for the polymer
     edm_local.compose_from_atomlist( atomlist_i );
    }
    // diagonalise and get the eigenvalues
    edm_local.diagonalise();
    // return the eigval vector for this polymer
    retval.push_back( edm_local.get_eigval() );

    if( (ipolymer+1) % count_interval == 0 ){
     cout << (ipolymer*100/n_polymer_local + 1) << "%\tcompleted " << endl;
    }

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
  vector< polymer_base<NUM> > group_storage;

  // storage of molecule lists for all polymers
  vector< array<int, NUM> > polymer_combination;

  // Group of fragment info object
  // to be evaluated by evaluate_subgroup()
  // Each fragment info stores the fragment information
  // for each type of unique fragment
  fragment_group_info frag_group;

  // a copy of the number of molecules in each polymer
  size_t n_molecule_per_unit_;

  // pointer to the molecule bulk, which is stored in
  // an interaction object
  shared_ptr<molecule_bulk> bulk_ptr;

  // whether the object is initialized from the bulk
  bool is_initialized_;

}; // end of struct polymer_group_base

} // end of namespace crystal

} // end of namespace iquads

#endif
