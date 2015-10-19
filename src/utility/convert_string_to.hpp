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

#ifndef CONVERT_STRING_TO_HPP
#define CONVERT_STRING_TO_HPP

#include <stdlib.h>
#include <iostream>
#include <string>

namespace iquads {

namespace utility {

namespace string_tool {

template < typename DataType > inline DataType convert_string_to( std :: string string_value ) {
  std :: cout << "unknown DataType to convert to" << std :: endl;
  abort();
}

template <> inline int convert_string_to< int > ( std :: string string_value ) 
  { return std :: stoi( string_value ); }

template <> inline long convert_string_to< long > ( std :: string string_value )
  { return std :: stol( string_value ); }

template <> inline long long convert_string_to< long long > ( std :: string string_value )
  { return std :: stoll( string_value ); }

template <> inline unsigned long convert_string_to< unsigned long > ( std :: string string_value )
  { return std :: stoul( string_value ); }

template <> inline unsigned long long convert_string_to< unsigned long long > ( std :: string string_value )
  { return std :: stoull( string_value ); }

template <> inline float convert_string_to< float > ( std :: string string_value )
  { return std :: stof( string_value ); }

template <> inline double convert_string_to< double > ( std :: string string_value )
  { return std :: stof( string_value ); }

template <> inline long double convert_string_to< long double > ( std :: string string_value )
  { return std :: stof( string_value ); }

template <> inline std :: string convert_string_to < std :: string > ( std :: string string_value )
  { return string_value; }

template <> inline const char* convert_string_to < const char* > ( std :: string string_value )
  { return string_value.c_str(); }

} // end of namespace string_tool

} // end of namespace utility

} // end of namespace iquads

#endif
