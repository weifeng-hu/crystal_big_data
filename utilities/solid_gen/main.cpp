/*
 *
 *  Copyright (C) 2013-2015 Weifeng Hu, all rights reserved.
 *  
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  @summary		A fragment generator for molecular crystals
 *  @description	This program identifies unique types of
 *  			fragments, e.g., dimers, trimers, in 
 *  			a big molecular crystal lattice.
 *  @author		Weifeng Hu<hulakui@gmail.com>
 *
 */

#include <stdio.h>
#include <string>
#include <vector>
#include "utilities/solid_gen/fragment_generator_driver.h"

int main( int argc, char* argv[] )
{

  using namespace std;

  // transfer arguments to strings
  vector<string> args;
  args.resize(argc);
  for( size_t iarg = 0; iarg < argc; iarg++ ){ 
   args[iarg] = argv[iarg]; 
  }

  // enter the main driver
  fragment_generator_driver( args );

  return 0;

}
