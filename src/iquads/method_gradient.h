#include "iquads/method_base.h"

namespace iquads{

class method_energygradient : public method_base
{
protected:
  virtual energy_gradient solve() = 0;

};

class scf_gradient : public method_energygradient
{
public:
  energy_gradient solve()
  { /* to be defined */ }

};

class orca_scfgrad : public method_energygradient
{
public:
  energy_gradient solve()
  { /* to be defined */ }
};

class ci_gradient : public method_energygradient
{
public:
  energy_gradient solve()
  { /* to be defined */ }
};

} // end of iquads
