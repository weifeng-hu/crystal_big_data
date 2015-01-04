#ifndef IQUADS_STAGE_H
#define IQUADS_STAGE_H

#include "iquads/solver.h"

namespace iquads{

class stage
{
protected:
  virtual void perform() = 0;
  virtual void set_condition() = 0;

protected:
  string stage_tag_;
  unsigned int code;
};

template < class Tframe, class Tevolver >
class evolve : protected stage
{
public:
  void perform()
  {
    initial = get_initial();
    final   = evolver.evolve( initial );
    final.save();
  }

private:
  vector<Tframe> frames;
  Tevolver evolver;
};

template < class Tsolver >
class solve : protected stage
{
public:
  void perform( const int condition_code )
   {
    this->solver.setup_condition( condition_code );
    this->solver.solve();
    this->solver.save_solution();
   }

private:
  Tsolver solver;

};

} // end of namespace iquads

#endif
