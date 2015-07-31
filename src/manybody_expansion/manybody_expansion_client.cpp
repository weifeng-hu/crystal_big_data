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
#include <manybody_expansion/manybody_expansion_client.h>
#include <manybody_expansion/manybody_expansion_agent.h>

namespace iquads {

namespace manybody_expansion {

typedef ManyBodyExpansionClient client_type;

client_type :: report_type 
client_type :: driver( client_type :: command_container_type command_container )
{

  using std::cout;
  using std::endl;

  client_type :: report_type report;
  {
   using std::shared_ptr;
   using std::make_shared;
   client_type :: command_setting_type command_settings = client_type :: analyse_command( command_container );
   client_type :: config_type config;
   config.read_config( command_settings.config_filename() );
   shared_ptr< client_type :: config_type > config_ptr = make_shared< client_type :: config_type >( config );
   shared_ptr< client_type :: report_type > report_ptr = make_shared< client_type :: report_type >( report );
   {
    ManyBodyExpansionAgent agent;
//    agent.set_runtime_environment( config_ptr );
//    agent.execute( report_ptr );
   }
  }
  return report;

}; // end of static function driver()

void client_type :: driver()
{

  using std::cout;
  using std::endl;

  using std::shared_ptr;
  using std::make_shared;
  this->command_setting_ = this->analyse_command( this->command_container_ );
  this->config_.read_config( this->command_setting_.config_filename() );
  {
   shared_ptr< client_type :: config_type > config_ptr 
    = make_shared< client_type :: config_type > ( this->config_ );
   shared_ptr< client_type :: report_type > report_ptr 
    = make_shared< client_type :: report_type >( this->report_ );
   ManyBodyExpansionAgent agent;
//   agent.set_runtime_environment( config_ptr );
//   agent.execute( report_ptr );
  }

//  this->report_.print( this->config_.print_level() );

}; // end of function driver()

client_type :: command_setting_type 
 client_type :: analyse_command( command_container_type command_container )
{

  using std::cout;
  using std::endl;

  if ( command_container.size() == 1 ){
    cout << "error: no command option input" << endl;
    client_type :: helper();
    exit(1);
  }

  client_type :: command_setting_type command_settings;
  for( size_t i = 0; i < command_container.size(); i++ ){
   client_type :: command_argument_type argument = command_container[i];
   if( argument == "--input" || argument == "-i" ){
    command_settings.set_config_filename() = command_container.at(i+1);
   }
  }

  return command_settings;

}; // end of function analyse_command()

void client_type :: show_help()
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
