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

class ManyBodyExpansionClient
{
public:
  typedef ManyBodyExpansionClient this_type;
  typedef typename CommandParser::container_type command_container_type;
  typedef typename CommandParser::argument_type command_argument_type;
  typedef ManyBodyExpansionCommandSetting command_setting_type;
  typedef ManyBodyExpansionConfig config_type;
  typedef ManyBodyExpansionReport report_type;
  typedef string filename_type;
  typedef string classname_type;
  typedef string function_name_type;

public:
  ManyBodyExpansionClient(){};
  ManyBodyExpansionClient( command_container_type command_container )
   {
     this->command_container_ = command_container;
   }

  // static functions
public:
  static report_type driver( command_container_type command_container );
  static command_setting_type analyse_command( command_container_type command_container );
  static void show_help();

  // non-static functions
public:
  void driver();

private:
  config_type config_;
  report_type report_;
  command_setting_type command_setting_;
  command_container_type command_container_;

  const string this_class_name = "ManyBodyExpansionClient";

}; // end of class ManyBodyExpansionClient

} // end of namespace manybody_expansion

} // end of namespace iquads

#endif
