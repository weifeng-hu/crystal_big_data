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

# A lousy group submission controller

def fg_binary_generation( calc_config ):

  from manybody_expansion import api
  from manybody_expansion.api import fragment_generator_config
  new_fg = fragment_generator_config.FragmentGeneratorConfig();

  from os import getcwd;
  current_directory = getcwd();

  new_fg.lattice_name = calc_config.lattice_name;
  new_fg.natom = calc_config.natom;
  new_fg.xyz_file_name = calc_config.xyz_file_name;
  new_fg.lattice_constant_file_name = calc_config.lattice_constant_file_name;
  new_fg.a = calc_config.a;
  new_fg.b = calc_config.b;
  new_fg.c = calc_config.c;
  new_fg.basis_set = calc_config.basis_set;
  new_fg.radius = calc_config.radius;
  new_fg.order  = calc_config.order;
  new_fg.correlation = calc_config.correlation;
  new_fg.mode   = "sbatch";
  #new_fg.lattice_name = "aspirin_form_I";
  #new_fg.natom = 84;
  #new_fg.xyz_file_name = "./aspirin_form_I.coord";
  #new_fg.lattice_constant_file_name = "./aspirin_form_I.const";
  new_fg.input_name = "unknown";
  new_fg.scratch_name = "unknown";
  new_fg.output_name = "unknown";
  #new_fg.a = 3;
  #new_fg.b = 3;
  #new_fg.c = 3;
  #new_fg.basis_set = "6-31g";
  #new_fg.radius = 15.0;
  #new_fg.order = 2;
  #new_fg.mode = "sbatch";
  
  new_fg.project_name = new_fg.lattice_name + '_' +  new_fg.correlation  + "_" + new_fg.basis_set    + "_" + new_fg.order_string()  + "_";
  new_fg.project_name += str(new_fg.radius)  + "_" + str(new_fg.a) + "_" + str(new_fg.b) + "_" + str(new_fg.c) + "_" + new_fg.mode;
  new_fg.cppsrcs = current_directory + "/" + new_fg.project_name + ".cpp";
  new_fg.cppobjs = current_directory + "/" + new_fg.project_name + ".o";
  new_fg.makefile_name = current_directory + "/" + "makefile_" + new_fg.project_name;
  new_fg.executable = current_directory + "/" + "fg_driver." + new_fg.project_name;
  from copy import deepcopy
  new_fg.driver_name = deepcopy(new_fg.cppsrcs);
  
  from manybody_expansion.api import fragment_generator;
  fragment_generator.generate_binary( new_fg );

  from subprocess import call;
  echo_string = "echo '" + new_fg.executable + " > " + new_fg.project_name + ".out' >> fg_group_run.sh";
  call(  echo_string , shell=True );

  from subprocess import call;
  sbatch_submission_string = "echo 'cd " + new_fg.project_name + "; cd input/; sbatch group_submission.sh; cd ../../;'" + " >> group_sbatch.sh";
  call( sbatch_submission_string, shell=True );

  return 0;


def fg_data_collection( calc_config ):

  from manybody_expansion import api
  from manybody_expansion.api import fragment_generator_config
  new_fg = fragment_generator_config.FragmentGeneratorConfig();

  from os import getcwd;
  current_directory = getcwd();

  new_fg.lattice_name = calc_config.lattice_name;
  new_fg.natom = calc_config.natom;
  new_fg.xyz_file_name = calc_config.xyz_file_name;
  new_fg.lattice_constant_file_name = calc_config.lattice_constant_file_name;
  new_fg.a = calc_config.a;
  new_fg.b = calc_config.b;
  new_fg.c = calc_config.c;
  new_fg.basis_set = calc_config.basis_set;
  new_fg.radius = calc_config.radius;
  new_fg.correlation = calc_config.correlation;
  new_fg.order  = calc_config.order;
  new_fg.mode   = "harvest";

  new_fg.input_name = "unknown";
  new_fg.scratch_name = "unknown";
  new_fg.output_name = "unknown";
  
  new_fg.project_name = new_fg.lattice_name + '_' +  new_fg.correlation  + "_" + new_fg.basis_set    + "_" + new_fg.order_string()  + "_";
  new_fg.project_name += str(new_fg.radius)  + "_" + str(new_fg.a) + "_" + str(new_fg.b) + "_" + str(new_fg.c) + "_" + new_fg.mode;
  new_fg.cppsrcs = current_directory + "/" + new_fg.project_name + ".cpp";
  new_fg.cppobjs = current_directory + "/" + new_fg.project_name + ".o";
  new_fg.makefile_name = current_directory + "/" + "makefile_" + new_fg.project_name;
  new_fg.executable = current_directory + "/" + "fg_driver." + new_fg.project_name;
  from copy import deepcopy
  new_fg.driver_name = deepcopy(new_fg.cppsrcs);

  from manybody_expansion.api import fragment_generator;
  fragment_generator.generate_binary( new_fg );

  from subprocess import call;
  echo_string = "echo '" + new_fg.executable + " > " + new_fg.project_name + ".out' >> fc_group_run.sh" ;
  call( echo_string, shell=True );

  return 0;


def main_driver( gc ):

  from copy import deepcopy
  group_config = deepcopy(gc);

  # fg_code_generation
  for iconfig in range( 0, len(group_config) ):
    from copy import deepcopy;
    current_config = deepcopy( group_config[iconfig] );
    fg_binary_generation( current_config );

  # fc_code_generation
  for iconfig in range( 0, len(group_config) ):
    from copy import deepcopy;
    current_config = deepcopy( group_config[iconfig] );
    fg_data_collection( current_config );

  return 0;
