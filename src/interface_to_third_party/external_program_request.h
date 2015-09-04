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

#ifndef EXTERNAL_PROGRAM_REQUEST_H
#define EXTERNAL_PROGRAM_REQUEST_H

#include <quantity_identifier.h>

namespace iquads {

namespace interface_to_third_party {

struct ExternalProgramRequest {
public:
  typedef double energy_data_type;
  typedef unsigned int quantity_identifier_type;
  tyoedef unsigned int run_mode_type;

private:
  quantity_identifier_type quantity_identifier_;
  run_mode_type run_mode_;

}; // end of struct ExternalProgramRequest

} // end of namespace interface_to_third_party

} // end of namespace iquads

#endif