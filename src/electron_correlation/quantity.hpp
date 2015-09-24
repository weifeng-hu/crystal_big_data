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

#ifndef ELECTRON_CORRELATION_QUANTITY_HPP
#define ELECTRON_CORRELATION_QUANTITY_HPP

#include <string>

namespace iquads {

  namespace electron_correlation {

   /**
    *  Previously, explicit definitions of quantities related to 
    *  specific correlated methods were coded here, like HF_ENERGy.
    *  Here we simply use this head file to define general quantities 
    *  since explicit quantities w.r.t actual correlated methods can 
    *  be identified along with the correlation_level head file.
    */
    namespace quantity {
  
      typedef unsigned int quantity_mask_type;
      const quantity_mask_type ENERGY   = 0x01 << 0;
      const quantity_mask_type GRADIENT = 0x01 << 1;

    } // end of namespac quantity
  
  } // end of namespace electron_correlation

} // end of namespace iquads

#endif
