#ifndef IQUADS_EVOLVER_BASE_H
#define IQUADS_EVOLVER_BASE_H

#include <vector>

namespace iquads {

template < class Tmethod, class Tframe >
class evolver : private Tmethod, private Tframe
{
public:
  Tframe evolve()
  {
    return Tmethod::evolve( Tframe::return_frame() );
  }

};

}

#endif
