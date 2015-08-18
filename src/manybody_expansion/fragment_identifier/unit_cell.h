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

#ifndef UNIT_CELL_H
#define UNIT_CELL_H

#include "utilities/solid_gen/atom.h"
#include "utilities/solid_gen/molecule.h"
#include "utilities/solid_gen/unit_cell_base.h"

using namespace std;

namespace iquads{

using namespace basic;

namespace crystal{

  template class unit_cell_base<atom>;
  template class unit_cell_base<molecule>;

  typedef unit_cell_base<atom> atomic_ucell;
  typedef unit_cell_base<molecule> molecular_ucell;

} // end of namespace crystal 

} // end of namespace iquads

#endif
