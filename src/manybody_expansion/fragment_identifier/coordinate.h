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

#ifndef IQUADS_COORDINATE_H
#define IQUADS_COORDINATE_H

#include <vector>
#include <tuple>

namespace iquads {

namespace basic {

  // stack storage for coordinates
  // using tuple of 3 doubles

  // we enforce using double precision for coordinates
  // since we may encounter big coordinates like 1e5
  // and the significant digits after the decimal point 
  // can only be 8 digits or so
  typedef std::tuple< double, double, double > Coord;
  typedef std::vector<Coord> CoordList;

} // end of namespace basic

} // end of namespace iquads

#endif
