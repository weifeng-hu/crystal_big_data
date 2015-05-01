#ifndef FRAGMENT_INFO_H
#define FRAGMENT_INFO_H

#include <vector>
#include <tuple>
#include <string>
#include <iostream>
#include <algorithm>
#include <memory>
#include "utilities/solid_gen/molecule.h"
#include "utilities/solid_gen/molecule_bulk.h"

using namespace std;

namespace iquads {

namespace crystal {

struct fragment_info {
public:
  fragment_info(){
   this->reset();
  }

public:
  void reset(){
   this->identical_fragment_list.resize(0);
   this->bulk_ptr.reset();
   this->n_molecule_per_fragment_ = 0;
  } // end of reset()

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
     MoleculeList mole_list_local = get<0>( frag.set_primitive_info() );
     const size_t n_mole_local = mole_list_local.size();
     for( size_t imole = 0; imole < n_mole_local; imole++ ){
      molecule mole_i = mole_list_local.at(imole);
      os << mole_i << endl;
     }
   }

   {
    DMatrixHeap eigval_edm = get<1>( frag.set_primitive_info() );
    os << eigval_edm << endl;
   }
   os << "Averaged intermolecular distance: "
        << get<2>( frag.set_primitive_info() ) << " Angstrom" << endl;
  
   return os;
  }

public:
  size_t  get_n_mole_per_frag() const
   { return this->n_molecule_per_fragment_; }
  size_t& set_n_mole_per_frag()
   { return this->n_molecule_per_fragment_; }

  tuple< MoleculeList, DMatrixHeap, double >& set_primitive_info() 
   { return this->primitive_info; }
  vector< tuple< vector<int>, int > >& set_fragment_list()
   { return this->identical_fragment_list; }
  shared_ptr<molecule_bulk>& set_bulk_ptr()
   { return this->bulk_ptr; }

  double get_avg_intm_dist() const 
   { return get<2>( this->primitive_info ); }

private:
  // stores a primitive fragment ( consisting of multiple molecules )
  tuple< MoleculeList, DMatrixHeap, double > primitive_info;

  // NEED TO REWRITE THE COMMENT
  // stores the list of molecule indices of this type of fragment
  // in the molecule bulk
  //  e.g., for dimer x = [ mole_a of type_x, mole_b of type_x ]
  //         or a hetergenours fragment type
  //  identical_fragment_list = [ [ 1 5 ] [ 2 6 ] ...  ]
  //  where 1, 5, 2, 6 are individual molecule index in the molecule bulk
  vector< tuple< vector<int>, int > > identical_fragment_list;

  size_t n_molecule_per_fragment_;

  // stores a printer to the molecule bulk, pointing to the one in 
  // an interaction object
  shared_ptr<molecule_bulk> bulk_ptr;

}; // end of struct fragment_info

}  // end of namespace crystal

}  // end of namespace iquads

#endif
