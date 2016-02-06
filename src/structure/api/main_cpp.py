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


def write_include( uc_config, f_main_cpp ):

  f_main_cpp.write( "#include <array>\n" );
  f_main_cpp.write( "#include <iostream>\n" );
  f_main_cpp.write( "#include <fstream>\n" );
  f_main_cpp.write( "#include <string>\n" );
  f_main_cpp.write( "#include <geometrical_space/rotator.hpp>\n" );
  f_main_cpp.write( "#include <structure/atom_list.hpp>\n" );
  f_main_cpp.write( "#include <structure/molecule.hpp>\n" );
  f_main_cpp.write( "#include <structure/unit_cell_instant.hpp>\n" );
  f_main_cpp.write( "#include <structure/unit_cell_canonicalizer.hpp>" );

  return 0;


def write_typedef( uc_config, f_main_cpp ):

  f_main_cpp.write( "  typedef std :: array< double, 3 > threed_vector_type;\n" );
  f_main_cpp.write( "  typedef iquads :: structure :: AtomList atom_list_type;\n" );
  f_main_cpp.write( "  typedef iquads :: structure :: MolecularUnitCell unit_cell_type;\n" );

  return 0;


def write_reference_nodes( uc_config, f_main_cpp ):

  import copy;

  quotation_mark = '"';

  node_info = copy.deepcopy( uc_config.reference_unit_cell.nodes );
  nnode_per_unit_cell = node_info.nnode;

  f_main_cpp.write( "  std :: vector< iquads :: structure :: Molecule > node_list;\n" );
  f_main_cpp.write( "  node_list.resize(0);\n" );

  for inode in range( 0, nnode_per_unit_cell ):
    f_main_cpp.write( "  iquads :: structure :: AtomList " + "atom_list_" + str(inode) + " = {\n" );
    current_molecule = node_info.molecules[inode];
    coordinate_of_node = current_molecule.coordinates;
    natom = current_molecule.natom;
    for iatom in range ( 0, natom ):
      element = coordinate_of_node[iatom][0];
      x       = coordinate_of_node[iatom][1];
      y       = coordinate_of_node[iatom][2];
      z       = coordinate_of_node[iatom][3];
      unit    = coordinate_of_node[iatom][4];
      f_main_cpp.write( "              iquads :: structure :: Atom( std :: string(" + quotation_mark + str(element) + quotation_mark + "), " + str(x) + ", " + str(y) + ", " + str(z) + ", " + "std :: string( " + quotation_mark + unit + quotation_mark + " ) )," + "\n");
    f_main_cpp.write( "          };\n" );
    f_main_cpp.write( "  iquads :: structure :: Molecule " + "molecule_" + str(inode) + "( atom_list_" + str(inode) + ", 0" + "); \n" );
    f_main_cpp.write( "  node_list.push_back( molecule_" + str( inode ) + " );\n");
    f_main_cpp.write( "\n" );

  return 0;


def write_reference_lattice_constant( uc_config, f_main_cpp ):

  import copy;

  lattice_constant = copy.deepcopy( uc_config.reference_unit_cell.lattice_constant );
  a = lattice_constant.a;
  b = lattice_constant.b;
  c = lattice_constant.c;
  alpha = lattice_constant.alpha;
  beta  = lattice_constant.beta;
  gamma = lattice_constant.gamma;

  f_main_cpp.write( "  iquads :: structure :: LatticeParameter lattice_parameter_reference( " + str(a) + ", " + str(b) + ", " + str(c) + ", " + str(alpha) + ", " + str(beta) + ", " + str(gamma) + " );\n");

  return 0;


def write_reference_unit_cell( uc_config, f_main_cpp ):

  write_reference_nodes( uc_config, f_main_cpp );
  write_reference_lattice_constant( uc_config, f_main_cpp );
  f_main_cpp.write( "  iquads :: structure :: UnitCell< iquads :: structure :: Molecule > reference_unit_cell( node_list, lattice_parameter_reference );\n" );

  return 0;


