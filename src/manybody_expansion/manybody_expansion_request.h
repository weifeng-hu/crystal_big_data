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

#ifndef MANYBODY_EXPANSION_REQUEST
#define MANYBODY_EXPANSION_REQUEST

#include <string>
#include <manybody_expansion/lattice.h>

using std::string;

namespace iquads {

namespace manybody_expansion {

struct Request {
public:
  typedef Lattice lattice_info_type;
  typedef lattice_info_type& lattice_info_ref;
  typedef string external_program_name_type;
  typedef external_program_name_type& external_program_name_ref;

public:
  lattice_info_ref set_lattice_info() 
   { return this->lattice_info_; }
  external_program_name_ref set_external_program_name()
   { return this->external_program_name; }

private:
  lattice_info_type lattice_info_;
  external_program_name_type external_program_name;

}; // end of struct Request

} // end of namespace manybody_expansion

} // end of namespace iquads

#endif
