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

#ifndef MOLECULE_HPP
#define MOLECULE_HPP

#include <vector>
#include <string>
#include <tuple>
#include <fstream>
#include <iostream>
#include <geometrical_space/coordinate.hpp>
#include <structure/atom_list.hpp>

namespace iquads {

namespace structure {

  /**
   *  A class to store molecule information (approximates a true molecule)
   *   + A list of atoms
   *   + charge
   *
   *  We don't include electron spin as a data member, since a molecule can 
   *  be at any spin state when number of electrons is given, and we'll need to 
   *  solved it!
   *
   *  In future, we can probably include other info like 
   *  atomic orbitals, point group symmetry, these are constant quantities for a molecule.
   *
   *  Also, the current object depends on cartesian coordinates,
   *  But a molecule object should be invariant to actual spatial position.
   *  So a ''true'' molecule object should be labeled with internal coordinates in future.
   *
   *  We can make a molecule class to be independent on actual positions, but another
   *  derived class to have position info, also position in a crystal, etc. But right now,
   *  everything is here:
   *   + lattice vector (to label in which unit cell)
   *   + a unique id (to label the molecule in a finite system)
   */

using std :: string;
using std :: make_tuple;
using std :: get;
using std :: istream;
using std :: ostream;
using geometrical_space :: Interval;
using geometrical_space :: Interval3D;

class Molecule {
public:
  typedef Molecule   this_type;
  typedef Atom       atom_type;
  /**
   *  We forward the below typedef from Atom class 
   *  due to the phyical dependence of molecules on atoms
   */
  typedef typename atom_type :: coordinate_value_type       coordinate_value_type;
  typedef typename atom_type :: coordinate_type             coordinate_type;
  typedef typename atom_type :: atom_coordinate_list_type   atom_coordinate_list_type;
  typedef typename atom_type :: mass_value_type             mass_value_type;
  typedef typename atom_type :: geometry_unit_type          geometry_unit_type;
  typedef Interval                                          interval_data_type;
  typedef Interval3D                                        interval_set_type;
  typedef AtomList                                          atom_list_type;
  typedef int                                               charge_value_type;
  typedef unsigned int                                      molecule_id_type;
  typedef bool                                              condition_type;

  typedef coordinate_type&     coodinate_ref;
  typedef atom_list_type&      atom_list_ref;
  typedef charge_value_type&   charge_value_ref;
  typedef molecule_id_type&    molecule_id_ref;

public:
  /**
   *  Default constructor makes a ghost molecule, like a ghost atom default constructor
   */
  Molecule()
    {
      this->atom_list_.resize(1);
      this->charge_ = 0;  // probably we should write something like charge :: not_set
      this->translation_vec_.fill(0);
    }

  /**
   *  The initialize list constructor eats an atom list and charge to make a molecule 
   *  object valid.
   *  In chemistry, a molecule can change in reactions, so essentially a molecule object
   *  is volatile, and mutators are allowed for any data member.
   */
  Molecule( atom_list_type    atom_list_obj,
            charge_value_type charge_value   ) :
    atom_list_(atom_list_obj), charge_(charge_value)
      {
        /**
         *  Don't forget to check the geometry unit.
         */
        using structure :: align_geometry_unit;
        align_geometry_unit( this->atom_list_ );
        this->translation_vec_.fill(0);
        this->molecule_id_ = 0; // probably also something like id :: not_set;
      }

public:
  /**
   *  Coordinate-related member functions:
   */
  /**
   *   + within_radius( Radius )
   *     Judge if all atoms of the molecule are within the Radius w.r.t. the origin.
   *     Return value is origin-dependent.
   *     Used in crystal.
   */
  condition_type within_radius( double Radius )
    {
      for( size_t iatom = 0; iatom < this->atom_list_.size(); iatom++ ) {
        if( this->atom_list_[iatom].within_radius( Radius ) == false ) {
          return false;
        }
      }
      return true;
    }

