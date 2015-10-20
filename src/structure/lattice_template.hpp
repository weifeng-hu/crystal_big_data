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


#ifndef LATTICE_TEMPLATE_HPP
#define LATTICE_TEMPLATE_HPP

#include <stdlib.h>
#include <string>
#include <tuple>
#include <vector>
#include <array>
#include <iostream>
#include <geometrical_space/coordinate.hpp>
#include <geometrical_space/threed_space_function.hpp>
//#include <manybody_expansion/fragment_identifier/fragment_info.hpp>

using std::string;
using std::tuple;
using std::vector;
using std::array;
using std::cout;
using std::endl;

namespace iquads {

using namespace geometrical_space :: threed_space;

namespace structure {

  /**
   *  A template class to store lattice information
   *
   *  It is designed to be a template class, with the template
   *  parameter as the unit cell type. It can be atomic, molecular,
   *  and ionic lattice types.
   *
   *  We don't store a big array of unit cells since it will eat up
   *  a big chunk of memory also cannot be put into the stack memory 
   *  easily. Therefore we rely on ultrafast front end CPU power 
   *  to generate a certain unit cell object in the lattice on the fly
   *  whenever needed.
   *
   *  Data members are:
   *  + A primitive unit cell, this cell will be the central cell, with id [ 0, 0, 0 ]
   *  + number of duplication in +/-a, +/-b, +/-c directions
   *    In the lattice object, we enforce number of cells in a, b, c directions to be odd,
   *    So we can easily have a central cell well-define to have a id [0, 0, 0].
   *    This is based on the rationale that in a perioidic lattice whether a, b, c are
   *    even and odd do not change the macro properties of the system, e.g. lattice energy per unit cell.
   *    If a user wants to compute some quantity which is dependent on the size of 
   *    a system, like a finite system, then their probably should use the Bulk object class in 
   *    this namespace. The Bulk class does not have any information about periodicity.
   *  + a flag to tell whether data is filled
   *
   *  We don't store copy of lattice parameter to ensure the data 
   *  dependence.
   *
   */

template < typename UnitCell_Type > class Lattice {
public:
  typedef UnitCell_Type              unit_cell_type;
  typedef Lattice< UnitCell_Type >   this_type;
  typedef typename UnitCell_Type :: lattice_parameter_type   lattice_parameter_type;
  typedef coord_value_type                          coordinate_value_type;
  typedef CartesianCoordinate3D                     coordinate_type;
  typedef Interval                                  interval_data_type;
  typedef Interval3D                                interval_set_type;
  typedef tuple< int, int >                         cell_interval_type;
  typedef size_t                                    size_type;
  typedef bool                                      condition_type;

  typedef UnitCell_Type&        unit_cell_ref;
  typedef cell_interval_type&   cell_interval_ref;

public:
//  typedef vector< tuple< array< int, 1 > , double > > sym_noneq_monomer_list_type;
//  typedef vector< tuple< array< int, 2 > , double > > sym_noneq_dimer_list_type;
//  typedef vector< tuple< array< int, 3 > , double > > sym_noneq_trimer_list_type;
//  typedef vector< tuple< array< int, 4 > , double > > sym_noneq_tetramer_list_type;

public:
  /**
   *  The default constructor sets everything to be zero
   */
  Lattice()
    {
      this->unit_cell_.resize(0);
      this->interval_a_ = make_tuple( 0, 0 );
      this->interval_b_ = make_tuple( 0, 0 );
      this->interval_c_ = make_tuple( 0, 0 );
      this->is_filled_ = false;
    }

  /**
   *  The initialize list constructor will set the is_flag_ as true 
   *  but we don't have a good algorithm to check whether the lattice is valid.
   *  so a developer must make sure the lattice will be a valid object when using this 
   *  constructor.
   */
  Lattice( UnitCell_Type& unit_cell,
           size_type na, size_type nb, size_type nc ) :
    unit_cell_ ( unit_cell ), 
    interval_a_ ( make_tuple( -na, na ) ),
    interval_b_ ( make_tuple( -nb, nb ) ),
    interval_c_ ( make_tuple( -nc, nc ) ) { this->is_filled_ = true; }

public:
  /**
   *  Coordinate-related functions
   */
  /**
   *  + edges()
   *    An overloaded function to return edges of an lattice in X, Y, Z directions.
   *    Can be overloaded for all object types in the namespace structure.
   *    Return value is an interval data type, see coordinate.hpp for definition.
   *    This function relies on the unit cell generation on the fly, and performs
   *    the rigorous edge check, does not rely on cell intervals.
   */
  interval_set_type edges() {
    coordinate_value_type x_plus  = get<0>( get<0> ( this->at(0,0,0).edges() ) ); 
    coordinate_value_type x_minus = get<1>( get<0> ( this->at(0,0,0).edges() ) ); 
    coordinate_value_type y_plus  = get<0>( get<1> ( this->at(0,0,0).edges() ) ); 
    coordinate_value_type y_minus = get<1>( get<1> ( this->at(0,0,0).edges() ) ); 
    coordinate_value_type z_plus  = get<0>( get<2> ( this->at(0,0,0).edges() ) ); 
    coordinate_value_type z_minus = get<1>( get<2> ( this->at(0,0,0).edges() ) ); 
    for( int index_a = this->a_min(); index_a <= this->a_max(); index_a++ ) {
      for( int index_b = this->b_min(); index_b <= this->b_max(); index_b++ ) {
        for( int index_c = this->c_min(); index_c <= this->c_max(); index_c++ ) {
          interval_set_type edges_inode = this->at( index_a, index_b, index_c ).edges();
          coordinate_value_type new_x_plus  = get<0>( get<0>( this->at( index_a, index_b, index_c ).edges() ) );
          coordinate_value_type new_x_minus = get<1>( get<0>( this->at( index_a, index_b, index_c ).edges() ) );
          coordinate_value_type new_y_plus  = get<0>( get<1>( this->at( index_a, index_b, index_c ).edges() ) );
          coordinate_value_type new_y_minus = get<1>( get<1>( this->at( index_a, index_b, index_c ).edges() ) );
          coordinate_value_type new_z_plus  = get<0>( get<2>( this->at( index_a, index_b, index_c ).edges() ) );
          coordinate_value_type new_z_minus = get<1>( get<2>( this->at( index_a, index_b, index_c ).edges() ) );
          if( ( new_x_plus - x_plus ) >= 0.0e0 ) { x_plus = new_x_plus; }
          if( ( new_y_plus - y_plus ) >= 0.0e0 ) { y_plus = new_y_plus; }
          if( ( new_z_plus - z_plus ) >= 0.0e0 ) { z_plus = new_z_plus; }
      
          if( ( new_x_minus - x_minus ) < 0.0e0 ) { x_minus = new_x_minus; }
          if( ( new_y_minus - y_minus ) < 0.0e0 ) { y_minus = new_y_minus; }
          if( ( new_z_minus - z_minus ) < 0.0e0 ) { z_minus = new_z_minus; }
        }
      }
    }
    return make_tuple( make_tuple( x_plus, x_minus ),
                       make_tuple( y_plus, y_minus ),
                       make_tuple( z_plus, z_minus ) );
  }


  /**
   *  + reorigin()
   *    An overloaded function to unit cell objects
   *    Reorigin all coordinates in the lattice.
   *    Invokes the reorigin() of the unit cell.
   *    Nothings needs to be done to the cell interval data since they are
   *    irrelevant to actual coordinates, just indices.
   *    The reorigin will affect all unit cells generated afterward, so developers 
   *    should make sure all unit cell instants generated in some pieces of code are consistent.
   */
  void reorigin() 
    { this->unit_cell_.reorigin(); }


public:
  /**
   *  Stream operators
   *  We don't provide insert operator since a lattice objcect is created not from reading files
   */
  /**
   *  + operator<< 
   *    Creates a unit_cell object and then use the operator<< of it
   */
  friend 
  ostream& operator<< ( ostream& os, this_type& lattice_obj ) {
    for( int index_a = lattice_obj.a_min(); index_a <= lattice_obj.a_max(); index_a++ ) {
      for( int index_b = lattice_obj.b_min(); index_b <= lattice_obj.b_max(); index_b++ ) {
        for( int index_c = lattice_obj.c_min(); index_c <= lattice_obj.c_max(); index_c++ ) {
          unit_cell_type unit_cell = lattice_obj( index_a, index_b, index_c );
          os << unit_cell << endl;
        }
      }
    }
    return os;
  }

  /**
   *  + operator<< 
   *    Creates a unit_cell object and then use the print_atomlist() function of it
   */
  void print_atomlist() {
    for( int index_a = this->a_min(); index_a <= this->a_max(); index_a++ ) {
      for( int index_b = this->b_min(); index_b <= this->b_max(); index_b++ ) {
        for( int index_c = this->c_min(); index_c <= this->c_max(); index_c++ ) {
          this->at( index_a, index_b, index_c ).print_atomlist(); 
        }
      }
    }
  }


/*  I should put these into the fragment handling classes
public:
  template < size_t NUM > 
   vector< tuple< array< int, NUM > , double > > 
    identify_symmetry_equvivalent_fragments_for_center( int center_index ){};
*/

public:
  /**
   *  Container-related functions
   */
  /**
   *  + at()
   *    Returns a duplicate of the unit cell
   *    we perform range check for a, b, c
   *    The return type is different from standard containers
   *    Since this function performs on the fly unit cell generation
   */
  UnitCell_Type at( int a, int b, int c ) {
    try {
      if( a > this->a_max() || a < this->a_min() ) { throw make_tuple( 0, a ); }
      if( b > this->b_max() || b < this->b_min() ) { throw make_tuple( 1, b ); }
      if( c > this->c_max() || c < this->c_min() ) { throw make_tuple( 2, c ); }
      return this->unit_cell_.translational_duplicate( a, b, c );
    } catch ( tuple< int, int > error_info ) {
      cout << " out of range index " << get<1>( error_info );
      cout << " requested for direction " << get<0> ( error_info ) << endl;
      abort();
    }
  }

  /**
   *  + operator()
   *    Returns a duplicate of the unit cell
   *    NO  range check for a, b, c
   *    The return type is different from standard containers
   *    Since this function performs on the fly unit cell generation
   */
  UnitCell_Type operator() ( int a, int b, int c ) {
    return this->unit_cell_.translational_duplicate( a, b, c );
  }

  /**
   *  + size()
   *    This function also is not like the standard container size()
   *    functions. It returns a virtual number of unit cells in this
   *    lattice.
   */
  size_type size() const 
    { return this->na() * this->nb() * this->nc(); }

public:
  /**
   *  Accessors
   */
  UnitCell_Type unit_cell() const 
    { return this->unit_cell_; }
  cell_interval_type interval_a() const
    { return this->interval_a_; }
  cell_interval_type interval_b() const
    { return this->interval_b_; }
  cell_interval_type interval_c() const
    { return this->interval_c_; }
  condition_type is_filled() const
    { return this->is_filled_; }

  /**
   *  Auxiliary accessors
   */
  lattice_parameter_type lattice_parameter() const
    { return this->unit_cell_.lattice_parameter(); }
  int a_min() const 
    { return get<0>( interval_a_ ); }
  int a_max() const 
    { return get<1>( interval_a_ ); }
  int b_min() const 
    { return get<0>( interval_b_ ); }
  int b_max() const 
    { return get<1>( interval_b_ ); }
  int c_min() const 
    { return get<0>( interval_c_ ); }
  int c_max() const 
    { return get<1>( interval_c_ ); }
  size_type na() const 
    { return this->a_max() - this->a_min() + 1; }
  size_type nb() const 
    { return this->b_max() - this->b_min() + 1; }
  size_type nc() const 
    { return this->c_max() - this->c_min() + 1; }

  /**
   *  Mutators
   *  We allow developers to change the unit cells and intervals
   *  This is probably useful in phase transition applications
   */
  unit_cell_ref set_unit_cell()
    { return this->unit_cell_; }
  cell_interval_ref set_interval_a()
    { return this->interval_a_; }
  cell_interval_ref set_interval_b()
    { return this->interval_b_; }
  cell_interval_ref set_interval_c()
    { return this->interval_c_; }

private:
  UnitCell_Type unit_cell_;
  cell_interval_type interval_a_;
  cell_interval_type interval_b_;
  cell_interval_type interval_c_;
  condition_type is_filled_;

}; // end of struct Lattice

} // end of namespace structure

} // end of namespace iquads

#endif
