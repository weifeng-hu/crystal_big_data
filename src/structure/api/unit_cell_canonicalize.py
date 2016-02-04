##  
#  @file
#  @author Weifeng Hu
#  
#  @section LICENSE
#  
#  Copyright (C) 2013, 2014, 2015  Weifeng Hu
#  
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 2 of the License, or
#  (at your option) any later version.
#  
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#  
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>.
#  
#  @section DESCRIPTION
#  
#  
## 


def import_unknown_unit_cell( uc_config ):

  import copy;
  natom = copy.deepcopy( uc_config.unknown_unit_cell.natom );

  '''create a unknown unit_cell obj'''
  import unknown_unit_cell_config;
  new_unknown_unit_cell = unknown_unit_cell_config.UnknownUnitCellConfig();

  '''read the unknown unit cell including the lattice constants'''
  input_file_name = uc_config.input_file_name;
  from read import read_unknown;
  new_unknown_unit_cell = read_unknown( input_file_name );

  natom_imported = copy.deepcopy( new_unknown_unit_cell.natom );
  if natom_imported != natom:
    print "warning: import number of atom ", natom_imported, " not equal to pre-set natom", natom;

  return new_unknown_unit_cell;


def import_reference_unit_cell( uc_config ):

  natom = uc_config.reference_unit_cell.natom;

  ''' Create a unit_cell obj '''
  import unit_cell_config;
  new_unit_cell = unit_cell_config.UnitCellConfig();

  ''' Read molecules in a unit cell '''
  xyz_file_name = uc_config.reference_xyz_file_name;

  from read import read_xyz;
  new_unit_cell.nodes = read_xyz( xyz_file_name );

  import copy;
  natom_imported = copy.deepcopy( new_unit_cell.natom() );

  if natom_imported != natom:
    print "warning: import number of atom ", natom_imported, " not equal to pre-set natom", natom;

  ''' Read lattice constants '''
  lattice_constant_file_name = uc_config.reference_lattice_constants_file_name;
  from read import read_lattice_constant;
  new_unit_cell.lattice_constant = read_lattice_constant( lattice_constant_file_name );

  return new_unit_cell;


def generate_binary( uc_config ):

  '''write main.cpp'''
  import main_cpp;
  main_cpp.write( uc_config );

  '''write makefile'''
  import makefile;
  makefile.write( uc_config );

  '''compile'''
  print "Compiling...", uc_config.makefile_name;
  import subprocess;
  make_string = "make -s -f " + uc_config.makefile_name;
  subprocess.call( make_string, shell=True );

  return 0;


def perform( uc_config_input ):

  import unit_cell_canonicalize_config;
  uc_config = unit_cell_canonicalize_config.UnitCellCanonicalizeConfig();

  import copy;
  uc_config = copy.deepcopy( uc_config_input );

  '''import unknown unit cell and reference unit cell'''
  unknown_unit_cell   = import_unknown_unit_cell( uc_config );
  reference_unit_cell = import_reference_unit_cell( uc_config );

  uc_config.unknown_unit_cell   = copy.deepcopy( unknown_unit_cell );
  uc_config.reference_unit_cell = copy.deepcopy( reference_unit_cell );

  # create the working directory, by date, time
  from os import getcwd;
  current_directory = getcwd();
  new_working_directory = current_directory;

  # add date and time to dir name
  import datetime
  current_date_time = datetime.datetime.now();
  tuple_date_time   = current_date_time.timetuple();
  year  = tuple_date_time[0];
  month = tuple_date_time[1];
  day   = tuple_date_time[2];
  hour  = tuple_date_time[3];
  minute = tuple_date_time[4];
  second = tuple_date_time[5];

  dir_name = str(year) + "-" + str(month) + "-" + str(day) + "-" + str(hour) + "-" + str(minute) + "-" + str(second);
  new_working_directory += "/";
  new_working_directory += dir_name;
  mkdir_string = "mkdir -p " + new_working_directory;
  print "Creating working directory ", new_working_directory, " ... (anything generated will be placed in this directory)";
  from subprocess import call;
  call( mkdir_string, shell = True );

  uc_config.working_directory = new_working_directory;
  uc_config.project_name  = uc_config.lattice_name + "_structure_canonicalization";
  uc_config.cppsrcs       = uc_config.working_directory + "/" + uc_config.project_name + ".cpp" ;
  uc_config.cppobjs       = uc_config.working_directory + "/" + uc_config.project_name + ".o"; 
  uc_config.makefile_name = uc_config.working_directory + "/" + "makefile_" + uc_config.project_name;
  uc_config.executable    = uc_config.working_directory + "/" + "unit_cell_canonicalizer." + uc_config.lattice_name;
  uc_config.driver_name   = copy.deepcopy( uc_config.cppsrcs );
  uc_config.target_lattice_constants_file_name = uc_config.working_directory + "/" + uc_config.lattice_name + "_canonicalized.const";
  uc_config.target_xyz_file_name = uc_config.working_directory + "/" + uc_config.lattice_name + "_canonicalized.coord";
  uc_config.target_gjf_file_name = uc_config.working_directory + "/" + uc_config.lattice_name + "_canonicalized.gjf";

  metadata_path = new_working_directory + "/METADATA" ;
  f_metadata = open( metadata_path, "wt" );
  f_metadata.write( "METADATA\n" );
  f_metadata.write( "project:         " + uc_config.project_name + "\n" );
  f_metadata.write( "lattice name:    " + uc_config.lattice_name + "\n" );
  f_metadata.write( "executable:      " + uc_config.executable + "\n" );
  f_metadata.write( "output lattice parameter:  " + uc_config.target_lattice_constants_file_name + "\n" );
  f_metadata.write( "output cell coordinates:   " + uc_config.target_xyz_file_name + "\n" );
  f_metadata.write( "output gjf:      " + uc_config.target_gjf_file_name + "\n" );
  f_metadata.close();

  generate_binary( uc_config );

  ''' run '''
  print "Canonicalizing unit cell ...";
  import subprocess;
  run_string = uc_config.executable;
  subprocess.call( run_string, shell=True );

  return 0;

