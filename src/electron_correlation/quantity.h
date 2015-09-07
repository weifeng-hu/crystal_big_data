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

#ifndef ELECTRON_CORRELATION_QUANTITY_H
#define ELECTRON_CORRELATION_QUANTITY_H

namespace iquads {

namespace electron_correlation {

  namespace quantity {

   typedef unsigned int quantity_mask_type;

   namespace energy {

    constexpr quantity_mask_type return_nest_mask()
     { return 0x01 << 0 ; }

    typedef unsigned int energy_mask_type;
    constexpr energy_mask_type HF_ENERGY = 0x01 << 0;
    constexpr energy_mask_type MP2_ENERGY = 0x01 << 1;
    constexpr energy_mask_type CASSCF_ENERGY = 0x01 << 2;

   } // end of namespace energy

   namespace gradient {

    constexpr quantity_mask_type return_nest_mask()
     { return 0x01 << 1 ; }

    typedef unsigned int gradient_mask_type;
    constexpr gradient_mask_type HF_GRADIENT = 0x01 << 0;
    constexpr gradient_mask_type MP2_GRADIENT = 0x01 << 1;
    constexpr gradient_mask_type CASSCF_GRADIENT = 0x01 << 2;

   } // end of namespace gradient

  } // end of namespac quantity

} // end of namespace electron_correlation

} // end of namespace iquads

#endif
