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
  constexpr std :: array< double, 3 > e_x = { 1.0e0, 0.0e0, 0.0e0 };
  constexpr std :: array< double, 3 > e_y = { 0.0e0, 1.0e0, 0.0e0 };
  constexpr std :: array< double, 3 > e_z = { 0.0e0, 0.0e0, 1.0e0 };
//  const tuple< double, double, double > e_x 
//   = make_tuple( 1.0e0, 0.0e0, 0.0e0 );
//  const tuple< double, double, double > e_y 
//   = make_tuple( 0.0e0, 1.0e0, 0.0e0 );
//  const tuple< double, double, double > e_z 
//   = make_tuple( 0.0e0, 0.0e0, 1.0e0 );

  // a tuple of all the unit vectors
  constexpr std :: array< std :: array< double, 3 >, 3 > e_3d = { e_x, e_y, e_z };
//  const array< tuple<double, double, double>,3 > e_3d
//   = { e_x, e_y, e_z };

  inline
  array< double, 3 > operator* ( array< double, 3 > vec, double a ) {
    array< double, 3 > retval
     = { vec.at(0) * a, vec.at(1) * a, vec.at(2) * a };
    return retval;
  }

  inline 
  array< double, 3 > operator+ ( array<double, 3 > lhs, array<double, 3> rhs ) {
    array< double, 3 > retval;
    retval[0] = lhs[0] + rhs[0];
    retval[1] = lhs[1] + rhs[1];
    retval[2] = lhs[2] + rhs[2];
    return retval;
  }

  inline
  double norm( array<double, 3> vec ) {
    double retval = vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2];
    retval = sqrt( retval );
    return retval;
  }


} // end of namespace threed_space

} // end of namespace geometrical_space

} // end of namespace iquads

#endif
