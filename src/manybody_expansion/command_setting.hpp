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

#ifndef MANYBODY_EXPANSION_COMMAND_SETTING_HPP
#define MANYBODY_EXPANSION_COMMAND_SETTING_HPP

#include <string>

using std::string;

namespace iquads {

namespace manybody_expansion {

struct CommandSetting {
public:
  typedef string file_name_type;
  typedef bool condition_type;
  typedef file_name_type& file_name_ref;
  typedef condition_type& condition_ref;

public:
  CommandSetting()
   {
     this->input_filename_ = "not set";
     this->output_filename_ = "not set";
   }

public:
  enum request_method_type { FROM_FILE, DEFAULT };

public:
  const file_name_type input_filename() const 
   { return this->input_filename_; }
  file_name_ref set_input_filename()
   { return this->input_filename_; }
  const file_name_type output_filename() const
   { return this->output_filename_; }
  file_name_ref output_filename()
   { return this->output_filename_; }
  const request_method_type request_method() const
   { return this->request_method_; } 

private:
  file_name_type input_filename_;
  file_name_type output_filename_;
  request_method_type request_method_;

}; // end of class CommandSetting

} // end of namespace manybody_expansion

} // end of namespace iquads

#endif
