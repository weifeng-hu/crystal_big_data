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

#ifndef COORDINATE_HPP
#define COORDINATE_HPP

#include <vector>
#include <tuple>

namespace iquads {

namespace geometrical_space {

  // stack storage for a coordinate set
  // using tuple of 3 doubles

  // we enforce using double precision for coordinates
  // since we may encounter big coordinates like 1e5
  // and the significant digits after the decimal point 
  // can only be 8 digits or so
  typedef std::tuple< double, double, double > Coord;
  typedef std::vector<Coord> CoordList;

} // end of namespace geometrical_space

} // end of namespace iquads

#endif