def write_unknown_unit_cell( uc_config, f_main_cpp ):

  import copy;

  quotation_mark = '"';

  unknown_unit_cell = copy.deepcopy( uc_config.unknown_unit_cell );
  coordinates = copy.deepcopy( unknown_unit_cell.coordinates );
  lattice_vectors = copy.deepcopy( unknown_unit_cell.lattice_vectors );
  natom = unknown_unit_cell.natom;

  f_main_cpp.write( "  iquads :: structure :: AtomList new_atom_list = {\n" );

  for iatom in range ( 0, natom ):
    element = coordinates[iatom][0];
    x       = coordinates[iatom][1];
    y       = coordinates[iatom][2];
    z       = coordinates[iatom][3];
    unit    = "angstrom";
    f_main_cpp.write( "              iquads :: structure :: Atom( std :: string(" + quotation_mark + str(element) + quotation_mark + "), " + str(x) + ", " + str(y) + ", " + str(z) + ", " + "std :: string( " + quotation_mark + unit + quotation_mark + " ) )," + "\n");
  f_main_cpp.write( "        };\n" );

  f_main_cpp.write( "  threed_vector_type a_vec = { " + str( lattice_vectors[0][0] ) + ", " + str( lattice_vectors[0][1] ) + ", " + str( lattice_vectors[0][2] ) + " };\n" );
  f_main_cpp.write( "  threed_vector_type b_vec = { " + str( lattice_vectors[1][0] ) + ", " + str( lattice_vectors[1][1] ) + ", " + str( lattice_vectors[1][2] ) + " };\n" );
  f_main_cpp.write( "  threed_vector_type c_vec = { " + str( lattice_vectors[2][0] ) + ", " + str( lattice_vectors[2][1] ) + ", " + str( lattice_vectors[2][2] ) + " };\n" );

  f_main_cpp.write( "  std :: array< threed_vector_type, 3 > lattice_vectors = { a_vec, b_vec, c_vec };\n" );

  if uc_config.reference_unit_cell.nodes.nnode_per_unit_cell <= 4 :
    f_main_cpp.write( "  std :: array< std :: tuple< int, int >, 3 > ranges = { std :: make_tuple( -1, 1 ), std :: make_tuple( -1, 1 ), std :: make_tuple( -1, 1 ) );\n" );
  else :
    f_main_cpp.write( "  std :: array< std :: tuple< int, int >, 3 > ranges = { std :: make_tuple( -1, 1 ), std :: make_tuple( -1, 1 ), std :: make_tuple( -1, 1 ) );\n" );


  return 0;


