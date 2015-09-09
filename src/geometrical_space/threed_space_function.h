/*
 *  Copyright (C) 2013-2015 Weifeng Hu, all rights reserved.
 *  
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  any later version.
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

#ifndef THREED_SPACE_FUNCTION_H
#define THREED_SPACE_FUNCTION_H

#include <vector>
#include <array>
#include <math.h>
#include <geometrical_space/coordinate.h>

using std::vector;
using std::array;

namespace iquads {

namespace geometrical_space {

namespace threed_space {

inline double compute_distance( Coord coord_a, Coord coord_b ){

  double retval = 0.0e0;
  {
   using std::get;
   const double x_a = get<0>(coord_a);
   const double y_a = get<1>(coord_a);
   const double z_a = get<2>(coord_a);
 
   const double x_b = get<0>(coord_b);
   const double y_b = get<1>(coord_b);
   const double z_b = get<2>(coord_b);
 
   const double dx = x_a - x_b;
   const double dy = y_a - y_b;
   const double dz = z_a - z_b;
 
   const double dis_sqr = dx * dx + dy * dy + dz * dz;
   retval = sqrt( dis_sqr );
  }
 
  return retval;

}

inline double compute_charge_weighted_distance( Coord coord_a, Coord coord_b, int charge_a, int charge_b )
{ 

  double retval = 0.0e0;
  {
   using std::get;
   const double x_a = get<0>(coord_a); //* charge_a/10.0e0;
   const double y_a = get<1>(coord_a); //* charge_a/10.0e0;
   const double z_a = get<2>(coord_a); //* charge_a/10.0e0;
 
   const double x_b = get<0>(coord_b); //* charge_b/10.0e0;
   const double y_b = get<1>(coord_b); //* charge_b/10.0e0;
   const double z_b = get<2>(coord_b); //* charge_b/10.0e0;
 
   const double dx = x_a - x_b;
   const double dy = y_a - y_b;
   const double dz = z_a - z_b;
 
   const double dis_sqr = dx * dx + dy * dy + dz * dz;
   retval = sqrt( dis_sqr ) * charge_a * charge_b;
  }
 
  return retval;
}

inline array< double, 3 > compute_recenter_vec( array< array<double, 2>, 3> edges )
{

  const double x_plus = edges.at(0).at(0);
  const double x_minus = edges.at(0).at(1);
  const double y_plus = edges.at(1).at(0);
  const double y_minus = edges.at(1).at(1);
  const double z_plus = edges.at(2).at(0);
  const double z_minus = edges.at(2).at(1);
  array<double, 3 > retval = { -(x_plus+x_minus)/2, -(y_plus+y_minus)/2, -(z_plus+z_minus)/2 };
  return retval;

}

} // end of namespace threed_space

} // end of namespace geometrical_space

} // end of namespace iquads

#endif
