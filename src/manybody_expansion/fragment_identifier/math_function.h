/*
 *  This source code applies all the terms in 
 *  GNU GENERAL PUBLIC LICENSE (GPL), Version3, 29 June 2007.
 *
 *  Copyright (C) 2013-2015 Weifeng Hu, all rights reserved.
 *  
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */


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
