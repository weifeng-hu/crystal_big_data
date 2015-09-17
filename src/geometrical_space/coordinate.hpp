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

#include <array>
#include <vector>
#include <tuple>

namespace iquads {

namespace geometrical_space {

  /**
   *  We enforce using double precision for coordinates
   *  since we may encounter big coordinates like 1e5
   *  and the significant digits after the decimal point 
   *  can only be 8 digits 
   */
  typedef double coord_value_type;

  /**
   *  Stack storage for a 3-dimensional cartesian coordinate set
   *  using a tuple of 3 doubles
   */
  typedef std::tuple< coord_value_type, coord_value_type, coord_value_type > CartesianCoordinate3D;

  /**
   *  A list of coordinates will be stored in the heap. That's fine,
   *  as long as we use a continuous STL container
   */
  typedef std::vector<CartesianCoordinate3D> CartesianCoordinate3DList;

  /**
   *  Data definitions to define coordinate intervals
   *  Can be used in storge geometrical edge/range info
   */
  typedef tuple< coord_value_type, coord_value_type > Interval;
  typedef tuple< Interval, Interval, Interval > Interval3D;

} // end of namespace geometrical_space

} // end of namespace iquads

#endif
