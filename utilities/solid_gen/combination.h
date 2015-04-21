#ifndef IQUADS_COMBINATION_H
#define IQUADS_COMBINATION_H

#include <array>
#include <vector>

using namespace std;

namespace iquads{

namespace math {

template< size_t r >
struct combinations
{
public:
  combinations(){
   this->all_combinations.resize(0);
   this->current.fill(0);
  }

public:
  void combination_util( vector<int> input_array, size_t start, size_t end, size_t index ){

   if( index == r ){
    this->all_combinations.push_back( this->current );
    return;
   }

   for( size_t i = start; ( i <= end && (end - i + 1) >= (r - index) ) ; i++ ){
    this->current[index] = input_array[i];
    this->combination_util( input_array, i+1, end, index+1 );
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
