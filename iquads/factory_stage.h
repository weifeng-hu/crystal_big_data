#ifndef FACTORY_STAGE_H
#define FACTORY_STAGE_H

#include <memory>
#include <iostream>
#include <iomanip>
#include <stdlib.h>

using namespace std;

namespace iquads{

class stage_factory
{
protected:
  virtual unique_ptr< stage > get_stage( const unsigned int code ) = 0;
};

class evolve_factory : public stage_factory
{
public:
  unique_ptr< stage > get_stage( code )
   {
     switch( code )
     {
       case GEOOPT_NR_HF:
        unique_ptr< stage > stage_ptr( new evolve< geo_optimizer_nr_hf > );
        return stage_ptr;
        break;
       case GEOOPT_HF_DIIS:
        unique_ptr< stage > stage_ptr( new evolve< geo_optimizer_diis_hf > );
        return stage_ptr;
        break;
       case GEOOPT_DMRG_NR:
        unique_ptr< stage > stage_ptr( new evolve< geo_optimizer_dmrg_nr> );
        return stage_ptr;
        break;
       case MECI_GRAD_ONLY_DMRG:
        unique_ptr< stage > stage_ptr( new evolve< meci_optimizer_ener_dmrg> );
        return stage_ptr;
        break;
       case MECI_NONADIA_DMRG:
        unique_ptr< stage > stage_ptr( new evolve< meci_optimizer_nona_dmrg> );
        return stage_ptr;
        break;
       default:
        cout << " error: unknown stage info: " << endl;
        cout << "   code: " << hex << code << endl;
        abort();
     }
   }
};

class solve_factory : public stage_factory
{
public:
  unique_ptr< stage > get_stage( const unsigned int code )
   {

     unsigned int CODE = ( TYPE & PARA & METHOD & SOLUTION );
     switch( code )
     {
      case SOLVE_HF:
       unique_ptr< stage > stage_ptr( new solve< scf_solver, orb_solution > );
       stage_ptr->set_para();
       return stage_ptr;
       break;
      case SOLVE_HF_ORCA:
       unique_ptr< stage > stage_ptr( new solve< scf_solver_orca, orb_solution > );
       return stage_ptr;
       break;
      case SOLVE_CPHF:
       unique_ptr< stage > stage_ptr( new solve< cphf_solver, orblr> );
       return stage_ptr;
       break;
      case SOLVE_CPHF:
       unique_ptr< stage > stage_ptr( new solve< cphf_solver_orca, orblr > );
       return stage_ptr;
       break;
      case SOLVE_DMRG:
       unique_ptr< stage > stage_ptr( new solve< dmrg_solver, mps_solution > );
       return stage_ptr;
       break;
      case SOLVE_DMRG_BLOCK:
       unique_ptr< stage > stage_ptr( new solve< dmrg_solver_block, mps_solution> );
       return stage_ptr;
       break;
      case SOLVE_CPDMRG:
       unique_ptr< stage > stage_ptr( new solve< cpdmrg_solver, mps_lr> );
       return stage_ptr;
       break;
      case SOLVE_CPDMRG_BLOCK:
       unique_ptr< stage > stage_ptr( new solve< cpdmrg_solver_block, mps_lr > );
       return stage_ptr;
      default:
        cout << " error: unknown stage info: " << endl;
        cout << "   code: " << hex << code << endl;
        abort();
     } 
   }

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
