#ifndef THREED_SPACE_VECTOR_H
#define THREED_SPACE_VECTOR_H

#include <tuple>
#include <array>

using namespace std;

namespace iquads {

namespace threed_space {

  const double pi = 3.14159265358979324e0;

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

  array< double, 3 >  
  operator* ( array< double, 3 > vec, double a ){
   array< double, 3 > retval
    = { vec.at(0) * a, vec.at(1) * a, vec.at(2) * a };
   return retval;
  }

} // end of namespace threed_space

} // end of namespace iquads

#endif
