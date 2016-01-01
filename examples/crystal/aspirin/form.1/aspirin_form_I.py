

from manybody_expansion import api
from manybody_expansion.api import fragment_generator_config
from os import getcwd;

current_directory = getcwd();
new_fg = fragment_generator_config.FragmentGeneratorConfig();

new_fg.lattice_name = "aspirin_form_I";
new_fg.natom = 84;
new_fg.xyz_file_name = "./aspirin_form_I.coord";
new_fg.lattice_constant_file_name = "./aspirin_form_I.const";
new_fg.input_name = "unknown";
new_fg.scratch_name = "unknown";
new_fg.output_name = "unknown";
new_fg.a = 3;
new_fg.b = 3;
new_fg.c = 3;
new_fg.basis_set = "6-31g";
new_fg.radius = 15.0;
new_fg.order = 2;
new_fg.mode = "sbatch";

new_fg.project_name = new_fg.lattice_name + '_' +  new_fg.correlation  + "_" + new_fg.basis_set    + "_" + new_fg.order_string()  + "_";
new_fg.project_name += str(new_fg.radius)  + "_" + str(new_fg.a) + "_" + str(new_fg.b) + "_" + str(new_fg.c) + "_" + new_fg.mode;

new_fg.cppsrcs = current_directory + "/" + new_fg.project_name + ".cpp";
new_fg.cppobjs = current_directory + "/" + new_fg.project_name + ".o";
new_fg.makefile_name = current_directory + "/" + "makefile_" + new_fg.project_name;

from copy import deepcopy

new_fg.driver_name = deepcopy(new_fg.cppsrcs);
new_fg.executable = current_directory + "/" + "fg_driver." + new_fg.project_name;

from manybody_expansion.api import fragment_generator;
fragment_generator.generate_binary( new_fg );
