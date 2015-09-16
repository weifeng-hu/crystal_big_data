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

#ifndef PROGRAM_MASK_HPP
#define PROGRAM_MASK_HPP

#include <string>
#include <iostream>

namespace iquads {

  namespace interface_to_third_party {

    namespace program {

      using std::string;
      typedef string program_name_type;
      typedef unsigned int program_mask_type;

      /**
       *  The mask for IQUADS/SELF is special, 0
       */
      constexpr program_mask_type IQUADS = 0x00;
      constexpr program_mask_type MOLPRO = 0x01 << 0;
      constexpr program_mask_type ORCA   = 0x01 << 1;
      constexpr program_mask_type PSI3   = 0x01 << 2;
      
      inline program_mask_type 
       return_program_mask( program_name_type program_name )
      {
      
        if( program_name == "molpro" || 
            program_name == "Molpro" ) {
         return MOLPRO;
        }
        else if( program_name == "orca" || 
                 program_name == "Orca" ) {
         return ORCA;
        }
        else if( program_name == "psi3" ||
                 program_name == "Psi3" ){
         return PSI3;
        }
        else if( program_name == "iquads" ||
                 program_name == "self" ){
         return IQUADS;
        }
        else{
         using std::cout;
         using std::endl;
         cout << "retrieve_external_program_mask():" << endl;
         cout << "Unknown program name: " << program_name << endl;
         exit(1);
        }
      }; // end of return_external_program_mask()

     }  // end of namespace program

  } // end of namespace interface_to_third_party

} // end of namespace iquads

#endif
