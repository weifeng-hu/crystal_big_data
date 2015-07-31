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

using std::string;

namespace iquads {

namespace file {

template < class DataType > 
DataType line_searcher( string identifier, string filename )
{

  typedef typename DataType return_type;
  return_type retval;
  {
   string value_str;
   {
    using std::vector;
    vector<string> identifier_details;
    {
     using boost::split;
     using boost::is_any_of;
     split( identifier_details, identifier, is_any_of(" ") );
    }
    const size_t nword = line_details.size();
    vector<string> line_details;
    {
     using std::ifstream;
     using std::ios::in;
     ifstream ofs( filename.c_str(), in );
     while( !ofs.eof() )
     {
      vector<string> line_details_tmp;
      {
       char[256] line_buf;
       ofs.getline( line_buf );
       string line_string( line_buf );
       {
        using boost::split;
        using boost::is_any_of;
        split( line_details, line_string, is_any_of(" ") );
       }
      }
 
      size_t idetail = 0;
      while( idetail != min( line_details.size(), identifier_details.size() ) )
      {
       if( line_details_tmp[idetail] != identifier_details[idetail] ){
        break;
       }
       else{
        idetail++;
       }
      }
      if( idetail == nword ){
       line_details = line_details_tmp;
       break;
      }
     }
     ofs.close();
    }
    value_str = (*line_details.rbegin());
   }
   using std::stringstream;
   stringstream ss;
   ss << value_str;
   ss >> retval;
  }
  return retval;

}; // end of function line_searcher()

} // end of namespace file

} // end of namespace iquads

#endif
