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

#ifndef EXTERNAL_PROGRAM_AGENT_FACTORY_HPP
#define EXTERNAL_PROGRAM_AGENT_FACTORY_HPP

#include <stdlib.h>
#include <interface_to_third_party/program_mask.hpp>
//#include <interface_to_third_party/external_program_agent_base.hpp>
//#include <interface_to_third_party/molpro_agent.hpp>
//#include <interface_to_third_party/orca_agent.hpp>

namespace iquads {

namespace interface_to_third_party {

using namespace program;

class ExternalProgramAgent_Factory {
public:
  typedef ExternalProgramAgent_Factory   this_type;
//  typedef ExternalProgramAgent_Base      base_agent_type;
  typedef program :: program_mask_type   agent_mask_type;

//  typedef base_agent_type*               base_agent_ptr;

public:
/*
  base_agent_ptr get_agent( agent_mask_type agent_mask )
   {
     switch( agent_mask ){
      case( program :: MOLPRO ):
//       return new MolproAgent;
       break;
      case( program :: ORCA ):
//       return new OrcaAgent;
       break;
      default:
       exit(1);
     }
   } // end of get_agent()
*/

}; // end of class ExternalProgramAgent_Factory

} // end of namespace interface_to_third_party

} // end of namespace iquads

#endif
