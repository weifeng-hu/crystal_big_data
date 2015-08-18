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

#ifndef LATTICE_H
#define LATTICE_H

#include <string>
#include <vector>
#include "utilities/solid_gen/unit_cell.h"
#include "utilities/solid_gen/lattice_base.h"

namespace iquads {

using namespace basic;

namespace crystal {

  template class lattice_base<atomic_ucell>;
  template class lattice_base<molecular_ucell>;

  typedef lattice_base<atomic_ucell> atomic_lattice;
  typedef lattice_base<molecular_ucell> molecular_lattice;

} // end of namespace crystal

} // end of namespace iquads

#endif
