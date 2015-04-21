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
   this->primitive.resize(0);
   this->identical_fragment_list.resize(0);
   this->bulk_ptr.reset();
   this->n_molecule_per_fragment_ = 0;
  } // end of reset()

  void print_info(){
   cout << "Fragment Info" << endl;
   cout << " number of identical fragment: " << this->identical_fragment_list.size() << endl;
   cout << "primitive info:" << endl;
   for( size_t imole = 0; imole < primitive.size(); imole++ ){
    molecule mole_i = primitive.at(imole);
    cout << " Molecule " << imole << endl;
    mole_i.print_info();
   }

   cout << " list of fragments in the bulk: " << endl;
   {
    const size_t n_frag_local = identical_fragment_list.size();
    for( size_t ifrag = 0; ifrag < n_frag_local; ifrag++ ){
     array<int, 100> molecule_tuple_local;
     const size_t n_mole_local = identical_fragment_list.at(ifrag).size();
     // copy the tuple elements to array
     copy_n( identical_fragment_list.at(ifrag).begin(), n_mole_local, molecule_tuple_local.begin() );
     cout << " [";
     for( size_t imole = 0; imole < n_mole_local; imole++ ){
      cout << " " << molecule_tuple_local.at(imole) << " " ;
     } // end of loop imole
     cout << "] ";
     cout << "   ";
     // let's print 5 tupes per line
     if( ( ifrag % 5 ) == 0 ) cout << endl;
    } // end of loop ifrag
   } // end of local scope of list printing
   cout << endl;
  } // end of print_info()

public:
  size_t get_n_mole_per_frag() const { return this->n_molecule_per_fragment_; }
  size_t& set_n_mole_per_frag() { return this->n_molecule_per_fragment_; }

  MoleculeList& set_primitive() { return this->primitive; }
  vector< vector<int> >& set_fragment_list() { return this->identical_fragment_list; }
  shared_ptr<molecule_bulk>& set_bulk_ptr() { return this->bulk_ptr; }

private:
  // stores a primitive fragment ( consisting of multiple molecules )
  MoleculeList primitive;

  // stores the list of molecule indices of this type of fragment
  // in the molecule bulk
  //  e.g., for dimer x = [ mole_a of type_x, mole_b of type_x ]
  //         or a hetergenours fragment type
  //  identical_fragment_list = [ [ 1 5 ] [ 2 6 ] ...  ]
  //  where 1, 5, 2, 6 are individual molecule index in the molecule bulk
  vector< vector<int> > identical_fragment_list;

  size_t n_molecule_per_fragment_;

  // stores a printer to the molecule bulk, pointing to the one in 
  // an interaction object
  shared_ptr<molecule_bulk> bulk_ptr;

}; // end of struct fragment_info

}  // end of namespace crystal

}  // end of namespace iquads

#endif
