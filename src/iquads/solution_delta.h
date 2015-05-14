#include "iquads/solution_base.h"

namespace iquad {

template < class Tdelta >
struct solution_delta : public solution_base
{
public:
  solution_delta() : solution_base( "delta" )
    {  }

public:
  Tdelta get_delta() const
    { return this->delta; }
  Tdelta& set_delta()
    { return this->delta; }

private:
  Tdelta delta;

};

typedef solution_delta< delta_x > displacement;

}
