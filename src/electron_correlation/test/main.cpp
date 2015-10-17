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
#include <electron_correlation/setting.hpp>
#include <electron_correlation/client.hpp>

int main( int argc, char* argv[] ) {

  // let's create a molecule
  iquads :: structure :: AtomList atom_list = { iquads :: structure :: Atom( string("H"), 0,  0,  0.5e0, "angstrom" ),
                                                iquads :: structure :: Atom( string("H"), 0,  0, -0.5e0, "angstrom" ),
                                                iquads :: structure :: Atom( string("O"), 0,  0,  0.0e0, "angstrom" ) };
  iquads :: structure :: Molecule molecule( atom_list, 0 ); // the second parameter is the charge
  std :: tuple < std :: string, iquads :: structure :: Molecule > molecule_info = std :: make_tuple( string("water"), molecule );
  std :: cout << "Molecule created:" << std :: endl;
  std :: cout << "name: " << std :: get<0>( molecule_info ) << std :: endl;
  std :: cout << "geometry: " << endl << std :: get<1>( molecule_info ) << endl;

  // let's create an electron correlation setting
  iquads :: electron_correlation :: Setting  calculation_setting( iquads :: sequence :: mode :: LOCAL_RUN,
                                                                  "sto-3g",
                                                                  0,
                                                                  0,
                                                                  iquads :: interface_to_third_party :: program :: MOLPRO,
                                                                  "./input/",
                                                                  "./scratch/",
                                                                  "./input/" );
  std :: cout << calculation_setting << std :: endl;

  // let's create a client
  iquads :: electron_correlation :: Client client;
  // and run application
  client.driver( molecule_info, calculation_setting );

}  // end of main()
