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

#ifndef MOLECULE_HPP
#define MOLECULE_HPP

#include <vector>
#include <string>
#include <tuple>
#include <fstream>
#include <iostream>
#include <geometrical_space/coordinate.hpp>
#include <structure/atom.hpp>

using std::vector;
using std::string;
using std::tuple;
using std::cout;
using std::endl;
using std::fstream;

namespace iquads {

using geometrical_space :: Coord;
using geometrical_space :: CoordList;

namespace structure {

struct Molecule{
public:
  typedef Atom atom_type; 
  typedef Coord coordinate_type;

  typedef atom_type& atom_ref;

public:
  Molecule(){
   this->atom_list.resize(0);
   this->molecule_name_ = "not set";
   this->natom_ = 0;
   this->mass_ = 0.0e0;
  }
  Molecule( string molecule_name ){
   this->atom_list.resize(0);
   this->molecule_name_ = molecule_name;
   this->natom_ = 0;
   this->mass_ = 0.0e0;
  }

public:
  void add_atom( atom_type new_atom ){
   this->atom_list.push_back( new_atom );
   this->natom_ += 1;
   this->mass_ += new_atom.get_mass();
  }

public:
  bool within_radius( double Radius ){
   bool retval = true;
   size_t n_atom_local = this->atom_list.size();
   for( size_t iatom = 0; iatom < n_atom_local; iatom++ ){
    atom_type atom_local = atom_list.at(iatom);
    if( atom_local.within_radius( Radius ) == false ){
     retval = false;
     break;
    }
   }
   return retval;
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

  array< array<double, 2>, 3 > get_edges(){
   array< array<double, 2>, 3 > retval;
   size_t natom_local = this->atom_list.size();
   double x_plus  = this->atom_list.at(0).get_edges().at(0).at(0);
   double x_minus = this->atom_list.at(0).get_edges().at(0).at(1);
   double y_plus  = this->atom_list.at(0).get_edges().at(1).at(0);
   double y_minus = this->atom_list.at(0).get_edges().at(1).at(1);
   double z_plus  = this->atom_list.at(0).get_edges().at(2).at(0);
   double z_minus = this->atom_list.at(0).get_edges().at(2).at(1);
   for( size_t iatom = 0; iatom < natom_local; iatom++ ){
    array< array<double, 2>, 3> edges_atom
     = this->atom_list.at(iatom).get_edges();
    if( ( edges_atom.at(0).at(0) - x_plus ) >= 0.0e0 )
     { x_plus = edges_atom.at(0).at(0); }
    if( ( edges_atom.at(1).at(0) - y_plus ) >= 0.0e0 )
     { y_plus = edges_atom.at(1).at(0); }
    if( ( edges_atom.at(2).at(0) - z_plus ) >= 0.0e0 )
     { z_plus = edges_atom.at(2).at(0); }

    if( ( edges_atom.at(0).at(1) - x_minus ) < 0.0e0 )
     { x_minus = edges_atom.at(0).at(1); }
    if( ( edges_atom.at(1).at(1) - y_minus ) < 0.0e0 )
     { y_minus = edges_atom.at(1).at(1); }
    if( ( edges_atom.at(2).at(1) - z_minus ) < 0.0e0 )
     { z_minus = edges_atom.at(2).at(1); }
   }
   retval.at(0) = array<double, 2> { x_plus, x_minus };
   retval.at(1) = array<double, 2> { y_plus, y_minus };
   retval.at(2) = array<double, 2> { z_plus, z_minus };
   return retval;
  }


public:
  AtomList get_atom_list() const { return this->atom_list; }
  atom_type get_atom( size_t i ) const { return this->atom_list.at(i); }
  string get_name() const { return this->molecule_name_; }
  size_t get_natom() const { return this->natom_; }
  double get_mass() const { return this->mass_; }

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

  coordinate_type get_center(){
   coordinate_type retval;
   double x_average = 0.0e0;
   double y_average = 0.0e0;
   double z_average = 0.0e0;
   for( size_t iatom = 0; iatom < this->natom_; iatom++ ){
    x_average += this->atom_list.at(iatom).get_x();
    y_average += this->atom_list.at(iatom).get_y();
    z_average += this->atom_list.at(iatom).get_z();
   }
   x_average = x_average/this->natom_;
   y_average = y_average/this->natom_;
   z_average = z_average/this->natom_;
   using std::make_tuple;
   retval = make_tuple( x_average, y_average, z_average );

   return retval;
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

private:
  // we enforce the use of vector to store atom_list in the heap
  // Note the that the construction of the atom coordinate is also
  // in the heap
  AtomList atom_list;
  array<int, 3> translation_vec;
  size_t natom_;
  double mass_;
  string molecule_name_;

}; // end of class Molecule

typedef vector<Molecule> MoleculeList;

} // end of namespace structure

} // end of namespace iquads

#endif
