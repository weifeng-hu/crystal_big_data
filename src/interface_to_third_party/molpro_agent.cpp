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
#include <electron_correlation/correlation_level.hpp>
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
    size_t spin  = request.spin() == -1 ? request.spin() : config_pointer_list[0]->check_spin( request.spin(), nelec );
    config_pointer_list[0] -> set_hartree_fock_config() = this_config_type :: HartreeFockConfig( nelec, request.sym(), spin );
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

agent_type :: dry_run_info_type 
agent_type :: write_dry_run_script( filepath_type input_path ) {

  try {
    filepath_type :: directory_type input_absolute_dir( input_path.directory().absolute() );
    if( input_absolute_dir.exists() == false ) { input_absolute_dir.create(); }
    {
      filepath_type :: filename_type dry_run_single_script_filename( input_path.filename().name(),  std :: string( ".sh" ) );
      filepath_type dry_run_single_script_filepath( input_absolute_dir, dry_run_single_script_filename );

      std :: ofstream ofs_single( dry_run_single_script_filepath.absolute().c_str(), std :: ios :: out );
      if( ofs_single.good() == false ) { throw dry_run_single_script_filepath.absolute(); }
      ofs_single << this->program_path_ + "/" + this->program_name_ + " " + input_path.absolute();
      ofs_single.close();

      filepath_type :: filename_type dry_run_group_submission_filename( std :: string( "group_submission" ), std :: string( ".sh" ) );
      filepath_type dry_run_group_submission_script_filepath( input_absolute_dir, dry_run_group_submission_filename );

      std :: ofstream ofs_group( dry_run_group_submission_script_filepath.absolute().c_str(), std :: ios_base :: app | std :: ios_base :: out );
      if( ofs_group.good() == false ) { throw dry_run_group_submission_script_filepath.absolute(); }
      ofs_group << this->program_path_ + "/" + this->program_name_ + " " + input_path.absolute() << std :: endl;
      ofs_group.close();

      dry_run_info_type dry_run_info( this->program_name_,
                                      input_path.directory().absolute(),
                                      input_path.filename().value(),
                                      std :: string( "not set" ),
                                      std :: string( "not set" ),
                                      std :: string( "not set" ),
                                      dry_run_single_script_filepath.absolute(),
                                      dry_run_group_submission_script_filepath.absolute() );
      return dry_run_info;
    }
  } catch ( filepath_type :: filename_type :: value_type script_file_name ) {
    std :: cout << "error in opening [ " << script_file_name << " ]" << std :: endl;
    abort();
  }

} // end of function write_dry_run_script()

agent_type :: pbs_run_info_type 
agent_type :: write_pbs_run_script( filepath_type input_path ) {

  try {
    filepath_type :: directory_type input_absolute_dir( input_path.directory().absolute() );
    if( input_absolute_dir.exists() == false ) { input_absolute_dir.create(); }
    {
      filepath_type :: filename_type pbs_run_single_script_filename( input_path.filename().name(),  std :: string( ".sh" ) );
      filepath_type pbs_run_single_script_filepath( input_absolute_dir, pbs_run_single_script_filename );

      std :: ofstream ofs_single( pbs_run_single_script_filepath.absolute().c_str(), std :: ios :: out );
      if( ofs_single.good() == false ) { throw pbs_run_single_script_filepath.absolute(); }
      ofs_single << this->program_path_ + "/" + this->program_name_ + " " + input_path.absolute();
      ofs_single.close();

      filepath_type :: filename_type pbs_run_group_submission_filename( std :: string( "group_submission" ), std :: string( ".sh" ) );
      filepath_type pbs_run_group_submission_script_filepath( input_absolute_dir, pbs_run_group_submission_filename );

      std :: ofstream ofs_group( pbs_run_group_submission_script_filepath.absolute().c_str(), std :: ios_base :: app | std :: ios_base :: out );
      if( ofs_group.good() == false ) { throw pbs_run_group_submission_script_filepath.absolute(); }
      ofs_group << this->program_path_ + "/" + this->program_name_ + " " + input_path.absolute() << std :: endl;
      ofs_group.close();

      pbs_run_info_type pbs_run_info( this->program_name_,
                                      input_path.directory().absolute(),
                                      input_path.filename().value(),
                                      std :: string( "not set" ),
                                      std :: string( "not set" ),
                                      std :: string( "not set" ),
                                      pbs_run_single_script_filepath.absolute(),
                                      pbs_run_group_submission_script_filepath.absolute() );
      return pbs_run_info;
    }
  } catch ( filepath_type :: filename_type :: value_type script_file_name ) {
    std :: cout << "error in opening [ " << script_file_name << " ]" << std :: endl;
    abort();
  }

} // end of function write_pbs_run_script()

