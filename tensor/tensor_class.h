#ifndef TENSOR_CLASS_H
#define TENSOR_CLASS_H

//#define NDEBUG

// tensor_class.h

// ========================================================
// 
//  A tensor is a n dimensional array, it can be a 
//  1. 1-d vector
//  2. 2-d matrix
//  3. d > 3 true tensors
//
// ========================================================
//
#include <stdlib.h>
#include <assert.h>
#include <stdexcept>
#include <iostream>
#include <vector>   // for std::vector
#include <array>    // for std::array
#include <numeric>  // for std::accumulate
#include <functional> // for std::multiply

using namespace std;

namespace iquads { 

#ifndef USE_VECTOR
template < class T, size_t N >
class tensor
{
public:
  tensor(){
   this->dimensions.fill(0);
   this->len = 0;
   this->check_size();
  }
  tensor( const int d0 ){
   this->dimensions.fill(0);
   this->dimensions[0] = d0;
   this->len = d0;
   this->check_size();
  }
  tensor( const int d0, const int d1 ){
   this->dimensions.fill(0);
   this->dimensions[0] = d0; this->dimensions[1] = d1;
   this->len = d0 * d1;
   this->check_size();
  }
  tensor( const int d0, const int d1, const int d2 ){
   this->dimensions.fill(0);
   this->dimensions[0] = d0; this->dimensions[1] = d1; this->dimensions[2] = d2;
   this->len = d0 * d1 * d2;
   this->check_size();
  }
  tensor( const int d0, const int d1, const int d2, const int d3 ){
   this->dimensions.fill(0);
   this->dimensions[0] = d0; this->dimensions[1] = d1; this->dimensions[2] = d2; this->dimensions[3] = d3;
   this->len = d0 * d1 * d2 * d3;
   this->check_size();
  }
/*
  tensor( const int d0, const int d1, const int d2, const int d3, const int d4 ){
   this->dimensions.fill(0);
   this->dimensions[0] = d0; this->dimensions[1] = d1; this->dimensions[2] = d2; this->dimensions[3] = d3; this->dimensions[4] = d4;
   this->len = d0 * d1 * d2 * d3 * d4;
   this->check_size();
  }
  tensor( const int d0, const int d1, const int d2, const int d3, const int d4, const int d5 ){
   this->dimensions.fill(0);
   this->dimensions[0] = d0; this->dimensions[1] = d1; this->dimensions[2] = d2; this->dimensions[3] = d3; this->dimensions[4] = d4; this->dimensions[5] = d5;
   this->len = d0 * d1 * d2 * d3 * d4 * d5;
   this->check_size();
  }
  tensor( const int d0, const int d1, const int d2, const int d3, const int d4, const int d5, const int d6 ){
   this->dimensions.fill(0);
   this->dimensions[0] = d0; this->dimensions[1] = d1; this->dimensions[2] = d2; this->dimensions[3] = d3; this->dimensions[4] = d4; this->dimensions[5] = d5; this->dimensions[6] = d6;
   this->len = d0 * d1 * d2 * d3 * d4 * d5 * d6;
   this->check_size();
  }
  tensor( const int d0, const int d1, const int d2, const int d3, const int d4, const int d5, const int d6, const int d7 ){
   this->dimensions.fill(0);
   this->dimensions[0] = d0; this->dimensions[1] = d1; this->dimensions[2] = d2; this->dimensions[3] = d3; this->dimensions[4] = d4; this->dimensions[5] = d5; this->dimensions[6] = d6; this->dimensions[7] = d7;
   this->len = d0 * d1 * d2 * d3 * d4 * d5 * d6 * d7;
   this->check_size();
  }
  tensor( const int d0, const int d1, const int d2, const int d3, const int d4, const int d5, const int d6, const int d7, const int d8 ){
   this->dimensions.fill(0);
   this->dimensions[0] = d0; this->dimensions[1] = d1; this->dimensions[2] = d2; this->dimensions[3] = d3; this->dimensions[4] = d4; this->dimensions[5] = d5; this->dimensions[6] = d6; this->dimmensions[7] = d7;
   this->dimensions[8] = d8;
   this->len = d0 * d1 * d2 * d3 * d4 * d5 * d6 * d7 * d8;
   this->check_size();
  }
  tensor( const int d0, const int d1, const int d2, const int d3, const int d4, const int d5, const int d6, const int d7, const int d8, const int d9 ){
   this->dimensions.fill(0);
   this->dimensions[0] = d0; this->dimensions[1] = d1; this->dimensions[2] = d2; this->dimensions[3] = d3; this->dimensions[4] = d4; this->dimensions[5] = d5; this->dimensions[6] = d6; this->dimensions[7] = d7;
   this->dimensions[8] = d8; this->dimensions[9] = d9;
   this->len = d0 * d1 * d2 * d3 * d4 * d5 * d6 * d7 * d8 * d9;
   this->check_size();
  }
*/

public:
  void check_size(){
   {
    const int size = store.size();
    if( len > size ){
     cout << " tensor construction error: len > size. " << endl;
     cout << " requested len: " << len << "\tcompiling-time size:" << size << endl;
     abort();
    }
   }
   if( len < 0 ){
    cout << " tensor construction error: len < 0 " << endl;
    abort();
   }
  }

public:
  const int get_dim( const int ind ) const { return this->dimensions.at(ind); }
  int get_dim( const int ind ) { return this->dimensions.at(ind); }

