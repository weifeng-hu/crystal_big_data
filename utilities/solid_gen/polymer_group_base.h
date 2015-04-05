#ifndef POLYMER_GROUP_BASE
#define POLYMER_GROUP_BASE

#include <stdlib.h>
#include "utilities/solid_gen/math_function.h"
#include "utilities/solid_gen/molecule.h"
#include "utilities/solid_gen/polymer_base.h"
#include "utiltiies/solid_gen/matrix_function.h"

namespace iquads {

using namespace iquads :: math;
using namespace iquads :: matrix;

namespace crystal {

template< size_t NUM >
struct polymer_group_base{
public:
  polymer_group_base(){
   this->group_storage.resize(0);
   this->fraginfo_list.resize(0);
   this->n_molecule_per_unit = NUM;
   this->bulk_ptr.reset();
   this->is_initialized_ = false;
  }

public:
  void init_from_bulk( shared_ptr< molecule_bulk > new_bulk, double Radius )
  {
   size_t n_mole_local = new_bulk->get_nmolecule();
   // set the local bulk pointer
   this->bulk_ptr = new_bulk;
   // get a list of combination
   this->polymer_combination = get_combination<NUM>( n_mole_local );

   size_t n_comb = polymer_combination.size();
   for( size_t icomb = 0; icomb < n_comb; icomb++ ){
    array<int, NUM> list_local = this->polymer_combination.at(icomb);
    // get the molecule list to construct a polymer
    MoleculeList molecule_list;
    for( size_t imole = 0; imole < n_comb; icomb++ ){
     const int index_mole = list_local.at(imole);
     const molecule mole_i = new_bulk->get_molecule(index_mole);
     molecule_list.push_back(mole_i);
    } // end of loop imole, a single polymer
    polymer_base<NUM> polymer_x;
    // initialize the polymer from molecule_list
    polymer_x.init_from( molecule_list );
    // if all atoms in the polymer are within a radius of Radius from
    // each other, then to add the polymer to the group storage
    if( polymer_x.within_radius( Radius ) == true ){
     this->group_storage.push_back( polymer_x );
    }
   } // end of loop icomb, all polymers

   this->is_initialized_ = true;

  } // end of init_from_bulk()

  void evaluate_subgroups()
  {
    if( this->is_initialize() == false ){
     cout << " error: polymer_group object is not initialized " << endl;
     abort();
    }

    vector< vector<int> > group_indices;
    group_indices.resize(0);
    {
     // compute euclidean distance matrix eigenvalues
     vector< DMatrixHeap > eigval_vectors = this->compute_dist_eigval();
     // get the ''eigenvalue boolean matrix''
     DMatrixHeap eigval_boolean_mat = compute_boolean_mat( eigval_vectors );
     // get the degeneracy structure of the boolean matrix
     group_indices = get_degeneracy_struct( eigval_boolean_mat );
    }

    // fill the fragment info
    for( size_t igroup = 0; igroup < group_indices.size(); igroup++ ){
     fragment_info fraginfo_i;
     fraginfo_i.set_bulk_ptr() = this->bulk_ptr;
     int primitive_index = group_indices[igroup].at(0);
     polymer_base< NUM > polymer_x = this->group_storage.at(primitive_index);
     MoleculeList molecule_list_local = polymer_x.get_group();
     fraginfo_i.set_primitive() = molecule_list_local;
     vector<int> subgroup_indices = group_indices.at(igroup);
     for( size_t isubgroup = 0; isubgroup < subgroup_indices.size(); isubgroup++ ){
      int index_i = subgroup_indices.at(i);
      array< int, NUM > molecule_indices = this->polymer_combination.at(index_i);
      vector<int> temp_vec;
      temp_vec.resize( NUM );
      copy_n( molecule_indices.begin(), NUM, temp_vec.begin() );
      fraginfo_i.set_fragment_list() = temp_vec;
     }
     this->fraginfo_list.push_back(fraginfo_i);
    }
  }

public:
  vector<fragment_info> get_fragment_info_list() const 
   { return this->fraginfo_list; }

private:
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
     edm_local.compose_from_atomlist( atom_list_i );
    }
    // diagonalise and get the eigenvalues
    edm_local.diagonalise();
    // return the eigval vector for this polymer
    retval.push_back( edm_local.get_eigval() );
   } // end of loop ipolymer
   return retval;
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
  vector<fragment_info> fraginfo_list;

  // a copy of the number of molecules in each polymer
  size_t n_molecule_per_unit;

  // pointer to the molecule bulk, which is stored in
  // an interaction object
  shared_ptr<molecule_bulk> bulk_ptr;

  // whether the object is initialized from the bulk
  bool is_initialized_;

}; // end of struct polymer_group_base

} // end of namespace crystal

} // end of namespace iquads

#endif
