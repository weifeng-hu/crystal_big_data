#ifndef INTERACTION_H
#define INTERACTION_H

#include <iostream>
#include <memory>
#include "utilities/solid_gen/fragment_group_info.h"

using namespace std;

namespace iquads {

namespace crystal {

struct interaction {
public:
  interaction(){
   this->fraginfo_list.resize(0);
   this->n_fragtype = 0;
   this->bulk_radius = 0.0e0;
   this->short_range_radius = 0.0e0;
   this->long_range_radius = 0.0e0;
  }

public:
  template< size_t NUM >
  fragment_group_info identify_subgroups( double Radius )
  {
   fragment_group_info retval;
   {
    polymer_group_base < NUM > polymer_group;
    share_ptr< molecule_bulk > bulk_ptr_local 
      = shared_ptr< molecule_bulk > ( &(this->bulk) );
    polymer_group.init_from_bulk ( bulk_ptr_local, Radius );
    polymer_group.evaluate_subgroups();
    retval = polymer_group.get_fragment_group_info();
   }
   return retval;
  }

public:
  // add a fragment_info object to the list
  void add_fragment_group( fragment_group_info fraggroup ){
   this->fragment_group_list.push_back( fraggroup );
   this->n_fragtype += 1;
  }

public:
  void print_fragment_groups(){
   cout << "Fragment Groups" << endl;
   cout << " number of fragment groups: " << this->n_fraggroup << endl;
   cout << endl;
   for( size_t igroup = 0; igroup < this->n_fraggroup; igroup++ ){
    cout << "Fragment Group " << igroup << endl;
    fragment_group_info frag_group_local 
      = this->fragment_group_list.at(igroup);
    frag_group_local.print_info();
   }
  } // end of print_fragment_groups() 

private:
  // a copy of the molecule bulk information
  molecule_bulk bulk;
  // fragment info for all kinds of fragment groups
  vector< fragment_group_info > fragment_group_list;
  // number of fragment groups, is size of fraginfo_list
  size_t n_fraggroup;
  // a copy of the bulk radius;
  double bulk_radius;
  // a copy of the short range radius
  double short_range_radius;
  // a copy of the long range radius
  double long_range_radius;

}; // end of struct interaction

} // end of namespace iquads

} // end of namespace iquads

#endif