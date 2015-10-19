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

#include <string>
#include <vector>
#include <utility/vector_of_string_functions.hpp>

int main( int argc, char* argv[] ) {

  std :: string str1( "apple" );
  std :: string str2( "orange" );
  std :: string str3( "banana" );

  std :: vector< std :: string > vec_of_str;
  vec_of_str.resize(0);
  vec_of_str.push_back( str1 );
  vec_of_str.push_back( str2 );
  vec_of_str.push_back( str3 );

  std :: cout << iquads :: utility :: string_tool :: return_last_value_of_strings < std :: string > ( vec_of_str ) << std :: endl;

  vec_of_str[2] = std :: string( "22" );

  std :: cout << iquads :: utility :: string_tool :: return_last_value_of_strings < const char*> ( vec_of_str ) << std :: endl;
  std :: cout << iquads :: utility :: string_tool :: return_last_value_of_strings < int > ( vec_of_str ) << std :: endl;
  std :: cout << iquads :: utility :: string_tool :: return_last_value_of_strings < long > ( vec_of_str ) << std :: endl;
  std :: cout << iquads :: utility :: string_tool :: return_last_value_of_strings < long long > ( vec_of_str ) << std :: endl;

  vec_of_str[2] = std :: string( "3.1415e1" );

  std :: cout << iquads :: utility :: string_tool :: return_last_value_of_strings < float > ( vec_of_str ) << std :: endl;
  std :: cout << iquads :: utility :: string_tool :: return_last_value_of_strings < double > ( vec_of_str ) << std :: endl;
  std :: cout << iquads :: utility :: string_tool :: return_last_value_of_strings < long double > ( vec_of_str ) << std :: endl;

  std :: vector< std :: string > vec_of_str2;
  vec_of_str2.push_back( std :: string( "apple" ) );
  vec_of_str2.push_back( std :: string( "orange" ) );
  std :: cout << iquads :: utility :: string_tool :: stringsA_has_stringsB( vec_of_str, vec_of_str2 ) << std :: endl;

  return 0;
} 
