#ifndef THREED_SPACE_FUNCTION_H
#define THREED_SPACE_FUNCTION_H

#include <vector>
#include <array>
#include "utilities/solid_gen/coordinate.h"

namespace iquads {

namespace threed_space {

inline double compute_distance( Coord coord_a, Coord coord_b ){

  double retval = 0.0e0;
  {
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

inline array< double, double, double> compute_recenter_vec( array< array<double, double>, 3> edges )
{

  array< double, double, double > retval;
  const double x_plus = edges.at(0).at(0);
  const double x_minus = edges.at(0).at(1);
  const double y_plus = edges.at(1).at(0);
  const double y_minus = edges.at(1).at(1);
  const double z_plus = edges.at(2).at(0);
  const double z_minus = edges.at(2).at(1);
  retval = { (x_plus+x_minus)/2, (y_plus+y_minus)/2, (z_plus+z_minus)/2};
  return retval;

}

} // end of namespace threeD_space

} // end of namespace iquads

#endif
