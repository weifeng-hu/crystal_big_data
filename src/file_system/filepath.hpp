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

#ifndef FILEPATH_HPP
#define FILEPATH_HPP

#include <stdlib.h>
#include <string>
#include <iostream>
#include <boost/filesystem.hpp>
#include <file_system/directory.hpp>
#include <file_system/filename.hpp>

namespace iquads {

namespace file_system {

using std :: string;

struct Filepath {
public:
  typedef Filepath this_type;
  typedef Directory directory_type;
  typedef Filename  filename_type;
  typedef std :: string value_type;

public:
  Filepath( directory_type directory_value,
            filename_type  filename_value ) :
    directory_( directory_value ), filename_( filename_value ) {}
  Filepath( value_type directory_value,
            value_type filename_value ) :
    directory_( directory_type( directory_value) ), filename_( filename_type( filename_value ) ) {}

public:
  bool exists()
    { return boost :: filesystem :: exists( boost :: filesystem :: path( this->value() ) ); }
  this_type rename_if_exists() {
    int count = 0;
    this_type filepath_temp( *this );
    while( true ) {
      if( filepath_temp.exists() == false ) {
        break;
      }
      else {
        count++;
        std :: string rename_string = "_rename_";
        rename_string += std :: to_string( count );
        filename_type new_filename( this->filename_.name() + rename_string, this->filename_.extension() );
        this_type new_filepath( this->directory_, new_filename );
        filepath_temp = new_filepath;
      }
    }
    this->directory_ = filepath_temp.directory();
    this->filename_  = filepath_temp.filename();
    return *this;
  }
  friend
  std :: ostream& operator<< ( std :: ostream& os, const this_type& obj ) {
    os << obj.absolute() << std :: endl;
    return os;
  }
  void copy_to( directory_type to ) {
    if( to.exists() == false ) { to.create(); }
    std :: string command = std :: string( "cp " ) + this->absolute() + std :: string( " " ) + to.absolute();
    int retval = system( command.c_str() );
    if( retval != 0 ) { 
      std :: cout << "error in copying file: " << command << std :: endl; abort();
    }
   /**
    *  Currently we cannot use copy_file for most of the boost versions, because --std=c++11 does not fit the actual boost implementation for this function
    */
    //boost :: filesystem :: path path_from( this->value() );
    //boost :: filesystem :: path path_to( std :: string( to.value() + std :: string("/") + this->filename_.value() ) );
    // boost :: filesystem :: copy_file( path_from, path_to );
  }
  friend
  bool operator== ( const this_type& lhs, const this_type& rhs ) {
    return lhs.absolute() == rhs.absolute() ? true : false;
  }

public:
  value_type value() const 
    { return std :: string( this->directory_.value() + string("/") + this->filename_.value() ); }
  value_type absolute() const
    { return std :: string( this->directory_.absolute() + string("/") + this->filename_.value() ); }
  directory_type directory() const 
    { return this->directory_; }
  filename_type filename() const
    { return this->filename_; }

private:
  directory_type directory_;
  filename_type  filename_;

}; // end of struct Filepath

} // end of namespace file_system

} // end of namespace iquads

#endif
