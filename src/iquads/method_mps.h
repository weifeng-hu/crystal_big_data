#include "iquads/method_base.h"

namespace iquads {

class mps_method : public method_base
{
protected:
  virtual iquads::mps_solution solve() = 0;

};

class dmrg : public mps_method
{
public:
  iquads::mps_solution solve()
  { /* to be defined */ }
};

class block : public mps_method
{
public:
  iquads::mps_solution solve()
  { /* tobe solved */ }}
};

} // end of iquads
