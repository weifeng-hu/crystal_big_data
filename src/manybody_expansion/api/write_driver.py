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


def write_include( f_main_cpp ):

  f_main_cpp.write( "#include <vector>\n" );
  f_main_cpp.write( "#include <tuple>\n" );
  f_main_cpp.write( "#include <string>\n" );
  f_main_cpp.write( "#include <structure/atom_list.hpp>\n");
  f_main_cpp.write( "#include <structure/molecule.hpp>\n");
  f_main_cpp.write( "#include <structure/unit_cell_template.hpp>\n");
  f_main_cpp.write( "#include <structure/lattice_parameter.hpp\n");
  f_main_cpp.write( "#include <structure/lattice_template.hpp>\n");
  f_main_cpp.write( "#include <structure/bulk_template.hpp\n");
  f_main_cpp.write( "#include <manybody_expansion/request.hpp>\n");
  f_main_cpp.write( "#include <manybody_expansion/report.hpp>\n");
  f_main_cpp.write( "#include <manybody_expansion/agent.hpp>\n");

  return 0;


def write_unit_cell( f_main_cpp, fg_config ):

  natom = fg_config.natom;
  nnode_per_unit_cell = fg_config.nnode_per_unit_cell;
  natom_per_node      = fg_config.natom_per_node;
  coordinates = fg_config.coordinates;
  constants   = fg_config.constants;

  f_main_cpp.write( "  std :: vector< iquads :: structure :: Molecule > node_list;\n" );
  f_main_cpp.write( "  node_list.resize(0);\n" );

  for inode in range( 0, nnode_per_unit_cell ):
    f_main_cpp.write( "  iquads :: structure :: AtomList " + "atom_list_" + str(inode) + " = {\n" );
    coordinate_of_node = coordinates[inode];
    for iatom in range ( 0, natom_per_node ):
      element = coordinates_of_node[iatom][0];
      x       = coordinates_of_node[iatom][1];
      y       = coordinates_of_node[iatom][2];
      z       = coordinates_of_node[iatom][3];
      unit    = coordinates_of_node[iatom][4];
      f_main_cpp.write( "  iquads :: structure :: Atom( std :: string(" + "'" + str(element) + "'" + "," + str(x) + "," + str(y) + "," + str(z) + str(unit) + ")," + "\n");
    f_main_cpp.write( "};\n" );
    f_main_cpp.write( "  iquads :: structure :: Molecule " + "molecule_" + str(inode) + "( atom_list_" + str(inode) + ", 0" + "); \n" );
    f_main_cpp.write( "node_list.push_back( molecule_" + str( inode ) + ");\n");

  f_main_cpp.write( "  iquads :: structure :: LatticeParameter lattice_parameter( " + str( constants.x ) + "," + str( constants.y ) + "," + str( constants.z ) + "," + str( constants.alpha ) + "," + str( constants.beta) + "," + str( constants.gamma) + ");\n");
  f_main_cpp.write( "  iquads :: structure :: UnitCell< iquads :: structure :: Molecule > unit_cell( node_List, lattice_parameter );\n" );
  f_main_cpp.write( "  iquads :: structure :: Lattice < iquads :: structure :: UnitCell< iquads :: structure :: Molecule > > lattice( unit_cell, " + str(a) + ", " + str(b) + ", " str(c) + ");\n" );

  f_main_cpp.write( "  iquads :: structure :: Bulk< iquads :: structure :: Molecule > bulk;\n" );

  f_main_cpp.write( "  iquads :: manybody_expansion :: Agent agent;\n" );
  f_main_cpp.write( "  iquads :: manybody_expansion :: Report report = agent.accept_request_and_process\n" );
  f_main_cpp.write( "     ( iquads :: manybody_expansion :: Request ( std :: make_tuple ( " + "'" + str(lattice_name) + "'" + ", lattice ), \n" );
  f_main_cpp.write( "                                                 std :: make_tuple ( 'unknown_bulk', bulk );\n" );
  f_main_cpp.write( "                                                 " + str( order ) + ", '" + str( correlation ) + "', '" + str( program ) + "', '" + str( basis_set ) + "'\n"  );
  f_main_cpp.write( "                                                 " + "'" + str(mode) + "',\n" ); 
  f_main_cpp.write( "                                                 " + "'" + str(project_name) + "',\n" );
  f_main_cpp.write( "                                                 'unknown',") + str() + );
  f_main_cpp.write( "                                                 " + str(radius) + ", iquads :: manybody_expansion :: PRODUCTION ) );\n");
  f_main_cpp.write( "  return 0;\n");
  f_main_cpp.write( "}\n");

  return 0;


def write_main():

  driver_name = "main.cpp";
  f_main = open( driver_name, "wt" );

  write_include( f_main );

  f_main.write( "int main( int argc, char* argv[] ) { \n" );

  write_unit_cell( coordinates, constants);

  f_main.write( "}\n" );

  f_main.close();

  return 0;
