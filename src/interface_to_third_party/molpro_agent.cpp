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
 agent_type :: write_input_hf_energy( config_type config )
{

  using std::ofstream;
  using std::endl;
  file_name_type input_file_name = config.work_path() + config.molecule_name() + config.file_extension();
  ofstream ofs.open( input_file_name.c_str(), "wt" );
  ofs << config.memory_config() << endl;
  ofs << config.basis_set_config() << endl;
  ofs << config.symmetry_config() << endl;
  ofs << config.geometry_config() << endl;
  ofs << config.hf_config() << endl;
  ofs.close();
  return input_filename;

}; // end of write_input()

agent_type :: file_name_type
 agent_type :: writ_input_mp2_energy( config_type config )
{
  return input_filename;
}

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
