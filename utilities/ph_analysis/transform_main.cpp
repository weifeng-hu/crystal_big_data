#include <utility>
#include <vector>
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <cmath>
#include "parameters.h"
#include "pdm.h"
#include "mo_coefficients.h"
#include "transform_info.h"
#include "ph_analysis.h"
#include "fc_fortran.h"

using namespace std;

namespace ph_analysis{

int transform_ph_main_element( multimap< double, pair<int, int> >& ph_pair, mo_coefficients &c_mo )
{

  std::multimap< double, pair<int, int> > :: iterator iter;
  for( iter = ph_pair.begin(); iter != ph_pair.end(); ++iter ){
   const double value = iter->first;
   const int ind_i = (iter->second).first;
   const int ind_j = (iter->second).second;
   onepdm mat = transform_element_1( c_mo, value, ind_i, ind_j );
   print_projected_element_1( mat, value, ind_i, ind_j ); 
  }
  return 0;

}

int transform_ph_main( onepdm& pdm_mo, mo_coefficients &c_mo )
{
  int norb = pdm_mo.get_norb();
  onepdm pdm_ao( norb );
  pdm_ao = transform_1( c_mo, pdm_mo );
  print_projected_element_1( pdm_ao, 0.0e0, 0, 0 );
//  iqs::matrix::oei_transform_( &norb, &norb, c_mo.set_store().data(), pdm_mo.set_store().data(), pdm_ao.set_store().data() );
//  print_projected_element_1( pdm_ao, 0.0e0, 0, 0 );
  return 0;
}

int transform_pphh_main( twopdm& pdm_mo, mo_coefficients &c_mo )
{
   int norb = pdm_mo.get_norb();
//   twopdm pdm_ao = transform_2( c_mo, pdm_mo );

// Debug
   twopdm pdm_ao( norb );
   iqs::matrix::tei_transform_( &norb, &norb, c_mo.set_store().data(), pdm_mo.set_store().data(), pdm_ao.set_store().data() );

   print_projected_element_double_spin_excitation( pdm_ao, c_mo);
}


int transform_pphh_main( multimap< double, pair<int, int> >& pphh_pair, const mo_coefficients &c_mo )
{


  std::multimap< double, pair<int, int> > :: iterator iter;

  for( iter = pphh_pair.begin(); iter != pphh_pair.end(); ++iter ){
   const double value = iter->first;
   const int ind_i = (iter->second).first;
   const int ind_j = (iter->second).second;
//   onepdm mat = transform_element_2( c_mo, value, ind_i, ind_j );
   twopdm mat = transform_element_2( c_mo, value, ind_i, ind_i, ind_j, ind_j );
//   print_projected_element_1( mat, value, ind_i, ind_j );
//   print_projected_element_2( mat, value, ind_i, ind_j );
   print_projected_element_double_spin_excitation( mat,  c_mo);
  }

  return 0;

}

multimap< double, pair<int, int> > get_ph_pairs( const onepdm& gamma1, const double thresh )
{

  multimap<double, pair<int, int> > ph_pairs;
  const int norb = gamma1.get_norb();

  for( int i = 0; i < norb; i++ ){
   for( int j = 0; j < norb; j++ ){
    double value = gamma1( i, j );
    if( fabs( value ) >= thresh ){
     ph_pairs.insert( pair< double, pair<int, int> >( value, pair< int, int >( i, j ) ) );
    }
   }
  }
  return ph_pairs;

}

multimap< double, pair<int, int> > get_pphh_pairs( const twopdm& gamma2, const double thresh )
{

  multimap< double, pair<int, int> > pphh_pairs;
  const int norb = gamma2.get_norb();

 cout << norb<< endl;

  for( int i = 0; i < norb; i++ ){
   for( int j = 0; j < norb; j++ ){
    double value = gamma2( i, i, j, j );
    if( fabs( value ) >= thresh ){
     pphh_pairs.insert( pair< double, pair<int, int> >( value, pair<int, int>( i, j )) );
    }
   }
  }
  return pphh_pairs;

}

multimap< double, array<int, 4> > get_pphh_list( const twopdm& gamma2, const double thresh )
{

  multimap< double, array<int,4> > pphh_list;
  const int norb = gamma2.get_norb();

  for( int i = 0; i < norb; i++ ){
   for( int j = 0; j < norb; j++ ){
    for( int k = 0; k < norb; k++ ){
     for( int l = 0; l < norb; l++ ){
      const double value = gamma2( i, j, k, l );
      array<int, 4> index;
      index[0] = i;
      index[1] = j;
      index[2] = k;
      index[3] = l;
      if( fabs( value ) >= thresh ){
       pphh_list.insert( pair< double, array<int, 4> >( value, index ) );
      }
     }
    }
   }
  }
  return pphh_list;

}

int transform_main( const transform_info& trans_info )
{

  if( trans_info.get_compute_s_only() != 0 ){
   return 0;
  }

  mo_coefficients u_mat;
  mo_coefficients u_mat_tmp;

  const array<int, NMO_THRESH> active_space = trans_info.get_active_space();
  if( trans_info.get_solve_u() == 0 ){
   cout << " user defined U matrix" << endl;
   u_mat_tmp = trans_info.get_u_tr();
  }
  else if( trans_info.get_solve_u() == 1 ){
   cout << " using localized orbital" << endl;
   const mo_coefficients c_mo = trans_info.get_c_mo();
   const mo_coefficients c_lmo = trans_info.get_c_lmo();
   const mo_coefficients s_ov  = trans_info.get_s_ov();
   u_mat_tmp = compute_u( c_mo, s_ov, c_lmo );

   u_mat.set_nmo() = trans_info.get_nact();
   u_mat.set_nao() = trans_info.get_nact();
   u_mat.set_n_element() = u_mat.get_nmo() * u_mat.get_nao();
   u_mat.set_transposed() = false;
   u_mat.set_inverse_computed() = false;
   for( int i = 0; i < u_mat.get_nmo(); i++ ){
    for( int j = 0; j < u_mat.get_nao(); j++ ){
     const int ind_old_i = active_space.at(i);
     const int ind_old_j = active_space.at(j);
     const double value = u_mat_tmp( ind_old_j, ind_old_i );
     u_mat( j, i ) = value;
    }
   }

  }
  else if( trans_info.get_solve_u() == 2 ){
   cout << " using orthogonalized atomic orbitals" << endl;
   const mo_coefficients c_mo = trans_info.get_c_mo();
   const overlap_matrix s_ov = trans_info.get_s_full();
   u_mat_tmp = compute_ctsh( c_mo, s_ov );

   u_mat.set_nmo() = trans_info.get_nact();
   u_mat.set_nao() = trans_info.get_nact();
   u_mat.set_n_element() = u_mat.get_nmo() * u_mat.get_nao();
   u_mat.set_transposed() = false;
   u_mat.set_inverse_computed() = false;

   // read the pz indices
   vector<int> pz_ind;
   {
     ifstream ifs;
     string filename = trans_info.get_prefix() + trans_info.get_basename() + ".orca.2pz_orbs";
     ifs.open( filename.c_str() );
     int count = 0;
     while( count <= trans_info.get_nact() ){
      int entry;
      ifs >> entry;
      pz_ind.push_back( entry );
      count = count + 1;
     }
     ifs.close();
   }

   for( int i = 0; i < u_mat.get_nmo(); i++ ){
    for( int j = 0; j < u_mat.get_nao(); j++ ){
     const int ind_old_i = pz_ind.at(i);
     const int ind_old_j = active_space.at(j);
     const double value = u_mat_tmp( ind_old_j, ind_old_i );
     u_mat( j , i ) = value;  // mo, pz
    }
   }
  }

  if( trans_info.get_trans_onepdm() == 1 )
  {
   if( trans_info.get_trans_onepdm_element() == -1 ){
    onepdm pdm_mo = trans_info.get_gamma1();
    transform_ph_main( pdm_mo, u_mat );
   }
   else if( trans_info.get_trans_onepdm_element() == 1 ){
    const double thresh = trans_info.get_t1_thresh();
    multimap< double, pair<int, int> > ph_pairs = get_ph_pairs( trans_info.get_gamma1(), thresh );
    transform_ph_main_element( ph_pairs, u_mat );
   }
  }

  if( trans_info.get_trans_twopdm() == 1 )
  {
    if( trans_info.get_trans_twopdm_element() == -1 ){
     twopdm pdm_mo = trans_info.get_gamma2();
     transform_pphh_main( pdm_mo, u_mat );
    }
    else if( trans_info.get_trans_twopdm_element() == 1 ){
     const double thresh = trans_info.get_t2_thresh();
     twopdm pdm_mo = trans_info.get_gamma2();
     multimap<double, pair<int, int> > pphh_pair = get_pphh_pairs( pdm_mo, thresh );
     transform_pphh_main( pphh_pair, u_mat );
    }
  }

/*
  {
   const double thresh = trans_info.get_t2_thresh();
   multimap< double, array<int, 4 > > pphh_list = get_pphh_list( trans_info.get_gamma2(), thresh );
   multimap< double, array<int, 4 > > :: reverse_iterator it_list = pphh_list.rbegin();
cout << pphh_list.size() << endl;
   twopdm total( trans_info.get_gamma2().get_norb() );
   for( ; it_list != pphh_list.rend(); it_list++ ){
    const double value = it_list->first;
    const int i = (it_list->second).at(0);
    const int j = (it_list->second).at(1);
    const int k = (it_list->second).at(2);
    const int l = (it_list->second).at(3);
    cout << i << " " << j << " " << k << " " << l << " " << value << endl;
    twopdm mat = transform_element_2( u_mat, value, i, j, k, l );
    total = total + mat;
//    break;
   }
   print_projected_element_double_spin_excitation( total, u_mat );
  }
*/

  return 0;

}

} // end of ph_analysis
