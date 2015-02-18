#include <utility>
#include "mo_coefficients.h"
#include "overlap_matrix.h"

using namespace std;

namespace ph_analysis{

mo_coefficients compute_ctsh( const mo_coefficients& c_mo, const overlap_matrix& s_full ){

  const int nmo = s_full.get_nao();
  const int nao = c_mo.get_nmo();

  mo_coefficients c_mo_t = c_mo;
  c_mo_t.set_transposed() = true;

  overlap_matrix s_half_t;
  s_half_t.set_nao() = nmo;
  for( int j = 0; j < nmo; j++ ){
   for( int i = 0; i < nmo; i++ ){
    const int ind_mat = j * nmo + i;
    s_half_t( i, j ) = s_full.set_half().at(ind_mat);
   }
  }
  // compute CT S^(1/2)

  mo_coefficients ctsh = c_mo_t * s_half_t;

  ctsh.check_unity();
//  ctsh.print_matrix();

  // check whether C ( CT S^1/2 ) = S^-1/2
  ctsh.set_transposed() = false;
  mo_coefficients s_inversehalf_trial = c_mo * ctsh;

  cout << " check inverse half computed by C . ( CT . S^(1/2) )" << endl;
  cout << "   C . ( CT . S^(1/2) ) == S^(-1/2) ? " << endl;
  for( int j = 0; j < nao; j++ ){
   for( int i = 0; i < nao; i++ ){
    const int ind_mat = j * nao + i;
    const double val = s_inversehalf_trial( i, j ) - s_full.set_inverse_half().at( ind_mat );
    if( fabs( val ) >= 1.0e-8 ){
     printf( "%d %d %20.16f\n", j, i, val );
    }
   }
  }

  return ctsh;

}

}

