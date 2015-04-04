#ifndef THREED_SPACE_FUNCTION_H
#define THREED_SPACE_FUNCTION_H

#include <vector>
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

inline CoordList re_center( CoordList input_coord_list )
{

}

} // end of namespace threeD_space

} // end of namespace iquads

#endif
