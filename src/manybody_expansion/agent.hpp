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

#ifndef MANYBODY_EXPANSION_AGENT_HPP
#define MANYBODY_EXPANSION_AGENT_HPP

#include <iostream>
#include <manybody_expansion/request.hpp>
#include <manybody_expansion/config.hpp>
#include <manybody_expansion/report.hpp>

namespace iquads {

namespace manybody_expansion {


  /**
   *  An agent class for many body expansion calculations
   *
   *  The agent object is responsible to invoke the actual formalism of many 
   *  body expansion, with receiving a request from the client about information 
   *  of an actual finite/infinite system as well as some detailed definition
   *  about the solution. According to the (abstract) definition of the 
   *  requested solution, corresponding concrete calculation method/sequence 
   *  will be performed by the agent object which further defines concrete 
   *  parameters for these calculations. Note that the agent cannot change 
   *  the formalism (system), it can only use the formalism (system). In the 
   *  end, the agent is responsible to gather a report(meta-data) of the 
   *  calculation and return it to the client. This design is also commonly 
   *  used in many other modules of the IQUADS package.
   *
   *  This agent probably does not have to have any data member, but even so
   *  the well-defined features/responsiblity/methods of it further defines it 
   *  to be an entity, thus the keyword class applies.
   *
   *  In the current design, the methods that this agent should have are follows:
   *   + A common method called 'accept request(from client) and process the 
   *     request and return a report'.
   *   + A method which translates information in the request, to a concrete
   *     run-time config which will be plugged in the many body expansion 
   *     formalism.
   *   + A method to start an actual many body expansion calculation for periodic 
   *     systems.
   *   + A method to start an actual many body expansion calculation for non-periodic 
   *     systems.
   *
   *  Note that we do not put the periodic many body expansion formalism and 
   *  non-periodic formalism in the same function, e.g. using flow control 
   *  or other branching methods, because conceptionally these two formalisms are 
   *  principly different.
   */

class Agent {
public:
  /**
   *  Since the agent ojbect is a crossing point of request, config 
   *  and report, these types will be viewed as essential in this 
   *  agent class.
   */
  typedef Request        request_type;
  typedef Config         config_type;
  typedef Report         report_type;
  typedef report_type&   report_ref;

private:
  /**
   *  These functions are set to be private since generally 
   *  external object instances, like a client,  do not need to 
   *  access these actual sequence to perform calculations, based on 
   *  the current design. Another reason is that only the agent is allowed
   *  to know how to handle the calculations in detail.
   */
  /**
   *  - setup_config_from_request()
   *    Maybe the config object can have a method about how to transform 
   *    information in a request to itself. But the Config instances are
   *    designed as a meta-data object, which is handled by the agent.
   *    So this means the agent should possess a method to perform this task.
   */
  config_type setup_config_from_request( request_type request );

  /**
   *  - execution_general()
   *    The method to invoke general manybody expansion calculation
   *    applying to bulk/finite system.
   */
  void execute_general( config_type config, report_ref report );
  /**
   *  - execution_periodic()
   *    The method to invoke general manybody expansion calculation
   *    applying to lattice/periodic system.
   */
  void execute_periodic( config_type config, report_ref report );

public:
  /**
   *  + accept_request_and_process
   *    Actually handles the request, and return a report.
   *    Is invoked externally but non-static.
   */
  report_type accept_request_and_process( request_type request )
    {
      using std::cout;
      using std::endl;

      report_type report;
      config_type config = this->setup_config_from_request( request );

      if( config.is_periodic() == true ) {
        cout << " PERIODIC flag detected; " << endl;
        this->execute_periodic( config, report );
      }
      else {
        cout << " no PERIODIC flag detected; " << endl;
        this->execute_general( config, report );
      }

      return report;
    } // end of function accept_request_and_process()

}; // end of class Agent

} // end of namespace manybody_expansion

} // end of namespace iquads

#endif
