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

#ifndef ATOM_LIST_HPP
#define ATOM_LIST_HPP

#include <vector>
#include <geometrical_space/threed_space_function.hpp>
#include <structure/atom.hpp>
#include <structure/geometry_unit.hpp>

namespace iquads {

  using std :: vector;
  using namespace geometrical_space :: threed_space;

  namespace structure {
  
    /**
     *  Typedef an the list of atoms.
     *  It serves as the container type of atoms in 
     *  molecules, lattice, unit cells, polymers, etc.
     *  Not in class Atom since this container is for a group of atoms.
     *
     *  This is only a typedef. Concerns about the geometry units may arise.
     *  If an AtomList is returned from a molecule, polymer or crystal, then it will 
     *  be safe since these classes have unit align operations when constructed.
     *  If an AtomList simply comes from a group of atoms, then developers must know
     *  whether units are the same among atoms, or the below function align_geometry_unit()
     *  must be called if they are not sure.
     */
    typedef vector< Atom > AtomList;

    /**
     *  + align_geometry_unit()
     *    geometry units of all atoms  will be aligned 
     *    to be the same as that of the first atom 
     *    in the atom list.
     */
    inline 
    void align_geometry_unit( AtomList& atom_list_obj ) {
      using geometry_unit :: unit_conversion_constant;
      for( size_t iatom = 0; iatom < atom_list_obj.size(); iatom++ ) {
        atom_list_obj[iatom].set_coordinate() *= unit_conversion_constant( atom_list_obj.at(iatom).geometry_unit(), 
                                                                           atom_list_obj.at(0).geometry_unit() );
      }
    } // end of inline function align_geometry_unit()

    /**
     *  + align_geometry_unit()
     *    geometry units of the last atom will be aligned 
     *    to be the same as that of the first atom 
     *    in the atom list.
     *    This function can be used in the push_back() where we
     *    attach a new atom to an atom list to make sure all geometry 
     *    units are the same for coordinates.
     *    Compared to align_geometry_unit(), we don't run the loop
     *    over all atoms but the developer must assure that all previous
     *    atoms are in the same geometry unit.
     */
    inline
    void align_geometry_unit_for_the_last_atom( AtomList& atom_list_obj ) {
      using geometry_unit :: unit_conversion_constant;
      (atom_list_obj.rbegin())->set_coordinate() *= 
                 unit_conversion_constant( (atom_list_obj.rbegin())->geometry_unit(), 
                                           (atom_list_obj.begin())->geometry_unit() );
    } // end of inline function align_geometry_unit_for_the_last_atom()
 
  } // end of namespace structure

} // end of namespace iquads

#endif
