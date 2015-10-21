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
#include <tuple>
#include <string>
#include <structure/atom_list.hpp>
#include <structure/molecule.hpp>
#include <structure/unit_cell_template.hpp>
#include <structure/lattice_parameter.hpp>
#include <structure/lattice_template.hpp>
#include <structure/bulk_template.hpp>
#include <manybody_expansion/request.hpp>
#include <manybody_expansion/report.hpp>
#include <manybody_expansion/agent.hpp>

int main( int argc, char* argv[] ) {

  std :: vector< iquads :: structure :: Molecule > node_list;
  node_list.resize(0);

  iquads :: structure :: AtomList atom_list_1 = { iquads :: structure :: Atom( std :: string("H"), 0.25e0, 0.25e0,  0.25e0, "angstrom" ),
                                                  iquads :: structure :: Atom( std :: string("H"), 0.25e0, 0.25e0, -0.25e0, "angstrom" ) };
  iquads :: structure :: Molecule molecule_1( atom_list_1, 0 );
  node_list.push_back( molecule_1 );

  iquads :: structure :: AtomList atom_list_2 = { iquads :: structure :: Atom( std :: string("H"), -0.25e0, -0.25e0,  0.25e0, "angstrom" ),
                                                  iquads :: structure :: Atom( std :: string("H"), -0.25e0, -0.25e0, -0.25e0, "angstrom" ) };
  iquads :: structure :: Molecule molecule_2( atom_list_2, 0 );
  node_list.push_back( molecule_2 );

  //std :: cout << molecule_1 << std :: endl;
  //std :: cout << molecule_2 << std :: endl;

  iquads :: structure :: LatticeParameter lattice_parameter( 1.0e0 , 1.0e0 , 1.0e0, 90.0e0, 90.0e0, 90.0e0 );

  //std :: cout << lattice_parameter << std :: endl;

  iquads :: structure :: UnitCell< iquads :: structure :: Molecule > unit_cell( node_list, lattice_parameter );

  iquads :: structure :: Lattice< iquads :: structure :: UnitCell< iquads :: structure :: Molecule > > lattice( unit_cell, 6, 6, 6 );

  iquads :: structure :: Bulk< iquads :: structure :: Molecule > bulk;
  //std :: cout << lattice.is_filled() << std :: endl;
  //std :: cout << bulk.is_filled() << std :: endl;
  //std :: cout << lattice << std :: endl;

  iquads :: manybody_expansion :: Agent agent;
  iquads :: manybody_expansion :: Report report = agent.accept_request_and_process
      ( iquads :: manybody_expansion :: Request ( std :: make_tuple ( "lattic_x", lattice ), 
                                                  std :: make_tuple ( "unknown_bulk", bulk ),
                                                  2, "hf", "molpro", "sto-3g",
                                                  "local",
                                                  "try",
                                                  "unknown", "/scratch/wh288/lattice_x/", "unknown" ) );
  std :: cout << "monomer energy per unit cell: "  << report.return_one_body_energy_per_unit_cell() << std :: endl;
  std :: cout << "dimer interaction energy per unit cell: " << report.return_two_body_interaction_energy_per_unit_cell() << std :: endl;
  std :: cout << "trimer interaction energy per unit cell: " << report.return_three_body_interaction_energy_per_unit_cell() << std :: endl;
  std :: cout << "tetramer interaction energy per unit cell: " << report.return_four_body_interaction_energy_per_unit_cell() << std :: endl;
  return 0;

} 
