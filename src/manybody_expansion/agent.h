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

#ifndef MANYBODY_EXPANSION_AGENT_H
#define MANYBODY_EXPANSION_AGENT_H

#include <iostream>
#include <manybody_expansion/request.h>
#include <manybody_expansion/config.h>
#include <manybody_expansion/report.h>

namespace iquads {

namespace manybody_expansion {

class Agent
{
public:
  typedef iquads :: manybody_expansion :: Request request_type;
  typedef iquads :: manybody_expansion :: Config  config_type;
  typedef iquads :: manybody_expansion :: Report  report_type;
  typedef report_type& report_ref;

private:
  config_type setup_config_from_request( request_type request );
  report_type execute_general( config_type config, report_ref report );
  report_type execute_periodic( config_type config, report_ref report );

public:
  report_type accept_request_and_process( request_type request )
   {
     using std::cout;
     using std::endl;

     report_type report;
     config_type config = this->setup_config_from_request( request );

     if( config.is_periodic() == true ){
      cout << " PERIODIC flag detected; " << endl;
      this->execute_periodic( config, report );
     }
     else{
      cout << " no PERIODIC flag detected; " << endl;
      this->execute_general( config, report );
     }

   } // end of function accept_request_and_process()

}; // end of class Agent

} // end of namespace manybody_expansion

} // end of namespace iquads

#endif
