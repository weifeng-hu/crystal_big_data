#include <stdio.h>
#include <iostream>
#include <math.h>
#include "tensor.h"
#include "mat_utils.h"
#include "qcread.h"
#include "scf.h"
#include "geometry_searching.h"

using namespace std;

double calc_dist( double* coord1, double* coord2 );

extern "C" {
  void e_a_( int* nbas, int* norb, int* nocc, double* ha_ao, double* eria_ao, double* C, double* Sa, double* eps,double* Ea);
  void linear_solver_( int* m, int* n, double* a, double* x, double* b );
  void bicgstab_( int* m, int* n, double* a, double* x, double* b);
  void eigtql2_( int* dim, double* eigvec, double* eigval );
  void get_q_( int* dim, double* hessian, double* q, double* f);
}

double calc_dis( double* coord1, double* coord2 )
{
  double dis, squ, retval;
  squ = 0.0e0;
  for( int i = 0; i < 3; i++ ){
    dis = coord1[i] - coord2[i];
    squ = squ + pow(dis,2.0);
  }
    retval = sqrt( squ );
    return retval;
};

cphf::geometry_searching::geometry_searching( cphf::qcread::psiread psird, cphf::scf scf_data )
{
  this->nbas   = psird.nbas;
  this->norb   = psird.norb;
  this->nocc   = psird.nocc;
  this->natom  = psird.natom;
  this->ncoord = psird.ncoord;

  this->distance     = tensor( natom*(natom-1)/2, this->distance );
  this->grad_enuc    = psird.grad_enuc;
  this->s_deriv1     = tensor_reshape( ncoord, nbas, nbas, psird.s_deriv1, ncoord, nbas*nbas, this->s_deriv1 );
  this->c            = scf_data.c;
  this->hcore_deriv1 = tensor_reshape( ncoord, nbas, nbas, psird.hcore_deriv1, ncoord, nbas*nbas, this->hcore_deriv1 );
  this->eri_deriv1   = tensor_reshape( ncoord, nbas, nbas, nbas, nbas, psird.eri_deriv1, ncoord, nbas*nbas*nbas*nbas, this->eri_deriv1 );
  this->OrbEns       = scf_data.OrbEns;

  this->coord = psird.coord;
  this->f     = tensor(ncoord, this->f);
  for( int i = 0; i < this->ncoord; i++ ){
   e_a_( &nbas, &norb, &nocc, hcore_deriv1[i], eri_deriv1[i], c, s_deriv1[i], OrbEns, &f[i]);
//   printf("  %20.10f\n", grad_enuc[i]);
   f[i] = f[i] + grad_enuc[i];
   f[i] = -1.00e0 * f[i];
//   printf(" %20.10f\n ", f[i]);
  }
  this->hessian = tensor_reshape( ncoord, ncoord, psird.hessian, ncoord*ncoord, this->hessian );

//  {
//   double* eigvec = tensor_copy( ncoord*ncoord, hessian, eigvec );
//   double* eigval = tensor( ncoord, eigval );
//   eigtql2_( &ncoord, eigvec, eigval );
   
//   double* diaghess = diag_matrix_( ncoord, eigval, diaghess );
//    for( int i = 0; i < ncoord; i++ ){
//     cout << diaghess[ i * ncoord + i ] << endl;
//    }
//   double* effect_diaghess =  non_zero_diag( ncoord, diaghess, effect_diaghess ); 
   
//  }

  this->q = tensor( ncoord, this->q );

  get_q_( &ncoord, hessian, q, f);

// linear_solver_( &ncoord, &ncoord, hessian, q, f);
//  bicgstab_( &ncoord, &ncoord, hessian, q, f);

  this->q1 = tensor_reshape( ncoord, q, natom, 3, q1 );

//  cout << coord[0][2] << endl;
  {
   int icount = 0;
   for( int i = 0; i < natom; i++ ){
    for( int j = i+1 ; j < natom; j++ ){
      distance[icount] = calc_dis( coord[i], coord[j] );
      cout << distance[icount] << endl;
    }
   }
  }

  for( int i = 0; i < natom; i++ ){
   for( int j = 0; j < 3; j++ ){
   coord[i][j] = coord[i][j] + q1[i][j];
   }
  }

  {
   int icount = 0;
  for( int i = 0; i < natom; i++ ){
   for( int j = i+1 ; j < natom; j++ ){
     distance[icount] = calc_dis( coord[i], coord[j] );
     cout << distance[icount] << endl;
   }
  }
  }

};
