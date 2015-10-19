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

inline std :: vector< std :: string > read_block_between_lineA_and_lineB( std :: string lineA, std :: string lineB, std :: string filepath ) {

  try {
    std :: vector< std :: string > retval;
    retval.resize(0);
    std :: ifstream ifs( filepath.c_str(), std :: ios :: in );
    bool lineA_is_found = false;
    bool lineB_is_found = false;
    while( ifs.eof() == false ) {
      char line_buffer[1024];
      ifs.getline( line_buffer, 1024 );
      std :: string line_string( line_buffer );
      boost :: trim_right( line_string );
      if( line_string == lineA ) {
        lineA_is_found = true;
        break;
      }
    }

    while( ifs.eof() == false ) {
      char line_buffer[1024];
      ifs.getline( line_buffer, 1024 );
      std :: string line_string( line_buffer );
      boost :: trim_right( line_string );
      if( line_string == lineB ) {
        lineB_is_found = true;
        break;
      }
      if( ( line_string != std :: string ( "" ) ) )  {
        retval.push_back( line_string );
      }
    }
    ifs.close();
    if( retval.size() == 0 ) { throw std :: make_tuple( lineA, lineB, filepath ); }
    if( lineA_is_found == false ) { throw std :: make_tuple( lineA, filepath ); }
    if( lineB_is_found == false ) { throw std :: make_tuple( lineB, filepath ); }
    return retval;
  } catch ( std :: tuple < std :: string, std :: string, std :: string> error_info ) {
    std :: cout << "error: cannot find any non while space block in file " << std :: get<2> ( error_info ) << " between lines " << std :: endl;
    std :: cout << "line A: " << std :: get<0> ( error_info ) << std :: endl;
    std :: cout << "line B: " << std :: get<1> ( error_info ) << std :: endl;
    abort();
  } catch ( std :: tuple < std :: string, std :: string > error_info ) {
    std :: cout << "error: cannot find a line in file " << std :: get<1> ( error_info ) << std :: endl;
    std :: cout << "line not found: " << std :: get<0> ( error_info ) << std :: endl;
    abort();
  }

}

inline std :: vector< std :: string > return_split_strings_if_line_contains_all_keywords( std :: vector< std :: string> keywords, std :: string filepath ) {

  try {
    std :: ifstream ifs( filepath.c_str(), std :: ios :: in );
    while( ifs.eof() == false ) {
      char line_buffer[1024];
      ifs.getline( line_buffer, 1024 );
      std :: string line_string( line_buffer );
      std :: vector< std :: string > line_details;
      boost :: trim( line_string );
      boost :: split( line_details, line_string, boost :: is_any_of( " " ), boost :: token_compress_on  );
      if( iquads :: utility :: string_tool :: stringsA_has_stringsB( line_details, keywords ) == true ) {
        return line_details;
      }
    }
    ifs.close();
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
