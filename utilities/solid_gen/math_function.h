#ifndef IQUADS_MATH_H
#define IQUADS_MATH_H

#include <vector>
#include <array>
#include <iostream>
#include <utilities/solid_gen/combination.h>

using namespace std;

namespace iquads {

namespace math {

template < size_t k >
inline vector< array<int, k > > get_combination( size_t total_n )
{

  vector<int> input_array;
  input_array.resize(0);
  for( size_t i = 0; i < total_n; i++ ){ input_array.push_back(i); }

  combinations<k> comb;
  comb.combination_util( input_array, 0, total_n-1, 0);

  return comb.get_all_comb();

}; // end of function get_combination()

} // end of namespace iquads

} // end of namespace iquads

#endif
