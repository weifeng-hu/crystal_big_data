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

#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include <string>

using std::string;

namespace iquads {

  namespace sequence {

    namespace mode {

      typedef string mode_name_type;
      typedef unsigned int mode_mask_type;

      constexpr mode_mask_type LOCAL_RUN            = 0x01 << 0;
      constexpr mode_mask_type WRITE_LOCAL_INPUT    = 0x01 << 1;
      constexpr mode_mask_type WRITE_PBS_INPUT      = 0x01 << 2;
      constexpr mode_mask_type WRITE_SBATCH_INPUT   = 0x01 << 3;
      constexpr mode_mask_type COLLECT_LOCAL_OUTPUT = 0x01 << 4;

      const inline mode_mask_type return_mode_mask( mode_name_type mode_name ) {

        if( mode_name == "local"   ) return LOCAL_RUN;
        if( mode_name == "pbs"     ) return WRITE_PBS_INPUT;
        if( mode_name == "scratch" ) return WRITE_SBATCH_INPUT;
        if( mode_name == "harvest" ) return COLLECT_LOCAL_OUTPUT;
        if( mode_name == "dryrun"  ) return WRITE_LOCAL_INPUT;

      } // end of function return_mode_mask()

    } // end of namespace mode

    namespace calculation {

      typedef unsigned int calculation_mask_type;

      constexpr calculation_mask_type SINGLE_POINT_ENERGY = 0x01 << 0;

    } // end of namespace 

  } // end of namespace run_mode

} // end of namespace iquads

#endif
