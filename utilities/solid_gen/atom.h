#ifndef ATOM_H
#define ATOM_H

#include <stdio.h>
#include <vector>
#include <array>
#include <string>
#include <tuple>
#include <iostream>
#include <fstream>
#include "utilities/solid_gen/coordinate.h"
#include "utilities/solid_gen/threed_space_function.h"

using namespace std;

namespace iquads {

namespace basic {

struct atom {
public:
  atom(){
   this->element_ = "not set";
   this->coordinate.fill(0.0e0);
   this->charge_ = 0;
  }
  atom( string element, double x, double y, double z, int charge ){
   this->set_info( element, x, y, z, charge );
  }

public:
  bool within_radius( double Radius ){
   Coord orig = make_tuple(0.0e0, 0.0e0, 0.0e0);
   Coord this_coord 
    = make_tuple( this->coordinate.at(0), this->coordinate.at(1), 
                  this->coordinate.at(2) );
   double R = threed_space :: compute_distance( orig, this_coord );
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
   return ifs;
  }

public:
  void set_info( string element, double x, double y, double z, int charge)
  {
   this->element_ = element;
   this->coordinate.at(0) = x;
   this->coordinate.at(1) = y;
   this->coordinate.at(2) = z;
   this->charge_ = charge;
  }

  array< array<double, 2>, 3 > get_edges(){
   array< array<double, 2>, 3 > retval;
   retval.at(0) = array<double, 2> { this->coordinate.at(0), this->coordinate.at(0) };
   retval.at(1) = array<double, 2> { this->coordinate.at(1), this->coordinate.at(1) };
   retval.at(2) = array<double, 2> { this->coordinate.at(2), this->coordinate.at(2) };
   return retval;
  }

  void print_info(){
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

  string& set_element() { return this->element_; }
  double& set_x() { return this->coordinate.at(0); }
  double& set_y() { return this->coordinate.at(1); }
  double& set_z() { return this->coordinate.at(2); }
  void set_coordinate( Coord new_coord ){
   const double x = get<0>( new_coord );
   const double y = get<1>( new_coord );
   const double z = get<2>( new_coord );
   this->coordinate.at(0) = x;
   this->coordinate.at(1) = y;
   this->coordinate.at(2) = z;
  }
  int& set_charge() { return this->charge_; }

private:
  // we use vector for coordinate 
  // since for a general storage case, these 
  // objects will be stored in the heap and invoked to stack
  array<double, 3> coordinate; 
  int charge_;
  string element_;

};

typedef vector<atom> AtomList;

} // end of namespace basic

} // end of namespace iquads

#endif
