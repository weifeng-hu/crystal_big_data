
from manybody_expansion import api
from manybody_expansion.api import fragment_generator_config

new_fg = fragment_generator_config.FragmentGeneratorConfig();

new_fg.natom = 84;
new_fg.xyz_file_name = "./aspirin_form_I.coord";
new_fg.lattice_constant_file_name = "./aspirin_form_I.const";
new_fg.driver_name = "./main.cpp";
new_fg.input_name = "unknown";
new_fg.scratch_name = "unknown";
new_fg.output_name = "unknown";
new_fg.project_name = "aspirin_form_1_hf_6-31g_md_15.0_3_3_3_sbatch"
new_fg.a = 3;
new_fg.b = 3;
new_fg.c = 3;
new_fg.basis_set = "6-31g";
new_fg.radius = 15.0;
new_fg.order = 2;
new_fg.mode = "harvest";

from manybody_expansion.api import fragment_generator;

fragment_generator.driver( new_fg );
