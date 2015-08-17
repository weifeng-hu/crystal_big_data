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

#ifndef ORCA_AGENT_H
#define ORCA_AGENT_H

#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <interface_to_third_party/external_program_agent_base.h>

namespace iquads {

namespace interface_to_third_party {

class OrcaAgent 
 : public ExternalProgramAgent_Base
{
public:
  OrcaAgent()
   {
     {
      using std::getenv;
      const char* program_path = getenv("ORCA_PATH");
      if( program_path == nullptr ){
        using std::cout;
        using std::endl;
        cout << "Environment Variable $ORCA_PATH not set" << endl;
        exit(1);
      }
      else{
       this->program_path_ = program_path;
      }
     }
     this->program_name_ = "orca";
   }

public:
  void run_calculation(){}
  file_name_type write_input(){}
  file_name_type write_script(){}
  file_name_type collect_result(){}
  void sequence_full(){}
  void sequence_export_input_only(){}
  void sequence_collect_result_only(){}

}; // end of class OrcaAgent

class Psi3Agent
 : public ExternalProgramAgent_Base
{
public:
  Psi3Agent()
   {
     {
      using std::getenv;
      const char* program_path = getenv("PSI3_PATH");
      if( program_path == nullptr ){
        using std::cout;
        using std::endl;
        cout << "Environment Variable $PSI3_PATH not set" << endl;
        exit(1);
      }
      else{
       this->program_path_ = program_path;
      }
     }
     this->program_name_ = "psi3";
   }

public:
  void run_calculation(){}
  file_name_type write_input(){}
  file_name_type write_script(){}
  file_name_type collect_result(){}
  void sequence_full(){}
  void sequence_export_input_only(){}
  void sequence_collect_result_only(){}

}; // end of class Psi3Agent

} // end of namespace interface_to_third_party

} // end of namespace iquads

#endif
