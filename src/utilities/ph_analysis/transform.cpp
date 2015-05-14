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

onepdm transform_1( mo_coefficients& u_mat, onepdm& mat )
{

  const size_t norb = mat.get_norb();
  onepdm mid( norb );
  {
   for( size_t i = 0; i < norb; i++ ){
    for( size_t j = 0; j < norb; j++ ){
     double value = 0.0e0;
     for( size_t k = 0; k < norb; k++ ){
      value = value + mat( i, k ) * u_mat( k, j );  // mo mo mo ao
     }
     mid( i, j ) = value;
    }
   }
  }

  onepdm final( norb );
  {
   for( size_t i = 0; i < norb; i++ ){
    for( size_t j = 0; j < norb; j++ ){
     double value = 0.0e0;
     for( size_t k = 0; k < norb; k++ ){
      value = value + u_mat( k, j ) * mid( k, i ); //mo ao mo ao
     }
     final( j, i ) = value;
    }
   }
  }

  return final;

}

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

onepdm transform_element_2( const mo_coefficients &u_mat, const double element, const int ind_i, const int ind_j )
{

   int norb = u_mat.get_nmo();
   double value = element;

   onepdm trans_pdm_ao( norb );
   for( int mu = 0; mu < norb; mu++ ){
    for( int nu = 0; nu < norb; nu++ ){
     const double transform_mo = value;
     const double u_i_mu = u_mat( ind_i, mu );
     const double u_j_nu = u_mat( ind_j, nu );
     trans_pdm_ao( mu, nu ) = value * u_i_mu * u_i_mu * u_j_nu * u_j_nu;
    }
   }

  return trans_pdm_ao;

}

twopdm transform_2( mo_coefficients& u_mat, twopdm& mat )
{

  const size_t norb = mat.get_norb();
  twopdm pdm_ao( mat.get_norb() );

  const size_t n_source = norb;
  const size_t n_target = norb;

  for( int i = 0; i < n_source; i++ ){
   for( int j = 0; j < n_source; j++ ){
    for( int k = 0; k < n_source; k++ ){
     for( int l = 0; l < n_source; l++ ){
//      if( i != 10 || j != 10 || k != 9 || l != 9 ) mat(i,j,k,l) = 0.0e0;
     }
    }
   }
  }

  twopdm mid1( norb );
  {
   for( size_t l = 0; l < n_source; l++ ){
    for( size_t k = 0; k < n_source; k++ ){
       onepdm midmat1(norb);
       for( size_t j = 0; j < n_source; j++ ){
        for( size_t i = 0; i < n_source; i++ ){
         midmat1( i, j ) = mat( l, k, j, i );
        }
       }
       onepdm midmat2(norb);
       midmat2 = transform_1( u_mat, midmat1 );
       for( size_t j = 0; j < n_source; j++ ){
        for( size_t i = 0; i < n_source; i++ ){
         mid1( l, k, j, i ) = midmat2( i, j );
        }
       }
    }
   }
  }
  
  {
   for( size_t i = 0; i < n_target; i++ ){
    for( size_t j = 0; j < n_target; j++ ){
       onepdm midmat1(norb);
       for( size_t k = 0; k < n_source; k++ ){
        for( size_t l = 0; l < n_source; l++ ){
          midmat1( k, l ) = mid1( k, l, i, j );
        }
       }
       onepdm midmat2(norb);
       midmat2 = transform_1( u_mat, midmat1 );

       for( size_t k = 0; k < n_target; k++ ){
        for( size_t l = 0; l < n_target; l++ ){
         pdm_ao( k, l, i, j ) = midmat2(k, l);
        }
       }
    }
   }
  }

  return pdm_ao;

}

twopdm transform_element_2( const mo_coefficients &u_mat, const double element, const int ind_i, const int ind_j, const int ind_k, const int ind_l )
{

   int norb = u_mat.get_nmo();
   double value = element;

   cout << value << endl;

   twopdm trans_pdm_ao( norb );
   for( int mu = 0; mu < norb; mu++ ){
    for( int nu = 0; nu < norb; nu++ ){
     for( int ro = 0; ro < norb; ro++ ){
      for( int si = 0; si < norb; si++ ){
        const double transform_mo = value;
        const double u_i_mu = u_mat( ind_i, mu );
        const double u_j_nu = u_mat( ind_j, nu );
        const double u_k_ro = u_mat( ind_k, ro );
        const double u_l_si = u_mat( ind_l, si );
        trans_pdm_ao( mu, nu, ro, si ) = value * u_i_mu * u_j_nu * u_k_ro * u_l_si;
//cout << mu << " " << nu << " " << ro << " " << si << " " << trans_pdm_ao( mu, nu, ro, si ) << endl;
      }
     }
    }
   }

  return trans_pdm_ao;

}

