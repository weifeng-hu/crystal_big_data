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

#include <interface_to_third_party/molpro_config.hpp>

namespace iquads { 

namespace interface_to_third_party { 

typedef MolproConfig config_type;

config_type :: set_defaults()
{

  this->basis_set_name_ = "sto-3g";
  this->memory_amount_ = 400;
  this->memory_unit = "m";
  this->geometry_format_ = "xyz";
  this->geometry_unit_ = "angstrom";

} // end of set_defaults()

} // end of namespace interface_to_third_party

} // end of namespace iquads
