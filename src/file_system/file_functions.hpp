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

#ifndef FILE_FUNCTIONS_H
#define FILE_FUNCTIONS_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <boost/algorithm/string.hpp>

namespace iquads {

namespace file_system {

template < typename DataType > DataType return_last_value_of_strings ( std :: vector< std :: string > strings ) {

  DataType retval = convert_string_to <DataType> ( *( strings.rbegin() ) );
  return retval;

} // end of template function return_last_value_of_strings

std :: vector< std :: string > return_split_strings_if_line_contains_all_keywords( std :: vector< std :: string> keywords, std :: string filepath ) {

  try {
    std :: ifstream ifs( filepath.c_str(), std :: ios :: in );
    while( ifs.eof() == false ) {
      char[1024] line_buffer;
      ifs.getline( line_buffer );
      std :: string line_string( line_buffer );
      std :: vector< std :: string > line_details;
      boost :: split( line_details, line_string, boost :: is_any_of( " " ) );
      if( stringsA_has_stringsB( line_details, keywords ) == true ) {
        return line_details;
      }
    }
    throw make_tuple( keywords, filepath );
  } catch ( tuple< std :: vector< std :: string>, std :: string>   error_info ) {
    std :: cout << "error: cannot find a line contains all the keywords in file " << std :: get<1> ( error_info ) << std :: endl;
    std :: cout << "       requested keywords are: " << std :: endl;
    for( size_t i = 0; i < ( std :: get<0>( error_info ) ).size(); i++ ) {
      std :: cout << ( std :: get<0>( error_info )[i] ) << ";";
    }
    std :: endl;
    abort();
  }

}; // end of function return_split_strings_if_line_contains_all_keywords()

} // end of namespace file_system

} // end of namespace iquads

#endif