  /**
   *   + edges()
   *     An overloaded function to return edges of an molecule in X, Y, Z directions.
   *     Can be overloaded for all object types in the namespace structure.
   *     Return value is an interval data type, see coordinate.hpp for definition.
   *     I adimit that this function body looks noisy.
   */
  interval_set_type edges() const {
    coordinate_value_type x_plus  = get<0>( get<0>( this->atom_list_[0].edges() ) );
    coordinate_value_type x_minus = get<1>( get<0>( this->atom_list_[0].edges() ) );
    coordinate_value_type y_plus  = get<0>( get<1>( this->atom_list_[0].edges() ) );
    coordinate_value_type y_minus = get<1>( get<1>( this->atom_list_[0].edges() ) );
    coordinate_value_type z_plus  = get<0>( get<2>( this->atom_list_[0].edges() ) );
    coordinate_value_type z_minus = get<1>( get<2>( this->atom_list_[0].edges() ) );
    for( size_t iatom = 0; iatom < this->atom_list_.size(); iatom++ ) {
      interval_set_type edges_iatom = this->atom_list_[iatom].edges();
      coordinate_value_type new_x_plus  = get<0>( get<0>( this->atom_list_[iatom].edges() ) );
      coordinate_value_type new_x_minus = get<1>( get<0>( this->atom_list_[iatom].edges() ) );
      coordinate_value_type new_y_plus  = get<0>( get<1>( this->atom_list_[iatom].edges() ) );
      coordinate_value_type new_y_minus = get<1>( get<1>( this->atom_list_[iatom].edges() ) );
      coordinate_value_type new_z_plus  = get<0>( get<2>( this->atom_list_[iatom].edges() ) );
      coordinate_value_type new_z_minus = get<1>( get<2>( this->atom_list_[iatom].edges() ) );
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
   *   + center()
   *     An overloaded function to return the geometrical center of an molecule.
   *     Can be overloaded for all object types in the namespace structure.
   */
  coordinate_type center() const {
    coordinate_value_type x_average = 0.0e0;
    coordinate_value_type y_average = 0.0e0;
    coordinate_value_type z_average = 0.0e0;
    for( size_t iatom = 0; iatom < this->atom_list_.size(); iatom++ ) {
      x_average += this->atom_list_[iatom].x();
      y_average += this->atom_list_[iatom].y();
      z_average += this->atom_list_[iatom].z();
    }
    x_average = x_average/double(this->atom_list_.size());
    y_average = y_average/double(this->atom_list_.size());
    z_average = z_average/double(this->atom_list_.size());
    return make_tuple( x_average, y_average, z_average );
  }

  /**
   *   + center_of_mass()
   *     An overloaded function to return center of mass of an molecule.
   *     Can be overloaded for all object types in the namespace structure.
   */
  coordinate_type center_of_mass() const {
    coordinate_value_type x_average = 0.0e0;
    coordinate_value_type y_average = 0.0e0;
    coordinate_value_type z_average = 0.0e0;
    for( size_t iatom = 0; iatom < this->atom_list_.size(); iatom++ ) {
      x_average += this->atom_list_[iatom].x() * this->atom_list_[iatom].mass();
      y_average += this->atom_list_[iatom].y() * this->atom_list_[iatom].mass();
      z_average += this->atom_list_[iatom].z() * this->atom_list_[iatom].mass();
    }
    x_average = x_average/this->mass();
    y_average = y_average/this->mass();
    z_average = z_average/this->mass();
    return make_tuple( x_average, y_average, z_average );
  }

  /**
   *   + operator+= ()
   *     Overloaded arithmetic operator +=
   *     Performs coordinate movement for an molecule object with the rhs as coordinate_type (3d vector).
   *     Invokes the operator += of atom objects.
   *     rhs is not implemented as an molecule, since an operation like molecule + molecule can mean something else.
   */
  this_type& operator+= ( const coordinate_type& rhs ) {
    for( size_t iatom = 0; iatom < this->atom_list_.size(); iatom++ ) {
      this->atom_list_[iatom] += rhs;
    }
    return *this;
  }

  /**
   *   + operator+ ()
   *     Overload arithmetic operator. Along with operator+= () for coordinate operations.
   */
  friend 
  this_type operator+ ( this_type lhs, const coordinate_type& rhs ) {
    lhs += rhs;
    return lhs;
  }

  /**
   *  Structure-object related functions
   */
  /**
   *   + operator+= ()
   *     Overloaded arithemetic operator +=
   *     Attach a new atom object to the molecule, and the overall charge
   *     remains the same (we should allow it to change in future).
   *     Does the same operation as member function push_back()
   */
  this_type& operator+= ( const atom_type& rhs ) {
    this->push_back( rhs );
    return *this;
  }

  /**
   *   + operator+ ()
   *     Overloaded arithmetic operator. 
   *     Along with operator+= () for structural object operations.
   *     LHS is a molecule object, and RHS is a atom object.
   */
  friend 
  this_type operator+ ( this_type lhs, const atom_type& rhs ) {
    lhs += rhs;
    return lhs;
  }

  /**
   *   + operator+ ()
   *     Overloaded arithmetic operator for structural object operations.
   *     Implemented as depending on operator+=.
   *     LHS is a atom object, and RHS is a atom object, generates a molecule object.
   *     Used as a starter for a new molecule object.
   */
  friend 
  this_type operator+ ( const atom_type& lhs, const atom_type& rhs ) {
    using structure :: align_geometry_unit;
    this_type new_molecule_obj;
    new_molecule_obj += lhs;
    new_molecule_obj += rhs;
    align_geometry_unit( new_molecule_obj.set_atom_list() );
    return new_molecule_obj;
  }

  /**
   *  I/O member functions:
   */
  /**
   *   + stream operator>> ()
   *     Overload stream operator>> .
   *     Invokes the stream operator >> of the atom class.
   */
  friend
  istream& operator>> ( istream& is, this_type& molecule_obj ) {
    size_t natom;
    is >> natom;
    for( size_t iatom = 0; iatom < natom; iatom++ ) {
      atom_type new_atom_obj;
      is >> new_atom_obj;
      molecule_obj.push_back( new_atom_obj );
    }
    return is;
  }

  /**
   *   + stream operator<< ()
   *     Overloaded stream operator<< .
   *     Invokes the stream operator >> of the atom class.
   *     So the streaming out format is 
   *     <Element0>  <X0>  <Y0>  <Z0>
   *     <Element1>  <X1>  <Y1>  <Z1>
   *     
   *     Note that we made the this_type& to be non-const such that we can use 
   *     operator[] of molecule class 
   */
  friend 
  ostream& operator<< ( ostream& os, this_type& molecule_obj ) {
    using std :: endl;
    for( size_t iatom = 0; iatom < molecule_obj.size(); iatom++ ) {
      os << molecule_obj[iatom] << endl;
    }
    return os;
  }

  /**
   *   + print_atomlist()
   *     An overloaded function to print atom coordinate list.
   *     Can be overloaded for all object types in the namespace structure.
   *     Actually this function is doing the same thing as operator<<
   */
  void print_atomlist(){
    for( size_t iatom = 0; iatom < this->atom_list_.size(); iatom++ ) {
      this->atom_list_[iatom].print_atomlist();
    }
  }

public:
  /**
   *  Container-related member functions
   *  If we treat a molecule object as a container of atoms
   */
  /**
   *  + size()
   *    Return number of atoms, actually
   */
  size_t size() const
    { return this->atom_list_.size(); }

  /**
   *  + push_back()
   *    Previously a function add_atom() was implemented
   *    Now I think overloading push_back() can be more straigtforward
   *    The same as operator+= .
   *    Any other objects using this push_back() will be safe for the geometry unit.
   */
  void push_back( const atom_type& atom_obj ) {
    this->atom_list_.push_back( atom_obj );
    using structure :: align_geometry_unit_for_the_last_atom;
    align_geometry_unit_for_the_last_atom( this->atom_list_ );
  }

  /**
   *  + at()
   *    We don't perform range check, simply leave this task to the actual
   *    vector :: at()
   */
  atom_type& at( size_t i )
    { return this->atom_list_.at(i); }

  /**
   *  + operator[]
   *    So as standard, no range check for the index i
   */
  atom_type& operator[] ( size_t i )
    { return this->atom_list_[i]; }

  /**
   *  Iterators will be implemented in future when needed
   */

public:
  /**
   *  Accessors and mutators for all class members are allowed
   */
  atom_list_type atom_list() const 
    { return this->atom_list_; }
  charge_value_type charge() const
    { return this->charge_; }
  molecule_id_type molecule_id() const
    { return this->molecule_id_; }

  atom_list_ref set_atom_list()
    { return this->atom_list_; }
  charge_value_ref set_charge()
    { return this->charge_; }
  molecule_id_ref set_molecule_id()
    { return this->molecule_id_; }

  /**
   *  Auxiliary Accessors
   */
  /**
   *  + mass()
   *    Return molecular mass, calculated on the fly.
   *    We don't separately store the mass since molecular mass depends on all atoms. 
   *    We sacrifice a little performance but to ensure the data responsibility and a clean design.
   */
  mass_value_type mass() const {
    mass_value_type retval;
    for( size_t iatom = 0; iatom < this->atom_list_.size(); iatom++ ) {
      retval += this->atom_list_[iatom].mass();
    }
    return retval;
  }

  size_t neutral_nelec() const {
    size_t retval;
    for( size_t iatom = 0; iatom < this->atom_list_.size(); iatom++ ) {
      retval += this->atom_list_[iatom].charge();
    }
    return retval;
  }

  /**
   *  + coordinate_list()
   *    An interface from atom list to atom_coordinate_list data type
   *    Return the coordinate list of this molecule, along with element names of atoms.
   *    Can be overloaded for all object types in the namespace structure.
   *    Invokes the coordinate_list() function of the atom class and takes the first data element.
   */
  atom_coordinate_list_type coordinate_list() const {
    atom_coordinate_list_type retval;
    for( size_t iatom = 0; iatom < this->atom_list_.size(); iatom++ ) {
      retval.push_back( (this->atom_list_[iatom].coordinate_list()).at(0) );
    }
    return retval;
  }

  /**
   *  + geometry_unit()
   *    Return the geometry unit of the first atom, normally geometry units
   *    of all atoms are aligned once the this object is created
   */
  geometry_unit_type geometry_unit() const
    { return this->atom_list_[0].geometry_unit(); }

  // I just leave this function for now
  array<int, 3>& set_translation_vec()
    { return this->translation_vec_; }

private:
  atom_list_type     atom_list_;
  charge_value_type  charge_;
  array<int, 3>      translation_vec_;
  molecule_id_type   molecule_id_;

}; // end of class Molecule

} // end of namespace structure

} // end of namespace iquads

#endif
