/**
 * @file
 * @author Weifeng Hu
 *
 * @section LICENSE
 *
 * Copyright (C) 2013, 2014, 2015  Weifeng Hu
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @section DESCRIPTION
 *
 *
 */


#ifndef COMBINATION_COMPUTATION_HPP
#define COMBINATION_COMPUTATION_HPP

#include <vector>
#include <array>
#include <iostream>
#include <math/combination_template.hpp>

namespace iquads {

namespace math {

using std :: vector;
using std :: array;

vector< vector< int > > get_combination( size_t total_n, size_t r ) {

  vector<int> input_array;
  input_array.resize(0);
  for( size_t i = 0; i < total_n; i++ ) { input_array.push_back(i); }

  iquads :: math :: Combinations_general comb(r);
  comb.combination_util( input_array, 0, total_n - 1, 0 );

  return comb.get_all_comb();

}

template < size_t k > inline vector< array< int, k > > get_combination( size_t total_n ) {

  vector<int> input_array;
  input_array.resize(0);
  for( size_t i = 0; i < total_n; i++ ){ input_array.push_back(i); }

  iquads :: math :: Combinations<k> comb;
  comb.combination_util( input_array, 0, total_n - 1, 0);

  return comb.get_all_comb();

}; // end of function get_combination()

} // end of namespace iquads

} // end of namespace iquads

#endif
