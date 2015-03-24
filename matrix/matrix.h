#include <vector>

namespace iquads{

namespace matrix{

struct dmatrix{
using namespace std;
public:
  matrix( size_t i, size_t j ){
   assert( i > 0 );
   assert( j > 0 );
   this->dim1 = i;
   this->dim2 = j;
   this->length = i * j;
   store.resize( length );
  }

public:
 double& operator() ( int i, int j ) { 
  assert( i >= 0 && i < dim1 );
  assert( j >= 0 && j < dim2 );
  return this->set_element( i, j ); 
 }

private:
 double& set_element( int i, int j ){
  return store.at( i * dim2 + j );
 }

private:
 vector<double> store;
 size_t dim1, dim2;
 size_t length;

};

}

}
