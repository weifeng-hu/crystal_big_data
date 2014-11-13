#include "iquads/method_base.h"

namespace iquads {

class meanfield_method : public method_base
{
protected:
  virtual iquads::meanfield_solution solve() = 0;

};

class scf : public meanfield_method
{
public:
  iquads::meanfield_solution solve()
  { /* to be defined */ }

};

class dft : public meanfield_method
{
public:
  iquads::meanfield_solution solve()
  { /* to be defined */ }

}

class orca_scf : public meanfield_method
{
public:
  iquads::meanfield_solution solve()
  { /* to be defined */ }

};

} // end of iquads
