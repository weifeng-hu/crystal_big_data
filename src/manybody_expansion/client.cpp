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

#include <iostream>
#include <memory>
#include <manybody_expansion/agent.hpp>
#include <manybody_expansion/client.hpp>

namespace iquads {

namespace manybody_expansion {

typedef Client mbe_client_type;

mbe_client_type :: request_type 
 mbe_client_type :: file_request( command_setting_type command_setting )
{

  request_type request;
  request.read_input_file( command_setting.input_filename() );
  return request;

}; // end of function file_request()

mbe_client_type :: command_setting_type 
 mbe_client_type :: analyse_command( command_container_type command_container )
{

  if ( command_container.size() == 1 ){
    cout << "error: no command option input" << endl;
    mbe_client_type :: show_help();
    exit(1);
  }

  command_setting_type command_settings;
  for( size_t i = 0; i < command_container.size(); i++ ){
   mbe_client_type :: command_argument_type argument = command_container[i];
   if( argument == "--input" || argument == "-i" ){
    command_settings.set_input_filename() = command_container.at(i+1);
   }
  }

  return command_settings;

}; // end of function analyse_command()

void mbe_client_type :: show_help()
{

  using std::cout;
  using std::endl;

  cout << "Usage:" << endl;
  cout << " mbe -i/--input <config_filename>" << endl;
  cout << endl;
  cout << " Options:" << endl;

} // end of function show_help()

} // end of namespace manybody_expansion

} // end of namespace iquads
