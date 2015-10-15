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

#include <stdlib.h>
#include <string>
#include <fstream>
#include <iquads/sequence.hpp>
#include <chemistry/periodic_table.hpp>
#include <interface_to_third_party/molpro_config.hpp>
#include <interface_to_third_party/molpro_agent.hpp>

namespace iquads {

namespace interface_to_third_party {

typedef MolproAgent agent_type;

agent_type :: base_config_ptr_list
agent_type :: generate_config_list_from_request( request_type request ) {

  base_config_ptr_list config_pointer_list;
  if( request.calculation() == iquads :: sequence :: calculation :: SINGLE_POINT_ENERGY ) {
    config_pointer_list.resize(1);
    config_pointer_list[0] = new this_config_type;

    config_pointer_list[0] -> set_memory_config() = this_config_type :: MemoryConfig( 400, "m" );
    config_pointer_list[0] -> set_basis_set_config() = this_config_type :: BasisSetConfig( request.basis_set_name() );
    config_pointer_list[0] -> set_geometry_config() = this_config_type :: GeometryConfig( request.molecule_obj().coordinate_list(), coordinate_representation :: CARTESIAN, request.molecule_obj().geometry_unit() );
    size_t nelec = request.molecule_obj().neutral_nelec() - request.molecule_obj().charge();
    size_t spin  = config_pointer_list[0]->check_spin( request.spin(), nelec );
    config_pointer_list[0] -> set_hartree_fock_config() = this_config_type :: HartreeFockConfig( nelec, spin, request.sym() ); // I need to get the periodic table! 
    config_pointer_list[0] -> set_mp2_config() = this_config_type :: MP2Config();
    config_pointer_list[0] -> set_casscf_config() = this_config_type :: MultiConfig();
  }

  return config_pointer_list;

}; // end of function generate_config_list_from_request()

agent_type :: file_name_type 
agent_type :: write_input_hf_energy( base_config_ptr base_config_pointer ) {

  using std::ofstream;
  using std::endl;
  file_name_type input_file_name = base_config_pointer->input_path() + 
                                   base_config_pointer->molecule_name() + 
                                   base_config_pointer->file_extension();
  ofstream ofs( input_file_name.c_str(), std::ios::out );
  base_config_pointer->set_memory_config().print( ofs );
  base_config_pointer->set_basis_set_config().print( ofs );
  base_config_pointer->set_geometry_config().print( ofs );
  base_config_pointer->set_hartree_fock_config().print( ofs );
  ofs.close();
  return input_file_name;

}; // end of function write_input_hf_energy()

agent_type :: file_name_type
agent_type :: write_input_mp2_energy( base_config_ptr base_config_pointer ) {

  using std::ofstream;
  using std::endl;
  file_name_type input_file_name = base_config_pointer->input_path() + 
                                   base_config_pointer->molecule_name() + 
                                   base_config_pointer->file_extension();

  return input_file_name;

}; // end of function write_input_mp2_energy()

agent_type :: file_name_type
agent_type :: write_input_casscf_energy( base_config_ptr base_config_pointer ) {
  using std::ofstream;
  using std::endl;
  file_name_type input_filename = base_config_pointer->input_path() + 
                                   base_config_pointer->molecule_name() + 
                                   base_config_pointer->file_extension();
  return input_filename;

}; // end of function write_input_casscf_energy()

agent_type :: energy_report_type 
agent_type :: collect_energy_data_from_output( file_name_type output_filename ) {

}; // end of function collect_energy_data_from_output()

} // end of namespace interface_to_third_party

} // end of namespace iquads