def write_execution_part( uc_config, f_main_cpp ):

  quotation_mark = '"';

  f_main_cpp.write( "  iquads :: structure :: UnitCellCanonicalizer canonicalizer( reference_unit_cell, " + str( uc_config.bond_length_limit ) + " );\n" );
  f_main_cpp.write( "  unit_cell_type new_unit_cell = canonicalizer.canonicalize( new_atom_list, lattice_vectors );\n" );
  f_main_cpp.write( "\n" ); 
  f_main_cpp.write( "  std :: ofstream ofs_coord( " + quotation_mark + uc_config.target_xyz_file_name + quotation_mark + ", std :: ios :: out );\n" );
  f_main_cpp.write( "  ofs_coord << new_unit_cell.size() << std :: endl;\n" );
  f_main_cpp.write( "  ofs_coord << new_unit_cell[0].size() << std :: endl;\n" );
  f_main_cpp.write( "  for( size_t inode = 0; inode < new_unit_cell.size(); inode++ ) {\n" );
  f_main_cpp.write( "    ofs_coord << iquads :: structure :: geometry_unit :: return_unit_name( new_unit_cell[0].geometry_unit() ) << std :: endl;\n" );
  f_main_cpp.write( "    ofs_coord << new_unit_cell[inode];\n" );
  f_main_cpp.write( "  }\n" );
  f_main_cpp.write( "  ofs_coord.close();\n" );

  f_main_cpp.write( "\n" );

  f_main_cpp.write( "  std :: ofstream ofs_gjf( " + quotation_mark + uc_config.target_gjf_file_name + quotation_mark + ", std :: ios :: out );\n" );
  f_main_cpp.write( "  ofs_gjf << " + quotation_mark + "#HF/3-21G" + quotation_mark + " << std :: endl;\n" );
  f_main_cpp.write( "  ofs_gjf << std :: endl;\n" );
  f_main_cpp.write( "  ofs_gjf << " + quotation_mark + "title card" + quotation_mark + " << std :: endl;\n" );
  f_main_cpp.write( "  ofs_gjf << std :: endl;\n" );
  f_main_cpp.write( "  ofs_gjf << " + quotation_mark + "0  1" + quotation_mark + " << std :: endl;\n" );
  f_main_cpp.write( "  for( size_t inode = 0; inode < new_unit_cell.size(); inode++ ) {\n" );
  f_main_cpp.write( "    ofs_gjf << new_unit_cell[inode];\n" );
  f_main_cpp.write( "  }\n" );
  f_main_cpp.write( "  ofs_gjf.close();\n" );

  f_main_cpp.write( "\n" );


  f_main_cpp.write( "  using iquads :: geometrical_space :: threed_space :: pi;\n" );
  f_main_cpp.write( "  std :: ofstream ofs_const( " + quotation_mark + uc_config.target_lattice_constants_file_name + quotation_mark + ", std :: ios :: out ); \n" );
  f_main_cpp.write( "  ofs_const << " + quotation_mark + "a\t" + quotation_mark + " << std :: setw(12) << std :: setprecision(8) << new_unit_cell.lattice_parameter().a() << std :: endl;\n" );
  f_main_cpp.write( "  ofs_const << " + quotation_mark + "b\t" + quotation_mark + " << std :: setw(12) << std :: setprecision(8) << new_unit_cell.lattice_parameter().b() << std :: endl;\n" );
  f_main_cpp.write( "  ofs_const << " + quotation_mark + "c\t" + quotation_mark + " << std :: setw(12) << std :: setprecision(8) << new_unit_cell.lattice_parameter().c() << std :: endl;\n" );
  f_main_cpp.write( "  ofs_const << " + quotation_mark + "alpha\t" + quotation_mark + " << std :: setw(12) << std :: setprecision(8) << 180.0e0 * new_unit_cell.lattice_parameter().alpha()/pi << std :: endl;\n" );
  f_main_cpp.write( "  ofs_const << " + quotation_mark + "beta\t"  + quotation_mark + " << std :: setw(12) << std :: setprecision(8) <<  180.0e0 * new_unit_cell.lattice_parameter().beta()/pi << std :: endl;\n" );
  f_main_cpp.write( "  ofs_const << " + quotation_mark + "gamma\t" + quotation_mark + " << std :: setw(12) << std :: setprecision(8) << 180.0e0 * new_unit_cell.lattice_parameter().gamma()/pi << std :: endl;\n" );

  return 0;


def write( uc_config ):

  driver_name = uc_config.driver_name;
  f_main_cpp = open( driver_name, "wt" );

  write_include( uc_config, f_main_cpp );
  f_main_cpp.write("\n");

  f_main_cpp.write( "int main( int argc, char* argv[] ) { \n" );
  f_main_cpp.write( "\n" );

  write_typedef( uc_config, f_main_cpp );
  f_main_cpp.write("\n");

  write_reference_unit_cell( uc_config, f_main_cpp );
  write_unknown_unit_cell( uc_config, f_main_cpp );
  write_execution_part( uc_config, f_main_cpp );

  f_main_cpp.write( "  return 0;\n");
  f_main_cpp.write( "\n" );
  f_main_cpp.write( "}\n" );

  f_main_cpp.close();

  return 0;

