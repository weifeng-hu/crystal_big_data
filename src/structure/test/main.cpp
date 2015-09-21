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

#include <structure/atom.hpp>
#include <structure/molecule.hpp>
#include <structure/lattice_parameter.hpp>
#include <structure/unit_cell_template.hpp>

int main( int argc, char* arg[] ) {

  using iquads :: structure :: Atom;
  Atom atom_obj;

  using iquads :: structure :: Molecule;
  Molecule molecule_obj;

  using iquads :: structure :: LatticeParameter;
  LatticeParameter lattice_parameter( 1.0e0, 1.0e0, 1.0e0, 90.0e0, 90.0e0, 90.0e0 );

  using iquads :: structure :: UnitCell;
  UnitCell< Molecule > mole_cell;
  UnitCell< Molecule > new_mole_cell = mole_cell.translational_duplicate(0,0,0);

} //  end of function main()
