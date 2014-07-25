#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "tensor.h"
#include "qcread.h"
#include "scf.h"
#include "cscphf.h"

using namespace std;

extern "C" {
 void e_matrix_( int* norb, double* OrbEns, double* E );
 void f_a_( int* norb, int* nocc, double* ha_mo, double* eria_mo, double* Fa );
 void a_matrix_( int* norb, double* eri_mo, double* A );
 void b_matrix_( int* norb, int* nocc, double* Fa, double* Sa, double* OrbEns, double* eri_mo, double* B );
 void oei_transform_( int* nbas, int* norb, double* u, double* oei1, double* oei2 );
 void tei_transform_( int* nbas, int* norb, double* u, double* tei1, double* tei2 );
 void u_matrix_( int* norb, int* nocc, double* E, double* A, double* B, double* U );
}

cphf::cscphf::cscphf( cphf::qcread::psiread psird , cphf::scf scf_data )
{
  this->ncoord = psird.ncoord;
  this->nbas   = psird.nbas;
  this->norb   = psird.norb;
  this->nocc   = psird.nocc;
  this->nvir   = this->norb - this->nocc;

  this->s = tensor_reshape( nbas, nbas, psird.s, nbas*nbas, this->s );

  this->hcore_mo = scf_data.hcore_mo;
  this->eri_mo   = scf_data.eri_mo;
  this->OrbEns   = scf_data.OrbEns;
  this->c        = scf_data.c;

  this->s_deriv1 = tensor_reshape( ncoord, nbas, nbas, psird.s_deriv1, ncoord, nbas*nbas, this->s_deriv1);
  this->t_deriv1 = tensor_reshape( ncoord, nbas, nbas, psird.t_deriv1, ncoord, nbas*nbas, this->t_deriv1);
  this->v_deriv1 = tensor_reshape( ncoord, nbas, nbas, psird.v_deriv1, ncoord, nbas*nbas, this->v_deriv1);

  this->hcore_deriv1 = tensor_reshape( ncoord, nbas, nbas, psird.hcore_deriv1, ncoord, nbas*nbas, this->hcore_deriv1);
  this->eri_deriv1   = tensor_reshape( ncoord, nbas, nbas, nbas, nbas, psird.eri_deriv1, ncoord, nbas*nbas*nbas*nbas, this->eri_deriv1);

  this->sa_mo   = tensor(ncoord, norb*norb, this->sa_mo );
  this->ha_mo   = tensor(ncoord, norb*norb, this->ha_mo );
  this->eria_mo = tensor(ncoord, norb*norb*norb*norb, this->eria_mo );
  for( int i = 0; i < ncoord; i++ ){
  oei_transform_( &this->nbas, &this->norb, this->c, this->s_deriv1[i], this->sa_mo[i] );
  oei_transform_( &this->nbas, &this->norb, this->c, this->hcore_deriv1[i], this->ha_mo[i] );
  tei_transform_( &this->nbas, &this->norb, this->c, this->eri_deriv1[i], this->eria_mo[i] );
  }

  this->Fa = tensor( ncoord, norb*norb, this->Fa );
  this->A  = tensor( norb*norb*norb*norb, this->A );
  this->B  = tensor( ncoord, norb*norb, this->B );
  this->E  = tensor( norb*norb, this->E ); 
  this->U  = tensor( ncoord, norb*norb, this->U );
  for( int i = 0; i < ncoord; i++ ){
    e_matrix_( &this->norb, this->OrbEns, this->E );
    f_a_( &this->norb, &this->nocc, this->ha_mo[i], this->eria_mo[i], this->Fa[i] );
    a_matrix_( &this->norb, this->eri_mo, this->A );
    b_matrix_( &this->norb, &this->nocc, this->Fa[i], this->sa_mo[i], this->OrbEns, this->eri_mo, this->B[i] );
    u_matrix_( &this->norb, &this->nocc, this->E, this->A, this->B[i], this->U[i] );
  }

}
