#ifndef FACTORY_STAGE_H
#define FACTORY_STAGE_H

#include <memory>

using namespace std;

namespace iquads{

class stage_factory
{
protected:
  virtual unique_ptr< stage > get_stage( /*condition*/ ) = 0;
};

class evolve_factory : public stage_factory
{
public:
  unique_ptr< stage > get_stage()
   { /* to be defined*/ }
};

class solve_factory : public stage_factory
{
public:
  unique_ptr< stage > get_stage()
   { /*to be defined*/ }
};

unique_ptr< stage_factory > createStageFactory( /* some condition */ )
{

  if( /* need to do evolution */ ){ 
     unique_ptr< stage_factory > ptr ( new evolve_factory );
     return ptr;
   }
  else if( /* need to do solving */ ){
     unique_ptr< stage_factory > ptr ( new solve_factory );
     return ptr;
   }

}

} // end of namespace iquads

#endif
