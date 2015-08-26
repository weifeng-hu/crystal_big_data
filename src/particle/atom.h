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

#ifndef ATOM_H
#define ATOM_H

#include <stdio.h>
#include <vector>
#include <array>
#include <string>
#include <tuple>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <geometrical_space/coordinate.h>
#include <geometrical_space/threed_space_function.h>

using std::vector;
using std::array;
using std::string;
using std::tuple;
using std::ostream;
using std::ifstream;

namespace iquads {

namespace particle {

using iquads :: geometrical_space :: Coord;

struct atom {
public:
  atom(){
   this->element_ = "not set";
   this->coordinate.fill(0.0e0);
   this->charge_ = 0;
   this->mass_ = 0.0e0;
  }
  atom( string element, double x, double y, double z, int charge, double mass ){
   this->set_info( element, x, y, z, charge, mass );
  }

public:
  bool within_radius( double Radius ){
   using std::make_tuple;
   Coord orig = make_tuple(0.0e0, 0.0e0, 0.0e0);
   Coord this_coord 
    = make_tuple( this->coordinate.at(0), this->coordinate.at(1),
                  this->coordinate.at(2) );
   using iquads :: geometrical_space :: threed_space :: compute_distance;
   double R = compute_distance( orig, this_coord );
   return ( R <= Radius ) ? true : false;
  }

  void operator+= ( array<double, 3> x ){
   this->coordinate.at(0) += x.at(0);
   this->coordinate.at(1) += x.at(1);
   this->coordinate.at(2) += x.at(2);
  }

  friend ifstream& operator>> ( ifstream& ifs, atom& new_atom ){
   ifs >> new_atom.set_element();
   ifs >> new_atom.set_x();
   ifs >> new_atom.set_y();
   ifs >> new_atom.set_z();
   ifs >> new_atom.set_charge();
   ifs >> new_atom.set_mass();
   return ifs;
  }

public:
  void set_info( string element, double x, double y, double z, int charge, double mass )
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

  friend ostream& operator<< ( ostream& os, atom& atom_ ){
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
  string get_element() const { return this->element_; }
  double get_x() const { return this->coordinate.at(0); }
  double get_y() const { return this->coordinate.at(1); }
  double get_z() const { return this->coordinate.at(2); }
  // interface from vector to tuple
  Coord get_coordinate_set(){
   const double x = this->get_x();
   const double y = this->get_y();
   const double z = this->get_z();
   Coord set = Coord( x, y, z );
   return set;
  }
  int get_charge() const { return this->charge_; }
  double get_mass() const { return this->mass_; }

  string& set_element() { return this->element_; }
  double& set_x() { return this->coordinate.at(0); }
  double& set_y() { return this->coordinate.at(1); }
  double& set_z() { return this->coordinate.at(2); }
  void set_coordinate( Coord new_coord ){
   using std::get;
   const double x = get<0>( new_coord );
   const double y = get<1>( new_coord );
   const double z = get<2>( new_coord );
   this->coordinate.at(0) = x;
   this->coordinate.at(1) = y;
   this->coordinate.at(2) = z;
  }
  int& set_charge() { return this->charge_; }
  double& set_mass() { return this->mass_; }

  Coord get_center() {
   using std::make_tuple;
   Coord retval = make_tuple( this->get_x(), this->get_y(), this->get_z() );
   return retval;
  }

  Coord get_center_of_mass() {
   using std::make_tuple;
   Coord retval = make_tuple( this->get_x(), this->get_y(), this->get_z() );
   return retval;
  }

  array<int, 3>& set_translation_vec()
   { return this->translation_vec; }

private:
  // we use vector for coordinate 
  // since for a general storage case, these 
  // objects will be stored in the heap and invoked to stack
  array<double, 3> coordinate;
  array<int, 3> translation_vec;
  int charge_;
  double mass_;
  string element_;

};

typedef vector<atom> AtomList;

} // end of namespace particle

} // end of namespace iquads

#endif