  const int get_len() const { return this->len; }
  int get_len() { return this->len; }

  T& operator() ( const int i0 )
     { return this->store.at(i0); }
  T& operator() ( const int i0, const int i1 )
     { return this->store.at(i1 * dimensions[0] + i0); }
  T& opeartor() ( const int i0, const int i1, const int i2 )
     { return this->store.at( i2 * dimensions[1] * dimensions[0] + i1 * dimensions[0] + i0 ); }
  T& operator() ( const int i0, const int i1, const int i2, const int i3 ) 
     { return this->store.at( i3 * dimensions[2] * dimensions[1] * dimensions[0] + i2 * dimensions[1] * dimensions[0] + i1 * dimensions[0] + i0 ); }

private:
  array< T, N > store;
  array< int, 10 > dimensions;
  int len;

}

#else

template < typename T >
class tensor
{

private:
   vector<T> data;
   vector<int> dimensions_;
   size_t size_;

public:                  // Constructors for different dimensions
    tensor(){};
    tensor( const int d0 );								// 1-d
    tensor( const int d0, const int d1 );						// 2-d
    tensor( const int d0, const int d1, const int d2 );					// 3-d
    tensor( int d0, int d1, int d2, int d3 );			// 4-d
    tensor( const int d0, const int d1, const int d2, const int d3, const int d4 );	// 5-d
    tensor( const int d0, const int d1, const int d2, const int d3, const int d4, const int d5 );  // 6-d
    ~tensor(){};

public:
    // data access
    vector<T>& get_data(){ return this->data; }
    // dimension access
    vector<int>& dimensions() { return this->dimensions_; }

    // size access
    size_t& size() { return this->size_; }

    // element access
    T& element( const int i0 );
    T& element( const int i0, const int i1 );
    T& element( const int i0, const int i1, const int i2 );
    T& element( const int i0, const int i1, const int i2, const int i3 );
    T& element( const int i0, const int i1, const int i2, const int i3, const int i4 );
    T& element( const int i0, const int i1, const int i2, const int i3, const int i4, const int i5 );

