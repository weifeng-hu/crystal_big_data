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


import copy;


def write_include( fg_config, f_main_cpp ):

  f_main_cpp.write( "#include <vector>\n" );
  f_main_cpp.write( "#include <tuple>\n" );
  f_main_cpp.write( "#include <string>\n" );
  f_main_cpp.write( "#include <structure/atom_list.hpp>\n" );
  f_main_cpp.write( "#include <structure/molecule.hpp>\n" );
  f_main_cpp.write( "#include <structure/unit_cell_template.hpp>\n" );
  f_main_cpp.write( "#include <structure/lattice_parameter.hpp>\n" );
  f_main_cpp.write( "#include <structure/lattice_template.hpp>\n" );
  f_main_cpp.write( "#include <structure/bulk_template.hpp>\n" );
  f_main_cpp.write( "#include <manybody_expansion/request.hpp>\n" );
  f_main_cpp.write( "#include <manybody_expansion/report.hpp>\n" );
  f_main_cpp.write( "#include <manybody_expansion/agent.hpp>\n" );

  return 0;


def write_nodes( fg_config, f_main_cpp ):

  quotation_mark = '"';

  node_info = copy.deepcopy( fg_config.nodes() );
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


def write_lattice_constant( fg_config, f_main_cpp ):

  lattice_constant = copy.deepcopy( fg_config.lattice_constant() );
  a = lattice_constant.a;
  b = lattice_constant.b;
  c = lattice_constant.c;
  alpha = lattice_constant.alpha;
  beta  = lattice_constant.beta;
  gamma = lattice_constant.gamma;

  f_main_cpp.write( "  iquads :: structure :: LatticeParameter lattice_parameter( " + str(a) + ", " + str(b) + ", " + str(c) + ", " + str(alpha) + ", " + str(beta) + ", " + str(gamma) + " );\n");
 
  return 0;


def write_unit_cell( fg_config, f_main_cpp ):

  a = fg_config.a;
  b = fg_config.b;
  c = fg_config.c;

  write_nodes( fg_config, f_main_cpp );
  write_lattice_constant( fg_config, f_main_cpp );

  f_main_cpp.write( "  iquads :: structure :: UnitCell< iquads :: structure :: Molecule > unit_cell( node_list, lattice_parameter );\n" );
  f_main_cpp.write( "  iquads :: structure :: Lattice < iquads :: structure :: UnitCell< iquads :: structure :: Molecule > > lattice( unit_cell, " + str(a) + ", " + str(b) + ", " + str(c) + " );\n" );

  f_main_cpp.write( "  using std :: get;\n" );
  
  f_main_cpp.write( '  std :: cout << "edges of the lattice:" << std :: endl\n' );
  f_main_cpp.write( '  std :: cout << " [ " << get<0> ( get<0> ( lattice.edges() ) ) << ", " << get<1> ( get<0> ( lattice.edges() ) ) << " ] " << std :: endl;\n' );
  f_main_cpp.write( '  std :: cout << " [ " << get<0> ( get<1> ( lattice.edges() ) ) << ", " << get<1> ( get<1> ( lattice.edges() ) ) << " ] " << std :: endl;\n' );
  f_main_cpp.write( '  std :: cout << " [ " << get<0> ( get<2> ( lattice.edges() ) ) << ", " << get<1> ( get<2> ( lattice.edges() ) ) << " ] " << std :: endl;\n' );
  f_main_cpp.write( "  iquads :: structure :: Bulk< iquads :: structure :: Molecule > bulk;\n" );
  f_main_cpp.write( "\n" );

  return 0;


def write_execution_part( fg_config, f_main_cpp ):

  quotation_mark = '"';

  lattice_name  = quotation_mark + fg_config.lattice_name + quotation_mark;
  order         = fg_config.order;
  correlation   = quotation_mark + fg_config.correlation + quotation_mark;
  program       = quotation_mark + fg_config.program + quotation_mark;
  mode          = quotation_mark + fg_config.mode + quotation_mark;
  project_name  = quotation_mark + fg_config.project_name + quotation_mark;
  radius        = fg_config.radius;
  input_name    = quotation_mark + fg_config.input_name + quotation_mark;
  scratch_name  = quotation_mark + fg_config.scratch_name + quotation_mark;
  output_name   = quotation_mark + fg_config.output_name + quotation_mark;
  basis_set     = quotation_mark + fg_config.basis_set + quotation_mark;

  f_main_cpp.write( "  iquads :: manybody_expansion :: Agent agent;\n" );
  f_main_cpp.write( "  iquads :: manybody_expansion :: Report report = agent.accept_request_and_process\n" );
  f_main_cpp.write( "     ( iquads :: manybody_expansion :: Request ( std :: make_tuple ( " + str(lattice_name) + ", lattice ), \n" );
  f_main_cpp.write( "                                                 std :: make_tuple ( " + quotation_mark + "unknown_bulk" + quotation_mark + ", bulk ),\n" );
  f_main_cpp.write( "                                                 " + str( order ) + ", " + str( correlation ) + ", " + str( program ) + ", " + str( basis_set ) + ",\n"  );
  f_main_cpp.write( "                                                 " + str(mode) + ",\n" ); 
  f_main_cpp.write( "                                                 " + str(project_name) + ",\n" );
  f_main_cpp.write( "                                                 " + str(input_name) + ", " + str(scratch_name) + ", " + str( output_name ) + ",\n " );
  f_main_cpp.write( "                                                 " + str(radius) + ", iquads :: manybody_expansion :: PRODUCTION ) );\n");

  return 0;


def write( fg_config ):

  driver_name = fg_config.driver_name;
  f_main_cpp = open( driver_name, "wt" );

  write_include( fg_config, f_main_cpp );
  f_main_cpp.write("\n");

  f_main_cpp.write( "int main( int argc, char* argv[] ) { \n" );
  f_main_cpp.write( "\n" );

  write_unit_cell( fg_config, f_main_cpp );
  write_execution_part( fg_config, f_main_cpp );

  f_main_cpp.write( "  return 0;\n");
  f_main_cpp.write( "\n" );
  f_main_cpp.write( "}\n" );

  f_main_cpp.close();

  return 0;

