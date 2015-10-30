/**
 * @file
 * @author Weifeng Hu
 *
 * @section LICENSE
 *
 * Copyright (C) 2013, 2014, 2015  Weifeng Hu
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @section DESCRIPTION
 *
 *
 */

#ifndef FRAGMENT_GROUP_INFO_TEMPLATE_HPP
#define FRAGMENT_GROUP_INFO_TEMPLATE_HPP

#include <stdlib.h>
#include <tuple>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <structure/lattice_instant.hpp>
#include <structure/bulk_instant.hpp>
#include <manybody_expansion/fragment_info.hpp>

namespace iquads {

namespace manybody_expansion {

template < size_t Order > struct FragmentGroupInfo {
public:
  typedef std :: string lattice_name_type;
  typedef std :: string bulk_name_type;
  typedef iquads :: structure :: MolecularLattice lattice_type;
  typedef iquads :: structure :: MolecularBulk    bulk_type;
  typedef std :: tuple < lattice_name_type, lattice_type > lattice_info_type;
  typedef std :: tuple < bulk_name_type, bulk_type > bulk_info_type;
  typedef iquads :: manybody_expansion :: FragmentInfo< Order > fragment_info_type;
  typedef std :: vector < fragment_info_type > fragment_info_list_type;

public:
  FragmentGroupInfo() {
    this->fragment_info_list_.resize(0);
  }

public:
  void build( lattice_info_type lattice_info ) {

  }
  void build( bulk_info_type bulk_info ) {

  }

public:
  /**
   *  We leave this function to some external module someday
   */
  /*
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
     cout << "List of fragments linking to the center: " << endl;
//    cout << (it->second) << endl;
     (it->second).print_fragment_list();
    }
    cout << "===============================================" << endl;
  }
  */

public:
  friend 
  std :: ostream& operator<< ( std :: ostream& os, const fragment_group_info& fragment_group_obj ) {
    std :: ostream << "Number of fragment types: " << this->size() << std :: endl;
    for( size_t itype = 0; itype < this->size(); itype++ ) {
      fragment_info_type fragment_info_local = fragment_group_obj[itype];
      os << fragment_info_local << std :: endl;
    }
    return os;
  }

public:
  size_t size() const 
    { return this->fragment_info_list_.size(); }
  void push_back( fragment_info_type fragment_info )
    { this->fragment_info_list_.push_back(); }
  fragment_info_type& at( size_t i )
    { return this->fragment_info_list_.at(i); }
  fragment_info_type& operator[] ( size_t i )
    { return this->fragment_info_list_[i]; }

private:
  fragment_info_list_type fragment_info_list_;

}; // end of template struct FragmentGroupInfo

} // end of namespace manybody_expansion

} // end of namespace iquads

#endif
