#include <utility>
#include "mo_coefficients.h"

using namespace std;

namespace ph_analysis{

mo_coefficients compute_u( const mo_coefficients& c_mo, const mo_coefficients& s_ov, const mo_coefficients& c_lmo ){

  const int nmo = c_mo.get_nmo();
  const int nao = c_mo.get_nao();

  mo_coefficients c_mo_t = c_mo;
  c_mo_t.set_transposed() = true;
  // construct C^-1 = CT S
  mo_coefficients c_inverse = c_mo_t * s_ov;

  // check CT S C
  mo_coefficients product = c_inverse * c_mo;
//  product.print_diag();

  // C' = C U
  // so C^-1 C' = C^-1 C U
  // so U = C^-1  C' = CT S C'
  mo_coefficients u_mat = c_inverse * c_lmo;

//  u_mat.check_unity();
//  u_mat.print_matrix();

  return u_mat;

}

}
