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

#ifndef ATOM_HPP
#define ATOM_HPP

#include <stdio.h>
#include <vector>
#include <array>
#include <string>
#include <tuple>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <geometrical_space/coordinate.hpp>
#include <geometrical_space/threed_space_function.hpp>

using std::vector;
using std::tuple;

namespace iquads {

namespace structure {

  /**
   *  A class to store atom information
   *    + charge, here we mean, nuclear charge
   *    + mass
   *    + element name
   *
   *  For a more sensible definition for objects, probably someday I have to 
   *  separate this class into two different classes.
   *
   *  One is to store these above inner properties of an atom, along with 
   *  some other information, e.g., orbital info., in term of "An atom = A particle".
   *
   *  The other is to include information which an Atom is independent from, 
   *  Like the coordinate info, or lattice-related info in a crystal environment.
   *  But right now these are included in one class, so:
   *
   *    + coordinate (for molecular uses)
   *    + lattice vector (for crystal/periodic uses, to label in which unit cell)
   */

using std :: string;
using std :: make_tuple;
using std :: get;
using std :: istream;
using std :: ostream;
using geometrical_space :: CartesianCoordinate3D;
using geometrical_space :: CartesianCoordinate3DList;
using geometrical_space :: Interval;
using geometrical_space :: Interval3D;

class Atom {
public:
  typedef Atom                                          this_type;
  typedef geometrical_space :: coord_value_type         coordinate_value_type;
  typedef CartesianCoordinate3D                         coordinate_type;
  typedef Interval                                      interval_data_type;
  typedef Interval3D                                    interval_set_type;
  typedef string                                        element_name_type;
  typedef tuple< element_name_type, coordinate_type >   atom_coordinate_type;
  typedef vector< atom_coordinate_type >                atom_coordinate_list_type;
  typedef double                                        mass_value_type;
  typedef double                                        coordinate_value_type;
  typedef int                                           charge_value_type;
  typedef bool                                          condition_type;

  typedef coordinate_type&   coordinate_ref;

public:
  /**
   *  The default constructor makes an atom object non-real, or ghost
   */
  Atom()
    {
      this->coordinate_ = make_tuple( 0.0e0, 0.0e0, 0.0e0 );
      this->element_ = "not set";
      this->charge_  = 0;
      this->mass_    = 0.0e0;
      this->translation_vec_.fill(0);
    }

  /**
   *  The initialize list constructor is the only way to set the 
   *  inner property values: element name, mass, and charge.
   *  An oxygen atom normally won't change itself to a hydrogen atom in chemistry, 
   *  so no mutators will be provided in this class for these data members.
   *  Developers must know what they are doing when using the copy constructor to change a
   *  already initialized atom object.
   */
  Atom( element_name_type     element, 
        mass_value_type       mass,
        charge_value_type     charge, 
        coordinate_value_type x, 
        coordinate_value_type y, 
        coordinate_value_type z ) :
    element_(element), mass_(mass), charge_(charge), coordinate_ ( make_tuple(x, y, z) ) 
      { this->translation_vec_.fill(0); }

public:
  /**
   *  Coordinate-related member functions:
   */
  /**
   *   + within_radius( Radius )
   *     Judge if the atom is within the Radius w.r.t. the origin.
   *     Return value is origin-dependent.
   *     Used in crystal.
   */
  condition_type within_radius( double Radius ) const 
    {
      using geometrical_space :: threed_space :: compute_distance;
      coordinate_type origin = make_tuple(0.0e0, 0.0e0, 0.0e0);
      double R = compute_distance( origin, this->coordinate_ );
      return ( R <= Radius ) ? true : false;
    }

  /**
   *   + edges()
   *     An overloaded function to return edges of an atom in X, Y, Z directions.
   *     Can be overloaded for all object types in the namespace structure.
   *     Return value is an interval data type, see coordinate.hpp for definition.
   *     So it actually returns the coordinates of an atom since the atom is treated
   *     as a dimensionless point.
   */
  interval_set_type edges() const {
    interval_data_type interval_x = make_tuple( get<0>( this->coordinate_ ), get<0>( this->coordinate_ ) );
    interval_data_type interval_y = make_tuple( get<1>( this->coordinate_ ), get<1>( this->coordinate_ ) );
    interval_data_type interval_z = make_tuple( get<2>( this->coordinate_ ), get<2>( this->coordinate_ ) );
    return make_tuple( interval_x, interval_y, interval_z );
  }

  /**
   *   + center()
   *     An overloaded function to return the geometrical center of an atom.
   *     Can be overloaded for all object types in the namespace structure.
   *     Actually returns the coordinate of this atom.
   */
  coordinate_type center() const 
    { return make_tuple( get<0>( this->coordinate_ ), get<1>( this->coordinate_ ), get<2>( this->coordinate_ ) ); }

