#ifndef NUMERICAL_NONADIABATIC_COUPLING_BASE_H
#define NUMERICAL_NONADIABATIC_COUPLING_BASE_H

#include <string>

namespace iquads {

class NumericalNonAdiabaticCoupling_Base
{
using std::string;
protected:
  virtual void return_results() = 0;
  virtual void compute_reference() = 0;
  virtual void compute_couplings() = 0;

protected:
  void execute( NumericalNonAdiabaticCoupling_Config config ){
   this->config_ = config;
   this->solve();
   this->return_results();
  }
  void solve(){
   if( this->reference_is_computed_ == false ) {
    this->compute_reference();
   }
   this->compute_couplings();
  }

public:
  string solver_tag() const { return this->solver_tag_; }
  NumericalNonAdiabaticCoupling_Config config_ptr() const
   { return this->config_ptr_; }
  bool reference_is_computed() const { return this->reference_is_computed_; }

protected:
  NumericalNonAdiabaticCoupling_Config config_;
  string solver_tag_;
  bool reference_is_computed_;

}; // end of class NumericalNonAdiabaticCoupling_Base

} // end of namespace iquads

#endif
