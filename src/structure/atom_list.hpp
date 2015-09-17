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
#include <structure/atom.hpp>

namespace iquads {

  using std :: vector;
    
  namespace structure {
  
    /**
     *  Typedef an the list of atoms.
     *  This typedef can be useful in all higher level objects, 
     *  summoned by molecules, lattice, unit cells, polymers, etc.
     */
    typedef vector< Atom > AtomList;
    
  } // end of namespace structure

} // end of namespace iquads

#endif
