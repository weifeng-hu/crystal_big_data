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

#ifndef VECTOR_OF_STRING_FUNCTIONS_HPP
#define VECTOR_OF_STRING_FUNCTIONS_HPP

#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <utility/convert_string_to.hpp>

namespace iquads {

namespace utility {

namespace string_tool {

std :: vector< std :: string > split_string( std :: string string_line, std :: string spliters ) {

  try {
    std :: vector< std :: string > retval;
    boost :: split( retval, string_line, boost :: is_any_of( spliters.c_str() ) );
    if( retval.size() == 0 ) { throw 1; }
    return retval;
  } catch ( int signal ) {
    std :: cout << "error: string " << string_line << " is not splitable by any of " << spliters << std :: endl;
    abort();
  }

}

template < typename DataType > inline DataType return_last_value_of_strings ( std :: vector< std :: string > strings ) {

  DataType retval = iquads :: utility :: string_tool :: convert_string_to <DataType> ( *( strings.rbegin() ) );
  return retval;

} // end of template function return_last_value_of_strings

inline bool stringsA_has_stringsB( std :: vector < std :: string> stringsA, std :: vector< std :: string > stringsB ) {

  if( stringsA.size() < stringsB.size() ) { return false; }

  std :: vector< bool > recode;
  recode.resize(0);
  for( size_t iB = 0; iB < stringsB.size(); iB++ ) {
    std :: string value_to_compare = stringsB[iB];
    recode.push_back( false );
    for( size_t iA = 0; iA < stringsA.size(); iA++ ) {
      if( stringsA[iA] == value_to_compare ) {
        recode[iB] = true;
        continue;
      }
    }
    if( recode[iB] == false ) { return false; }
  }

  return true;

} // end of function stringsA_has_stringsB()

} // end of namespace string_tool

} // end of namespace utility

} // end of namespace iquads

#endif
