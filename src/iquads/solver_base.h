#ifndef IQUADS_SOLVER_BASE_H
#define IQUADS_SOLVER_BASE_H

namespace iquads{

template < class Tcondition, class Tmethod, class Tsolution >
class solver : private Tcondition, private Tmethod, private Tsolution
{
public:
  void solve()
   {
    this->set_solution() = this->run( this->get_condition() ) ;
   }
  Tsolution solve( Tcondition condition )
   {
    return Tmethod::run( condition );
   }

};

} // end of iquads

#endif
