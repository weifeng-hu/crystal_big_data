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

#ifndef COORDINATE_REPRESENTATION_HPP
#define COORDINATE_REPRESENTATION_HPP

#include <string>

using std::string;

namespace iquads {

  namespace structure {
 
    namespace coordinate_representation {
 
      typedef string representation_literal_type;
      typedef unsigned int representation_mask_type;

      constexpr representation_mask_type UNKNOWN   = 0x00;
      constexpr representation_mask_type CARTESIAN = 0x01 << 0;
      constexpr representation_mask_type INTERNAL  = 0x01 << 1;

      inline
      const representation_literal_type return_representation_name ( representation_mask_type mask )
        {
          switch( mask ) {
            case( CARTESIAN ): return "cartesian";  break;
            case( INTERNAL ):  return "internal";   break;
            default:           return "unknown";    break;
          } 
        } // end of inline function return_representation_name()
 
    } // end of namespace coordinate_representation
 
  } // end of namespace structure
  
} // end of namespace iquads

#endif
