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
   *  A class to store molecule information
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

struct Molecule {
public:
  typedef Molecule                                     this_type;
  typedef Atom                                         atom_type;
  /**
   *  We forward the below typedef from Atom class 
   *  due to the phyical dependence of molecules on atoms
   */
  typedef typename atom_type :: coordinate_value_type  coordinate_value_type;
  typedef typename atom_type :: coordinate_type        coordinate_type;
  typedef typename atom_type :: coordinate_list_type   coordinate_list_type;
  typedef Interval                                     interval_data_type;
  typedef Interval3D                                   interval_set_type;
  typedef AtomList                                     atom_list_type;
  typedef int                                          charge_value_type;
  typedef unsigned int                                 molecule_id_type;
  typedef bool                                         condition_type;

public:
  /**
   *  Default constructor makes a ghost molecule, like a ghost atom default constructor
   */
  Molecule()
    {
      this->atom_list_.resize(0);
      this->charge_ = 0;  // probably we should write something like charge :: not_set
      this->translation_vec_.fill(0);
    }

  /**
   *  The initialize list constructor eats an atom list and charge to make a molecule 
   *  object valid.
   *  In chemistry, a molecule can change in reactions, so essentially a molecule object
   *  is volatile, and mutators are allowed for any data member.
   */
  Molecule( atom_list_type    atom_list,
            charge_value_type charge   ) :
    atom_list_(atom_list), charge_(charge)
      {
        this->translation_vec_.fill(0);
        this->molecule_id_ = 0; // probably also something like id :: not_set;
      }

public:
  void add_atom( atom_type new_atom ){
    this->atom_list.push_back( new_atom );
    this->natom_ += 1;
    this->mass_ += new_atom.get_mass();
  }

public:
  /**
   *  Coordinate-related functions:
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
        if( this->atom_list_.at(iatom).within_radius( Radius ) == false ) {
          return false;
        }
      }
      return true;
    }

  /**
   *   + atom_coordinate_list()
   *     An interface from the atom list to atom_coordinate list data type.
   *     Return the coordinate list of this molecule, along with element names.
   *     Can be overloaded in all object types in the namespace structure.
   */
  atom_coordinate_list coordinate_list() const
    {
      atom_coordinate_list_type retval;
      for( size_t iatom = 0; iatom < this->atom_list_.size(); iatom++ ) {
        retval.push_back( make_tuple( this->atom_list_.at(iatom).element(), 
                                      this->atom_list_.at(iatom).coordinate() ) );
      }
      return retval;
    }

  /**
   *   + edges()
   *     An overloaded function to return edges of an molecule in X, Y, Z directions.
   *     Can be overloaded for all object types in the namespace structure.
   *     Return value is an interval data type, see coordinate.hpp for definition.
   *     I adimit that this function body looks noisy.
   */
  interval_set_type edges() const {
    coordinate_value_type x_plus  = get<0>( get<0>( this->atom_list_.at(0).edges() ) );
    coordinate_value_type x_minus = get<1>( get<0>( this->atom_list_.at(0).edges() ) );
    coordinate_value_type y_plus  = get<0>( get<1>( this->atom_list_.at(0).edges() ) );
    coordinate_value_type y_minus = get<1>( get<1>( this->atom_list_.at(0).edges() ) );
    coordinate_value_type z_plus  = get<0>( get<2>( this->atom_list_.at(0).edges() ) );
    coordinate_value_type z_minus = get<1>( get<2>( this->atom_list_.at(0).edges() ) );
    for( size_t iatom = 0; iatom < this->atom_list_.size(); iatom++ ) {
      interval_set_type edges_iatom = this->atom_list_.at(iatom).edges();
      coordinate_value_type new_x_plus  = get<0>( get<0>( this->atom_list_.at(iatom).edges() ) );
      coordinate_value_type new_x_minus = get<1>( get<0>( this->atom_list_.at(iatom).edges() ) );
      coordinate_value_type new_y_plus  = get<0>( get<1>( this->atom_list_.at(iatom).edges() ) );
      coordinate_value_type new_y_minus = get<1>( get<1>( this->atom_list_.at(iatom).edges() ) );
      coordinate_value_type new_z_plus  = get<0>( get<2>( this->atom_list_.at(iatom).edges() ) );
      coordinate_value_type new_z_minus = get<1>( get<2>( this->atom_list_.at(iatom).edges() ) );
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
      x_average += this->atom_list_.at(iatom).x();
      y_average += this->atom_list_.at(iatom).y();
      z_average += this->atom_list_.at(iatom).z();
    }
    x_average = x_average/this->atom_list_.size();
    y_average = y_average/this->atom_list_.size();
    z_average = z_average/this->atom_list_.size();
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
      x_average += this->atom_list_.at(iatom).x() * this->atom_list_.at(iatom).mass();
      y_average += this->atom_list_.at(iatom).y() * this->atom_list_.at(iatom).mass();
      z_average += this->atom_list_.at(iatom).z() * this->atom_list_.at(iatom).mass();
    }
    x_average = x_average/this->mass();
    y_average = y_average/this->mass();
    z_average = z_average/this->mass();
    return make_tuple( x_average, y_average, z_average );
  }


  void operator+= ( array<double, 3> x ){
   size_t n_atom_local = this->atom_list.size();
   for( size_t iatom = 0; iatom < n_atom_local; iatom++ ){
    atom_list.at(iatom) += x;
   }
  }

  friend ifstream& operator>> ( ifstream& ifs, Molecule& new_mole ){
   ifs >> new_mole.set_name();
   size_t natom;
   ifs >> natom;
   for( size_t iatom = 0; iatom < natom; iatom++ ){
    atom_type new_atom;
    ifs >> new_atom;
    new_mole.add_atom( new_atom );
   }
   return ifs;
  }

