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

#include <iostream>
#include <vector>
#include <tuple>
#include <electron_correlation/report.hpp>
#include <electron_correlation/client.hpp>
#include <electron_correlation/setting.hpp>

int main( int argc, char* argv[] ) {

  using std :: cout;
  using std :: endl;
  using iquads :: electron_correlation :: Report;
  using iquads :: electron_correlation :: Client;
  using iquads :: electron_correlation :: Setting;

  // let's create a molecule
  iquads :: structure :: AtomList atom_list = { iquads :: structure :: Atom( "H", 1, 0, 0.5e0, 0.0e0, 0.0e0, "angstrom" ), 
                                                iquads :: structure :: Atom( "H", 1, 0, -0.5e0, 0.0e0, 0.0e0, "angstrom" ),
                                                iquads :: structure :: Atom( "O", 16, 0, 0.0e0, 0.0e0, 0.0e0, "angstrom" ) };
  iquads :: structure :: Molecule molecule( atom_list, 0 ); // the second parameter is the charge
  cout << molecule << endl;

  Report report;
  Setting setting;
  Client client;

} // end of main()
