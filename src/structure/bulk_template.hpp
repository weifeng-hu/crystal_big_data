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

#ifndef BULK_TEMPLATE_HPP
#define BULK_TEMPLATE_HPP

#include <utility>
#include <vector>
#include <tuple>
#include <map>
#include <geometrical_space/coordinate.hpp>
#include <geometrical_space/threed_space.hpp>
#include <geometrical_space/threed_space_function.hpp>
#include <structure/unit_cell_template.hpp>
#include <structure/lattice_template.hpp>

namespace iquads {

namespace structure {

using std :: vector;
using std :: tuple;
using std :: pair;
using std :: make_tuple;
using std :: multimap;
using namespace iquads :: geometrical_space;

  /**
   *  A templated class for a particle bulk
   *  Compared to the Lattice template class, a bulk object doesn't hold
   *  any information about periocidity, therefore applies to any sort 
   *  of finite system. We use keywork class to tell that this object 
   *  will be sort of an entity rather than volatile POD.
   *
   *  As a payoff, any bulk object is an actual massive container of 
   *  its nodes, can be molecule, atom, ions, polymers, etc. Therefore it 
   *  eats a lot of memory (in heap) thus will produce some sort of memory overhead.
   *
   *  At the implementation level, all these node type classes must share
   *  the same interface, i.e., overloaded functions to ensure the general use 
   *  of this bulk template. This is similar to Lattice nodes.
   *
   *  Data members of this class are:
   *  + a list of nodes, actual storage
   *  + a flag to tell whether it is filled.
   */

template < class Node_Type > class Bulk {
public:
  typedef Bulk< Node_Type >       this_type;
  typedef vector< Node_Type >     node_list_type;
  typedef coord_value_type        coordinate_value_type;
  typedef CartesianCoordinate3D   coordinate_type;
  typedef Interval                interval_data_type;
  typedef Interval3D              interval_set_type;
  typedef array<double, 3>        threed_vector_type;
  typedef size_t size_type;
  typedef bool condition_type;

public:
  /**
   *  The default constructor ensures that everything is not set.
   */
  Bulk() {
    this->node_list_.resize(0);
    this->is_filled_ = false;
  }
  /**
   *  We use external (possibly overloaded) functions to convert an other object 
   *  to a Bulk.
   */

public:
  /**
   *  Coordinate-related functions
   */

  /**
   *  + edges()
   *    Return edges of a Bulk
   */
  interval_set_type edges() const {
    coordinate_value_type x_plus  = get<0>( get<0>( this->node_list_[0].edges() ) );
    coordinate_value_type x_minus = get<1>( get<0>( this->node_list_[0].edges() ) );
    coordinate_value_type y_plus  = get<0>( get<1>( this->node_list_[0].edges() ) );
    coordinate_value_type y_minus = get<1>( get<1>( this->node_list_[0].edges() ) );
    coordinate_value_type z_plus  = get<0>( get<2>( this->node_list_[0].edges() ) );
    coordinate_value_type z_minus = get<1>( get<2>( this->node_list_[0].edges() ) );
    for( size_t inode = 0; inode < this->node_list_.size(); inode++ ) {
      interval_set_type edges_node = this->node_list_.at(inode).edges();
      coordinate_value_type new_x_plus  = get<0>( get<0>( this->node_list_[inode].edges() ) );
      coordinate_value_type new_x_minus = get<1>( get<0>( this->node_list_[inode].edges() ) );
      coordinate_value_type new_y_plus  = get<0>( get<1>( this->node_list_[inode].edges() ) );
      coordinate_value_type new_y_minus = get<1>( get<1>( this->node_list_[inode].edges() ) );
      coordinate_value_type new_z_plus  = get<0>( get<2>( this->node_list_[inode].edges() ) );
      coordinate_value_type new_z_minus = get<1>( get<2>( this->node_list_[inode].edges() ) );
      if( ( new_x_plus - x_plus ) >= 0.0e0 ) { x_plus = new_x_plus; }
      if( ( new_y_plus - y_plus ) >= 0.0e0 ) { y_plus = new_y_plus; }
      if( ( new_z_plus - z_plus ) >= 0.0e0 ) { z_plus = new_z_plus; }
  
      if( ( new_x_minus - x_minus ) < 0.0e0 ) { x_minus = new_x_minus; }
      if( ( new_y_minus - y_minus ) < 0.0e0 ) { y_minus = new_y_minus; }
      if( ( new_z_minus - z_minus ) < 0.0e0 ) { z_minus = new_z_minus; }
    }
    return make_tuple( make_tuple( x_plus, x_minus ),
                       make_tuple( y_plus, y_minus ),
                       make_tuple( z_plus, z_minus ) );
  }

  /**
   *  + reorigin()
   *    Reorigin the whole bulk
   */
  void reorigin() {
    threed_vector_type reorigin_vector = compute_recenter_vec( this->edges() );
    coordinate_type coord = make_tuple( reorigin_vector[0], reorigin_vector[1], reorigin_vector[2] );
    for( size_t inode = 0; inode < this->node_list_.size(); inode++ ) {
      this->node_list_[inode] += coord;
    }
  }

public:
  /**
   *  Stream and I/O operators
   *  + operator<<
   *    We don't use const since we need to invoke operator[] of nodes
   */
  friend
  ostream& operator<< ( ostream& os, this_type& bulk_obj ) {
    for( size_t inode = 0 ; inode < bulk_obj.size(); inode++ ) {
      os << bulk_obj[inode] << endl;
    }
    return os;
  }

  /**
   *  + print_atomlist()
   *    It is basically doing the same thing as operator<<
   */
  void print_atomlist() {
    for( size_t inode = 0; inode < this->node_list_.size(); inode++ ) {
      this->node_list_[inode].print_atomlist();
    }
  }

public:
  /**
   *  Container-related overloaded function
   */

  /**
   *  + resize()
   *    Overloaded function resize()
   *    Usually resize of a molcule bulk object doesn't mean anything.
   *    This function is to be used in the constructor (then probably meaningful).
   */
  void resize( size_t size )
    { this->node_list_.resize( size ); }

  /**
   *  + size()
   *    Return this number of nodes
   *    Overloaded function.
   */
  size_type size() const
    { return this->node_list_.size(); }

  /**
   *  + at()
   *    Overloaded function at()
   *    Range check is performed by std :: vector :: at()
   */
  Node_Type& at( size_t i ) 
    { return this->node_list_.at(i); }

  /**
   *  + operator[]
   *    Overloaded operator[]
   *    No range check.
   */
  Node_Type& operator[] ( size_t i )
    { return this->node_list_[i]; }

  /**
   *  + push_back()
   *    Overloaded function push_back()
   *    To add a new Node_Type object.
   */
  void push_back( const Node_Type new_node_obj ) { 
    this->node_list_.push_back( new_node_obj );
    using structure :: align_geometry_unit;
    align_geometry_unit( this->node_list_.begin()->set_atom_list(),
                         this->node_list_.end()->set_atom_list() );
  }

public:
  /**
   *  Accessors
   */
  node_list_type node_list() const 
    { return this->node_list_; }
  condition_type is_filled() const
    { return this->is_filled_; }

  /**
   *  Auxiliary accessors
   */
  Node_Type center_node() {
    coordinate_type origin = make_tuple( 0, 0, 0 );
    multimap< double, int > dist_map;
    for( size_t inode = 0; inode < this->node_list_.size(); inode++ ) {
      coordinate_type center_i = this->node_list_[inode].center();
      double dist = compute_distance( center_i, origin );
      dist_map.insert( pair< double, int > ( dist, inode ) );
    }
    return this->node_list_[ dist_map.rbegin()->second ];
  }

private:
  node_list_type   node_list_;
  condition_type   is_filled_;

}; // end of struct MoleculeBulk 


/**
 *  + convert_lattice_to_bulk()
 *    Convert a lattice of a certain node type to a bulk
 *    This functions uses template template class, hopefully will not give us 
 *    trouble.
 */
template < class Node_Type > inline Bulk< Node_Type >
convert_lattice_to_bulk( Lattice< UnitCell<Node_Type> >& lattice_obj ) {

  Bulk< Node_Type > new_bulk_obj;
  for( int index_a = lattice_obj.a_min(); index_a <= lattice_obj.a_max(); index_a++ ) {
    for( int index_b = lattice_obj.b_min(); index_b <= lattice_obj.b_max(); index_b++ ) {
      for( int index_c = lattice_obj.c_min(); index_c <= lattice_obj.c_max(); index_c++ ) {
        UnitCell<Node_Type> cell_obj = lattice_obj( index_a, index_b, index_c);
        for( size_t icellnode = 0; icellnode < cell_obj.size(); icellnode++)
        new_bulk_obj.push_back( cell_obj[icellnode] );
      }
    }
  }
  return new_bulk_obj;
} // end of templated function convert_lattice_to_bulk()

} // end of structure

} // end of iquads

#endif
