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
#include <sstream>
#include <string>
#include <fstream>
#include <boost/filesystem.hpp>
#include <iquads/sequence.hpp>
#include <utility/convert_string_to.hpp>
#include <file_system/file_functions.hpp>
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

    config_pointer_list[0] -> set_solution_tag() = quantity :: ENERGY;
    config_pointer_list[0] -> set_correlation_tag() = request.method();
    config_pointer_list[0] -> set_file_extension() = ".com";
    config_pointer_list[0] -> set_molecule_name() = request.molecule_name();
    config_pointer_list[0] -> set_input_dir() = request.input_dir();
    config_pointer_list[0] -> set_scratch_dir() = request.scratch_dir();
    config_pointer_list[0] -> set_output_dir()  = request.output_dir();
    config_pointer_list[0] -> set_memory_config() = this_config_type :: MemoryConfig( 400, "m" );
    config_pointer_list[0] -> set_basis_set_config() = this_config_type :: BasisSetConfig( request.basis_set_name() );
    config_pointer_list[0] -> set_geometry_config() = this_config_type :: GeometryConfig( request.molecule_obj().coordinate_list(), coordinate_representation :: CARTESIAN, request.molecule_obj().geometry_unit() );
    size_t nelec = request.molecule_obj().neutral_nelec() - request.molecule_obj().charge();
    size_t spin  = config_pointer_list[0]->check_spin( request.spin(), nelec );
    config_pointer_list[0] -> set_hartree_fock_config() = this_config_type :: HartreeFockConfig( nelec, request.sym(), spin ); // I need to get the periodic table! 
    config_pointer_list[0] -> set_mp2_config() = this_config_type :: MP2Config();
    config_pointer_list[0] -> set_casscf_config() = this_config_type :: MultiConfig();
  }

  return config_pointer_list;
// end of function generate_config_list_from_request()
}; // end of function generate_config_list_from_request()

agent_type :: filepath_type
agent_type :: write_input_hf_energy( base_config_ptr base_config_pointer ) {

  using std::ofstream;
  directory_type input_dir ( base_config_pointer->input_dir() );
  input_dir.create();
  filepath_type :: filename_type input_name ( base_config_pointer->molecule_name(), base_config_pointer->file_extension() );
  filepath_type input_filepath( input_dir, input_name );
  input_filepath.rename_if_exists();

  ofstream ofs( input_filepath.absolute().c_str(), std::ios::out );
  base_config_pointer->set_memory_config().print( ofs );
  base_config_pointer->set_basis_set_config().print( ofs );
  base_config_pointer->set_geometry_config().print( ofs );
  base_config_pointer->set_hartree_fock_config().print( ofs );
  ofs.close();
  return input_filepath;

}; // end of function write_input_hf_energy()

agent_type :: filepath_type
agent_type :: write_input_mp2_energy( base_config_ptr base_config_pointer ) {

  using std::ofstream;
  using std::endl;
  file_name_type input_file_name = base_config_pointer->input_dir() + 
                                   base_config_pointer->molecule_name() + 
                                   base_config_pointer->file_extension();
  //return input_file_name;

}; // end of function write_input_mp2_energy()

agent_type :: filepath_type
agent_type :: write_input_casscf_energy( base_config_ptr base_config_pointer ) {
  using std::ofstream;
  using std::endl;
  file_name_type input_filename = base_config_pointer->input_dir() + 
                                   base_config_pointer->molecule_name() + 
                                   base_config_pointer->file_extension();
  //return input_filename;

}; // end of function write_input_casscf_energy()

agent_type :: local_run_info_type 
agent_type :: run_external_program( filepath_type input_path, directory_type scratch_dir, directory_type output_dir ) {
  try {
    // check whether input_file exists;
    if( input_path.exists() == true ) {
      // copy input file to scratch
      if( input_path.directory() == scratch_dir ) {
        std :: cout << "warning: input file path and scratch path are the same! suggest to have a different scratch path " << std :: endl;
      }
      else {
        input_path.copy_to( scratch_dir );
      }

      // get the file name + path for scratch run
      filepath_type scratch_input_path = filepath_type( scratch_dir, input_path.filename() );
      filepath_type :: filename_type output_filename( input_path.filename().name() , std :: string( ".out" ) );
      filepath_type scratch_output_path = filepath_type( scratch_dir, output_filename );

      // RUN, for molpro, we don't need to tell the run-time output filename
      command_line_type command_line 
        = this->program_path_ + "/" + program_name_ + " " + scratch_input_path.absolute();
      int retval_run = system( command_line.c_str() );
      if( retval_run != 0 ) { throw 2; }

      // after a successful run we copy the output file from scratch to output path
      // we should check whether this output file is there
      if( scratch_output_path.exists() == false ) {
        throw 3;
      }
      if( scratch_dir == output_dir ) {
        // do nothing;
        std :: cout << " scratch path and output path are the same; suggest to have a different output path" << std :: endl;
      }
      else {
        if( input_path.directory() == output_dir ) {
          std :: cout << " input path and output path are the same; suggest to have a different output path" << std :: endl;
        }
        scratch_output_path.copy_to( output_dir );
      } 
      return local_run_info_type( this->program_name_, 
                                  input_path.directory().absolute(),
                                  input_path.filename().value(),
                                  scratch_dir.absolute(),
                                  output_dir.absolute(),
                                  output_filename.value() );

    }
    else {
      throw 0;
    }
  } catch ( int signal ) {
    switch ( signal ) {
      case( 0 ):
        std :: cout << " cannot find input file " << input_path.absolute() << std :: endl;
        break;
      case( 1 ):
        std :: cout << " cannot copy input file to the scratch file " << std :: endl;
        break;
      case( 2 ):
        std :: cout << " molpro program returns an error" << std :: endl;
        break;
      case( 3 ):
        std :: cout << " cannot find the output file in scratch" << std :: endl;
        break;
      case( 4 ):
        std :: cout << " cannot copy output file from scratch to output dir" << std :: endl;
        break;
      default:
        std :: cout << " unknown error in run external program" << std :: endl;
        break;
    }
    abort();
  }
} // end of function run_external_program()

