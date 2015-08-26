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


#ifndef POLYMER_TEMPLATE_H
#define POLYMER_TEMPLATE_H

#include <vector>
#include <iostream>
#include <geometrical_space/threed_space.h>
#include <geometrical_space/threed_space_function.h>
#include <geometrical_space/coordinate.h>
#include <particle/atom.h>
#include <structure/molecule.h>

using std::vector;
using std::cout;
using std::endl;

namespace iquads {

using namespace geometrical_space :: threed_space;
using namespace particle;

namespace structure {

template< size_t NUM >
struct Polymer {
public:
  Polymer(){
   this->n_molecule_ = NUM;
   this->group.resize( NUM );
   this->natom_ = 0;
   this->mass_ = 0.0e0;
  }
  Polymer( MoleculeList poly ){
   this->n_molecule_ = NUM;
   this->group.resize( NUM );
   this->natom_ = 0;
   this->mass_ = 0.0e0;
   this->init_from( poly );
  }

public:
  void init_from( MoleculeList new_molecule_list ){
   try{
    const size_t n_molecule = new_molecule_list.size();
    if( n_molecule != this->n_molecule_ ) throw n_molecule;
    for( size_t imolecule = 0; imolecule < this->n_molecule_; imolecule++ ){
     this->group.at(imolecule) = new_molecule_list.at(imolecule);
     const size_t natom_i = new_molecule_list.at(imolecule).get_natom();
     this->natom_ += natom_i;
     const double mass_i = new_molecule_list.at(imolecule).get_mass();
     this->mass_ += mass_i;
    }
   }
   catch ( size_t n ){
    cout << " polymer exception: init_from() " << endl;
    cout << " n_molecule " << n << " != " << this->n_molecule_ << endl;
    abort();
   }
  }

public:
  bool within_radius( double radius ){
   bool retval = true;
   CoordList coordlist_local = this->get_coordinate_list();
   const size_t ncoord_local = coordlist_local.size();
   for( size_t icoord = 0; icoord < ncoord_local; icoord++ ){
    for( size_t jcoord = 0; jcoord < icoord; jcoord++ ){
     double dist = compute_distance( coordlist_local.at(icoord), coordlist_local.at(jcoord) );
     if( ( dist - radius ) > 0.0e0 ){
      retval = false;
      goto end;
     }
    }
   }
end:
   return retval;
  }

  bool within_mean_radius_by_center_of_mass( double radius ){
//    const double dist = this->compute_mean_distance_by_center_of_mass();
//    cout << " dist of center of mass "  << dist << "  radius " << radius << "  dist <= radius ? " << (dist <= radius) << endl;
    return ( this->compute_mean_distance_by_center_of_mass() <= radius ? true : false );
  }

  bool within_mean_radius_by_center( double radius ){
   return ( this->compute_mean_distance_by_center() <= radius ? true : false );
  }

  double compute_mean_distance_by_center(){
   double retval = 0.0e0;
   int count = 0;
   for( size_t imole = 0; imole < this->n_molecule_; imole++ ){
    Coord com_i = this->group.at(imole).get_center();
    for( size_t jmole = imole+1; jmole < this->n_molecule_; jmole++ ){
     Coord com_j = this->group.at(jmole).get_center();
     retval += compute_distance( com_i, com_j );
     count = count + 1;
    }
   }
   retval = retval/count;
   return retval;
  }

  double compute_mean_distance_by_center_of_mass(){
   double retval = 0.0e0;
   int count = 0;
   for( size_t imole = 0; imole < this->n_molecule_; imole++ ){
    Coord com_i = this->group.at(imole).get_center_of_mass();
    for( size_t jmole = imole+1; jmole < this->n_molecule_; jmole++ ){
     Coord com_j = this->group.at(jmole).get_center_of_mass();
     retval += compute_distance( com_i, com_j );
     count = count + 1;
    }
   }
   retval = retval/count;
   return retval;
  }

public:
  // interface to Euclidean distance matrix
  CoordList get_coordinate_list(){
   CoordList retval;
   for( size_t imolecule = 0; imolecule < NUM; imolecule++ ){
    Molecule mole_i = group.at(imolecule);
    CoordList coordlist_i = mole_i.get_coordinate_list();
    retval.insert( retval.end(), coordlist_i.begin(), coordlist_i.end() );
   }
   return retval;
  }
  AtomList get_atom_list(){
   AtomList retval;
   for( size_t imolecule = 0; imolecule < NUM; imolecule++ ){
    Molecule mole_i = group.at(imolecule);
    AtomList atomlist_i = mole_i.get_atom_list();
    retval.insert( retval.end(), atomlist_i.begin(), atomlist_i.end() );
   }
   return retval;
  }
  // should think about using std::move() to append vectors

  friend 
  ostream& operator<< ( ostream& os, Polymer<NUM> polymer ){
   const size_t n_member = NUM;
   for( size_t imember = 0; imember < n_member; imember++ ){
    Molecule mole_i = polymer.set_member(imember);
    os << mole_i << endl;
   }
   return os;
  }

public:
  MoleculeList get_group() const { return this->group; }
  size_t get_natom() const { return this->natom_; }
  double get_mass() const { return this->mass_; }
public:
  Polymer<1> at( size_t i ) 
   { 
     MoleculeList mole_list;
     mole_list.push_back( group.at(i) );
     Polymer<1> retval(mole_list);
     return retval;
   }

private:
  Molecule& set_member( size_t i ){ return group.at(i); }

private:
  vector< Molecule > group;
  double mass_;
  size_t n_molecule_;
  size_t natom_;

}; // end of template class Polymer

template < size_t NUM_1, size_t NUM_2, size_t NUM_3 = NUM_1 + NUM_2 > Polymer< NUM_3 > 
 operator+ ( Polymer<NUM_1> poly_a, Polymer<NUM_2> poly_b )
{

}

} // end of structure

} // end of iquads

#endif
