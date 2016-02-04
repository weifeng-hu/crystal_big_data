/**
 * @file
 * @author Weifeng Hu
 *
 * @section LICENSE
 *
 * Copyright (C) 2013, 2014, 2015  Weifeng Hu
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @section DESCRIPTION
 *
 *
 */

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <structure/atom_list.hpp>
#include <utility/convert_string_to.hpp>
#include <structure/molecule.hpp>
#include <structure/duplication_remover.hpp>
#include <structure/molecule_isolator.hpp>

int main( int argc, char* argv[] ) {

  iquads :: structure :: AtomList atom_list;

  std :: string filename = argv[1];
  std :: string bond_length_limit_str = argv[2];
  double bond_length_limit = iquads :: utility :: string_tool :: convert_string_to<double> ( bond_length_limit_str );

  size_t natom = 0;
  std :: string element;
  double x, y, z;
  std :: ifstream ifs( filename, std :: ios :: in );
  ifs >> natom;
  for( size_t iatom = 0; iatom < natom; iatom++ ) {
    ifs >> element >> x >> y >> z;
    atom_list.push_back( iquads :: structure :: Atom( element, x, y, z, "angstrom" ) );
  }
  ifs.close();

  iquads :: structure :: DuplicationRemover remover( 1.0e-4 );

  iquads :: structure :: AtomList new_atom_list = remover.strip( atom_list );

  std :: cout << "previous number of atoms: " << natom << std :: endl;
  std :: cout << "finally number of atoms: "  << new_atom_list.size() << std :: endl;

  iquads :: structure :: MoleculeIsolator isolator( bond_length_limit );

  std :: vector< iquads :: structure :: Molecule > molecule_list = isolator.split( new_atom_list );

  std :: string output_filename = filename + ".coord";
  std :: ofstream ofs( output_filename.c_str(), std :: ios :: out );
  ofs << molecule_list.size() << std :: endl;
  ofs << molecule_list[0].size() << std :: endl;
  for( size_t imole = 0; imole < molecule_list.size(); imole++ ) {
    ofs << "angstrom" << std :: endl;
    ofs << molecule_list[imole];
  }
  ofs.close();

} // end of function main
