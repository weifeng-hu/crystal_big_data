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


#ifndef MANYBODY_EXPANSION_ORDER_MASK_HPP
#define MANYBODY_EXPANSION_ORDER_MASK_HPP

#include <stdlib.h>
#include <iostream>

namespace iquads {

  namespace manybody_expansion {
  
    namespace order {
   
      typedef size_t expansion_order_type; 
      typedef unsigned int order_mask_type;
    
      constexpr order_mask_type FIRST_ORDER   = 0x01 << 0;
      constexpr order_mask_type SECOND_ORDER  
                = ( FIRST_ORDER | 0x01 << 1 );
      constexpr order_mask_type THIRD_ORDER   
                = ( FIRST_ORDER | SECOND_ORDER | 0x01 << 2 );
      constexpr order_mask_type FOURTH_ORDER  
                = ( FIRST_ORDER | SECOND_ORDER | THIRD_ORDER | 0x01 << 3 );

      const inline order_mask_type return_order_mask( expansion_order_type expansion_order ) 
       {
         switch( expansion_order ) {
           case( 1 ): return FIRST_ORDER;  break;
           case( 2 ): return SECOND_ORDER; break;
           case( 3 ): return THIRD_ORDER;  break;
           case( 4 ): return FOURTH_ORDER; break;
           default:
            using std::cout;
            using std::endl;
            cout << " order out of range: " << expansion_order << endl;
            abort();
         }
       } // end of function return_order_mask()

    } // end of namespace order
  
  } // end of manybody_expansion

} // end of namespace iquads

#endif
