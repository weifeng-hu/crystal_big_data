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
#include <interface_to_third_party/external_program_agent.h>

namespace iquads {

namespace interface_to_third_party {

string MolproAgent :: write_input()
{

  using std::ofstream;
  using std::endl;
  // these are subject to change
  ofstream ofs.open( this->input_name.c_str() );
  ofs << "memory, " << this->config_ptr()->memory_size() << ", m" << endl;
  ofs << "basis=" << this->config_ptr()->basis_set() << endl;
  ofs << "angstrom" << endl;
  ofs << "geomtyp=xyz" << endl;
  ofs << "geomtry={" << endl << this->config_ptr()->molecule() << "}" << endl;
  if( this->config_ptr()->hf_requested() ) { ofs << "hf" << endl; }
  else if( this->config_ptr()->mp2_requested() ){ ofs << "hf" << endl << "mp2" << endl; }
  else if( this->config_ptr()->mp3_requested() ){ ofs << "hf" << endl << "mp3" << endl; }
  else if( this->config_ptr()->ccsd_requested() ){ ofs << "hf" << endl << "ccsd" << endl; }
  else if( this->config_ptr()->ccsdt_requested() ){ ofs << "hf" << endl << "ccsd(t)" << endl; }
  ofs.close();

}; // end of write_input()

Molpro :: write_script()
{

}; // end of write_script()

MolproAgent :: collect_result()
{

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

}; // end of collect_result()

} // end of namespace interface_to_third_party

} // end of namespace iquads
