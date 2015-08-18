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


#ifndef MANYBODY_EXPANSION_ORDER_BITMASK_H
#define MANYBODY_EXPANSION_ORDER_BITMASK_H

namespace iquads {

namespace manybody_expansion {

namespace order_bitmask {

  typedef unsigned int bitmask_type;

  constexpr bitmask_type AUTO          = 0x01 << 0
  constexpr bitmask_type FIRST_ORDER   = 0x01 << 1;
  constexpr bitmask_type SECOND_ORDER  = 0x01 << 2;
  constexpr bitmask_type THIRD_ORDER   = 0x01 << 3;
  constexpr bitmask_type FOURTH_ORDER  = 0x01 << 4;

} // end of namespace order_bitmask

} // end of manybody_expansion

} // end of namespace iquads

#endif
