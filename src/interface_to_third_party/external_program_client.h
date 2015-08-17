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

#ifndef EXTERNAL_PROGRAM_CLIENT_H
#define EXTERNAL_PROGRAM_CLIENT_H

#include <interface_to_third_party/external_program_agent_base.h>
#include <interface_to_third_party/external_program_agent_factory.h>

namespace iquads {

namespace interface_to_third_party {

template < class Request_Type >
class ExternalProgramClient
{
public:
  typedef ExternalProgramAgent_Factory agent_factory_type;
  typedef ExternalProgramAgent_Base base_agent_type;
  typedef base_agent_type* base_agent_ptr;
  typedef IQUADS_Report report_type;

public:
  report_type driver()
   {
    base_agent_ptr base_agent_pointer 
      = this->agent_factory_.get_agent( /*need agent mask*/ );
    report_type report 
      = base_agent_pointer->accept_request_and_process( this->calculation_request_ );
    return report;
   } // end of driver()

public:
  Request_Type calculation_request_;
  agent_factory_type agent_factory_;

}; // end of class ExternalProgramClient

} // end of namespace interface_to_third_party

} // end of namespace iquads

#endif
