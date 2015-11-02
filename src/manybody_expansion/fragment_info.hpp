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

#ifndef FRAGMENT_INFO_TEMPLATE_HPP
#define FRAGMENT_INFO_TEMPLATE_HPP

#include <array>
#include <vector>
#include <tuple>
#include <string>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <matrix/matrix_instant.hpp>
#include <structure/molecule.hpp>
#include <structure/polymer_template.hpp>
#include <structure/lattice_instant.hpp>
#include <structure/bulk_instant.hpp>

namespace iquads {

namespace manybody_expansion {

template < size_t NUM > struct FragmentInfo {
public:
  typedef iquads :: matrix :: DMatrixHeap  eigenvalue_container_type;
  typedef iquads :: structure :: Polymer   polymer_template;
  typedef double distance_data_type;
  typedef iquads :: manybody_expansion :: PolymerReport<NUM>  polymer_report_type;
  typedef std :: tuple< polymer_template<NUM>, eigenvalue_container_type, distance_data_type, polymer_report_type >  signature_data_type;
  typedef std :: tuple< int, int, int >                       unit_cell_index_type;
  typedef std :: tuple< unit_cell_index_type, int >           lattice_node_index_type;
  typedef std :: array< lattice_node_index_type, NUM >        lattice_fragment_composition_type;
  typedef std :: vector< lattice_fragment_composition_type >  lattice_identical_fragment_list_type;
  typedef std :: array< int, NUM >                            bulk_fragment_composition_type;
  typedef std :: vector< bulk_fragment_composition_type >     bulk_identical_fragment_list_type;

public:
  FragmentInfo() {
    this->lattice_identical_fragment_list_.resize(0);
    this->bulk_identical_fragment_list_.resize(0);
  }

  FragmentInfo( signature_data_type signature_data, 
                const lattice_identical_fragment_list_type& lattice_identical_fragment_list_obj ) 
    signature_ ( signature_data ),
    lattice_identical_fragment_list_ ( lattice_identical_fragment_list_obj )
    { this->bulk_identical_fragment_list_.resize(0); }

  FragmentInfo( signature_data_type signature_data, 
                const bulk_identical_fragment_list_type& bulk_identical_fragment_list_obj )
    signature_ ( signature_data ), 
    bulk_identical_fragment_list_ ( bulk_identical_fragment_list_obj )
    { this->lattice_identical_fragment_list_.resize(0); }

  /*  we will let some external module to treat these printing methods
public:
  void print_info(){
   cout << "Number of symmetry-equivalent fragments: "
        << this->identical_fragment_list.size() << endl;
   cout << "Primitive info:" << endl;
   {
     MoleculeList mole_list_local = get<0>( this->primitive_info );
     const size_t n_mole_local = mole_list_local.size();
     for( size_t imole = 0; imole < n_mole_local; imole++ ){
      molecule mole_i = mole_list_local.at(imole);
      mole_i.print_info();
     }
   }

   {
    DMatrixHeap eigval_edm = get<1>( primitive_info );
    for( size_t ival = 0; ival < eigval_edm.get_nrow(); ival++ ){
     cout << eigval_edm( ival, 0 ) << " ";
    }
    cout << endl;
   }

   cout << "Averaged intermolecular distance: "
        << get<2>( primitive_info ) << " Angstrom" << endl;

   cout << "List of fragments in the bulk: " << endl;
   {
    const size_t n_frag_local = this->identical_fragment_list.size();
    for( size_t ifrag = 0; ifrag < n_frag_local; ifrag++ ){
     tuple< vector<int>, int > list_i 
      = this->identical_fragment_list.at(ifrag);
     {
      const int ind_frag_local = get<1>( list_i );
      cout << ind_frag_local << ": ";
     }

     {
      vector<int> ind_mole_local = get<0>( list_i );
      array<int, 100> molecule_tuple_local;
      const size_t n_mole_local = ind_mole_local.size();
      // copy the tuple elements to array
      copy_n( ind_mole_local.begin(), n_mole_local, molecule_tuple_local.begin() );
      cout << "<";
      for( size_t imole = 0; imole < n_mole_local; imole++ ){
       cout << molecule_tuple_local.at(imole);
       if( imole != n_mole_local -1 ) cout<< "-";
      } // end of loop imole
      cout << ">";
      cout << "\t";
     }
     if( (ifrag+1) % 5 == 0 ) cout << endl;
    } // end of loop ifrag
   } // end of local scope of list printing
   cout << endl;
  } // end of print_info()

  friend 
  ostream& operator<< ( ostream& os, fragment_info& frag ){
   {
   //
  //   MoleculeList mole_list_local = get<0>( frag.set_primitive_info() );
  //   const size_t n_mole_local = mole_list_local.size();
  //   for( size_t imole = 0; imole < n_mole_local; imole++ ){
  //    molecule mole_i = mole_list_local.at(imole);
  //    os << mole_i << endl;
  //   }
  //

     for( size_t iset = 0; iset < frag.set_fragment_list().size(); iset++ ){
      vector<int> mole_list_local = get<0>( frag.set_fragment_list().at(iset) );
      int icomb = get<1>( frag.set_fragment_list().at(iset) );
      os << "  member " << iset << " combination id " << icomb << endl;
      for( size_t imole = 0; imole < mole_list_local.size(); imole++ ){
       size_t mole_id = mole_list_local.at(imole);
       molecule mole_i = (frag.set_bulk_ptr())->get_molecule(mole_id);
       os << "      molecule " << mole_id << endl << mole_i << endl;
      }
     }
//   }

//   {
//    DMatrixHeap eigval_edm = get<1>( frag.set_primitive_info() );
//    os << eigval_edm << endl;
//   }
//   os << "Averaged intermolecular distance: "
//        << get<2>( frag.set_primitive_info() ) << " Angstrom" << endl;
  
   return os;
  }

  void print_fragment_list(){

   vector< vector<int> > list;
   int center_molecule = (this->bulk_ptr)->get_central_molecule();
   const size_t n_frag = this->identical_fragment_list.size();
   for( size_t ifrag = 0; ifrag < n_frag; ifrag++ ){
    tuple< vector<int>, int > frag_local = this->identical_fragment_list.at(ifrag);
    vector<int> mole_list = get<0>( frag_local );
    int comb_ind = get<1>( frag_local );
    for( size_t imole = 0; imole < mole_list.size(); imole++ ){
     const int ind = mole_list.at(imole);
     if( ind == center_molecule ){
      list.push_back( mole_list );
      break;
     }
    }
   }

//   {
//    DMatrixHeap eigval_edm = get<1>( set_primitive_info() );
//    cout << eigval_edm << endl;
//   }
   cout << "weight factor: " << list.size() << endl;

   array<int, 3> origin_vec 
    = ( (this->bulk_ptr)->get_molecule( center_molecule ) ).set_translation_vec();
   for( size_t ilist = 0; ilist < list.size(); ilist++ ){
    vector<int> list_local = list.at(ilist);
//    cout << "[ ";
    cout << " polymer " << ilist << ": " << endl;
    for( size_t imole = 0; imole < list_local.size(); imole++ ){
     cout << list_local.at(imole) << ": ";
     {
      molecule mole_i = (this->bulk_ptr)->get_molecule( list_local.at(imole) );
      cout << mole_i << endl;
      array<int, 3> mole_vec = mole_i.set_translation_vec();
      array<int, 3> relative_vec 
       = array<int, 3>{ mole_vec.at(0) - origin_vec.at(0), 
                        mole_vec.at(1) - origin_vec.at(1),
                        mole_vec.at(2) - origin_vec.at(2) };
      string mole_name = mole_i.get_name();
      const Coord center_of_mass = mole_i.get_center_of_mass();
      array< double, 3 > xyz_local = array<double, 3> { get<0>(center_of_mass),
                                                 get<1>(center_of_mass),
                                                 get<2>(center_of_mass) };
      array< double, 3 > nvec = ((this->bulk_ptr)->get_constants()).compute_coeffs_of_abc( xyz_local );
      cout << " center of mass " << fixed << setw(4) << setprecision(2) << nvec.at(0) << "a + " << nvec.at(1) << "b + " << nvec.at(2) << "c " << endl;
//      cout << mole_name << " < " << relative_vec.at(0) << "a + " << relative_vec.at(1) << "b + " << relative_vec.at(2) << "c >";
     }
     cout << endl; 
//     cout << "    ";
    }
//    cout << "]" << endl;
    for( size_t imole = 0; imole < list_local.size(); imole++ ){
     for( size_t jmole = imole + 1; jmole < list_local.size(); jmole++ ){
      molecule mole_i = (this->bulk_ptr)->get_molecule( list_local.at(imole) );
      molecule mole_j = (this->bulk_ptr)->get_molecule( list_local.at(jmole) );
      const Coord center_of_mass_i = mole_i.get_center_of_mass();
      const Coord center_of_mass_j = mole_j.get_center_of_mass();
      double distance = compute_distance( center_of_mass_i, center_of_mass_j );
      cout << " distance: " << list_local.at(imole) << " <-> " << list_local.at(jmole) << " : " << distance << endl;
     } 
    }
    cout << endl;
   }

   cout << endl;
  }
  */

public:
  bool has_fragment_with_lattice_indices( lattice_fragment_composition_type lattice_index ) {
    for( size_t i = 0; i < this->lattice_identical_fragment_list_.size(); i++ ) {
      const lattice_node_index_type lattice_node_index = this->lattice_identical_fragment_list_[i];
      for( size_t j = 0; j < NUM; j++ ) {
        if( std :: find( std :: begin( lattice_node_index ), 
                         std :: end( lattice_node_index ),
                         lattice_index[j] ) == std :: end( lattice_node_index ) ) return false;
      }
    }
  }

public:
  signature_data_type signature() const
    { return this->signature_; }
  polymer_template<NUM> prototype_polymer() const
    { return std :: get<0>( this->signature_ ); }
  eigenvalue_container_type eigenvalues() const
    { return std :: get<1>( this->signature_ ); }
  distance_data_type average_intermolecular_distance() const
    { return std :: get<2>( this->signature_ ); }
  polymer_report_type polymer_report() const
    { return std :: get<3>( this->signature_ ); }
  bulk_fragment_composition_type prototype_bulk_fragment_composition() const 
    { return this->bulk_identical_fragment_list_.begin(); }
  bulk_identical_fragment_list_type bulk_identical_fragment_list()
    { return this->bulk_identical_fragment_list_; }
  lattice_fragment_composition_type prototype_lattice_fragment_composition() const
    { return this->lattice_identical_fragment_list_.begin(); }
  lattice_identical_fragment_list_type lattice_identical_fragment_list()
    { return this->lattice_identical_fragment_list_; }

private:
  // stores a primitive fragment signature ( consisting of multiple molecules )
  signature_data_type signature_;

  // NEED TO REWRITE THE COMMENT
  // stores the list of molecule indices of this type of fragment
  // in the molecule bulk
  //  e.g., for dimer x = [ mole_a of type_x, mole_b of type_x ]
  //         or a hetergenours fragment type
  //  identical_fragment_list = [ [ 1 5 ] [ 2 6 ] ...  ]
  //  where 1, 5, 2, 6 are individual molecule index in the molecule bulk
  bulk_identical_fragment_list_type   bulk_identical_fragment_list_;

  // also for the molecular lattice case
  lattice_identical_fragment_list_type  lattice_identical_fragment_list_;

}; // end of template struct FragmentInfo

}  // end of namespace manybody_expansion

}  // end of namespace iquads

#endif
