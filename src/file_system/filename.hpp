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

#ifndef FILENAME_HPP
#define FILENAME_HPP

#include <string>
#include <iostream>
#include <vector>
#include <boost/algorithm/string.hpp>

namespace iquads {

namespace file_system {

using std :: string;

struct Filename {
public:
  typedef Filename this_type;
  typedef std :: string value_type;
  typedef std :: string name_type;
  typedef std :: string extension_type;

public:
  Filename() {
    this->name_ = "";
    this->extension_ = "";
  }
  Filename( name_type name_value ) {
    std :: vector< std :: string > results;
    results.resize(0);
    boost :: split( results, name_value, boost :: is_any_of(".") );
    if( results.size() == 1 ) {
      this->name_ = name_value;
      this->extension_ = "";
    }
    else {
      this->extension_ = ".";
      this->extension_ += *(results.rbegin());
      this->name_ = "";
      for( size_t i = 0; i < results.size() - 1; i++ ) {
        this->name_ += results.at(i);
      }
    }
  }
  Filename( name_type name_value,
            extension_type extension_value ):
    name_( name_value ), extension_( extension_value ) {
      if( this->extension_.size() == 0 ) return;
      if( this->extension_.size() != 0 && this->extension_.at(0) != '.' ) {
        this->extension_.insert( 0, std :: string( "." ) );
        return;
      }
    }

public:
  friend
  std :: ostream& operator<< ( std :: ostream& os, const this_type& obj ) {
    os << obj.value() << std :: endl;
    return os;
  }

public:
  name_type name() const 
    { return this->name_; }
  name_type extension() const
    { return this->extension_; }
  value_type value() const
    { return std :: string( this->name_ + this->extension_ ); } 

private:
  name_type name_;
  extension_type extension_;

}; // end of struct Filename

} // end of namespace file_system

} // end of namespace iquads

#endif
