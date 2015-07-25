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
#include <external_program_agent.h>

namespace iquads {

namespace manybody_expansion {

class ExternalProgramAgent_Factory
{
public:
  typedef unsigned int bitmask_type;

public:
  ExternalProgramAgent_Base* get_agent( bitmask_type agent_mask )
   {
     switch( agent_mask ){
      case( molpro ):
       return new MolproAgent;
       break;
      case( orca );
       return new OrcaAgent;
       break;
      default:
       abort();
     }
   }

private:
  constexpr bitmask_type molpro = 0x01;
  constexpr bitmaks_type orca   = 0x02;

}; // end of class ExternalProgramAgent_Factory

} // end of namespace manybody_expansion

} // end of namespace iquads

#endif
