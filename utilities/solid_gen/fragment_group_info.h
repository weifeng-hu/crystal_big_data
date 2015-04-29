#ifndef FRAGMENT_GROUP_INFO
#define FRAGMENT_GROUP_INFO

#include <stdlib.h>
#include <iostream>
#include <memory>
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
   cout << "Fragment Group Info" << endl;
   cout << "{" << endl;
   cout << "number of fragment types: " << this->group_storage.size() << endl;
   cout << "all fragment types:" << endl;
   for( size_t itype = 0; itype < group_storage.size(); itype++ ){
    cout << "Fragment Type " << itype << endl;
    cout << "{" << endl;
    fragment_info fraginfo_local = group_storage.at(itype);
    fraginfo_local.print_info();
    cout << "}" << endl;
   }
   cout << "}" << endl;
  } // end of print_info()

public:
  size_t get_n_mole_per_frag() const 
    { return this->n_molecule_per_fragment_; }

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
