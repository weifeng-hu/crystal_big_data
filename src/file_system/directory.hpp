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

#ifndef DIRECTORY_HPP
#define DIRECTORY_HPP

#include <string>
#include <iostream>
#include <boost/filesystem.hpp>

namespace iquads {

namespace file_system {

using std :: string;

struct Directory {
public:
  typedef Directory this_type;
  typedef std :: string value_type;

public:
  Directory() { this->value_ = ""; }
  Directory( value_type dir_value ) :
    value_ ( dir_value ) {}

public:
  value_type create() {
    boost :: filesystem :: path current_path( this->value_ );
    boost :: filesystem :: create_directory( boost :: filesystem :: absolute( current_path ) );
    return this->value_;
  }
  bool exists() 
    { return boost :: filesystem :: exists( boost :: filesystem :: absolute ( boost :: filesystem :: path( this->value_ ) ) ); }
  friend
  std :: ostream& operator<< ( std :: ostream& os, const this_type& obj ) { 
    os << obj.absolute() << std :: endl;
    return os;
  }
  friend
  bool operator== ( const this_type& lhs, const this_type& rhs ) {
    return lhs.absolute() == rhs.absolute() ? true : false;
  }

public:
  value_type value() const
    { return this->value_; } 
  value_type absolute() const { 
    boost :: filesystem :: path current_path( this->value_ );
    boost :: filesystem :: path absolute_path = boost :: filesystem :: absolute( current_path );
    return absolute_path.string();
  }

private:
  value_type value_;

}; // end of struct Directory

} // end of namespace file_system

} // end of namespace iquads

#endif
