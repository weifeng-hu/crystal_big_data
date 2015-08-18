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


#ifndef POLYMER_H
#define POLYMER_H

#include "utilities/solid_gen/polymer_base.h"

namespace iquads {

namespace crystal {

  // explicit template instantiation
  template class polymer_base<2>;
  template class polymer_base<3>;
  template class polymer_base<4>;

  // self defined types
  typedef polymer_base<2> dimer;
  typedef polymer_base<3> trimer;
  typedef polymer_base<4> tetramer;

} // end of namespace crystal

} // end of namespace iquads

#endif
