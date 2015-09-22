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

#ifndef UNIT_CELL_INSTANT_HPP
#define UNIT_CELL_INSTANT_HPP

#include <structure/atom.hpp>
#include <structure/molecule.hpp>
#include <structure/unit_cell_template.hpp>

namespace iquads{

namespace structure {

  /**
   * explicit template instantiation and typedef for unit cells
   */
  template class UnitCell<Atom>;
  template class UnitCell<Molecule>;

  typedef UnitCell<Atom>       AtomicUnitCell;
  typedef UnitCell<Molecule>   MolecularUnitCell;

} // end of namespace structure 

} // end of namespace iquads

#endif
