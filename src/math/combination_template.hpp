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

#ifndef COMBINATION_TEMPLATE_HPP
#define COMBINATION_TEMPLATE_HPP

#include <array>
#include <vector>

namespace iquads {

namespace math {

using std::array;
using std::vector;

template< size_t r > struct Combinations {
public:
  Combinations() {
    this->all_combinations.resize(0);
    this->current.fill(0);
  }

public:
  void combination_util( vector<int> input_array, size_t start, size_t end, size_t index ) {
    if( index == r ) {
      this->all_combinations.push_back( this->current );
      return;
    }
    for( size_t i = start; ( i <= end && (end - i + 1) >= (r - index) ) ; i++ ) {
      this->current[index] = input_array[i];
      this->combination_util( input_array, i + 1, end, index + 1 );
    }
  }

  vector< array<int, r> > get_all_comb() { return this->all_combinations; }

private:
  vector< array< int, r > > all_combinations;
  array<int, r> current;

};


/*
template <typename Iterator>
inline bool next_combination(const Iterator first, Iterator k, const Iterator last)
{
   if ((first == last) || (first == k) || (last == k))
      return false;
   Iterator itr1 = first;
   Iterator itr2 = last;
   ++itr1;
   if (last == itr1)
      return false;
   itr1 = last;
   --itr1;
   itr1 = k;
   --itr2;
   while (first != itr1)
   {
      if (*--itr1 < *itr2)
      {
         Iterator j = k;
         while (!(*itr1 < *j)) ++j;
         std::iter_swap(itr1,j);
         ++itr1;
         ++j;
         itr2 = k;
         std::rotate(itr1,j,last);
         while (last != j)
         {
            ++j;
            ++itr2;
         }
         std::rotate(k,itr2,last);
         return true;
      }
   }
   std::rotate(first,k,last);
   return false;
}
*/

} // end of namespace math

} // end of namespace iquads

#endif
