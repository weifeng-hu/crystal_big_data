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

def single_fg_binary_generation( calc_config ):

  from manybody_expansion import api
  from manybody_expansion.api import fragment_generator_config
  new_fg = fragment_generator_config.FragmentGeneratorConfig();

  new_fg.working_directory = calc_config.working_directory;
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
  new_fg.cppsrcs = new_fg.working_directory + "/" + new_fg.project_name + ".cpp";
  new_fg.cppobjs = new_fg.working_directory + "/" + new_fg.project_name + ".o";
  new_fg.makefile_name = new_fg.working_directory + "/" + "makefile_" + new_fg.project_name;
  new_fg.executable = new_fg.working_directory + "/" + "fg_driver." + new_fg.project_name;
  from copy import deepcopy
  new_fg.driver_name = deepcopy(new_fg.cppsrcs);
  
  from manybody_expansion.api import fragment_generator;
  fragment_generator.generate_binary( new_fg );

  from subprocess import call;
  outfile_name = new_fg.working_directory + "/" + new_fg.project_name + ".out";
  group_sh_name = new_fg.working_directory + "/" + "fg_group_run.sh";
  echo_string = "echo '" + new_fg.executable + " > " + outfile_name + "' >> " + group_sh_name ;
  call(  echo_string , shell=True );
  print_string = "echo '" + "echo ... done with " + new_fg.executable + "' >> " + group_sh_name ;
  call(  print_string , shell=True );

  from subprocess import call;
  group_sbatch_sh_name = new_fg.working_directory + "/group_sbatch.sh";
  sbatch_submission_string = "echo 'cd " + new_fg.project_name + "; cd input/; sh group_submission.sh; cd ../../;'" + " >> " + group_sbatch_sh_name;
  call( sbatch_submission_string, shell=True );

  return 0;

# fc stands for fragment collection, means data collection after calculations
def single_fc_binary_generation( calc_config ):

  from manybody_expansion import api
  from manybody_expansion.api import fragment_generator_config
  new_fg = fragment_generator_config.FragmentGeneratorConfig();

  new_fg.working_directory = calc_config.working_directory;
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
  new_fg.cppsrcs = new_fg.working_directory + "/" + new_fg.project_name + ".cpp";
  new_fg.cppobjs = new_fg.working_directory + "/" + new_fg.project_name + ".o";
  new_fg.makefile_name = new_fg.working_directory + "/" + "makefile_" + new_fg.project_name;
  new_fg.executable = new_fg.working_directory + "/" + "fg_driver." + new_fg.project_name;
  from copy import deepcopy;
  new_fg.driver_name = deepcopy(new_fg.cppsrcs);

  from manybody_expansion.api import fragment_generator;
  fragment_generator.generate_binary( new_fg );

  from subprocess import call;
  outfile_name = new_fg.working_directory + "/" + new_fg.project_name + ".out";
  group_sh_name = new_fg.working_directory + "/" + "fc_group_run.sh";
  echo_string = "echo '" + new_fg.executable + " > " + outfile_name + "' >> " + group_sh_name ;
  call( echo_string, shell=True );
  print_string = "echo '" + "echo ... done with " + new_fg.executable + "' >> " + group_sh_name ;
  call( print_string , shell=True );

  return 0;


def main_driver( gc ):

  from copy import deepcopy
  group_config = deepcopy(gc);

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

  # write a task group metadata in the directory
  print "Writing metadata file ... ";
  meta_filename = new_working_directory + "/" + "METADATA";
  f_meta = open( meta_filename, "wt" );
  f_meta.write( "METADATA\n" );
  f_meta.write( "datetime:   " + dir_name + "\n" );
  f_meta.write( "targets:\n" );
  f_meta.write( "lattice size\torder\tcutoff radius\tcorrelation\tbasis set\tmode\tnotes\n" )

  # fg_code_generation
  print "Generating fragment generators ..."; 
  for iconfig in range( 0, len(group_config) ):
    from copy import deepcopy;
    current_config = deepcopy( group_config[iconfig] );
    current_config.working_directory = new_working_directory;
    single_fg_binary_generation( current_config );
    lattice_size = str( current_config.a ) + "x" + str( current_config.b ) + "x" + str( current_config.c );
    f_meta.write( lattice_size + "\t\t" + str( current_config.order ) + "\t" + str( current_config.radius ) + "\t\t" + current_config.correlation + "\t\t" + current_config.basis_set + "\t\t" + "sbatch" + "\t" + current_config.notes + "\n"  );

  # fc_code_generation
  print "Generating fragment data collectors ..."; 
  for iconfig in range( 0, len(group_config) ):
    from copy import deepcopy;
    current_config = deepcopy( group_config[iconfig] );
    current_config.working_directory = new_working_directory;
    single_fc_binary_generation( current_config );
    lattice_size = str( current_config.a ) + "x" + str( current_config.b ) + "x" + str( current_config.c );
    f_meta.write( lattice_size + "\t\t" + str( current_config.order ) + "\t" + str( current_config.radius ) + "\t\t" + current_config.correlation + "\t\t" + current_config.basis_set + "\t\t" + "harvest" + "\t" + current_config.notes + "\n"  );

  f_meta.close();

  print "Done";

  return 0;
