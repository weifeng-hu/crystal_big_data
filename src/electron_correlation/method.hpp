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
 * the Free Software Foundation, either version 3 of the License, or
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

#ifndef ELECTRON_CORRELATION_METHOD_HPP
#define ELECTRON_CORRELATION_METHOD_HPP

namespace iquads {

 namespace electron_correlation {

  namespace method {

   typedef unsigned int mask_type;

   constexpr mask_type RHF   = 0x01 << 0;
   constexpr mask_type MP2   = 0x01 << 1;
   constexpr mask_type CCSD  = 0x01 << 2;
   constexpr mask_type CCSDT = 0x01 << 3;
   constexpr mask_type DMRG  = 0x01 << 4;

  } // end of namespace method

 } // end of namespace electron_correlation

} // end of namespace iquads

#endif
