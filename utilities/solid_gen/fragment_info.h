#ifndef FRAGMENT_INFO_H
#define FRAGMENT_INFO_H

#include <vector>
#include <tuple>
#include <string>
#include <iostream>
#include <memory>

using namespace std;

namespace iquads {

namespace crystal {

struct fragment_info {

public:
  vector<atom> get_store() const { return this->store_; }
  vector<atom>& set_store(){ return this->store_; }
 
  string get_element ( size_t i ){
   return store_.at(i).get_element();
  }
  tuple< double, double, double > get_coord( size_t i )
  {
   double x = store_.at(i).get_x();
   double y = store_.at(i).get_y();
   double z = store_.at(i).get_z();
   tuple< double, double, double > retval = 
      make_tuple (x, y, z);
   return retval;
  }
  void print_info(){
   cout << "  Fragment Info " << endl;
   for( size_t i = 0; i < store_.size(); i++ ){
    cout << store_.at(i).get_element() << " " << store_.at(i).get_x() << " " << store_.at(i).get_y() << " " << store_.at(i).get_z() << endl;
   }
  }

public:
  MoleculeList& set_primitive() { return this->primitive; }
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
  vector< vector<int> > > identical_fragment_list;
  // stores a printer to the molecule bulk, pointing to the one in 
  // an interaction object
  shared_ptr<molecule_bulk> bulk_ptr;

};

}

}

#endif
