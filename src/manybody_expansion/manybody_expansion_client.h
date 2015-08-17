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

#ifndef MANYBODY_EXPANSION_CLIENT_H
#define MANYBODY_EXPANSION_CLIENT_H

#include <string>
#include <iquads/command_parser.h>
#include <manybody_expansion/manybody_expansion_command_setting.h>
#include <manybody_expansion/manybody_expansion_config.h>
#include <manybody_expansion/manybody_expansion_report.h>

using std::string;

namespace iquads {

namespace manybody_expansion {

class Client
{
public:
  typedef typename CommandParser::container_type command_container_type;
  typedef typename CommandParser::argument_type command_argument_type;
  typedef iquads :: manybody_expansion :: Request request_type;
  typedef iquads :: manybody_expansion :: Report  report_type;
  typedef iquads :: manybody_expansion :: Agent   agent_type;
  typedef iquads :: manybody_expansion :: CommandSetting command_setting_type;

public:
  static void show_help();
  static command_setting_type analyse_command( command_container_type command_container );
  void file_request( command_setting_type command_setting );
  void driver( command_container_type command_container )
   {
     command_setting_type command_settings
      = mbe_client_type :: analyse_command( command_container );
     agent_type agent;
     this->report_ 
      = agent.accept_request_and_process( file_request( command_settings ) );
     this->print_report();
   }  // end of function driver()

  void print_report() const 
   { this->report_.print(); } // end of function print_report()

private:
  report_type report_;

}; // end of class Client

} // end of namespace manybody_expansion

} // end of namespace iquads

#endif
