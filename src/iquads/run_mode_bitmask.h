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

#ifndef RUN_MODE_BITMASK_H
#define RUN_MODE_BITMASK_H

namespace iquads {

namespace run_mode {

  typedef unsigned int run_mode_type;

  constexpr run_mode_type LOCAL_RUN           = 0x01 << 0;
  constexpr run_mode_type WRITE_LOCAL_INPUT   = 0x01 << 1; 
  constexpr run_mode_type WRITE_PBS_INPUT     = 0x01 << 2;
  constexpr run_mode_type WRITE_SBATCH_INPUT  = 0x01 << 3;
  constexpr run_mode_type COLLECT_LOCAL_OUTPUT = 0x01 << 4;

} // end of namespace run_mode

} // end of namespace iquads

#endif
