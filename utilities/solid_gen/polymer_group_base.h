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
   cout << "Initializing polymer group" << endl;
   cout << "Number of monomer per polymer: " << NUM << endl;
   size_t n_mole_local = new_bulk->get_nmolecule();
   cout << "Number of molecules in the bulk: " << n_mole_local << endl;
   // set the local bulk pointer
   this->bulk_ptr = new_bulk;
   // get a list of combination
   vector<array<int, NUM> > polymer_combination_orig = get_combination<NUM>( n_mole_local );
   size_t n_comb = polymer_combination_orig.size();
   cout << "Number of unique polymers of " << NUM << " before cut: " << n_comb << endl;
   for( size_t icomb = 0; icomb < n_comb; icomb++ ){
    // get the molecule list to construct a polymer
    array<int, NUM> list_local = polymer_combination_orig.at(icomb);
    vector<int> list_vec( list_local.begin(), list_local.end() );
    MoleculeList molecule_list = new_bulk->get_molelist_from_list( list_vec );
    // initialize the polymer from molecule_list
    polymer_base<NUM> polymer_x;
    polymer_x.init_from( molecule_list );
    // if all atoms in the polymer are within a radius of Radius from
    // each other, then to add the polymer to the group storage
//    if( polymer_x.within_radius( Radius ) == true ){
//    if( polymer_x.within_mean_radius_by_center_of_mass( Radius ) == true ){
    if( polymer_x.within_mean_radius_by_center( Radius ) == true ){
     this->group_storage.push_back( polymer_x );
     this->polymer_combination.push_back(list_local);
    }
   } // end of loop icomb, all polymers

   this->is_initialized_ = true;
  } // end of init_from_bulk()

  void evaluate_subgroups()
  {
    cout << "Dividing subgroups among " << this->group_storage.size() << " polymer<" << NUM << ">" << endl;
    if( this->is_initialized_ == false ){
     cout << " error: polymer_group object is not initialized " << endl;
     abort();
    }

    vector< vector<int> > group_indices;
    group_indices.resize(0);
    {
     // compute euclidean distance matrix eigenvalues
//     vector< DMatrixHeap > eigval_vectors = this->compute_dist_eigval();
//     cout << "Number of Eigenvalue vectors for this group: " << eigval_vectors.size() << endl;
     vector< DMatrixHeap > edm_all = this->compute_all_edm();
     // get the ''eigenvalue boolean matrix''
     IMatrixHeap eigpair_boolean_mat = compute_boolean_mat( &edm_all, 50.0 );
//     IMatrixHeap eigpair_boolean_mat = compute_boolean_mat( &eigval_vectors );
     // get the degeneracy structure of the boolean matrix
     group_indices = get_groups( &eigpair_boolean_mat );
     cout << "Number of subgroups: " << group_indices.size() << endl;
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
   vector< DMatrixHeap > retval;
   size_t n_polymer_local = this->group_storage.size();
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
//    edm_local.print_eigval();
    // return the eigval vector for this polymer
    retval.push_back( edm_local.get_eigval() );
   } // end of loop ipolymer
   return retval;
  }

  MoleculeList get_primitive_for_groupset( vector<int> group_set ){
   MoleculeList retval;
   {
    const size_t prim_index = group_set.at(0);
    polymer_base<NUM> polymer_x = this->group_storage.at( prim_index );
    retval = polymer_x.get_group();
    euclidean_distance_matrix edm_local;
    AtomList atomlist_i = polymer_x.get_atom_list();
    edm_local.compose_from_atomlist( atomlist_i );
    edm_local.diagonalise();
    DMatrixHeap eigval = edm_local.get_eigval();
    for( size_t i = 0; i < eigval.get_nrow(); i++ ){
     cout << eigval(i,0) << " ";
    }
    cout << endl;
   }
   return retval;
  }

  vector< vector<int> > extract_mole_indices_for_groupset( vector<int> group_set ){
   vector< vector<int> > retval;
   const size_t n_polymer = group_set.size();
   for( size_t ipolymer = 0; ipolymer < n_polymer; ipolymer++ ){
    vector<int> molecule_indices_polymer;
    molecule_indices_polymer.resize( this->n_molecule_per_unit_ );
    array<int, NUM> molecule_indices_orig 
      = this->polymer_combination.at(group_set.at(ipolymer));
    copy_n( molecule_indices_orig.begin(), 
            this->n_molecule_per_unit_, 
            molecule_indices_polymer.begin() );
    retval.push_back( molecule_indices_polymer );
    if( ipolymer==1)
    for( size_t imole = 0; imole < n_molecule_per_unit_; imole++ ){
     (bulk_ptr->get_molecule( molecule_indices_polymer.at(imole)) ).print_info();
    }
   }
   return retval;
  }

  void fill_frag_group( vector< vector<int> > group_indices ){
   size_t n_group = group_indices.size();
   for( size_t igroup = 0; igroup < n_group; igroup++ ){
    for( size_t iset = 0; iset < group_indices.at(igroup).size(); iset++ ){
     const int value = group_indices.at(igroup).at(iset);
     cout << value << "[";
     for( size_t jset = 0; jset < NUM; jset++) cout << this->polymer_combination.at(value).at(jset) << " ";
     cout << "] " ;
    }
    cout << endl;
    fragment_info fraginfo_local;
    fraginfo_local.set_n_mole_per_frag() = this->n_molecule_per_unit_;
    fraginfo_local.set_bulk_ptr() = this->bulk_ptr;
    fraginfo_local.set_primitive() 
      = this->get_primitive_for_groupset( group_indices.at(igroup) );
    fraginfo_local.set_fragment_list()
      = this->extract_mole_indices_for_groupset( group_indices.at(igroup) );
    this->frag_group.add_fragment_info( fraginfo_local );
   }
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