agent_type :: sbatch_run_info_type 
agent_type :: write_sbatch_run_script( filepath_type input_path ) {

  // Instead of implementing a script structure like local run: individual scripts + a group submission as a piling up of individual 
  // scripts,
  // the sbatch script features individual scripts which are standalone sbatch scripts, including a completed setup of sbatch environment 
  // settings, and a group submission script, which is not a piling up of individual scripts(run commands) but a dependency list submission.
  // Nowadays job scheduling systems usually have short job time allowance, e.g., 24hr, so requesting a long time for a group of jobs is 
  // less favorable.

  try {
    filepath_type :: directory_type input_absolute_dir( input_path.directory().absolute() );
    if( input_absolute_dir.exists() == false ) { input_absolute_dir.create(); }
    {
      filepath_type :: filename_type sbatch_run_single_script_filename( input_path.filename().name(),  std :: string( ".sh" ) );
      filepath_type sbatch_run_single_script_filepath( input_absolute_dir, sbatch_run_single_script_filename );

      std :: ofstream ofs_single( sbatch_run_single_script_filepath.absolute().c_str(), std :: ios :: out );
      if( ofs_single.good() == false ) { throw sbatch_run_single_script_filepath.absolute(); }

      int num_node = 1;
      int num_procs_per_node = 1;
      int memory = 8000 * num_procs_per_node;
      std :: string runtime = "12:00:00";

      ofs_single << "#!/bin/sh"                                        << std :: endl;
      // for molpro we should request 1 machine and 1 core
      ofs_single << "#SBATCH -N " << num_node                          << std :: endl;
      ofs_single << "#SBATCH --ntasks-per-node=" << num_procs_per_node << std :: endl;
      ofs_single << "#SBATCH --mem=" << memory                         << std :: endl;
      ofs_single << "#SBATCH -t " << runtime                           << std :: endl;
      ofs_single << std :: endl;

      ofs_single << "mkdir -p ../output/" << std :: endl;
      // On servers, program_name_ is assumed to be in $PATH, so we omit the program_path_ here;
      // Also, molpro doesn't need output name, also we don't use absolute path of input file, just assuming that we are in the current dir
      ofs_single << this->program_name_ + " ./" + input_path.filename().value()        << std :: endl;
      ofs_single << "cp ./" << input_path.filename().name() << ".out" << " ../output/" << std :: endl;
      ofs_single << "cp ./" << input_path.filename().name() << ".xml" << " ../output/" << std :: endl;
      ofs_single.close();

      filepath_type :: filename_type sbatch_run_group_submission_filename( std :: string( "group_submission" ), std :: string( ".sh" ) );
      filepath_type sbatch_run_group_submission_script_filepath( input_absolute_dir, sbatch_run_group_submission_filename );

      const bool group_submission_script_already_created = sbatch_run_group_submission_script_filepath.exists();

      std :: ofstream ofs_group( sbatch_run_group_submission_script_filepath.absolute().c_str(), std :: ios_base :: app | std :: ios_base :: out );
      if( ofs_group.good() == false ) { throw sbatch_run_group_submission_script_filepath.absolute(); }
      // write a sbatch dependency list
      if( group_submission_script_already_created == false ) {
        // if the first time, then no dependency
        ofs_group << "new_jobid=`sbatch ./" << sbatch_run_single_script_filename.value() << " | awk '{ print $NF }'` " << std :: endl;
        ofs_group << "echo $new_jobid not dependent" << std :: endl;
        ofs_group << "old_jobid=$new_jobid" << std :: endl;
        ofs_group << std :: endl;
      }
      else {
        ofs_group << "new_jobid=`sbatch --dependency=afterany:$old_jobid ./" << sbatch_run_single_script_filename.value() << " | awk '{ print $NF }'` " 
                  << std :: endl;
        ofs_group << "echo $new_jobid is dependent on $old_jobid" << std :: endl;
        ofs_group << "old_jobid=$new_jobid" << std :: endl;
        ofs_group << std :: endl; 
      }
      ofs_group.close();

      sbatch_run_info_type sbatch_run_info( this->program_name_,
                                      input_path.directory().absolute(),
                                      input_path.filename().value(),
                                      std :: string( "not set" ),
                                      std :: string( "not set" ),
                                      std :: string( "not set" ),
                                      sbatch_run_single_script_filepath.absolute(),
                                      sbatch_run_group_submission_script_filepath.absolute(),
                                      num_node, num_procs_per_node, memory, runtime );
      return sbatch_run_info;
    }
  } catch ( filepath_type :: filename_type :: value_type script_file_name ) {
    std :: cout << "error in opening [ " << script_file_name << " ]" << std :: endl;
    abort();
  }

} // end of function write_sbatch_run_script

