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

#include <string>

using std::string;

namespace iquads {

namespace structure {

 namespace geometry {

  namespace unit {

   typedef unsigned int unit_mask_type;
   typedef string unit_literal_type;
   constexpr unit_mask_type ANGSTROM = 0x01 << 0;
   constexpr unit_mask_type BOHR     = 0x01 << 1;
   const inline unit_literal_type return_unit_name( unit_mask_type mask )
    {
      switch( mask ){
       case( ANGSTROM ): return "angstrom"; break;
       case( BOHR ): return "bohr"; break;
       default: return "unknown "; break;
      }
    } // end of return_unit_name();

  } // end of namespace unit

  namespace coordinate_system {

    typedef unsigned int coordinate_mask_type;
    typedef string coordinate_literal_type;
    constexpr coordinate_mask_type CARTESIAN = 0x01 << 0;
    constexpr coordinate_mask_type INTERNAL  = 0x01 << 1;
    const inline coordinate_literal_type return_coordinate_name( coordinate_mask_type mask )
     {
       switch( mask ){
        case( CARTESIAN ): return "cartesian"; break;
        case( INTERNAL ): return "internal"; break;
        default: return "unknown"; break;
       } 
     } // end of return_coordinate_name()

  } // end of namespace coordinate_type

 } // end of namespace geometry

} // end of namespace structure

} // end of namespace iquads

#endif
