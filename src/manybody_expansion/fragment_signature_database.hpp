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

#ifndef FRAGMENT_SIGNATURE_DATABASE_HPP
#define FRAGMENT_SIGNATURE_DATABASE_HPP

#include <tuple>
#include <string>
#include <memory>
#include <algorithm>
#include <structure/lattice_instant.hpp>
#include <electron_correlation/setting.hpp>
#include <manybody_expansion/order_mask.hpp>
#include <manybody_expansion/polymer_report_template.hpp>
#include <manybody_expansion/fragment_group_info_template.hpp>

namespace iquads {

namespace manybody_expansion {

template < class T_Parent, class T_Child, size_t X > struct Interface {
public:
  Interface( const T_Parent* input_pointer ) : parent_ptr_ ( input_pointer ) {}
public:
  const T_Child& return_child_ref( size_t i ) const {
  }
private:
  const T_Parent* parent_ptr_;
};

//template < > const FragmentGroupInfo<1>& Interface< FragmentSignatureDataBase, FragmentGroupInfo<1>, 1> :: return_child_ref( size_t i ) const {
// if( i == 1 ) return parent_ptr_->set_child_one_ref();
//}

struct FragmentSignatureDataBase {
public:
  typedef iquads :: electron_correlation :: Setting electron_calc_setting_type;
  typedef std :: tuple< std :: tuple < int, int, int >, int >  lattice_index_type;
  typedef FragmentGroupInfo<1> monomer_signature_database_type;
  typedef FragmentGroupInfo<2> dimer_signature_database_type;
  typedef FragmentGroupInfo<3> trimer_signature_database_type;
  typedef FragmentGroupInfo<4> tetramer_signature_database_type;
  typedef std :: tuple < monomer_signature_database_type, dimer_signature_database_type, trimer_signature_database_type, tetramer_signature_database_type > database_set_type;
  typedef std :: tuple < std :: string, iquads :: structure :: MolecularLattice > lattice_info_type;

public:
  // template < size_t NUM > why explicit instantiation not work for this ?
  void build( order :: order_mask_type order_value, lattice_info_type lattice_info, double radius, electron_calc_setting_type setting ) {
    if( order_value == order :: FOURTH_ORDER ) {
      std :: get<3> ( this->database_set_ ).build( lattice_info, radius, setting );

      double largest_trimer_radius 
               = ( std :: get<3> ( this->database_set_ ) ).largest_trimer_intermolecular_distance();
      std :: get<2> ( this->database_set_ ).build( lattice_info, std :: max ( radius , largest_trimer_radius ), setting );
      double largest_dimer_radius_from_tetramer 
               = std :: max( ( std :: get<3> ( this->database_set_ ) ).largest_dimer_intermolecular_distance(), radius );
      double largest_dimer_radius_from_trimer 
               = std :: max( ( std :: get<2> ( this->database_set_ ) ).largest_dimer_intermolecular_distance(), radius );
      std :: get<1> ( this->database_set_ ).build( lattice_info, std :: max( largest_dimer_radius_from_tetramer, largest_dimer_radius_from_trimer ), setting );

      std :: get<0> ( this->database_set_ ).build( lattice_info, radius, setting );
    }
    else if( order_value == order :: THIRD_ORDER ) {

      std :: get<2> ( this->database_set_ ).build( lattice_info, radius, setting );
    
      double largest_dimer_radius 
               = std :: max( radius, ( std :: get<2> ( this->database_set_ ) ).largest_dimer_intermolecular_distance() );
      std :: get<1> ( this->database_set_ ).build( lattice_info, largest_dimer_radius, setting );

      std :: get<0> ( this->database_set_ ).build( lattice_info, radius, setting );
    }
    else if( order_value == order :: SECOND_ORDER ) {
      std :: get<0> ( this->database_set_ ).build( lattice_info, radius, setting );
      std :: get<1> ( this->database_set_ ).build( lattice_info, radius, setting );
    }
    else if( order_value == order :: FIRST_ORDER ) {
      std :: get<0> ( this->database_set_ ).build( lattice_info, radius, setting );
    }
  }

  template < size_t NUM > PolymerReport<NUM> get_report_by_lattice_index( std :: array< lattice_index_type, NUM > lattice_index ) const {

    //Interface< FragmentSignatureDataBase, FragmentGroupInfo<NUM>, NUM > interface_class(this);
    // Interesting! no matter how I tried, there is no way to use this template to call individual database using different function names;
    // One way is to use storage-address-to-type conversion, such as tuple
    // The other way is to use out-of-class-scope explicit specialization, static and non-static both work, but pay attention to the c-v qualifier for this function
    const FragmentGroupInfo<NUM>& data_ref = std :: get<NUM-1> ( this->database_set_ );
    PolymerReport<NUM> report = data_ref.get_report_by_lattice_index( lattice_index );
    return report;
  }

public:
  database_set_type& set_database_set()
    { return this->database_set_; }
  const database_set_type& set_database_set() const
    { return this->database_set_; }

private:
  database_set_type database_set_;

}; // end of struct FragmentSignatureDataBase

// WHY EXPLICIT INSTANTIATION FAILS
//template <> void FragmentSignatureDataBase :: build<1> ( lattice_info_type lattice_info, double radius, electron_calc_setting_type setting ) {
//  std :: get<0> ( this->database_set_ ).build( lattice_info, radius, setting );
//}
//
//template <> void FragmentSignatureDataBase :: build<2> ( lattice_info_type lattice_info, double radius, electron_calc_setting_type setting ) {
//  std :: get<0> ( this->database_set_ ).build( lattice_info, radius, setting );
//  std :: get<1> ( this->database_set_ ).build( lattice_info, radius, setting );
//}
//
//template <> void FragmentSignatureDataBase :: build<3> ( lattice_info_type lattice_info, double radius, electron_calc_setting_type setting ) {
//  std :: get<2> ( this->database_set_ ).build( lattice_info, radius, setting );
//
//  double largest_dimer_radius = ( std :: get<2> ( this->database_set_ ) ).largest_average_intermolecular_distance();
//  std :: get<1> ( this->database_set_ ).build( lattice_info, largest_dimer_radius, setting );
//
//  std :: get<0> ( this->database_set_ ).build( lattice_info, radius, setting );
//}
//
//template <> void FragmentSignatureDataBase :: build<4> ( lattice_info_type lattice_info, double radius, electron_calc_setting_type setting ) {
//  std :: get<3> ( this->database_set_ ).build( lattice_info, radius, setting );
//
//  double largest_trimer_radius = ( std :: get<3> ( this->database_set_ ) ).largest_average_intermolecular_distance();
//  std :: get<2> ( this->database_set_ ).build( lattice_info, largest_trimer_radius, setting );
//
//  double largest_dimer_radius_from_tetramer = ( std :: get<3> ( this->database_set_ ) ).largest_average_intermolecular_distance();
//  double largest_dimer_radius_from_trimer =   ( std :: get<2> ( this->database_set_ ) ).largest_average_intermolecular_distance();
//  std :: get<1> ( this->database_set_ ).build( lattice_info, std :: max( largest_dimer_radius_from_tetramer, largest_dimer_radius_from_trimer ), setting );
//
//  std :: get<0> ( this->database_set_ ).build( lattice_info, radius, setting );
//}
// just a test
// template <> PolymerReport<1> FragmentSignatureDataBase :: get_report_by_lattice_index( std :: array< lattice_index_type, 1 > lattice_index ) const {
// }

} // end of namespace manybody_expansion

} // end of namespace iquads

#endif
