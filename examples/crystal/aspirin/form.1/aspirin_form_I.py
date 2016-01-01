

def new_calc_config( lattice_name, xyz_file_name, lattice_constant_file_name, natom, a, b, c, order, basis_set, radius ):
  from manybody_expansion.api.calculation_config import CalculationConfig;
  new_cg = CalculationConfig();

  new_cg.lattice_name = lattice_name;
  new_cg.xyz_file_name = xyz_file_name;
  new_cg.lattice_constant_file_name = lattice_constant_file_name;
  new_cg.natom = natom;
  new_cg.a = a;
  new_cg.b = b;
  new_cg.c = c;
  new_cg.order = order;
  new_cg.basis_set = basis_set;
  new_cg.radius = radius;
  return new_cg; 


group_config = [];
lattice_name = "aspirin_form_I";
xyz_file_name = "./aspirin_form_I.coord";
lattice_constant_file_name = "./aspirin_form_I.const";
natom = 84;
basis_set = "6-31g";

from copy import deepcopy;

#new_calc_config( lattice_name, xyz_file_name, lattice_constant_file_name, natom, a, b, c, order, basis_set, radius );
group_config.append(deepcopy(new_calc_config(lattice_name, xyz_file_name, lattice_constant_file_name, natom, 2, 2, 2, 2, basis_set, 7.0)));
group_config.append(deepcopy(new_calc_config(lattice_name, xyz_file_name, lattice_constant_file_name, natom, 2, 2, 2, 2, basis_set, 8.0)));

from manybody_expansion.api.group import main_driver;
main_driver( group_config ); 
