#include <string>
#include "tensor/tensor_class.h"

#ifndef ONE_ELECTRON_INTEGRAL_H
#define ONE_ELECTRON_INTEGRAL_H

using namespace std;

namespace iquads { namespace matrix {

class one_electron_integral
{
private:
  iquads::tensor<double> data;

public:
  one_electron_integral( const int dim ) : data( dim, dim ) {} ;
  ~one_electron_integral(){}

public:
  iquads::tensor<double>& get_data(){ return this->data; }
  double& operator() ( const int i, const int j ){ return this->data( i, j ); }

public:
  void read( const string filename );
  void read_r( const string filename );

}; 

} }   // end of iqs::matrix

#endif
