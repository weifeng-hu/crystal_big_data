#include <deltafunctional_base.h>
#include <derivative.h>

namespace iquads {

namespace numerical_recipe {

template 
 < class Functional_Type, class Variable_Type >
class CentralDifference
{
public:
  // When doing numerical derivative, the functional type of the derivative 
  // and the functional type of the original functional are the same.
  Derivative< Functional_Type, Variable_Type, Functional_Type >
  compute( Functional_Type functional_at_reference, Variable_Type difference )
  {
    Derivative< Functional, Variable_Type, Functional_Type > derivative;
    {
      DeltaFunctional<Functional_Type, Variable_Type > delta_functional;
      {
       Functional_Type functional_plus = functional_at_reference;
       functional_plus.apply_difference( +difference );
       Functional_Type functional_minus = functionl_at_reference;
       functional_minus.apply_difference( -difference );
       delta_functional = functional_plus - functional_minus;
      }
      derivative = delta_functional/( 2.0e0 * difference );
    }

    return derivative;
  }

};

} // end of numerical_method

} // end of namespace iquads
