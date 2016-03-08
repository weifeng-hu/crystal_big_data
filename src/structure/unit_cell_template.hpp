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

#ifndef UNIT_CELL_TEMPLATE_HPP
#define UNIT_CELL_TEMPLATE_HPP

#include <vector>
#include <string>
#include <iostream>
#include <tuple>
#include <geometrical_space/coordinate.hpp>
#include <geometrical_space/threed_space.hpp>
#include <geometrical_space/threed_space_function.hpp>
#include <structure/atom.hpp>
#include <structure/atom_list.hpp>
#include <structure/lattice_parameter.hpp>

namespace iquads {

using std :: cout;
using std :: endl;
using std :: tuple;
using std :: make_tuple;
using std :: array;
using std :: vector;
using std :: string;

  /**
   *   A template class to represent primitive unit cells in crystals
   *
   *   It is designed to be a template class, with the template
   *   parameter as node type. to be instantiated as molecular 
   *   unit cells or atomic unit cells, thus can be to construct 
   *   ionic, molecular, and atomic crystals.
   *
   *   Data members are:
   *    + a list of nodes in the unit cell
   *    + lattice parameter
   *
   *   These are external quantities of an unit cell
   *    + unit cell id
   *    + translational vector from the original primitive cell
   */

namespace structure {

template < class NodeType > class UnitCell {
public:
  typedef UnitCell < NodeType >   this_type;
  typedef coord_value_type        coordinate_value_type;
  typedef CartesianCoordinate3D   coordinate_type;
  typedef vector<NodeType>        node_list_type;
  typedef LatticeParameter        lattice_parameter_type;
  typedef Interval                interval_data_type;
  typedef Interval3D              interval_set_type;
  typedef array<double, 3>        threed_vector_type;
  typedef array<int, 3>           cell_id_type;
  typedef bool                    condition_type;

  typedef node_list_type&         node_list_ref;
  typedef lattice_parameter_type& lattice_parameter_ref;
  typedef cell_id_type&           cell_id_ref;

public:
  /**
   *  Default constructor sets everything to be zero.
   *  Currently I don't know 
   */
  UnitCell()
    {
      this->node_list_.resize(0);
      this->lattice_parameter_ = LatticeParameter( 0, 0, 0, 0, 0, 0 );
      this->cell_id_ = array< int, 3 > { 0, 0, 0 };
      this->translation_vec_.fill(0);
    }
  UnitCell( node_list_type           node_list,
            lattice_parameter_type   lattice_parameter) :
    node_list_ (node_list), lattice_parameter_ (lattice_parameter)
      {
        /**
         *  Don't forget to check the geometry unit.
         *  Here we run the loop from 0, so the first atom list units can also be aligned
         */
        using structure :: align_geometry_unit;
        for( size_t inode = 0; inode < this->node_list_.size(); inode++ ) {
          align_geometry_unit( this->node_list_[0].set_atom_list(), this->node_list_[inode].set_atom_list() );
        }
        this->translation_vec_.fill(0);
        this->cell_id_.fill(0);
      }

  /**
   *  Coordinate-related member functions:
   */
  /**
   *   + within_radius( Radius )
   *     Judge if all nodes of the molecule are within the Radius w.r.t. the origin.
   *     Return value is origin-dependent.
   *     Used in crystal.
   */
  condition_type within_radius( double Radius )
    {
      for( size_t inode = 0; inode < this->node_list_.size(); inode++ ) {
        if( this->node_list_[inode].within_radius( Radius ) == false ) {
          return false;
        }
      }
      return true;
    }

  /**
   *   + edges()
   *     An overloaded function to return edges of an node in X, Y, Z directions.
   *     Can be overloaded for all object types in the namespace structure.
   *     Return value is an interval data type, see coordinate.hpp for definition.
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
   *   + reorigin()
   *     Reorigin all coordinate in the unit cell
   */
  void reorigin() {
    threed_vector_type reorigin_vector = compute_recenter_vec( this->edges() );
    coordinate_type coord = make_tuple( reorigin_vector[0], reorigin_vector[1], reorigin_vector[2] );
    for( size_t inode = 0; inode < this->node_list_.size(); inode++ ) {
      this->node_list_[inode] += coord;
    }
  }

  /**
   *  We don't overload center() and center_of_mass() here
   *  for now.
   */

  /**
   *   + translational_duplicate()
   *     Returns a new unit cell by a translational operation.
   *     Need to use the lattice parameters stored in the object.
   *     The final direction vector is 
   *     vec = a * vec_a + b * vec_b + c * vec_c
   *     a, b, c can be non integers.
   *     invokes the operator+=
   */
  this_type translational_duplicate( double a, double b, double c ) {
    this_type copy = *this;
    copy.set_translation_vec() = array<double, 3> { a, b, c };
    using geometrical_space :: threed_space :: operator+;
    using geometrical_space :: threed_space :: operator*;
    threed_vector_type translation_vector = this->lattice_parameter_.a_vector() * a +
                                            this->lattice_parameter_.b_vector() * b +
                                            this->lattice_parameter_.c_vector() * c;
    coordinate_type rhs = make_tuple( translation_vector[0], translation_vector[1], translation_vector[2] );
    copy += rhs;
    return copy;
  } 

  coordinate_type center() const {
    coordinate_value_type x_average = 0.0e0;
    coordinate_value_type y_average = 0.0e0;
    coordinate_value_type z_average = 0.0e0;
    for( size_t inode = 0; inode < this->node_list_.size(); inode++ ) {
      x_average += std :: get<0> ( this->node_list_[inode].center() );
      y_average += std :: get<1> ( this->node_list_[inode].center() );
      z_average += std :: get<2> ( this->node_list_[inode].center() );
    }
    x_average = x_average/double(this->node_list_.size());
    y_average = y_average/double(this->node_list_.size());
    z_average = z_average/double(this->node_list_.size());
    return make_tuple( x_average, y_average, z_average );
 
  }

  /**
   *   + operator+= ()
   *     Overloaded arithmetic operator +=
   *     Performs coordinate movement for an unit cell object with the rhs as coordinate_type (3d vector).
   *     Invokes the operator += of atom objects.
   */
  this_type& operator+= ( const coordinate_type& rhs ) {
    for( size_t inode = 0; inode < this->node_list_.size(); inode++ ) {
      this->node_list_[inode] += rhs;
    }
    return *this;
  }

  /**
   *  + operator == ()
   *    Judge whether two unit cell objects are the same in the lattice,
   *    by comparing the translation vector coefficients
   */
  friend
  inline condition_type operator== ( const this_type& lhs, const this_type& rhs ) {
    threed_vector_type vec_lhs = lhs.translation_vec();
    threed_vector_type vec_rhs = rhs.translation_vec();
    if( fabs( vec_lhs[0] - vec_rhs[0] ) > 1.0e-3 ) return false;
    if( fabs( vec_lhs[1] - vec_rhs[1] ) > 1.0e-3 ) return false;
    if( fabs( vec_lhs[2] - vec_rhs[2] ) > 1.0e-3 ) return false;
    return true;
  }

  /**
   *  I/O member functions:
   */
  /**
   *   + stream operator>> ()
   *     Overload stream operator>> .
   *     Invokes the stream operator >> of the node class.
   *     Also stream in the lattice parameters.
   */
  friend 
  istream& operator>> ( istream& is, this_type& unit_cell_obj )
    {
      size_t n_node;
      is >> n_node;
      for( size_t inode = 0; inode < n_node; inode++ ) {
        NodeType new_node_obj;
        is >> new_node_obj;
        unit_cell_obj.push_back( new_node_obj );
      }
      lattice_parameter_type new_lattice_parameter;
      is >> new_lattice_parameter;
      std :: cout << new_lattice_parameter << std :: endl;
      unit_cell_obj.set_lattice_parameter() = new_lattice_parameter;
      return is;
    }

  /**
   *   + stream operator<< ()
   *     Overload stream operator<<.
   *     Invokes the stream operator<< of the node class
   *     Note that we made the this_type& to be non-const so we can use 
   *     operator[] of the node class.
   *     Print out the atom list.
   */
  friend
  ostream& operator<< ( ostream& os, this_type& unit_cell_obj ) {
    using std :: endl;
    for( size_t inode = 0; inode < unit_cell_obj.size(); inode++ ) {
      os << unit_cell_obj[inode] << endl;
    }
    return os;
  }

  /**
   *   + print_atomlist()
   *     An overloaded function to print atom coordinate list.
   *     Can be overloaded for all object types in the namespace structure.
   */
  void print_atomlist() {
    for( size_t inode = 0; inode < this->node_list_.size(); inode++ ) {
      this->node_list_[inode].print_atomlist();
    }
  }

  /**
   *  + print_fractional_coordinates()
   *    print the fractional coordinates of all atoms in the unit cell
   *    We don't implement overloaded function in the sub structure classes,
   *    e.g., atoms, molecules, because fractional coordinates is only 
   *    meaningful if there is a unit cell.
   */
  void print_fractional_coordinates() {
    printf( "Fractional coordinates:\n" );
    for( size_t inode = 0; inode < this->node_list_.size(); inode++ ) {
      NodeType node = this->node_list_[inode];
      iquads :: structure :: Atom :: atom_coordinate_list_type coordinate_list = node.coordinate_list();
      for( size_t icoord = 0; icoord < coordinate_list.size(); icoord++ ) {
        std :: string element_name = std :: get<0> ( coordinate_list[icoord] );
        printf( "%s        ", element_name.c_str() );
        coordinate_type coordinate = std :: get<1> ( coordinate_list[icoord] );
        threed_vector_type fractional_coordinate = 
          this->lattice_parameter_.compute_translational_coefficient_for_point( coordinate );
          printf( "%16.8lf        %16.8lf        %16.8lf\n", fractional_coordinate[0],
                                                             fractional_coordinate[1],
                                                             fractional_coordinate[2] );
      }
    }
    printf( "end\n" );
  }

public:
  /**
   *  Container-related overloaded functions
   *  If we treat a unit cell object as a container as nodes
   */
  /**
   *  + size()
   *    Return number of nodes, depends on the actual node type
   */
  size_t size() const
    { return this->node_list_.size(); }

  /**
   *  + resize()
   */
  void resize( size_t size )
    { this->node_list_.resize(size); }

  /**
   *   + push_back()
   *     Previously a function add_node() was implemented
   *     Now we use the STL container naming, also with a 
   *     geometry unit check.
   */
  void push_back( const NodeType& node_obj  )
    {
      this->node_list_.push_back( node_obj );
      using structure :: align_geometry_unit;
      align_geometry_unit( this->node_list_.begin()->set_atom_list(), 
                           this->node_list_.rbegin()->set_atom_list() );
    }
 
  /**
   *   + at()
   *     We do not perform range check for index i, leaving
   *     it to the at() function of std :: vector.
   */
  NodeType& at( size_t i )
    { return this->node_list_.at(i); }

  /**
   *   + operator []
   *     no range check
   */
  NodeType& operator[] ( size_t i )
    { return this->node_list_[i]; }

  /**
   *  Iterators will be implemented in future when needed
   */

public:
  /**
   *  Accessors
   */
  node_list_type node_list() const 
    { return this->node_list_; }
  lattice_parameter_type lattice_parameter() const
    { return this->lattice_parameter_; }
  cell_id_type cell_id() const
    { return this->cell_id_; }
  array<double, 3> translation_vec() const
   { return this->translation_vec_; }


  /**
   *  Mutators
   *  Here we provide the mutators, since there is no strong 
   *  rule against changes to a unit cell. But developers 
   *  should know what they are doing when changing the data
   *  members.
   */
  node_list_ref set_node_list()
    { return this->node_list_; }
  lattice_parameter_ref set_lattice_parameter()
    { return this->lattice_parameter_; }
  cell_id_ref set_cell_id()
    { return this->cell_id_; }
  array<double, 3>& set_translation_vec()
   { return this->translation_vec_; }

private:
  node_list_type           node_list_;
  lattice_parameter_type   lattice_parameter_;
  cell_id_type             cell_id_;
  array<double, 3>         translation_vec_;

}; // end of class UnitCell

} // end of namespace structure

} // end of namespace iquads

#endif
