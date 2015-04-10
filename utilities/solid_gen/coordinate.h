#ifndef IQUADS_COORDINATE_H
#define IQUADS_COORDINATE_H

#include <vector>
#include <tuple>

namespace iquads {

namespace basic {

  // stack storage for coordinates
  // using tuple of 3 doubles

  // we enforce using double precision for coordinates
  // since we may encounter big coordinates like 1e5
  // and the significant digits after the decimal point 
  // can only be 8 digits or so
  typedef std::tuple< double, double, double > Coord;
  typedef std::vector<Coord> CoordList;

} // end of namespace basic

} // end of namespace iquads

#endif
