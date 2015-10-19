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


#ifndef COMMAND_PARSER_HPP
#define COMMAND_PARSER_HPP

#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>

namespace iquads {

using std::vector;
using std::string;
using std::cout;
using std::endl;

class CommandParser
{
public:
  typedef string argument_type;
  typedef vector<string> container_type;
  typedef bool condition_type;

public:
  CommandParser( int argc, char* argv[] ){
   cout << "::CommandParser::" << endl;
   cout << "  command arguments:";
   for( int i = 0; i < argc; i++ ){
    const argument_type argument = argv[i];
    this->command_string_.push_back( argument );
    cout << argument;
    cout << " ";
   }
   cout << endl;
   this->filled_ = true;
  }

public:
  container_type command_string() const 
   { 
     try{
      if( this->filled_ == true ){
       return this->command_string_; 
      }
      else {
       throw 1;
      }
     } catch ( int code ) {
      cout << "error: commands not initialized " << endl;
      exit(1);
     }
   }

private:
  container_type command_string_;
  condition_type filled_;

}; // end of class CommandParser

} // end of namespace iquads

#endif
