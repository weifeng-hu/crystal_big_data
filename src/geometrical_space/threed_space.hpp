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
 */


#ifndef THREED_SPACE_VECTOR_HPP
#define THREED_SPACE_VECTOR_HPP

#include <tuple>
#include <array>

using std::tuple;
using std::array;

namespace iquads {

namespace geometrical_space {

namespace threed_space {

  constexpr double pi = 3.14159265358979324e0;

  using std::make_tuple;
  // the x unit vector
  const tuple< double, double, double > e_x 
   = make_tuple( 1.0e0, 0.0e0, 0.0e0 );
  const tuple< double, double, double > e_y 
   = make_tuple( 0.0e0, 1.0e0, 0.0e0 );
  const tuple< double, double, double > e_z 
   = make_tuple( 0.0e0, 0.0e0, 1.0e0 );

  // a tuple of all the unit vectors
  const array< tuple<double, double, double>,3 > e_3d
   = { e_x, e_y, e_z };

  inline array< double, 3 >  
  operator* ( array< double, 3 > vec, double a ){
   array< double, 3 > retval
    = { vec.at(0) * a, vec.at(1) * a, vec.at(2) * a };
   return retval;
  }

} // end of namespace threed_space

} // end of namespace geometrical_space

} // end of namespace iquads

#endif
