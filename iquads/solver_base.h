#ifndef IQUADS_SOLVER_BASE_H
#define IQUADS_SOLVER_BASE_H

#include <string>
#include <vector>

namespace iquads{

template < class Tcondition, class Tmethod, class Tsolution >
class solver : private Tcondition, private Tmethod, private Tsolution
{
public:
  Tsolution solve()
  {
    return Tmethod::solve( Tcondition condition );
  }

};


} // end of iquads

#endif