agent_type :: energy_report_type 
agent_type :: return_energy_null_info() {

  return energy_report_type( std :: make_tuple( std :: string( "" ), iquads :: structure :: Molecule() ), 0.0e0, iquads :: electron_correlation :: UNKNOWN );

} // end of function return_energy_basic_info

std :: tuple< agent_type :: filepath_type, bool > 
agent_type :: locate_energy_input( base_config_ptr base_config_pointer ) {

  directory_type input_dir( base_config_pointer->input_dir() );
  filepath_type :: filename_type input_name( base_config_pointer->molecule_name(), base_config_pointer->file_extension() );
  filepath_type input_filepath( input_dir, input_name );

  return std :: make_tuple( input_filepath, input_filepath.exists() );

} // end of function locate_energy_input()

std :: tuple < agent_type :: filepath_type, bool >
agent_type :: locate_energy_output( base_config_ptr base_config_pointer ) {

  directory_type output_dir( base_config_pointer->output_dir() );
  filepath_type :: filename_type output_name( base_config_pointer->molecule_name(), std :: string( ".out" ) );
  filepath_type output_filepath( output_dir, output_name );

  return std :: make_tuple( output_filepath, output_filepath.exists() );

} // end of function locate_energy_output()

agent_type :: harvest_run_info_type 
agent_type :: return_previous_run_status( std :: tuple< filepath_type, bool > input_status, std :: tuple< filepath_type, bool > output_status ) {

  const bool input_is_found = std :: get<1> ( input_status );
  const bool output_is_found = std :: get<1> ( output_status );

  bool input_matches_output = false;
  if( input_is_found && output_is_found ) {
    atom_list_type atom_list_input  = this->read_atom_list_from_input( std :: get<0>( input_status ) );
    atom_list_type atom_list_output = this->read_atom_list( std :: get<0> ( output_status ) );
    if( atom_list_input.size() != atom_list_output.size() ) { input_matches_output = false; }
    for( size_t i = 0; i < atom_list_input.size(); i++ ) {
      if( atom_list_input[i] == atom_list_output[i] ) {
        input_matches_output = true;
      } else {
        input_matches_output = false;
        break;
      }
    }
  }

  return harvest_run_info_type( this->program_name_,
                                std :: get<0> ( input_status ).directory().absolute(),
                                std :: get<0> ( input_status ).filename().value(),
                                std :: string( "not set" ),
                                std :: get<0> ( output_status ).directory().absolute(),
                                std :: get<0> ( output_status ).filename().value(),
                                input_matches_output,
                                input_is_found,
                                output_is_found );

} // end of function return_previous_run_status()

