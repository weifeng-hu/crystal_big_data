
from manybody_expansion import api
from manybody_expansion.api import fragment_generator_config

new_fg = fragment_generator_config.FragmentGeneratorConfig();

new_fg.natom = 84;
new_fg.xyz_file_name = "./aspirin_form_I.coord";
new_fg.lattice_constant_file_name = "./aspirin_form_I.const";
new_fg.driver_name = "./main.cpp";
new_fg.input_name = "unknown";
new_fg.scratch_name = "/scratch/wh288/";
new_fg.output_name = "unknown";
new_fg.a = 1;
new_fg.b = 1;
new_fg.c = 1;
new_fg.basis_set = "6-31g";

from manybody_expansion.api import fragment_generator;

fragment_generator.driver( new_fg );
