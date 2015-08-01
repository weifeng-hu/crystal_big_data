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

#include <string>

namespace iquads { 

namespace interface_to_third_party { 

namespace qcdmrg {

class cmd_options : public ithaca::cmd_options
{
public:
  cmd_options( int argc, char* argv[] );
  ~cmd_options(){};

public:
  std::string path_exec;

  std::string dmrg_input;
  char* _dmrg_input;
  bool dmrg_input_is_set;

  std::string dmrg_output;
  char* _dmrg_output;
  bool dmrg_output_is_set;

  std::string work_dir;

};

} 

} // end of namespace interface_to_third_party

} // end of namespace iquads