agent_type :: atom_list_type 
agent_type :: read_atom_list_from_input( filepath_type input_path ) {

  iquads :: structure :: AtomList retval;
  retval.resize(0);

  std :: string lineA( "geometry={" );
  std :: string lineB( "}" );
  std :: vector< std :: string > coordinate_block = iquads :: file_system :: read_block_between_lineA_and_lineB( lineA, lineB, input_path.absolute() );

  for( size_t i = 0; i < coordinate_block.size(); i++ ) {
    std :: string line = coordinate_block[i];
    std :: vector< std :: string > vector_of_string;
    boost :: trim( line );
    boost :: split( vector_of_string, line, boost :: is_any_of( " " ), boost :: token_compress_on );
    retval.push_back ( iquads :: structure :: Atom( vector_of_string.at(0), 
                                                    iquads :: utility :: string_tool :: convert_string_to<double> ( vector_of_string.at(1) ), 
                                                    iquads :: utility :: string_tool :: convert_string_to<double> ( vector_of_string.at(2) ), 
                                                    iquads :: utility :: string_tool :: convert_string_to<double> ( vector_of_string.at(3) ), 
                                                    std :: string( "bohr" ) ) );
  }

  return retval;

} // end of function read_atom_list()

agent_type :: atom_list_type 
agent_type :: read_atom_list( filepath_type output_path ) {

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

} // end of function read_atom_list()

std :: tuple< agent_type :: number_value_type, agent_type :: number_value_type > 
agent_type :: read_na_nb( filepath_type output_path ) {

  std :: vector< std :: string > keywords;
  keywords.push_back( std :: string( "NUMBER" ) );
  keywords.push_back( std :: string( "OF" ) );
  keywords.push_back( std :: string( "ELECTRONS:" ) );
  keywords.push_back( std :: string( "SPACE" ) );
  keywords.push_back( std :: string( "SPIN" ) );
  std :: vector< std :: string > line = iquads :: file_system :: return_split_strings_if_line_contains_all_keywords( keywords, output_path.absolute() );
  agent_type :: number_value_type na = iquads :: utility :: string_tool :: convert_string_to< agent_type :: number_value_type > ( line.at(3) );
  agent_type :: number_value_type nb = iquads :: utility :: string_tool :: convert_string_to< agent_type :: number_value_type > ( line.at(4) );

  return make_tuple( na, nb );

}

agent_type :: number_value_type 
agent_type :: read_nelec( filepath_type output_path ) {

  std :: tuple<int, int> na_nb = this->read_na_nb( output_path );
  return std :: get<0> ( na_nb ) + std :: get<1> ( na_nb );

}

agent_type :: spin_value_type
agent_type :: read_spin( filepath_type output_path ) {

  std :: tuple<int, int> na_nb = this->read_na_nb( output_path );
  return ( agent_type :: spin_value_type ) ( ( std :: get<0> ( na_nb ) - std :: get<1> ( na_nb ) ) / 2.0e0 );

}

agent_type :: charge_value_type 
agent_type :: read_nuclear_charge( filepath_type output_path ) {

  std :: vector< std :: string > keywords_charge;
  keywords_charge.push_back( "NUCLEAR" );
  keywords_charge.push_back( "CHARGE:" );
  int nuclear_charge = iquads :: utility :: string_tool :: return_last_value_of_strings< int > ( iquads :: file_system :: return_split_strings_if_line_contains_all_keywords( keywords_charge, output_path.absolute() ) );

  return nuclear_charge;

}

agent_type :: energy_value_type 
agent_type :: read_energy( correlation_tag_type correlation_tag, filepath_type output_path ) {

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
  std :: string molecule_name = output_path.filename().name();
  //std :: cout << "\t" << std :: setw(16) << std :: setprecision(12) << energy_data;

  // also get the atom list and molecule name
  // molecule name is the filename, but without extension

  // find out the molecule atom list
  agent_type :: atom_list_type atom_list = this->read_atom_list( output_path );
  // find out the molecule charge
  int charge = this->read_nuclear_charge( output_path ) - this->read_nelec( output_path );

  return ExternalProgramReport :: EnergyReport( std :: make_tuple( molecule_name, iquads :: structure :: Molecule( atom_list, charge ) ), energy_data, correlation_tag );

}; // end of function collect_energy_data_from_output()

} // end of namespace interface_to_third_party

} // end of namespace iquads
