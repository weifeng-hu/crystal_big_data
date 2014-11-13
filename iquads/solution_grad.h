#include "iquads/solution_base.h"

namespace iquads{

template< class Tgradient >
struct solution_gradient : public solution_base
{
public:
  solution_gradient() : solution_base( "gradient" )
    {  }

public:
  Tgradient get_grad() const 
    { return this->grad; }

private:
  Tgrad grad;
  
};

typedef solution_gradient< debydx > energy_gradient;
typedef solution_gradient< debydr > orb_gradient;
typedef solution_gradient< dcibydx> ci_gradient;
typedef solution_gradient< dmpsbydx > mps_gradient;

} // end of iquads
