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

namespace iquads {

namespace manybody_expansion {

  /**
   *  A data container to store command information for 
   *  a many body expansion calculation.
   *
   *  Essential data members are:
   *   + input, output file names, input file name is essential if
   *     actual calculation parameters are read from a file.
   *   + It has an enum type, to tell the source to file an request.
   *   + We can add some faster keywords to the data member to 
   *     further help define a calculation. But these data member/
   *     command options should be "enviromental" rather than 
   *     "calculation data related, e.g. the order of the expansion".
   *
   *  Since a data container usually does not manipulate data 
   *  by itself, we leave the task for setting data to the 
   *  analyse_command() method defined in the client class.
   *  And we use keyword struct for this container since 
   *  data stored are not always at a valid state.
   */

using std::string;

struct CommandSetting {
  enum request_source_type { UNKNOWN, FROM_FILE };
public:
  typedef string file_name_type;

public:
  CommandSetting()
    {
      this->input_filename_ = "not set";
      this->output_filename_ = "not set";
      this->request_source_ = UNKNOWN;
    }

public:
  /**
   *  Accessors
   */
  file_name_type input_filename() const 
    { return this->input_filename_; }
  file_name_type output_filename() const
    { return this->output_filename_; }
  request_source_type request_source() const
    { return this->request_source_; } 

  /**
   *  Mutators 
   */
  file_name_type& set_input_filename()
    { return this->input_filename_; }
  file_name_type& set_output_filename()
    { return this->output_filename_; }
  request_source_type& set_request_source()
    { return this->request_source_; } 

private:
  file_name_type   input_filename_;
  file_name_type   output_filename_;
  request_source_type   request_source_;

}; // end of struct CommandSetting

} // end of namespace manybody_expansion

} // end of namespace iquads

#endif
