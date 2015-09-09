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

#ifndef GEOMETRY_SETTINGS_HPP
#define GEOMETRY_SETTINGS_HPP

namespace iquads {

namespace structure {

 namespace geometry {

  namespace unit {

   typedef unsigned int unit_type_mask;

   constexpr unit_type_mask ANGSTROM = 0x01 << 0;
   constexpr unit_type_mask BOHR     = 0x01 << 1;

  } // end of namespace unit

  namespace coordinate_system {

    typedef unsigned int coordinate_type_mask;

    constexpr coordinate_type_mask CARTESIAN = 0x01 << 0;
    constexpr coordinate_type_mask INTERNAL  = 0x01 << 1;

  } // end of namespace coordinate_type

 } // end of namespace geometry

} // end of namespace structure

} // end of namespace iquads

#endif
