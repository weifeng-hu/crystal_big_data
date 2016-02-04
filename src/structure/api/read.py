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

def read_unknown( input_file_name ):

  from decimal import Decimal;
  import unknown_unit_cell_config;

  new_unknown_unit_cell = unknown_unit_cell_config.UnknownUnitCellConfig();

  f_input = open( input_file_name, "rt" );
  natom_str = f_input.readline();
  natom = int( natom_str );

  new_lattice_vectors = [];
  for ivec in range( 0, 3 ):
    line = f_input.readline();
    words = line.split();
    x = Decimal( words[0] );
    y = Decimal( words[1] );
    z = Decimal( words[2] );
    vector = [ x, y, z ];
    new_lattice_vectors.append( vector );

  new_coordinates = [];
  for iatom in range( 0, natom ):
    line = f_input.readline();
    words = line.split();
    element = words[0];
    x = Decimal( words[1] );
    y = Decimal( words[2] );
    z = Decimal( words[3] );
    new_coordinate = [ element, x, y, z ];
    new_coordinates.append( new_coordinate );

  import copy;
  new_unknown_unit_cell.natom = copy.deepcopy( natom );
  new_unknown_unit_cell.lattice_vectors = copy.deepcopy( new_lattice_vectors );
  new_unknown_unit_cell.coordinates = copy.deepcopy( new_coordinates );

  f_input.close();

  return new_unknown_unit_cell;


def read_xyz( xyz_file_name ):

  from decimal import Decimal;

  from structure.api import nodes_config;
  new_nodes_info = nodes_config.NodesConfig();
  
  f_xyz = open( xyz_file_name , "rt" );
  nnode_str          = f_xyz.readline();
  natom_per_node_str = f_xyz.readline();

  nnode = int( nnode_str );
  natom_per_node = int( natom_per_node_str );

  natom = nnode * natom_per_node;

  import copy;
  new_nodes_info.nnode = copy.deepcopy( nnode );
  new_nodes_info.natom = copy.deepcopy( natom );
  new_nodes_info.natom_per_node = copy.deepcopy( natom_per_node );

  for inode in range( 0, nnode ):
    from structure.api import molecule_config;
    new_molecule = molecule_config.MoleculeConfig();

    import copy;
    new_molecule.natom = copy.deepcopy( natom_per_node );

    unit = f_xyz.readline();
    new_molecule.unit = copy.deepcopy( unit.rstrip('\r\n') );

    new_coordinates = [];
    for iatom_per_node in range( 0, natom_per_node ):
      line = f_xyz.readline();
      words = line.split();
      element = words[0];
      x = Decimal( words[1] );
      y = Decimal( words[2] );
      z = Decimal( words[3] );
      new_coordinate = [ element, x, y, z, new_molecule.unit ];
      new_coordinates.append( new_coordinate );

    import copy;
    new_molecule.coordinates = copy.deepcopy( new_coordinates );

    new_nodes_info.molecules.append( new_molecule );

  f_xyz.close();

  return new_nodes_info;



def read_lattice_constant( lattice_constant_file_name ):

  from structure.api import lattice_constant;
  from decimal import Decimal;

  new_constants = lattice_constant.LatticeConstant();
  word_a = "";
  word_b = "";
  word_c = "";
  word_alpha = "";
  word_beta  = "";
  word_gamma = "";

  f_lattice_constant = open( lattice_constant_file_name, "rt" );

  for line in f_lattice_constant:
    '''a_line = f_lattice_constant.readline();'''
    words = line.split();

    if len( words ) != 2 :
      break;

    if words[0] == 'a' :
      word_a = words[1];
    elif words[0] == 'b' :
      word_b = words[1];
    elif words[0] == 'c' :
      word_c = words[1];
    elif words[0] == 'alpha' :
      word_alpha = words[1];
    elif words[0] == 'beta' :
      word_beta  = words[1];
    elif words[0] == 'gamma' :
      word_gamma = words[1];
    else:
      print "unknown keyword ", words[0], " in lattice constant file\n";
      quit();

  f_lattice_constant.close();

  a = Decimal( word_a );
  b = Decimal( word_b );
  c = Decimal( word_c );
  alpha = Decimal( word_alpha );
  beta  = Decimal( word_beta  );
  gamma = Decimal( word_gamma );

  new_constants.a = a;
  new_constants.b = b;
  new_constants.c = c;
  new_constants.alpha = alpha;
  new_constants.beta  = beta;
  new_constants.gamma = gamma;

  return new_constants;



