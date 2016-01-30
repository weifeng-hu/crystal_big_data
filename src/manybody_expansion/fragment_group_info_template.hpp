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
#include <electron_correlation/setting.hpp>
#include <manybody_expansion/polymer_report_template.hpp>
#include <manybody_expansion/fragment_info_template.hpp>
#include <manybody_expansion/fragment_signature_identifier_template.hpp>

namespace iquads {

namespace manybody_expansion {

template < size_t NUM > struct FragmentGroupInfo {
public:
  typedef FragmentGroupInfo<NUM> this_type;
  typedef double distance_data_type;
  typedef std :: tuple< std :: tuple< int, int, int >, int >  lattice_index_type;
  typedef std :: string lattice_name_type;
  typedef std :: string bulk_name_type;
  typedef iquads :: structure :: MolecularLattice lattice_type;
  typedef iquads :: structure :: MolecularBulk    bulk_type;
  typedef std :: tuple < lattice_name_type, lattice_type > lattice_info_type;
  typedef std :: tuple < bulk_name_type, bulk_type > bulk_info_type;
  typedef iquads :: electron_correlation :: Setting electron_calc_setting_type;
  typedef iquads :: manybody_expansion :: FragmentInfo< NUM > fragment_info_type;
  typedef std :: vector < fragment_info_type > fragment_info_list_type;

public:
  FragmentGroupInfo() {
    this->fragment_info_list_.resize(0);
  }

public:
  void build( const lattice_info_type& lattice_info, distance_data_type radius, electron_calc_setting_type setting ) {
    this->copy_of_lattice = std :: get<1> ( lattice_info );
    iquads :: manybody_expansion :: FragmentSignatureIdentifier< NUM > identifier;
    identifier.initialize( std :: get<1>( lattice_info ), radius );
    identifier.evaluate_subgroups( this->fragment_info_list_, setting );
  }
  void build( const bulk_info_type& bulk_info, distance_data_type radius, electron_calc_setting_type setting ) {
    iquads :: manybody_expansion :: FragmentSignatureIdentifier< NUM > identifier;
    identifier.initialize( std :: get<1>( bulk_info ), radius );
    identifier.evaluate_subgroups( this->fragment_info_list_, setting );
  }

public:
  PolymerReport<NUM> get_report_by_lattice_index( std :: array< lattice_index_type, NUM > lattice_indices ) const {
    for( size_t ifragment_info = 0; ifragment_info < this->fragment_info_list_.size(); ifragment_info++ ) {
      fragment_info_type fragment_info_local = fragment_info_list_[ifragment_info];
      if( fragment_info_local.has_fragment_with_lattice_indices( lattice_indices ) == true ) {
        PolymerReport<NUM> retobj = fragment_info_local.polymer_report();
        return retobj;
      }
    }
    std :: cout << " polymer not found " << std :: endl;
    std :: cout << " polymer info: " << std :: endl;
    std :: cout << " polymer " << NUM << std :: endl;
    for( size_t iind = 0; iind < NUM; iind++ ) {
      std :: cout << " index [ " << iind << " ] " << std :: endl;
      std :: cout << std :: get<0> ( std :: get<0> ( lattice_indices[iind] ) ) << " ";
      std :: cout << std :: get<1> ( std :: get<0> ( lattice_indices[iind] ) ) << " ";
      std :: cout << std :: get<2> ( std :: get<0> ( lattice_indices[iind] ) ) << " ";
      std :: cout << std :: get<1> ( ( lattice_indices[iind] ) ) << " ";
      std :: cout << std :: endl;
    }
    std :: array< iquads :: structure :: Molecule, NUM > molecule_list;
    lattice_type copy_of_lattice_again = this->copy_of_lattice;
    for( size_t i = 0; i < NUM; i++ ) {
      std :: tuple< std :: tuple<int, int, int>, int > ix = lattice_indices[i];
      int a = std :: get <0> ( std :: get<0> ( ix ) );
      int b = std :: get <1> ( std :: get<0> ( ix ) );
      int c = std :: get <2> ( std :: get<0> ( ix ) );
      lattice_type :: unit_cell_type unit_cell = copy_of_lattice_again.at( a, b, c );
      int j = std :: get <1> ( ix );
      iquads :: structure :: Molecule molecule = unit_cell.at(j);
      molecule_list[i] = molecule;
    }
    iquads :: structure :: Polymer<NUM> polymer( molecule_list );
    double dist = polymer.mean_distance_by_center_of_mass();
    std :: cout << " distance center of mass: " << std :: setw(16) << std :: setprecision(11) << dist << std :: endl;
    abort();
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
  std :: ostream& operator<< ( std :: ostream& os, const fragment_info_list_type& fragment_group_obj ) {
    os << "Number of fragment types: " << fragment_group_obj.size() << std :: endl;
    for( size_t itype = 0; itype < fragment_group_obj.size(); itype++ ) {
      fragment_info_type fragment_info_local = fragment_group_obj[itype];
      os << fragment_info_local << std :: endl;
    }
    return os;
  }

  double largest_dimer_intermolecular_distance() {
    double retval = 0.0;
    for( size_t i = 0; i < this->fragment_info_list_.size(); i++ ) {
      fragment_info_type fragment_info = fragment_info_list_[i];
      iquads :: structure :: Polymer<NUM> polymer = fragment_info.prototype_polymer();
      for( size_t ip = 0; ip < NUM; ip++ ) {
        iquads :: structure :: Polymer<1> imonomer = polymer(ip);
        for( size_t jp = 0; jp < ip; jp++ ) {
          iquads :: structure :: Polymer<1> jmonomer = polymer(jp);
          iquads :: structure :: Polymer<2> dimer_ij = imonomer + jmonomer;
          const double current_value = dimer_ij.mean_distance_by_center_of_mass();
          if( current_value > retval ) {
            retval = current_value;
          }
        }
      }
    }
    return retval;
  }

  double largest_trimer_intermolecular_distance() {
    double retval = 0.0;
    for( size_t i = 0; i < this->fragment_info_list_.size(); i++ ) {
      fragment_info_type fragment_info = fragment_info_list_[i];
      iquads :: structure :: Polymer<NUM> polymer = fragment_info.prototype_polymer();
      for( size_t ip = 0; ip < NUM; ip++ ) {
        iquads :: structure :: Polymer<1> imonomer = polymer(ip);
        for( size_t jp = 0; jp < NUM; jp++ ) {
          iquads :: structure :: Polymer<1> jmonomer = polymer(jp);
          for( size_t kp = 0; kp < NUM; kp++ ) {
            iquads :: structure :: Polymer<1> kmonomer = polymer(kp);
            iquads :: structure :: Polymer<3> trimer_ijk = imonomer + jmonomer + kmonomer;
            const double current_value = trimer_ijk.mean_distance_by_center_of_mass();
            if( current_value > retval ) {
              retval = current_value;
            }
          }
        }
      }
    }
    return retval;
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
  lattice_type copy_of_lattice;

}; // end of template struct FragmentGroupInfo

} // end of namespace manybody_expansion

} // end of namespace iquads

#endif