  /**
   *   + center_of_mass()
   *     An overloaded function to return center of mass of an atom.
   *     Can be overloaded for all object types in the namespace structure.
   *     Actually returns the coordinate of this atom.
   */
  coordinate_type center_of_mass() const 
    { return make_tuple( get<0>( this->coordinate_ ), get<1>( this->coordinate_ ), get<2>( this->coordinate_ ) ); }

  /**
   *   + operator+= ()
   *     Overloaded arithmetic operator for +=
   *     Performs coordinate movement for an atom object with the rhs as coordinate_type.
   *     rhs is not implemented as an atom, since an operation like atom + atom can mean something else.
   */
  this_type& operator+= ( const coordinate_type& rhs ) {
    get<0>( this->coordinate_ ) += get<0>( rhs );
    get<1>( this->coordinate_ ) += get<1>( rhs );
    get<2>( this->coordinate_ ) += get<2>( rhs );
    return *this;
  }

  /**
   *   + operator+ ()
   *     Overload arithmetic operator. Along with operator+= ()
   */
  friend 
  this_type operator+ ( this_type lhs, const coordinate_type& rhs ) {
    lhs += rhs;
    return lhs;
  }

  /**
   *  I/O member functions
   */
  /**
   *   + stream operator>> ()
   *     Overload stream operator>> .
   *     Since we don't have mutators for data members like element and mass,
   *     we have to use the initialize list constructor and the copy constructor.
   *     The standard input sequence (or what users should write in input files ) is:
   *     C 0.5 0.3 1.0 6 12.0
   */
  friend
  istream& operator>> ( istream& is, this_type& atom_obj ) {
    element_name_type element;
    mass_value_type mass;
    charge_value_type charge;
    coordinate_value_type x,y,z;
    is >> element >> x >> y >> z >> charge >> mass;
    this_type atom_obj_local( element, mass, charge, x, y, z );
    atom_obj = atom_obj_local;
    return is;
  }

  /**
   *   + stream operator>> ()
   *     Overload stream operator<< .
   *     We don't print out nuclear charge and mass, since everybody knows these quantities 
   *     of an atom when their see the element symbol.
   */
  friend
  ostream& operator<< ( ostream& os, const this_type& atom_obj ) {
    using std::fixed;
    using std::setw;
    using std::setprecision;
    os << atom_obj.element().c_str() << "  ";
    os << fixed << setw(12) << setprecision(8) << atom_obj.x() << "  ";
    os << fixed << setw(12) << setprecision(8) << atom_obj.y() << "  ";
    os << fixed << setw(12) << setprecision(8) << atom_obj.z() << "  ";
    return os;
  } // end of operator<<

  /**
   *    + print_atomlist()
   *      An overloaded function to print atom coordinate list (one atom for this class).
   *      Can be overloaded for all object types in the namespace structure
   */
  void print_atomlist() {
    using std::cout;
    using std::endl;
    cout << *this << endl;
  } 

public:
  /**
   *  Accessors for all class members are allowed
   */
  element_name_type element() const
    { return this->element_; }
  coordinate_value_type x() const 
    { return get<0>( this->coordinate_ ); }
  coordinate_value_type y() const 
    { return get<1>( this->coordinate_ ); }
  coordinate_value_type z() const 
    { return get<2>( this->coordinate_ ); }
  coordinate_type coordinate() const
    { return this->coordinate_; }
  charge_value_type charge() const
    { return this->charge_; }
  mass_value_type mass() const 
    { return this->mass_; }

  /**
   *  Auxiliary accessors
   */
  /**
   *   + coordinate_list()
   *     An interface from atom list to atom_coordinate_list data type.
   *     Return the coordinate list of this atom (only one coordinate set here),
   *     along with the element name.
   *     Can be overloaded in all object types in the namespace structure.
   */
  atom_coordinate_list_type coordinate_list() const
    { 
       atom_coordinate_list_type retval;
       retval.push_back( make_tuple( this->element_name_, this->coordinate_ ) ); 
       return retval;
    }

  /**
   *  Mutators for external properties are allowed
   */
  coordinate_value_ref set_x()
    { return get<0>( this->coordinate_ ); }
  coordinate_value_ref set_y()
    { return get<1>( this->coordinate_ ); }
  coordinate_value_ref set_z()
    { return get<2>( this->coordinate_ ); }
  coordinate_ref set_coordinate()
    { return this->coordinate_; }
  void set_coordinate( coordinate_value_type x, coordinate_value_type y, coordinate_value_type z )
    { this->coordinate_ = make_tuple( x, y, z ); }

  // I just leave this function like this for now
  array<int, 3>& set_translation_vec()
   { return this->translation_vec_; }

private:
  /**
   *  remind that the coordinate (3D) is stored as std::tuple<double, double, double>
   */
  coordinate_type    coordinate_;
  array<int, 3> translation_vec_;
  charge_value_type  charge_;
  mass_value_type    mass_;
  element_name_type  element_;

};  // end of class Atom

} // end of namespace particle

} // end of namespace iquads

#endif
