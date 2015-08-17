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
#include <fstream>
#include <interface_to_third_parth/molpro_config.h>
#include <interface_to_third_party/molpro_agent.h>

namespace iquads {

namespace interface_to_third_party {

typedef MolproAgent agent_type;

agent_type :: file_name_type 
 agent_type :: write_input() 
{

  using agent_type::file_name_type;
  using std::ofstream;
  using std::endl;

  this->input_file_name_ 
    = this->work_path_ + this->molecule_name_ + ".com";

  {
    ofstream ofs.open( this->input_filename_.c_str() );
  
    ofs << "memory, " ;
    ofs << static_cast<config_pointer_type>( base_config_pointer )->memory_size();
    ofs << ",";
    ofs << static_cast<config_pointer_type> ( base_config_pinter ) ->memory_unit() << endl;
  
    ofs << "basis=";
    ofs << static_cast<config_pointer_type> ( base_config_pointer )->basis_set_name() << endl;
  
    ofs << base_config_pointer->geometry_unit()<< endl;
  
    ofs << "geomtyp = ";
    ofs << static_cast<config_pointer_type> ( base_config_pointer )-> geometry_type() << endl;
  
    ofs << "geomtry={" << endl;
//  ofs << static_cast<config_pointer_type> ( base_config_pointer )->molecule() << "}" << endl;
    ofs.close();
  }

  return input_filename;

}; // end of write_input()

client_type::file_name_type
 client_type::write_run_script( base_config_ptr base_config_pointer )
{

  using std::ofstream;
  ofstream ofs( script_filename.c_str(), ofstream::out | ofstream::app );
  ofs << this->program_path_ << this->program_name_ << " " << ;
  ofs.close();

}; // end of write_script()

client_type :: file_name_type
 client_type :: collect_result()
{
/*
  using iquads::file::line_searcher;
  using std::string;
  // these are are subject to change
  if( this->config_ptr()->hf_requested() ){ 
    this->report_ptr()->set_total_energy() = line_searcher< energy_data_type >(" !RHF STATE 1.1 Energy", this->output_name );
  }
  else if( this->config_ptr()->mp2_requested() ){
    this->report_ptr()->set_total_energy() = line_searcher< energy_data_type >( " !MP2 total energy", this->output_name );
  }
  else if( this->config_ptr()->ccsd_requested() ){
//    this->report_ptr()->set_total_energy() = line_searcher< energy_data_type >(" ", this->output_name );
  }
  else if( this->config_ptr()->ccsdt_requested() ){
//    this->report_ptr()->set_total_energy() = line_searcher< energy_data_type >("", this->output_name );
  }
*/
}; // end of collect_result()

void agent_type::sequence_local_run()
{

  config_type config;
  config->set_defaults();
  this->write_input( config );
  this->run_calculation( config );
  this->collect_result( config );

} // end of sequence_local_run()

} // end of namespace interface_to_third_party

} // end of namespace iquads
