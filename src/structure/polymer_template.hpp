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


#ifndef POLYMER_TEMPLATE_HPP
#define POLYMER_TEMPLATE_HPP

#include <vector>
#include <iostream>
#include <geometrical_space/threed_space.hpp>
#include <geometrical_space/threed_space_function.hpp>
#include <geometrical_space/coordinate.hpp>
#include <structure/atom_list.hpp>
#include <structure/molecule.hpp>
#include <structure/molecule_list.hpp>


namespace iquads {

using namespace geometrical_space :: threed_space;
using std :: cout;
using std :: endl;
using std :: array;


  /**
   *  A template class to store polymer information
   *   + A list of molecules
   *     We use std :: array instead of std :: vector for molecule list
   *     because this polymer class can be compile-time instantiated in 
   *     the code, i.e., a developer always knows how many molecules will 
   *     be included.
   *
   *  In many body expansion, polymers are also the interface to different 
   *  terms, as well as the object to produce the euclidean distance matrix
   *
   */

namespace structure {

template< size_t NUM > class Polymer {
public:
  typedef Polymer< NUM >  this_type;
  typedef Molecule         molecule_type;
  /**
   *  This is the vector< Molecule >, we call it external.
   *  The number of molecules is known at run-time.
   */
  typedef MoleculeList                  external_molecule_list_type;
  typedef array< molecule_type, NUM >   molecule_list_type;
  typedef AtomList                      atom_list_type;
  typedef molecule_type :: charge_value_type      charge_value_type;
  typedef molecule_type :: mass_value_type        mass_value_type;
  typedef molecule_type :: coordinate_type        coordinate_type;
  typedef vector< coordinate_type >               coordinate_list_type;
  typedef bool condition_type;

  typedef molecule_list_type& molecule_list_ref;

public:
  /**
   *  We let the compiler make the default constructor, as long 
   *  as the Molecule object has its well-defined default constructor
   *  Here we write a simple initialize list constructor
   */
  Polymer() {};
  Polymer( molecule_list_type molecule_list ) :
    molecule_list_ ( molecule_list ) { }

public:
  /**
   *  These functions can be useful in actual crystal treatments
   *  in a typical many body expansion calculation
   */

  /**
   *  + within_distance()
   *    Judges whether all atoms in the polymer are within the distance.
   */
  condition_type within_distance( double distance ){
    condition_type retval = true;
    coordinate_list_type coord_list_local = this->coordinate_list();
    for( size_t icoord = 0; icoord < coord_list_local.size(); icoord++ ) {
      for( size_t jcoord = 0; jcoord < coord_list_local.size(); jcoord++ ) {
        double dist = compute_distance( coord_list_local[icoord], coord_list_local[jcoord] );
        if( ( dist - distance ) > 0.0e0 ) { return false; }
      }
    }
    return true;
  }

  /**
   *  + within_mean_distance_by_center_of_mass()
   *    Judges whether the mean distance, calculated by center of mass, 
   *    is within a distance threshold
   */
  condition_type within_mean_distance_by_center_of_mass( double distance ) {
    return ( ( this->mean_distance_by_center_of_mass() - distance ) <= 0.0e0 ? true : false );
  }

  /**
   *  + within_mean_distance_by_center()
   *    Judges whether the mean distance, calculated by geometrical centers , 
   *    is within a distance threshold
   */
  condition_type within_mean_distance_by_center( double distance ) {
    return ( ( this->mean_distance_by_center() - distance ) <= 0.0e0 ? true : false );
  }

public:
  /**
   *  Stream operators
   *  + operator <<
   *    Also we have to set this_type as non-const for the cv qualification
   *    in order to use operator[] of molcule objects.
   *    Invokes the operator<< of molecule objects
   */  
  friend 
  ostream& operator<< ( ostream& os, const this_type& polymer_obj ) {
    for( size_t imolecule = 0; imolecule < NUM; imolecule++ ) {
      molecule_type molecule = polymer_obj[imolecule];
      os << molecule << endl;
    }
    return os;
  }


  /**
   *  + operator >>
   *    Invokes the operator >> of molecule objects
   */
  friend
  istream& operator>> ( istream& is, this_type& polymer_obj ) {
    for( size_t imolecule = 0; imolecule < NUM; imolecule++ ) {
      molecule_type new_molecule;
      is >> new_molecule;
      polymer_obj[imolecule] = new_molecule;
    }
    return is;
  }

public:
  /**
   *  Container related member functions
   *  This polymer object class is like a std::array,
   *  so not like std::vector, we only have quite a few 
   *  member functions here.
   */
  molecule_type& at( size_t i )
    { return this->molecule_list_.at(i); }
  molecule_type& operator[] ( size_t i )
    { return this->molecule_list_[i]; }

  /**
   *  This operator() allows us to return a 
   *  monomer object, when can be used for further 
   *  arithmetic operations of polymers.
   *  We cannot overload at() since function cannot be 
   *  overloaded simply by return type.
   */
  Polymer<1> operator() ( size_t i ) 
    {
      array< molecule_type, 1 > monomer_obj;
      monomer_obj[0] = this->molecule_list_[i];
      return Polymer<1>( monomer_obj );
    }

public:
  /**
   *  Accessors
   */
  molecule_list_type molecule_list() const 
    { return this->molecule_list_; }

  /**
   *  Auxiliary accessors
   */

  /**
   *  + atom_list()
   *    A handy function to return the whole atom list of the polymer object
   */
  atom_list_type atom_list() const {
    atom_list_type retval;
    for( size_t imolecule = 0; imolecule < NUM; imolecule++ ) {
      atom_list_type atomlist_i = this->molecule_list_[imolecule].atom_list();
      retval.insert( retval.end(), atomlist_i.begin(), atomlist_i.end() );
    }
    return retval;
  }
  // should think about using std::move() to append vectors

  /**
   *  + charge()
   *    charge value is computed on the fly.
   */
  charge_value_type charge() const {
    charge_value_type retval = 0;
    for( size_t imolecule = 0; imolecule < NUM; imolecule++ ) {
      retval += this->molecule_list_[imolecule].charge();
    }
    return retval;
  }

  /**
   *  + natom()
   *    natom value is computed on the fly.
   *    We don't use size() to name it since it can mean 
   *    number of molecules in the polymer. So we name it 
   *    here more specifically.
   */
  size_t natom() const {
    size_t retval = 0;
    for( size_t imolecule = 0; imolecule < NUM; imolecule++ ) {
      retval += this->molecule_list_[imolecule].size();
    }
    return retval;
  }

  /**
   *  + mass()
   *    mass value is computed on the fly.
   */
  mass_value_type mass() const {
    mass_value_type retval = 0;
    for( size_t imolecule = 0; imolecule < NUM; imolecule++ ) {
      retval += this->molecule_list_[imolecule].mass();
    }
    return retval;
  }

  /**
   *  + coordinate_list()
   *    Returns the pure coordinate list
   *    This function serves as an interface to build the euclidean distance matrix
   */
  coordinate_list_type coordinate_list(){
    coordinate_list_type retval;
    for( size_t imolecule = 0; imolecule < NUM; imolecule++ ) {
      for( size_t iatom = 0; iatom < this->molecule_list_[imolecule].size(); iatom++ ) {
        retval.push_back( this->molecule_list_[imolecule][iatom].coordinate() );
      }
    }
    return retval;
  }

  /**
   *  + mean_distance_by_center()
   *    Returns the mean distance among molecular geometrical centers.
   */
  double mean_distance_by_center() {
    double retval = 0.0e0;
    if( NUM == 1 ) return 0.0e0;
    int count = 0;
    for( size_t imolecule = 0; imolecule < NUM; imolecule++ ) {
      coordinate_type coord_i = this->molecule_list_[imolecule].center();
      for( size_t jmolecule = imolecule + 1; jmolecule < NUM; jmolecule++ ) {
        coordinate_type coord_j = this->molecule_list_[jmolecule].center();
        retval += compute_distance( coord_i, coord_j );
        count = count + 1;
      }
    }
    retval = retval/(double)( count );
    return retval;
  }

  /**
   *  + mean_distance_by_center_of_mass()
   *    Returns the mean distance among molecular centers of mass.
   */
  double mean_distance_by_center_of_mass() {
    double retval = 0.0e0;
    if( NUM == 1 ) return 0.0e0;
    int count = 0;
    for( size_t imolecule = 0; imolecule < NUM; imolecule++ ){
      coordinate_type coord_i = this->molecule_list_[imolecule].center_of_mass();
      for( size_t jmolecule = imolecule+1; jmolecule < NUM; jmolecule++ ){
        coordinate_type coord_j = this->molecule_list_[jmolecule].center_of_mass();
        retval += compute_distance( coord_i, coord_j );
        count = count + 1;
      }
    }
    retval = retval/(double)( count );
    return retval;
  }

  /**
   *  Mutators
   */
  molecule_list_ref set_molecule_list() const 
    { return this->molecule_list_; }

private:
  molecule_list_type molecule_list_;

}; // end of template class Polymer

/**
 *  These are auxiliary functions 
 *  as interfaces between molecules and polymers
 */

/**
 *  convert_polymer_to_molecule()
 *  Returns a Molecule object by feeding a polymer object
 *  We did put this function as Molecule class or Polymer class member functions
 *  because it may produce a loop "include" of molecule and polymer head files.
 *  Also because these functions do not necessarily need to work with an object
 *  They can be static.
 */

template < size_t NUM > inline Molecule convert_polymer_to_molecule( Polymer<NUM> polymer_obj ) {

  typename Polymer<NUM> :: atom_list_type new_atom_list = polymer_obj.atom_list();
  typename Polymer<NUM> :: charge_value_type charge = polymer_obj.charge();
  return Molecule( new_atom_list, charge );

} // end of function convert_polymer_to_molecule()


/**
 *  This operator+ will be useful as we combine two 
 *  polymers together into a big polymer.
 */

template < size_t NUM_1, size_t NUM_2, size_t NUM_3 = NUM_1 + NUM_2 > inline Polymer< NUM_3 > 
operator+ ( Polymer<NUM_1> polymer_obj_1, Polymer<NUM_2> polymer_obj_2 ) {

  typename Polymer<NUM_1> :: molecule_list_type molecule_list_1 = polymer_obj_1.molecule_list();
  typename Polymer<NUM_2> :: molecule_list_type molecule_list_2 = polymer_obj_2.molecule_list();
  typename Polymer<NUM_3> :: molecule_list_type molecule_list_3;
  for( size_t i = 0; i < NUM_1; i++ ) {
    molecule_list_3[i] = molecule_list_1[i];
  }
  for( size_t i = 0; i < NUM_2; i++ ) {
    molecule_list_3[ i + NUM_1 ] = molecule_list_2[i];
  }

  return Polymer< NUM_3 > ( molecule_list_3 );

} // end of operator+ ()

} // end of structure

} // end of iquads

#endif
