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


#ifndef EXTERNAL_PROGRAM_AGENT_H
#define EXTERNAL_PROGRAM_AGENT_H

#include <stdlib.h>
#include <external_program_agent_base.h>

namespace iquads {

namespace manybody_expansion {

class MolproAgent 
  : public ExternalProgramAgent_Base
{
public:
  MolproAgent()
   {
     this->program_name_ = "molpro";
     this->program_path_ = "";
   }

public:
  void run_calculation()
   {
     command_line_type command_line = this->program_path_ + this->input_name_;
     int res = system( command_line.c_str() );
   }
  void write_input(){};
  void write_script(){};
  void collect_result(){};
  void sequence_full()
   {
     this->write_input();
     this->run_calculation();
     this->collect_result();
   }
  void sequence_export_input_only()
   {
     this->write_input();
     this->write_script();
   }
  void sequence_collect_result_only()
   {
     this->collect_result();
   }

}; // end of class MolproAgent


class OrcaAgent 
 : public ExternalProgramAgent_Base
{
public:
  OrcaAgent()
   {
     this->program_name_ = "orca";
     this->program_path_ = "";
   }

public:
  void run_calculation(){}
  void write_input(){}
  void write_script(){}
  void collect_result(){}
  void sequence_full(){}
  void sequence_export_input_only(){}
  void sequence_collect_result_only(){}

}; // end of class OrcaAgent

} // end of namespace manybody_expansion

} // end of namespace iquads

#endif
