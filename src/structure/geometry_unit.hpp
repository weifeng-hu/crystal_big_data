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

#ifndef GEOMETRY_UNIT_HPP
#define GEOMETRY_UNIT_HPP

#include <stdlib.h>
#include <string>

using std::string;

namespace iquads {

  namespace structure {
  
    namespace geometry_unit {
   
      typedef string unit_literal_type;
      typedef unsigned int unit_mask_type;

      constexpr unit_mask_type UNKNOWN  = 0x00;
      constexpr unit_mask_type ANGSTROM = 0x01 << 0;
      constexpr unit_mask_type BOHR     = 0x01 << 1;

      inline
      const unit_literal_type return_unit_name( unit_mask_type mask )
        {
          switch( mask ) {
            case( ANGSTROM ):  return "angstrom";  break;
            case( BOHR ):      return "bohr";      break;
            default:           return "unknown ";  break;
          }
        } // end of inline function return_unit_name();

      inline 
      const unit_mask_type return_unit_mask( unit_literal_type literal )
        {
          if( literal == "ang" || literal == "angstrom" 
           || literal == "Ang" || literal == "Angstrom"
           || literal == "ANG" || literal == "ANGSTROM" ) {
            return ANGSTROM;
          }

          if( literal == "bohr" || literal == "Bohr" || literal == "BOHR" ) {
            return BOHR;
          }

          return UNKNOWN;
        } // end of inline function return_unit_mask()

      inline
      double unit_conversion_constant( unit_mask_type from, unit_mask_type to )
        {
          if( !(from & UNKNOWN) ) { 
            cout << " unknown geometry unit type in FROM " << endl;
            abort();
          }
          if( !(to   & UNKNOWN) ) {
            cout << " unknown geometry unit type in TO " << endl;
            abort();
          }
          if( from & ANGSTROM && to & BOHR ) return 1.0e0/0.529177208e0;
          if( from & BOHR     && to & ANGSTROM ) return 0.529177208e0;
          return 1.0e0;
        } // end of inline function unit_conversion_constant;

    } // end of namespace geometry_unit
  
  } // end of namespace structure

} // end of namespace iquads

#endif
