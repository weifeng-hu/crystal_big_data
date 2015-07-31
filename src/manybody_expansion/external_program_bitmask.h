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

#ifndef EXTERNAL_PROGRAM_BITMASK_H
#define EXTERNAL_PROGRAM_BITMASK_H

#include <string>
#include <iostream>

namespace iquads {

namespace manybody_expansion {

namespace external_program {

  using std::string;
  typedef string external_program_name_type;
  typedef unsigned int external_program_bitmask_type;

  constexpr external_program_bitmask_type molpro = 0x01;
  constexpr external_program_bitmask_type orca   = 0x02;

inline external_program_bitmask_type 
 retrieve_external_program_mask( external_program_name_type external_program_name )
{

  if( external_program_name == "molpro" || 
      external_program_name == "Molpro" ) {
   return molpro;
  }
  else if( external_program_name == "orca" || 
           external_program_name == "Orca" ) {
   return orca;
  }
  else{
   using std::cout;
   using std::endl;
   cout << "retrieve_external_program_mask():" << endl;
   cout << "Unknown program name: " << external_program_name << endl;
   exit(1);
  }

}; // end of retrieve_external_program_mask()

} // end of namespace external_program

} // end of namespace manybody_expansion

} // end of namespace iquads

#endif