iquads :: structure :: AtomList 
agent_type :: read_coordinate( filepath_type output_path ) {

  iquads :: structure :: AtomList retval;
  retval.resize(0);

  std :: string lineA( " NR  ATOM    CHARGE       X              Y              Z" );
  std :: string lineB( " Bond lengths in Bohr (Angstrom)" );
  std :: vector< std :: string > coordinate_block = iquads :: file_system :: read_block_between_lineA_and_lineB( lineA, lineB, output_path.absolute() );

  for( size_t i = 0; i < coordinate_block.size(); i++ ) {
    std :: string line = coordinate_block[i];
    std :: vector< std :: string > vector_of_string;
    boost :: trim( line );
    boost :: split( vector_of_string, line, boost :: is_any_of( " " ), boost :: token_compress_on );
    retval.push_back ( iquads :: structure :: Atom( vector_of_string.at(1), 
                                                    iquads :: utility :: string_tool :: convert_string_to<double> ( vector_of_string.at(3) ), 
                                                    iquads :: utility :: string_tool :: convert_string_to<double> ( vector_of_string.at(4) ), 
                                                    iquads :: utility :: string_tool :: convert_string_to<double> ( vector_of_string.at(5) ), 
                                                    std :: string( "bohr" ) ) );
  }

  return retval;

} // end of function read_coordinate()

int agent_type :: read_charge( filepath_type output_path ) {

  std :: vector< std :: string > keywords;
  keywords.push_back( std :: string( "NUMBER" ) );
  keywords.push_back( std :: string( "OF" ) );
  keywords.push_back( std :: string( "ELECTRONS:" ) );
  keywords.push_back( std :: string( "SPACE" ) );
  keywords.push_back( std :: string( "SPIN" ) );
  std :: vector< std :: string > line = iquads :: file_system :: return_split_strings_if_line_contains_all_keywords( keywords, output_path.absolute() );
  int na = iquads :: utility :: string_tool :: convert_string_to<int> ( line.at(3) );
  int nb = iquads :: utility :: string_tool :: convert_string_to<int> ( line.at(4) );

  std :: vector< std :: string > keywords_charge;
  keywords_charge.push_back( "NUCLEAR" );
  keywords_charge.push_back( "CHARGE:" );
  int nuclear_charge = iquads :: utility :: string_tool :: return_last_value_of_strings< int > ( iquads :: file_system :: return_split_strings_if_line_contains_all_keywords( keywords_charge, output_path.absolute() ) );

  return nuclear_charge - na - nb ;

}

double agent_type :: read_energy( correlation_tag_type correlation_tag, filepath_type output_path ) {

  typedef ExternalProgramReport :: EnergyReport :: energy_data_type energy_data_type;
  std :: vector< std :: string > correlation_name_aka_list = iquads :: electron_correlation :: return_level_name_aka_list( correlation_tag );
  for( size_t i = 0; i < correlation_name_aka_list.size(); i++ ) {
    correlation_name_aka_list[i].insert( 0, std :: string( "!" ) );
  }
  // I have to confess that this part is not that black box, because developer needs to know that molpro uses upper case
  // keywords to label correlation method, with "!". And the developers also need to know that the first element of the AKA list
  // is for molpro use.
  std :: vector< std :: string > keywords;
  keywords.push_back( correlation_name_aka_list[0] );
  keywords.push_back( std :: string( "Energy" ) );
  energy_data_type energy_data 
    = iquads :: utility :: string_tool :: return_last_value_of_strings< energy_data_type > ( iquads :: file_system :: return_split_strings_if_line_contains_all_keywords( keywords, output_path.absolute() ) );

  return energy_data;
}

agent_type :: energy_report_type 
agent_type :: collect_energy_data_from_output( correlation_tag_type correlation_tag, filepath_type output_path ) {

  // get the energy value to a correlation
  double energy_data = this->read_energy( correlation_tag, output_path );

  // also get the atom list and molecule name
  // molecule name is the filename, but without extension
  std :: string molecule_name = output_path.filename().name();

  // find out the molecule atom list
  iquads :: structure :: AtomList atom_list = this->read_coordinate( output_path );
  int charge = this->read_charge( output_path );
  // find out the molecule charge
  return ExternalProgramReport :: EnergyReport( std :: make_tuple( molecule_name, iquads :: structure :: Molecule( atom_list, charge ) ), energy_data, correlation_tag );

}; // end of function collect_energy_data_from_output()

} // end of namespace interface_to_third_party

} // end of namespace iquads
