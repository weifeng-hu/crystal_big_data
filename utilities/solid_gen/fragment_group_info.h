#ifndef FRAGMENT_GROUP_INFO
#define FRAGMENT_GROUP_INFO

#include <stdlib.h>
#include <iostream>
#include <memory>
#include <map>
#include "utilities/solid_gen/fragment_info.h"

using namespace std;

namespace iquads {

namespace crystal {

struct fragment_group_info {
public:
  fragment_group_info(){
   this->reset();
  }
  fragment_group_info( shared_ptr<molecule_bulk> new_bulk_ptr ){
   this->reset();
   this->bulk_ptr = new_bulk_ptr;
  }

public:
  void reset()
  {
   this->group_storage.resize(0);
   this->n_molecule_per_fragment_ = 0;
   this->bulk_ptr.reset();
  }

  void print_info()
  {
   cout << "Number of fragment types: " << this->group_storage.size() << endl;
   for( size_t itype = 0; itype < group_storage.size(); itype++ ){
    fragment_info fraginfo_local = group_storage.at(itype);
    fraginfo_local.print_info();
   }
  } // end of print_info()

  void print_summary()
  {
   cout << "Number of fragment types: " << this->group_storage.size() << endl;
   multimap< double, fragment_info > frag_ordered_map;
   for( size_t itype = 0; itype < group_storage.size(); itype++ ){
    fragment_info frag_local = group_storage.at(itype);
    double dist = frag_local.get_avg_intm_dist();
    pair< double, fragment_info > pair_i = make_pair( dist, frag_local );
    frag_ordered_map.insert( pair_i );
   }

   int count = 0;
   cout << "===============================================" << endl;
   for( multimap< double, fragment_info> :: iterator it = frag_ordered_map.begin(); 
        it != frag_ordered_map.end(); 
        it++ ){
    if( count !=0 )cout << "-----------------------------------------------" << endl;
    cout << "Fragment " << ++count << endl;
    cout << "Averaged intermolecular distance: " << fixed << setw(4) << setprecision(2) << it->first << endl;
   }
   cout << "===============================================" << endl;
  }

  friend 
  ostream& operator<< ( ostream& os, fragment_group_info& frag_group ){
   const size_t n_member = frag_group.set_store().size();
   for( size_t itype = 0; itype < n_member; itype++ ){
    fragment_info fraginfo_local = frag_group.set_store().at(itype);
    os << fraginfo_local << endl;
   }
   return os;
  }

public:
  size_t get_n_mole_per_frag() const 
   { return this->n_molecule_per_fragment_; }
  vector<fragment_info>& set_store()
   { return this->group_storage; }

public:
  void add_fragment_info( fragment_info fraginfo ){
   try{
    size_t n_mole_in_frag = fraginfo.get_n_mole_per_frag();
    if( this->n_molecule_per_fragment_ == 0 ){
     this->n_molecule_per_fragment_ = n_mole_in_frag;
    }
    else{
     if( n_mole_in_frag != this->n_molecule_per_fragment_ ){
      throw n_mole_in_frag;
     }
    } // end of the block setting n_molecule_per_fragment_
    this->group_storage.push_back( fraginfo );
   }
   catch( size_t n ){
    cout << " fragment_info_group exception: " << endl;
    cout << "  different n_molecule_per_fragment " << endl;
    cout << "  input: " << n << "   this:" << this->n_molecule_per_fragment_ << endl;
    abort();
   }
  } // end of add_fragment_info() 

private:
  vector< fragment_info > group_storage;
  size_t n_molecule_per_fragment_;
  shared_ptr<molecule_bulk> bulk_ptr;

}; // end of struct fragment_group_info

} // end of namespace crystal

} // end of namespace iquads

#endif
