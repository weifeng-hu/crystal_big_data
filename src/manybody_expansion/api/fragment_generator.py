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


def import_unit_cell( fg_config ):

  natom = fg_config.natom;

  ''' Create a unit_cell obj '''
  import unit_cell_config;
  new_unit_cell = unit_cell_config.UnitCellConfig();

  ''' Read molecules in a unit cell '''
  xyz_file_name = fg_config.xyz_file_name;
  from read import read_xyz;
  new_unit_cell.nodes = read_xyz( xyz_file_name );
  import copy;
  natom_imported = copy.deepcopy( new_unit_cell.natom() );

  if natom_imported != natom:
    print "warning: import number of atom ", natom_imported, " not equal to pre-set natom", natom;

  ''' Read lattice constants ''' 
  lattice_constant_file_name = fg_config.lattice_constant_file_name;
  from read import read_lattice_constant;
  new_unit_cell.lattice_constant = read_lattice_constant( lattice_constant_file_name );
 
  return new_unit_cell;


def driver( fg_config_input ):

  ''' Initialize the fragment generator config '''
  import fragment_generator_config;
  fg_config = fragment_generator_config.FragmentGeneratorConfig();

  ''' fg_config_input is something user-defined, unless the coordinates '''
  import copy;
  fg_config = copy.deepcopy( fg_config_input );

  ''' Impport a unit_cell obj '''
  new_unit_cell = import_unit_cell( fg_config );

  ''' Set the main config, the unit_cell info '''
  fg_config.unit_cell_info = copy.deepcopy( new_unit_cell );

  import main_cpp;
  main_cpp.write( fg_config );

  import makefile;
  makefile.write( fg_config );

  print "Compiling...\n";
  import subprocess;
  subprocess.call( "make" ); 

  return 0;
