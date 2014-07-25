#include "cphf_class.h"
#include "qcdmrg_class.h"
#include "tensor/tensor.h"

namespace ithaca { namespace analytical {

gradient_class::gradient_class( cphf cphf_data, qcdmrg dmrg_data )
{

   this->nbas = cphf_data.nbas;
   this->norb = cphf_data.norb;
   this->nocc = cphf_data.nocc;
   this->nvir = norb - nocc;
   this->ncore = cphf_data.ncore;
   this->nact  = cphf_data.nact;

// Construct one and two pdms
   this->q = tensor( norb*norb, this->one_pdm );
   this->g = tensor( norb*norb*norb*norb, this->two_pdm );

   this->build_one_rdm( dmrg_data.one_pdm );
   this->build_two_rdm( this->one_pdm, dmrg_data.two_pdm );

   this->gradient = tensor( cphf_data.ncoord, this->gradient );
// Calculate the CI gradient
   for( int i = 0; i < cphf_data.ncoord; i++ ){
   this->gradient[i] = this->fci_gradient( this->norb, this->q, this->g, cphf_data.h, cphf_data.eri, cphf_data.h_a, cphf_data.tei_a, cphf_data.u, this->gradient[i] );
   }

/* This part is not adequent

// Construct the core gradient part
   this->E_core_a = tensor( ncore, thie->E_core_a );

   this->h_core = tensor( ncore*ncore, this->h_core );
   get_h_core( norb, ncore, cphf_data.hcore_mo, this->h_core );

   this->eri_core = tensor( ncore*ncore*ncore*ncore, this->eri_core );
   get_eri_core( norb, ncore, cphf_data.eri_mo, this->eri_core );

   this->c_core = tensor( norb*ncore, this->c_core );
   get_c_core( norb, ncore, cphf_data.c, c_core );

   this->eps_core = tensor( ncore, this->eps_core );
   get_eps_core( norb, ncore, cphf_data.eps, eps_core );

   this->sa_core = tensor( ncore*ncore, this->sa_core );
   for( int i = 0; i < cphf_data_data.ncoord; i++ ){
   get_sa_core( norb, ncore, cphf_data.sa[i], sa_core);
   E_core_a[i] = hf_gradient( ncore, ncore, ncore, h_core, eri_core, c_core, sa_core[i], eps_core, this->E_core_a[i] );
   }

// Construct the active space part, full ci part, without the core-active correlation

   this->E_act_a = tencor( ncore, this->E_act_a );

   this->h_act   = tensor( nact*nact, this->h_act );
   this->eri_act = tensor( nact*nact*nact*nact, this->eri_act );
   this->q_act = tensor( nact*nact, this->q_act );
   this->g_act = tensor( nact*nact*nact*nact, this->g_nact);
   get_2_act( norb, ncore, nact, cphf_data.hcore_mo, this->h_act );
   get_4_act( norb, ncore, nact, cphf_data.eri_mo, this->eri_act );
   get_2_act( norb, ncore, nact, dmrg_data.one_pdm, this->q_act );
   get_4_act( norb, ncore, nact, dmrg_data.two_pdm, this->g_act );

   for( int i = 0; i < cphf_data.ncoord; i++ ){
    this->ha_act   = tensor( nact*nact, this->ha_act );
    this->eria_act = tensor( nact*nact, nact, nact, this->eria_act );
    this->u_act    = tensor( norb*nact, this->u_act );
    get_u_act( norb, ncore, nact, cphf_data.u_a[i], this->u_act );
    get_2_act( norb, ncore, nact, cphf_data.ha_mo, this->ha_act );
    get_4_act( norb, ncore, nact, cphf_data.eria_mo, this->eria_act );
    E_act_a[i] = fci_gradient( nact, q_act, g_act, h_act, eri_act, ha_act, eria_act, u_act, this->E_act_a[i] );
   }

// construct the core-active part
  this->E_core_act_a = tensor( ncoord, this->E_core_act_a );
  for( int i = 0; i < cphf_data.ncoord; i++ ){
  E_core_act_a[i] = core_act_gradient( norb, ncore, nact, dmrg_data.one_pdm, cphf_data.eri_mo, cphf_data.eria_mo, cphf_data.u_a, this-> E_core_act_a[i] );
  }

// add up all the gradient components
  this->gradient = tensor( ncoord, this->gradient );
  for( int i = 0; i < cphf_data.ncoord; i++ ){
  gradient[i] = E_core_a[i] + E_act_a[i] + E_core_act_a[i];
  }

*/

};

} } // end of ithaca::analytical
