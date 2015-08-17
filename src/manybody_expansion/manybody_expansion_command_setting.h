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

#ifndef MANYBODY_EXPANSION_COMMAND_SETTING_H
#define MANYBODY_EXPANSION_COMMAND_SETTING_H

#include <string>

using std::string;

namespace iquads {

namespace manybody_expansion {

struct CommandSetting
{
public:
  typedef string filename_type;
  typedef filename_type& filename_reference;
  typedef bool condition_type;
  typedef condition_type& condition_reference;

public:
  ManyBodyExpansion_CommandSetting()
   {
     this->set_default();
   }

public:
  void set_default()
   {
     this->config_filename_ = "not set";
     this->output_filename_ = "not set";
   }

public:
  const filename_type config_filename() const 
   { return this->config_filename_; }
  filename_reference set_config_filename()
   { return this->config_filename_; }
  const filename_type output_filename() const
   { return this->output_filename_; }
  filename_type output_filename()
   { return this->output_filename_; }

private:
  filename_type config_filename_;
  filename_type output_filename_;

}; // end of class CommandSetting

} // end of namespace manybody_expansion

} // end of namespace iquads

#endif
