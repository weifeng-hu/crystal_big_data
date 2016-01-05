
group_config = [];
lattice_name = "aspirin_form_I";
xyz_file_name = "./aspirin_form_I.coord";
lattice_constant_file_name = "./aspirin_form_I.const";
natom = 84;
correlation = "hf";
basis_set = "6-31g";

from manybody_expansion.api.calculation_config import new_calc_config;
from copy import deepcopy;

#new_calc_config( lattice_name, xyz_file_name, lattice_constant_file_name, natom, a, b, c, order, basis_set, radius );
group_config.append(deepcopy(new_calc_config(lattice_name,xyz_file_name,lattice_constant_file_name,natom,3, 3, 3, 3, basis_set,correlation,9.0)));
#group_config.append(deepcopy(new_calc_config(lattice_name,xyz_file_name,lattice_constant_file_name,natom,3, 3, 3, 2, basis_set,correlation,12.0)));
#group_config.append(deepcopy(new_calc_config(lattice_name,xyz_file_name,lattice_constant_file_name,natom,3, 3, 3, 2, basis_set,correlation,15.0)));
#group_config.append(deepcopy(new_calc_config(lattice_name,xyz_file_name,lattice_constant_file_name,natom,3, 3, 3, 2, basis_set,correlation,18.0)));
#group_config.append(deepcopy(new_calc_config(lattice_name,xyz_file_name,lattice_constant_file_name,natom,4, 4, 4, 2, basis_set,correlation,9.0)));
#group_config.append(deepcopy(new_calc_config(lattice_name,xyz_file_name,lattice_constant_file_name,natom,4, 4, 4, 2, basis_set,correlation,12.0)));
#group_config.append(deepcopy(new_calc_config(lattice_name,xyz_file_name,lattice_constant_file_name,natom,4, 4, 4, 2, basis_set,correlation,15.0)));
#group_config.append(deepcopy(new_calc_config(lattice_name,xyz_file_name,lattice_constant_file_name,natom,4, 4, 4, 2, basis_set,correlation,18.0)));
#group_config.append(deepcopy(new_calc_config(lattice_name,xyz_file_name,lattice_constant_file_name,natom,5, 5, 5, 2, basis_set,correlation,9.0)));
#group_config.append(deepcopy(new_calc_config(lattice_name,xyz_file_name,lattice_constant_file_name,natom,5, 5, 5, 2, basis_set,correlation,12.0)));
#group_config.append(deepcopy(new_calc_config(lattice_name,xyz_file_name,lattice_constant_file_name,natom,5, 5, 5, 2, basis_set,correlation,15.0)));
#group_config.append(deepcopy(new_calc_config(lattice_name,xyz_file_name,lattice_constant_file_name,natom,5, 5, 5, 4, basis_set,correlation,18.0)));

from manybody_expansion.api.group import group_generator;
dir_name = group_generator( group_config ); 

from manybody_expansion.api.remote_config import RemoteConfig;
remote_config = RemoteConfig();
remote_config.remote = "della.princeton.edu";
remote_config.user   = "weifeng";
remote_config.dir_name = dir_name;
remote_config.remote_directory = "/scratch/gpfs/weifeng/aspirin/";
remote_config.push_to_remote = False;
remote_config.pull_from_remote = False;

from manybody_expansion.api.group import push_to_remote;
from manybody_expansion.api.group import pull_from_remote;

push_to_remote( remote_config );
pull_from_remote( remote_config );
