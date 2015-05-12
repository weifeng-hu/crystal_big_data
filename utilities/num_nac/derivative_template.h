#include <deltafunctional_base.h>

namespace iquads {

template < class Functional_Type, class Variable_Type, class Value_Type >
class Derivative
{
public:
  // Used in numerical derivative, like central difference policy
  // The third type argument will be Functional_Type
  friend Derivative_Base< Functional_Type, Variable_Type, Functional_Type > 
   operator/ 
   ( DeltaFunctional_Base< Functional_Type, Variable_Type > delta_functional, Variable_Type delta_variable )
  {
    Derivative_Base< Functional_Type, Variable_Type, Functional_Type > retval;
    {
      delta_functional /= delta_variable;
      retval = delta_functional;
    }
    return retval;
  }

public:
  Derivative_Base< Functional_Type, Variable_Type, Functional_Type >* 
   operator= ( DeltaFunctional_Base< Functional_Type, Variable_Type > delta_functional )
  {
    if( delta_functional.quotient_computed() == false )
    {

    }
    this->value_ = delta_functional.get_value();
    return this;
  }

public:
  Value_Type value() const { return this->value_; }

private:
  Value_Type value_;

}; // end of class general_deritive_base



} // end of namespace iquads
