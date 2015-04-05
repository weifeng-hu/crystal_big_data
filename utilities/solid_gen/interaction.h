#ifndef INTERACTION_H
#define INTERACTION_H

#include <memory>

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
  vector<fragment_info> identify_subgroups( double Radius )
  {
   vector<fragment_info> retval;
   {
    polymer_group_base < NUM > polymer_group;
    share_ptr< molecule_bulk > bulk_ptr_local 
      = shared_ptr< molecule_bulk > ( &(this->bulk) );
    polymer_group.init_from_bulk ( bulk_ptr_local, Radius );
    polymer_group.evaluate_subgroups();
    retval = polymer_group.get_fraglist_info();
   }
   return retval;
  }

public:
  // add a fragment_info object to the list
  void add_fragment_type( fragment_info fraginfo ){
   this->fraginfo_list.push_back();
   this->n_fragtype += 1;
  }

private:
  // a copy of the molecule bulk information
  molecule_bulk bulk;
  // fragment info for all kinds of fragments
  vector< vector< fragment_info > > fraginfo_list;
  // number of fragment types, is size of fraginfo_list
  size_t n_fragtype;
  // a copy of the bulk radius;
  double bulk_radius;
  // a copy of the short range radius
  double short_range_radius;
  // a copy of the long range radius
  double long_range_radius;

};

} // end of namespace iquads

} // end of namespace iquads

#endif
