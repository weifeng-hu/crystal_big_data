#include <utility>
#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include <cmath>
#include "parameters.h"
#include "pdm.h"
#include "mo_coefficients.h"
#include "transform_info.h"
#include "ph_analysis.h"

using namespace std;

namespace ph_analysis{

int transform_ph_main( multimap< double, pair<int, int> >& ph_pair, const mo_coefficients &c_mo )
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

int transform_pphh_main( multimap< double, pair<int, int> >& pphh_pair, const mo_coefficients &c_mo )
{

  std::multimap< double, pair<int, int> > :: iterator iter;
  for( iter = pphh_pair.begin(); iter != pphh_pair.end(); ++iter ){
   double value = iter->first;
   int ind_i = (iter->second).first;
   int ind_j = (iter->second).second;
//    mo_coefficients mat2 = transform_element_2( c_mo, value, ind_i, ind_i, ind_j, ind_j );
//    print_projected_twopdm( mat, value, ind_i, ind_i, ind_j, ind_j );
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
//     cout << count << " " << trans_info.get_nact() << endl;
//     if( count != trans_info.get_nact() ){ cout << " error: number of pz orbitals != nact " << endl; abort(); }
   }

   for( int i = 0; i < u_mat.get_nmo(); i++ ){
    for( int j = 0; j < u_mat.get_nao(); j++ ){
     const int ind_old_i = pz_ind.at(i);
     const int ind_old_j = active_space.at(j);
     const double value = u_mat_tmp( ind_old_j, ind_old_i );
     u_mat( j , i ) = value;
    }
   }
  }

  {
   const double thresh = trans_info.get_t1_thresh();
   multimap< double, pair<int, int> > ph_pairs = get_ph_pairs( trans_info.get_gamma1(), thresh );
   transform_ph_main( ph_pairs, u_mat );
  }

/*
  {
   const double thresh = trans_info.get_t2_thresh();
   multimap< double, pair<int, int> > pphh_pairs = get_pphh_pairs( trans_info.get_gamma2(), thresh );
   transform_pphh_main( pphh_pairs, u_mat );
  }
*/

  return 0;

}

} // end of ph_analysis
