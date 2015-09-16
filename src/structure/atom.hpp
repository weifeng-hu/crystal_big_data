/*
 *  This source code applies all the terms in 
 *  GNU GENERAL PUBLIC LICENSE (GPL), Version3, 29 June 2007.
 *
 *  Copyright (C) 2013-2015 Weifeng Hu, all rights reserved.
 *  
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
using std::array;
using std::string;
using std::tuple;
using std::ostream;
using std::ifstream;

namespace iquads {

namespace structure {

using geometrical_space :: Coord;

class Atom {
public:
  typedef Atom this_type;
  typedef int charge_type;
  typedef string element_type;
  typedef double mass_type;
  typedef double coordinate_value_type;
  typedef Coord coordinate_type;
  typedef bool condition_type;

  typedef element_type& element_ref;
  typedef coordinate_value_type& coordinate_value_ref;
  typedef charge_type& charge_ref;
  typedef mass_type& mass_ref;

public:
  Atom()
    {
      this->element_ = "not set";
      this->coordinate.fill(0.0e0);
      this->charge_ = 0;
      this->mass_ = 0.0e0;
    }
  Atom( element_type element, 
        coordinate_value_type x, 
        coordinate_value_type y, 
        coordinate_value_type z, 
        charge_type charge, mass_type mass ){
   this->set_info( element, x, y, z, charge, mass );
  }

public:
  condition_type within_radius( double Radius ){
   using std::make_tuple;
   coordinate_type orig = make_tuple(0.0e0, 0.0e0, 0.0e0);
   coordinate_type this_coord 
    = make_tuple( this->coordinate.at(0), this->coordinate.at(1),
                  this->coordinate.at(2) );
   using iquads :: geometrical_space :: threed_space :: compute_distance;
   double R = compute_distance( orig, this_coord );
   return ( R <= Radius ) ? true : false;
  }

  void operator+= ( array<coordinate_value_type, 3> x ){
   this->coordinate.at(0) += x.at(0);
   this->coordinate.at(1) += x.at(1);
   this->coordinate.at(2) += x.at(2);
  }

  friend ifstream& operator>> ( ifstream& ifs, Atom& new_atom ){
   ifs >> new_atom.set_element();
   ifs >> new_atom.set_x();
   ifs >> new_atom.set_y();
   ifs >> new_atom.set_z();
   ifs >> new_atom.set_charge();
   ifs >> new_atom.set_mass();
   return ifs;
  }

public:
  void set_info( element_type element, 
                 coordinate_value_type x, 
                 coordinate_value_type y, 
                 coordinate_value_type z, charge_type charge, mass_type mass )
  {
   this->element_ = element;
   this->coordinate.at(0) = x;
   this->coordinate.at(1) = y;
   this->coordinate.at(2) = z;
   this->charge_ = charge;
   this->mass_ = mass;
  }

  array< array<double, 2>, 3 > get_edges(){
   array< array<double, 2>, 3 > retval;
   retval.at(0) = array<double, 2> { this->coordinate.at(0), this->coordinate.at(0) };
   retval.at(1) = array<double, 2> { this->coordinate.at(1), this->coordinate.at(1) };
   retval.at(2) = array<double, 2> { this->coordinate.at(2), this->coordinate.at(2) };
   return retval;
  }

  void print_info(){
   using std::cout;
   using std::endl;
   char line[100];
//   sprintf( line, "(%s)   X(%12.8f)  Y(%12.8f)  Z(%12.8f)  CHARGE(%d)", 
//                  this->element_.c_str(), this->coordinate.at(0),
//                  this->coordinate.at(1), this->coordinate.at(2),
//                  this->charge_);
   sprintf( line, "%s   %12.8f  %12.8f  %12.8f  ", 
                  this->element_.c_str(), this->coordinate.at(0),
                  this->coordinate.at(1), this->coordinate.at(2)
                  );
   cout << line << endl;
  }

  friend ostream& operator<< ( ostream& os, Atom& atom_ ){
   using std::fixed;
   using std::setw;
   using std::setprecision;
   os << atom_.get_element().c_str() << "  ";
   os << fixed << setw(12) << setprecision(8) << atom_.get_x() << "  ";
   os << fixed << setw(12) << setprecision(8) << atom_.get_y() << "  ";
   os << fixed << setw(12) << setprecision(8) << atom_.get_z() << "  ";
   return os;
  }

  void print_atomlist(){
   this->print_info();
  }

public:
  element_type get_element() const { return this->element_; }
  coordinate_value_type get_x() const { return this->coordinate.at(0); }
  coordinate_value_type get_y() const { return this->coordinate.at(1); }
  coordinate_value_type get_z() const { return this->coordinate.at(2); }
  // interface from vector to tuple
  coordinate_type get_coordinate_set() const {
   const coordinate_value_type x = this->get_x();
   const coordinate_value_type y = this->get_y();
   const coordinate_value_type z = this->get_z();
   Coord set = Coord( x, y, z );
   return set;
  }
  charge_type get_charge() const { return this->charge_; }
  mass_type get_mass() const { return this->mass_; }

  element_ref set_element() { return this->element_; }
  coordinate_value_ref set_x() { return this->coordinate.at(0); }
  coordinate_value_ref set_y() { return this->coordinate.at(1); }
  coordinate_value_ref set_z() { return this->coordinate.at(2); }
  void set_coordinate( coordinate_type new_coord ){
   using std::get;
   const coordinate_value_type x = get<0>( new_coord );
   const coordinate_value_type y = get<1>( new_coord );
   const coordinate_value_type z = get<2>( new_coord );
   this->coordinate.at(0) = x;
   this->coordinate.at(1) = y;
   this->coordinate.at(2) = z;
  }
  charge_ref set_charge() { return this->charge_; }
  mass_ref set_mass() { return this->mass_; }

  coordinate_type get_center() {
   using std::make_tuple;
   coordinate_type retval = make_tuple( this->get_x(), this->get_y(), this->get_z() );
   return retval;
  }

  coordinate_type get_center_of_mass() {
   using std::make_tuple;
   coordinate_type retval = make_tuple( this->get_x(), this->get_y(), this->get_z() );
   return retval;
  }

  array<int, 3>& set_translation_vec()
   { return this->translation_vec; }

private:
  // we use vector for coordinate 
  // since for a general storage case, these 
  // objects will be stored in the heap and invoked to stack
  array<coordinate_value_type, 3> coordinate;
  array<int, 3> translation_vec;
  charge_type  charge_;
  mass_type    mass_;
  element_type element_;

};

typedef vector<Atom> AtomList;

} // end of namespace particle

} // end of namespace iquads

#endif
