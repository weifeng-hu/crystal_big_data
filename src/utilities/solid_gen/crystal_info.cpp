/*
 *  This source code applies all the terms in 
 *  GNU GENERAL PUBLIC LICENSE (GPL), Version3, 29 June 2007.
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
 */

#include <string>
#include <fstream>
#include "utilities/solid_gen/crystal_info.h"

using namespace std;

namespace iquads {

namespace crystal {

void molecular_crystal_info::read( string input )
{

  ifstream ifs;
  ifs.open( input.c_str(), ios::in );
  char line[100];
  while( ifs.getline( line, 100 ) ){
   string entry;
   entry = line;
   if( entry == "radius" ) ifs >> this->radius_;
   if( entry == "sizes" ){
    size_t a, b, c;
    ifs >> a >> b >> c;
    this->sizes = make_tuple ( a, b, c );
   }
   if( entry == "unit_cell" ){
    ifs >> this->primitive_;
   }
   if( entry == "short_range_radius" ){
    ifs >> this->short_range_radius_;
    this->short_range_requested_ = true;
   }
   if( entry == "long_range_radius" ){
    ifs >> this->long_range_radius_;
    this->long_range_requested_ = true;
   }
   if( entry == "request_dimer" ){
    this->dimer_requested_ = true;
   }
   if( entry == "request_trimer" ){
    this->trimer_requested_ = true;
   }
   if( entry == "request_tetramer" ){
    this->tetramer_requested_ = true;
   }
   if( entry == "request_visual" ){
    this->visualization_ = true;
   }
  }

} // end of crystal_info :: read()

} // end of namespace crystal

} // end of namespace iquads
