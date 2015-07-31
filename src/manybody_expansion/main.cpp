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
#include <iquads/command_parser.h>
#include <manybody_expansion/manybody_expansion_client.h>

int main( int argc, char* argv[] )
{

  using std::cout;
  using std::endl;

  cout << endl;
  cout << "ManyBody Expansion Lattice Energy Calculation" << endl;
  cout << endl;

  using iquads :: manybody_expansion :: ManyBodyExpansionClient;
  ManyBodyExpansionClient client;
  {
    using iquads :: CommandParser;
    CommandParser command_parser( argc, argv );
    client.driver( command_parser.command_string() );
  }

  return 0;

} // end of main()
