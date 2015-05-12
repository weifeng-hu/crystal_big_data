#ifndef NUMERICAL_NONADIABATIC_COUPLING_TEMPLATE_H
#define NUMERICAL_NONADIABATIC_COUPLING_TEMPLATE_H

#include <central_difference.h>
#include <numerical_nonadiabatic_coupling_base.h>

namespace iquads {

template 
< class Reference_Functional_Type, 
  class Coupling_Type 
         = Derivative< Reference_Functional_Type, AtomicCoordinateDisplacement >,
  class Policy_Type 
         = CentralDifference< Reference_Functional_Type, AtomicCoordinateDisplacement >,
>
class NumericalNonAdiabaticCoupling
  : public NumericalNonAdiabaticCoupling_Base
{

private:
  void compute_reference(){
   this->reference_.compute();
  }
  void compute_couplings(){
   for( size_t icoord = 0; icoord < ncoord; icoord++ ){
    AtomicCoordinateDisplacement displacement_local;
    Policy_Type policy;
    Couping_Type current_coupling = policy.compute( this->get_reference(), displacement_local );
    this->result_.push_back( current_coupling );
   } 
  }
  void return_results()
  { /* TBI */ }

private:
  Reference_Functional_Type reference_;
  vector< Coupling_Type > result_;

};

} // end of namespace iquads

#endif
