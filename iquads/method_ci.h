#include "iquads/method_base.h"

namespace iquads{

class ci_method : public method_base
{
protected:
  virtual iquads::ci_solution solve() = 0;

};

class fci : public ci_method 
{
public:
  iquads::ci_solution solve()
  { /* to be defined */ }

};

class orca_fci : public ci_method
{
public:
  iquads::ci_solution solve()
  { /* to be defined */ }

}

} // end of iquads
