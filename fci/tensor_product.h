#include <array>
#include <utility>
#include <cmath>
#include "fci.h"

using namespace std;

namespace fci {

template <class T>
array<T, DIM_THRESH>& tensor_product( array<T, DIM_THRESH/4>& sub_tensor, const array<T, 4> unit_tensor, const int sub_length )
{

  array<T, DIM_THRESH> prod_tensor;
  for( int i = 0; i < 4; i++ ){
   for( int j = 0; j < sub_length; j++ ){
    const int ind_prod = i * sub_length + j;
    prod_tensor[ind_prod] = sub_tensor[j] + unit_tensor[i];
   }
  }

  return std::move( prod_tensor );

}

template < class T >
array<T, DIM_THRESH>& tensor_product( const array<T, 4>& unit, const int nsite )
{

  array<T, DIM_THRESH> prod;
  array<T, DIM_THRESH/4> sub;
  for( int i = 0; i < 4; i++ ){ sub.at(i) = unit.at(i); }

  int isite = 0;
  while( isite < nsite ){
   sub_length = pow( 4, isite + 1 );
   prod = tensor_product( sub, unit, sub_length );
   isite = isite + 1;
  }

  return std::move( prod );

}

}
