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

#include <manybody_expansion/report.hpp>

namespace iquads {

namespace manybody_expansion {

typedef Report report_type;

void report_type :: print() const 
{

  // * periodic or disordered?

  // * (if periodic) total energy per unit cell
  // * (if non periodic) total energy 

  // * monomer energy, percentage

  // * dimer interaction energy, percentage

  // * trimer interaction energy, percentage

  // * tetramer interaction energy, percentage

  // * data storage information
  //   * result data
  //   * external program inputs
  //   * external program outputs
  //   * where did external program run?

}; // end of functiin print

} // end of namespace manybody_expansion

} // end of namespace iquads