    // element access operator()
    T& operator()( const int i0 ){ return element( i0 ); }
    T& operator()( const int i0, const int i1 ){ return element( i0, i1 ); }
    T& operator()( const int i0, const int i1, const int i2 ){ return element( i0, i1, i2 ); }
    T& operator()( const int i0, const int i1, const int i2, const int i3 ){ return element( i0, i1, i2, i3 ); }
    T& operator()( const int i0, const int i1, const int i2, const int i3, const int i4 ){ return element( i0, i1, i2, i3, i4 ); }
    T& operator()( const int i0, const int i1, const int i2, const int i3, const int i4, const int i5 ){ return element( i0, i1, i2, i3, i4, i5 ); }

public:
    // get contents
    const vector<int> get_dimensions() const { return this->dimensions_; }
    const size_t get_size() const { return this->size_; }


private:
    void tensor_out_of_range( const int this_dim, const std::out_of_range& oor );

};

template < typename T >
inline void tensor<T>::tensor_out_of_range( const int this_dim, const out_of_range& oor ){
  cout << " exception: tensor::element() :: out_of_range :: what() = " << oor.what() << endl;
  cout << " requested dimension = " <<  this_dim << "   actual dimension = " << this->dimensions().size() << endl;
}

template < typename T > 
inline T& tensor<T>::element( const int i0 )
{
   try
   {
      assert( dimensions().size() == 1 );
      return this->data.at(i0);
   }
   catch ( const out_of_range& oor )
   {
     this->tensor_out_of_range( 1, oor );
   }

}

template < typename T > 
inline T& tensor<T>::element( const int i0, const int i1 )
{
   try
   {
     assert( dimensions().size() == 2 );
     return this->data.at( i0 * dimensions().at(1) + i1 );
   }
   catch ( const out_of_range& oor )
   {
     this->tensor_out_of_range( 2, oor );
   }
}

template < typename T > 
inline T& tensor<T>::element( const int i0, const int i1, const int i2 )
{
   try
   {
     assert( dimensions().size() == 3 );
     return this->data.at( i0 * dimensions().at(1) * dimensions().at(2) + 
                           i1 * dimensions().at(2) + 
                           i2 );
   }
   catch ( const out_of_range& oor )
   {
     this->tensor_out_of_range( 3, oor );
   }
}

template < typename T > 
inline T& tensor<T>::element( const int i0, const int i1, const int i2, const int i3 )
{
  try
  {
    assert( dimensions().size() == 4 );
    return this->data.at( i0 * dimensions().at(1) * dimensions().at(2) * dimensions().at(3) + 
                          i1 * dimensions().at(2) * dimensions().at(3) + 
                          i2 * dimensions().at(3) + 
                          i3  );
  }
  catch ( const out_of_range& oor )
  {
    this->tensor_out_of_range( 4, oor );
  }
}

template < typename T > 
inline T& tensor<T>::element( const int i0, const int i1, const int i2, const int i3, const int i4 )
{
  try
  {
    assert( dimensions().size() == 5 );
    return this->data.at( i0 * dimensions().at(1) * dimensions().at(2) * dimensions().at(3) * dimensions().at(4) + 
                          i1 * dimensions().at(2) * dimensions().at(3) * dimensions().at(4) + 
                          i2 * dimensions().at(3) * dimensions().at(4) + 
                          i3 * dimensions().at(4) + 
                          i4 );
  }
  catch ( const out_of_range& oor )
  {
    this->tensor_out_of_range( 5, oor );
  }

}

template < typename T >
inline T& tensor<T>::element( const int i0, const int i1, const int i2, const int i3, const int i4, const int i5 )
{
  try
  {
    assert( dimensions().size() == 6 );
    return this->data.at( i0 * dimensions().at(1) * dimensions().at(2) * dimensions().at(3) * dimensions().at(4) * dimensions().at(5) + 
                          i1 * dimensions().at(2) * dimensions().at(3) * dimensions().at(4) * dimensions().at(5) + 
                          i2 * dimensions().at(3) * dimensions().at(4) * dimensions().at(5) + 
                          i3 * dimensions().at(4) * dimensions().at(5) + 
                          i4 * dimensions().at(5) + 
                          i5 );
  }
  catch ( const out_of_range& oor )
  {
    this->tensor_out_of_range( 6, oor );
  }
}


// Constructors
template < typename T > 
inline tensor<T> :: tensor( const int d0 )
{
  dimensions().push_back(d0);
  this->data.resize( d0 );
  this->size_ = data.size();
}

template < typename T > 
inline tensor<T> :: tensor( const int d0, const int d1 )
{
  dimensions().push_back(d0);
  dimensions().push_back(d1);
  this->data.resize( d0 * d1 );
  this->size_ = data.size();
}

template < typename T > 
inline tensor<T> :: tensor( const int d0, const int d1, const int d2 )
{
  dimensions().push_back(d0);
  dimensions().push_back(d1);
  dimensions().push_back(d2);
  this->data.resize( d0 * d1 * d2 );
  this->size_ = data.size();
}

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
#endif

} // end of iqs

#endif
