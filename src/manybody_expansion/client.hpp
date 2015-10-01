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

#ifndef MANYBODY_EXPANSION_CLIENT_HPP
#define MANYBODY_EXPANSION_CLIENT_HPP

#include <string>
#include <iquads/command_parser.hpp>
#include <manybody_expansion/command_setting.hpp>
#include <manybody_expansion/agent.hpp>
#include <manybody_expansion/request.hpp>
#include <manybody_expansion/report.hpp>

namespace iquads {

namespace manybody_expansion {


  /**
   *  A client class for many body expansion calculations
   *
   *  The tasks of a many body expansion client, i.e., leading to the 
   *  actual definition of a client, are:
   *   + file a request, which contains essential information about
   *     "what to solve".
   *   + find a many body expansion agent, which will further start the 
   *     actual method for calculations.
   *   + collect and keep a report from the calculation, which is returned 
   *     by the agent.
   *   + also do post-calculation handling of a report, like storage, 
   *     transferring, etc.
   *
   *  Based on these conceptions, client instances can be viewed as entities, since 
   *  the features (methods, tasks) makes any client instance at a valid state and 
   *  always keep valid at runtime. We therefore use keyword class 
   *  to implement it.
   */

using iquads :: CommandParser;
using std :: string;

class Client {
public:
  typedef CommandParser :: container_type   command_container_type;
  typedef CommandParser :: argument_type    command_argument_type;
  typedef CommandSetting                    command_setting_type;
  typedef Request  request_type;
  typedef Report   report_type;
  typedef Agent    agent_type;

public:
  /**
   *  + show_help()
   *    Probably users need to get help any time, even when no client object or calculation is needed.
   */
  static void show_help();

  /**
   *  + analyse_command()
   *    command analyser, translate a command string to execution options for further 
   *    sequence.
   */
  static command_setting_type analyse_command( command_container_type command_container );

  /**
   *  + file_request()
   *    A request doesn't prepare itself usually, and here it is prepared by a client.
   */
  request_type file_request( command_setting_type command_setting );

  /**
   *  + driver()
   *    The actual method to start a many body expansion calculation, based on an external command string.
   */
  void driver( command_container_type command_container )
    {
      agent_type agent;
      this->report_ = 
         agent.accept_request_and_process( this->file_request( this->analyse_command( command_container ) ) );
//     this->report().save();  // to be implemented
    }  // end of function driver()

public:
  report_type report() const 
    { return this->report_; }
  report_type& set_report()
    { return this->report_; }

private:
  report_type report_;

}; // end of class Client

} // end of namespace manybody_expansion

} // end of namespace iquads

#endif
