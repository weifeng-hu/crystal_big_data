#ifndef THREED_SPACE_H
#define THREED_SPACE_H

#include <tuple>
#include <array>

using namespace std;

namespace iquads {

namespace threed_space {

  const pi = 3.14159265358979324e0;

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

  array< double, double, double > 
  operator* ( array< double, double, double > x, double a ){
   array< double, double, double> retval
    = { x.at(0) * a, x.at(1) * a, x.at(2) * a };
   return retval;
  }

} // end of namespace threed_space

} // end of namespace iquads

#endif