// print double spin excitation in real space
// this will apply to <2Ag| C+sigma C+ sigma' C sigma' C sigma | 1Ag > , with sigma = - sigma', since two excitations with opposite spins will conserve the spin symmetry
// recipe:
//  1. all < 1 | C+ alpha C+ beta C beta C alpha | 0 > and < 1 | C+ beta C+ alpha C alpha C beta | 0 > need to be obtained separately, in the MO space
//  2. for each term above, transform it to AO space, of course, we can take the dorminant terms to reduce the transformation time
//  3. we consider the following terms in AO space, for each ( a = alpha, b = beta )
//     (1). ia+ i'b+ ib i'a   i goes from i and i+1, also i' goes from i' to i'+1, i and i' are symmetric w.r.t center, so for each term there are 16 subterms
//     (2). ib+ i'a+ ia i'b   same as above
//  4. add (1) and (2)
//  5. plot the sum w.r.t. i
//  note that i need to jump by 2 every time --- to jump 2 bond
int print_projected_element_double_spin_excitation( const twopdm& mat_a, const mo_coefficients& u_mat )
{

  cout.precision(8);
  // here we consider 
  const int norb = mat_a.get_norb();
cout << norb << endl;
//  for( int i = 0; i < norb/2; i = i+2 ){
  for( int i = 0; i < norb; i = i+1 ){
   const int i_prime = norb - 1 - i;
   const double value = mat_a( i, i_prime, i, i_prime );
/*
these are essentially wrong for using pz oribtals, maybe will be correct if using localized orbitals
   for( int j = i; j < i+2; j++ ){
    for( int k = i_prime; k > i_prime-2; k-- ){
     value += mat_a( j, k, j, k );
     cout << j << " " << k << " " << j << " " << k << " " << mat_a(j, k, j, k) << "   U(10, " << j << ") = " << u_mat( 10, j ) << "   U(10, " << k << ") = " << u_mat( 10, k ) << "   U(9, " << j << ") = " << u_mat( 9, j ) << "   U(9, " << k << ") = " << u_mat(9, k) << endl;;
    }
   }
*/
   cout << " < 1 | C+(" << i << "s) C+(" << i_prime << "s') C(" << i << "s') C(" << i_prime << "s) = " << value << endl;
  }

  return 0;

}

int print_projected_element_2( const twopdm& mat, const double value, const int ind_i, const int ind_j )
{

  cout.precision(8);
  const int norb = mat.get_norb();
  {
   const int created = ind_i;
   const int destroyed = ind_j;
   double mo_value = value;
   cout << " Original canonical transition pdm element: " << endl;
   cout << "  " << " < Psi_1 | " << " C+ " << created << " C " << destroyed << " | Psi_0 > = " << mo_value << endl;
  }

  cout << endl;
  cout << "Projected localized trasition pdm info: " << endl;
  cout << "type: " << endl;
  cout << " local neighbouring excitation: < 1 | particle-hole particle-hole | 0 > " << endl;
  cout << " < Psi_1 | C+(i) C+(i) C(i+1) C(i+1) | Psi_2 > + < Psi_1 | C+(i+1) C+(i+1) C(i) C(i) | Psi_2 > + " << endl;;

  for( int i = 0; i < norb-1; i=i+2 ){
   cout << " < Psi_1 | C+(" << i << ") C+(" << i << ") C(" << i+1 << ") C(" << i+1 << ") | Psi_2 > + " 
        << " < Psi_1 | C+(" << i+1 << ") C+(" << i+1 << ") C(" << i << ") C(" << i << ") | Psi_2 > = " << mat( i, i, i+1, i+1 ) + mat( i+1, i+1, i, i ) << endl;
  }

  return 0;

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
  cout << "  probability of electrons coming in to this orb: " << endl;
  for( int i = 0; i < norb; i++ ){
   double total_prob = 0.0e0;
   for( int j = 0; j < norb; j++ ){
    const double ao_value = mat(i, j);
//      total_prob = total_prob + fabs( ao_value );
     total_prob = total_prob + pow( ao_value, 2 );
//     cout << "  " << " < Psi_1 | " << " C+" << i << " C " << j << " | Psi_0 > = " << ao_value<< endl;
   }
   cout << " < Psi_1 | C+ " << i << " C all | Psi_0 > = " << total_prob << endl;
  }
  cout << "  probability of electrons going out from this orb: " << endl;
  for( int j = 0; j < norb; j++ ){
   double total_prob = 0.0e0;
   for( int i = 0; i < norb; i++ ){
    const double ao_value = mat(i, j);
//       total_prob = total_prob + fabs( ao_value );
     total_prob = total_prob + pow( ao_value, 2 );
//     cout << "  " << " < Psi_1 | " << " C+" << i << " C " << j << " | Psi_0 > = " << ao_value<< endl;
   }
   cout << " < Psi_1 | C+ all | C" << j << " | Psi_0 > = " << total_prob << endl;
  }

  cout << "  probability of electron excitation from center to edge: " << endl;
  for( int i = norb/2 - 1; i >= 0; i-- ){
   int R_minus_r = i;
   int R_plus_r  = norb - 1 - i;
   double element1 = mat( R_plus_r,  R_minus_r );
   double element2 = mat( R_minus_r, R_plus_r  );
   cout << " R-r/2 = " << R_minus_r << " to  R+r/2 = " << R_plus_r  << " particle-hole separation r = " << R_plus_r - R_minus_r << "\tphi(r) = " << element1 << "\tphi(r)^2 = " << pow( element1, 2 ) << endl;
//   cout << " R+r/2 = " << R_plus_r  << " to  R-r/2 = " << R_minus_r << " particle-hole separation r = " << R_minus_r - R_plus_r << "\tphi(r) = " << element2 << "\tphi(r)^2 = " << pow( element2, 2 ) << endl;
  }

}

} // end of ph_analysis