public:
  size_t get_natom() const { return this->natom_; }
  double get_mass() const { return this->mass_; }

  mass_value_type mass() const {
    mass_value_type retval;
    for( size_t iatom = 0; iatom < this->atom_list_.size(); iatom++ ) {
      retval += this->atom_list_.at(iatom).mass();
    }
    return retval;
  }

  AtomList& set_atom_list() { return this->atom_list; }
  atom_ref& set_atom( size_t i ) { return this->atom_list.at(i); }
  string& set_name() { return this->molecule_name_; }
  size_t& set_natom() { return this->natom_; }
  double& set_mass() { return this->mass_; }

  CoordList get_coordinate_list(){
   CoordList retval;
   for( size_t iatom = 0; iatom < natom_; iatom++ ){
    const coordinate_type set = this->atom_list.at(iatom).get_coordinate_set();
    retval.push_back(set);
   }
   return retval;
  }

  array<int, 3>& set_translation_vec()
   { return this->translation_vec; }

  void print_info(){
   cout << "MOLECULE INFO" << endl;
   cout << "{" << endl;
   cout << "molecule name:\t" << this->molecule_name_ << endl;
   AtomList atomlist_local = this->get_atom_list();
   const size_t natom = atomlist_local.size();
   cout << "number of atom:\t" << natom << endl;
   cout << "Atom List:" << endl;
   cout << "{" << endl;
   for( size_t iatom = 0; iatom < natom; iatom++ ){
    atomlist_local[iatom].print_info();
   }
   using std::get;
   cout << "}" << endl;
   cout << "centroid:\t" 
        << get<0>( this->get_center() ) << " " 
        << get<1>( this->get_center() ) << " " 
        << get<2>( this->get_center() ) << endl;
   cout << "center of mass:\t" 
        << get<0>( this->get_center_of_mass() ) << " " 
        << get<1>( this->get_center_of_mass() ) << " " 
        << get<2>( this->get_center_of_mass() ) << endl;
   cout << "}" << endl;
  }

  void print_atomlist(){
   AtomList atomlist_local = this->get_atom_list();
   const size_t natom = atomlist_local.size();
   for( size_t iatom = 0; iatom < natom; iatom++ ){
    atomlist_local[iatom].print_atomlist();
   }
  }

  friend 
  ostream& operator<< ( ostream& os, Molecule mole ){
   AtomList atomlist_local = mole.get_atom_list();
   const size_t natom = atomlist_local.size();
   for( size_t iatom = 0; iatom < natom; iatom++ ){
    Atom atom_i = atomlist_local.at(iatom);
    os << atom_i << endl;
   }
   return os;
  }

  coordinate_type get_center_of_mass(){
   coordinate_type retval;
   double x_average = 0.0e0;
   double y_average = 0.0e0;
   double z_average = 0.0e0;
   for( size_t iatom = 0; iatom < this->natom_; iatom++ ){
    x_average += this->atom_list.at(iatom).get_x() * this->atom_list.at(iatom).get_mass();
    y_average += this->atom_list.at(iatom).get_y() * this->atom_list.at(iatom).get_mass();
    z_average += this->atom_list.at(iatom).get_z() * this->atom_list.at(iatom).get_mass();
   }
   x_average = x_average/this->mass_;
   y_average = y_average/this->mass_;
   z_average = z_average/this->mass_;
   using std::make_tuple;
   retval = make_tuple( x_average, y_average, z_average );
   return retval;
  }

public:
  atom_list_type atom_list() const 
    { return this->atom_list_; }
  charge_value_type charge() const
    { return this->charge_; }
  molecule_id_type molecule_id() const
    { return this->molecule_id_; }

private:
  atom_list_type     atom_list_;
  charge_value_type  charge_;
  array<int, 3>      translation_vec_;
  molecule_id_type   molecule_id_;

}; // end of class Molecule

} // end of namespace structure

} // end of namespace iquads

#endif
