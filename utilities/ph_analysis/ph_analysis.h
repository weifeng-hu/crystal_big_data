#ifndef PH_ANALYSIS_H
#define PH_ANALYSIS_H

#include <map>

#include "pdm.h"
#include "overlap_matrix.h"
#include "mo_coefficients.h"
#include "transform_info.h"

using namespace std;

namespace ph_analysis {

onepdm transform_element_1( const mo_coefficients& mo, const double element, const int ind_i, const int ind_j );

twopdm transform_element_2( const mo_coefficients& mo, const double element, const int ind_i, const int ind_j, const int ind_k, const int ind_l );

int print_projected_element_1( const onepdm& mat, const double value, const int ind_i, const int ind_j);

int transform_ph_main( multimap<double, pair<int, int> >& ph_pair, const mo_coefficients& c_mo, const double thresh );

int transform_pphh_main( multimap<double, pair<int, int> >& pphh_pair, const mo_coefficients& c_mo, const double thresh );

multimap<double, pair<int, int> > get_ph_pairs( const onepdm& gamma1, const double thresh);

multimap<double, pair<int, int> > get_pphh_pair( const twopdm& gamma2, const double thresh );

int transform_main( const transform_info& trans_info);

mo_coefficients compute_u( const mo_coefficients& c_mo, const mo_coefficients& s_ov, const mo_coefficients& c_lmo );

mo_coefficients compute_ctsh( const mo_coefficients& c_mo, const overlap_matrix& s_ov );

} // end of namespace ph_analysis

#endif
