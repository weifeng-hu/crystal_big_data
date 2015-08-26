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

#ifndef MOLPRO_CONFIG_H
#define MOLPRO_CONFIG_H

#include <string>

namespace iquads {

namespace interface_to_third_party {

using std::string;

struct MolproConfig
{
public:
  typedef MolproConfig this_type;

  typedef bool condition_type;
  typedef string file_name_type;
  typedef string work_path_type;
  typedef string basis_set_name_type;
  typedef string memory_unit_type;
  typedef string geometry_format_type;
  typedef string geometry_unit_type;
  typedef string molecule_name_type;
  typedef size_t memory_amount_type;
  typedef size_t number_type;

public:
  void set_defaults(){};

public:
  const file_name_type input_filename() const
   { return this->input_filename_; }
  const file_name_type output_filename() const
   { return this->output_filename_; }
  const work_path_type work_path() const
   { return this->work_path_; }

private:
  file_name_type input_filename_;
  file_name_type output_filename_;
  work_path_type work_path_;
  basis_set_name_type basis_set_name_;
  memory_amount_type memory_amount_;
  memory_unit_type memory_unit_;
  geometry_format_type geometry_format_;
  geometry_unit_type geometry_unit_;
  molecule_name_type molecule_name_;

}; // end of struct MolproConfig

} // end of namespace interface_to_third_party

} // end of namespace iquads

#endif
