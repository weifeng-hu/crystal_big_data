#ifndef IQUADS_MATH_H
#define IQUADS_MATH_H

namespace iquads {

namespace math {

template< size_t k >
vector< array<int, k > > get_combination( size_t total_n )
{

  vector<int> input_array;
  for( size_t i = 0; i < total_n; i++ ){ input_array.push_back(i); }

  combination<k> comb;
  comb.combinationa_util( input_array, 0, total_n-1, 0);

  return comb.get_all_comb();

};

} // end of namespace iquads

} // end of namespace iquads

#endif
