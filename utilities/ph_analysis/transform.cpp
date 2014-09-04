#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <array>
#include <utility>
#include <cmath>
#include "pdm.h"
#include "mo_coefficients.h"
#include "transform_info.h"

using namespace std;

namespace ph_analysis{

onepdm transform_element_1( const mo_coefficients &u_mat, const double element, const int ind_i, const int ind_j )
{

  const int norb = u_mat.get_nmo();
  const double value = element;

  onepdm trans_pdm_ao( norb );
  for( int mu = 0; mu < norb; mu++ ){
   for( int nu = 0; nu < norb; nu++ ){
    const double u_i_mu = u_mat( ind_i, mu );
    const double u_j_nu = u_mat( ind_j, nu );
//    const double u_i_mu = u_mat( mu, ind_i );
//    const double u_j_nu = u_mat( nu, ind_j );
//    cout << u_i_mu << " " << u_j_nu << endl;
    trans_pdm_ao(mu, nu) = value* u_i_mu* u_j_nu;
   }
  }

  return trans_pdm_ao;

}

onepdm transform_element_2( const mo_coefficients &u_mat, const double element, const int ind_i, const int ind_j, const int ind_k, const int ind_l )
{

   int norb = u_mat.get_nmo();
   double value = element;

   onepdm trans_pdm_ao( norb );
   for( int mu = 0; mu < norb; mu++ ){
    for( int nu = 0; nu < norb; nu++ ){
     double transform_mo = value;
     double u_i_mu = u_mat.get_element( ind_i, mu );
     double u_j_nu = u_mat.get_inverse_element( ind_j, nu );
     trans_pdm_ao( mu, nu ) = value * u_i_mu * u_i_mu * u_j_nu * u_j_nu;
    }
   }

  return trans_pdm_ao;

}

int print_projected_element_1( const onepdm& mat, const double value, const int ind_i, const int ind_j )
{

  const int norb = mat.get_norb();

  {
   const int created = ind_i;
   const int destroyed = ind_j;
   double mo_value = value;
   cout << " Original canonical transition pdm element: " << endl;
   cout << "  " << " < Psi_1 | " << " C+ " << created << " C " << destroyed << " | Psi_0 > = " << mo_value << endl;
  }

  cout << endl;
  cout << " Projected localized transition pdm info: " << endl;
  cout << "  receiving: " << endl;
  for( int i = 0; i < norb; i++ ){
   double total_prob = 0.0e0;
   for( int j = 0; j < norb; j++ ){
    const double ao_value = mat(i, j);
     total_prob = total_prob + pow( ao_value, 2 );
//     cout << "  " << " < Psi_1 | " << " C+" << i << " C " << j << " | Psi_0 > = " << ao_value<< endl;
   }
   cout << " < Psi_1 | C+ " << i << " C all | Psi_0 > = " << total_prob << endl;
  }
  cout << "  excited: " << endl;
  for( int j = 0; j < norb; j++ ){
   double total_prob = 0.0e0;
   for( int i = 0; i < norb; i++ ){
    const double ao_value = mat(i, j);
     total_prob = total_prob + pow( ao_value, 2 );
//     cout << "  " << " < Psi_1 | " << " C+" << i << " C " << j << " | Psi_0 > = " << ao_value<< endl;
   }
   cout << " < Psi_1 | C+ all | C" << j << " | Psi_0 > = " << total_prob << endl;
  }

}

/*
int print_project_element_2( const mo_coefficients& mat, const double value, const int ind_i, const int ind_j, const int ind_k, const ind_l )
{

  int created = 0;
  int destroyed = 1;
  double mo_value = 0.0e0;

  cout << " Original canonical transition pdm element: " << endl;
  cout << "  " << " < Psi_1 | " << " C+ " << created << " C+ " << created << " C " << destroyed << " C " << destroyed << " | Psi_0 > = " << mo_value << endl;
  cout << endl;
  cout << " Projected localized transition pdm info: " << endl;
  for( int i = 0; i < npair; i++ ){
   cout << "  " << " < Psi_1 | " << " C+ " << created << " C+ " << created << " C " << destroyed << " C "<< destroyed << " | Psi_0 > = " << ao_value<< endl;
  }

}
*/

} // end of ph_analysis
