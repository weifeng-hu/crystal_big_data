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
 * the Free Software Foundation, either version 3 of the License, or
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

#ifndef EXTERNAL_PROGRAM_AGENT_BASE_H
#define EXTERNAL_PROGRAM_AGENT_BASE_H

#include <string>
#include <memory>
#include <manybody_expansion/electron_correlation_config.h>
#include <manybody_expansion/electron_correlation_report.h>

using std::string;
using std::shared_ptr;

namespace iquads {

namespace manybody_expansion {

class ExternalProgramAgent_Base
{
public:
  typedef electron_correlation::ElectronCorrelation_Config config_type;
  typedef electron_correlation::ElectronCorrelation_Report report_type;
  typedef string program_name_type;
  typedef string program_path_type;
  typedef string working_path_type;
  typedef string file_name_type;
  typedef string command_line_type;
  typedef double energy_data_type;

public:
  virtual void run_calculation() = 0;
  virtual void write_input() = 0;
  virtual void write_script() = 0;
  virtual void collect_result() = 0;

public:
  void set_essential_data()
   { /* To be define */ }

public:
  virtual void sequence_full() = 0;
  virtual void sequence_export_input_only() = 0;
  virtual void sequence_collect_result_only() = 0;

protected:
  shared_ptr< config_type > config_ptr_;
  shared_ptr< report_type > report_ptr_;
  program_name_type program_name_;
  program_path_type program_path_;
  working_path_type scratch_;
  file_name_type input_name_;
  file_name_type output_name_;

}; // end of class ExternalProgramAgent_Base

} // end of namespace manybody_expansion

} // end of namespace iquads

#endif
