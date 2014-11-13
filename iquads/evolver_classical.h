#ifndef IQUADS_CLASSICAL_EVOLVER_H
#define IQUADS_CLASSICAL_EVOLVER_H

namespace iquads {

class meci_todd
{
public:
  template < class Tmol_info >
  Tmol_info evolve( Tmol_info initial_frame )
  {
    Tmol_info current_frame = initial_frame;
    while( !is_converged )
    {
      const energy_gradient g1 = current_frame.solve_g( state1 );
      const energy_gradient g2 = current_frame.solve_g( state2 );
      const energy_gradient gl = this->compute_lagrangian_g( g1, g2 );
      const energy_hessian h = this->compute_hessian();
      current_frame.set_geo() += Tdx_solver::( gl, h );
      this->judge_convergence( current_frame.get_e( state1 ), current_frame.get_e(state2) );
    }
    return current_frame;
  }

private:
  void judge_convergence( const double e1, const double e2, const energy_gradient gl )
    { /* to be defined */ }

private:
  bool is_converged;

};

template< class Tdx_solver >
class energy_min
{
public:
  template < class Tmol_info >
  Tmol_info evolve( Tmol_info initial_frame )
  {
    Tmol_info current_frame = initial_frame;
    double energy_last;
    while( !this->converged )
    {
     const double energy = current_frame.solve_e();
     const double de = energy - energy_last;
     current_frame.set_geo() += Tdx_solver::solve( current_frame.solve_g(), current_frame.solve_h() );
     this->judge_convergence( current_frame.get_gnorm(), de );
    }
    return current_frame;
  }

private:
  void judge_convergence( const double gnorm, const double de )
  { /* to be defined */ }

private:
  bool converged;

};

class classic_md
{
public:
  template < class Tmol_info >
  Tmol_info evolve( Tmol_info initial_frame )
  {
    Tmol_info current_frame = initial_frame;
    for( unsigned int i = 0; i < this->maxstep; i++ ){
     current_frame.set_geo() += Tdx_solver::solve( current_frame.solve_g() );
    }
    return current_frame;
  }

private:
  unsigned int maxstep;

};

} // end of iquads

#endif
