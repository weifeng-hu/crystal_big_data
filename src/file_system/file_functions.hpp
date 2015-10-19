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

#include <tuple>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <utility/vector_of_string_functions.hpp>

namespace iquads {

namespace file_system {

inline std :: vector< std :: string > return_split_strings_if_line_contains_all_keywords( std :: vector< std :: string> keywords, std :: string filepath ) {

  try {
    std :: ifstream ifs( filepath.c_str(), std :: ios :: in );
    while( ifs.eof() == false ) {
      char line_buffer[1024];
      ifs.getline( line_buffer, 1024 );
      std :: string line_string( line_buffer );
      std :: vector< std :: string > line_details;
      boost :: split( line_details, line_string, boost :: is_any_of( " " ) );
      if( iquads :: utility :: string_tool :: stringsA_has_stringsB( line_details, keywords ) == true ) {
        return line_details;
      }
    }
    throw std :: make_tuple( keywords, filepath );
  } catch ( std :: tuple< std :: vector< std :: string>, std :: string >   error_info ) {
    std :: cout << "error: cannot find a line contains all the keywords in file " << std :: get<1> ( error_info ) << std :: endl;
    std :: cout << "       requested keywords are: " << std :: endl;
    for( size_t i = 0; i < ( std :: get<0>( error_info ) ).size(); i++ ) {
      std :: cout << ( std :: get<0>( error_info )[i] ) << ";";
    }
    std :: cout << std :: endl;
    abort();
  }

}; // end of function return_split_strings_if_line_contains_all_keywords()

} // end of namespace file_system

} // end of namespace iquads

#endif
