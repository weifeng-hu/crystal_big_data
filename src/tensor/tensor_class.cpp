#include <vector>
#include "tensor/tensor_class.h"

namespace iquads { 

// Constructors
export
template < typename T > 
inline tensor<T> :: tensor( const int d0 )
{
  dimensions().push_back(d0);
  this->data.resize( d0 );
  this->size_ = data.size();
}

export
template < typename T > 
inline tensor<T> :: tensor( const int d0, const int d1 )
{
  dimensions().push_back(d0);
  dimensions().push_back(d1);
  this->data.resize( d0 * d1 );
  this->size_ = data.size();
}

export
template < typename T > 
inline tensor<T> :: tensor( const int d0, const int d1, const int d2 )
{
  dimensions().push_back(d0);
  dimensions().push_back(d1);
  dimensions().push_back(d2);
  this->data.resize( d0 * d1 * d2 );
  this->size_ = data.size();
}

export
template < typename T >
inline tensor<T> :: tensor( int d0, int d1, int d2, int d3 )
{
  cout << d0 << d1 << d2 << d3 << endl;
  dimensions().push_back(d0);
  dimensions().push_back(d1);
  dimensions().push_back(d2);
  dimensions().push_back(d3);
  this->data.resize( d0 * d1 * d2 * d3 );
  this->size_ = data.size();
}

export
template < typename T >
inline tensor<T> :: tensor( const int d0, const int d1, const int d2, const int d3, const int d4 )
{
  dimensions().push_back(d0);
  dimensions().push_back(d1);
  dimensions().push_back(d2);
  dimensions().push_back(d3);
  dimensions().push_back(d4);
  this->data.resize( d0 * d1 * d2 * d3 * d4 );
  this->size_ = data.size();
}

export
template < typename T > 
inline tensor<T> :: tensor( const int d0, const int d1, const int d2, const int d3, const int d4, const int d5 )
{
  dimensions().push_back(d0);
  dimensions().push_back(d1);
  dimensions().push_back(d2);
  dimensions().push_back(d3);
  dimensions().push_back(d4);
  dimensions().push_back(d5);
  this->data.resize( d0 * d1 * d2 * d3 * d4 * d5 );
  this->size_ = data.size();
}


}  // end of iqs
