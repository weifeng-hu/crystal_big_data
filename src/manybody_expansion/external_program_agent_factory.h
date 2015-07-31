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

#ifndef EXTERNAL_PROGRAM_AGENT_FACTORY_H
#define EXTERNAL_PROGRAM_AGENT_FACTORY_H

#include <stdlib.h>
#include <manybody_expansion/external_program_bitmask.h>
#include <manybody_expansion/external_program_agent.h>

namespace iquads {

namespace manybody_expansion {

class ExternalProgramAgent_Factory
{
public:
  typedef unsigned int bitmask_type;
  typedef ExternalProgramAgent_Base base_agent_type;
  typedef base_agent_type* base_agent_pointer_type;

public:
  base_agent_pointer_type get_agent( bitmask_type agent_mask )
   {
     switch( agent_mask ){
      case( external_program::molpro ):
       return new MolproAgent;
       break;
      case( external_program::orca ):
       return new OrcaAgent;
       break;
      default:
       exit(1);
     }
   } // end of get_agent()

}; // end of class ExternalProgramAgent_Factory

} // end of namespace manybody_expansion

} // end of namespace iquads

#endif
