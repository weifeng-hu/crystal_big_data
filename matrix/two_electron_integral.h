#ifndef TWO_ELECTRON_INTEGRAL_H
#define TWO_ELECTRON_INTEGRAL_H

#include <string>
#include "tensor/tensor_class.h"

#define inh 1

using namespace std;

namespace iqs {

//template class iqs::tensor<double>;

namespace matrix {

#if inh

class two_electron_integral
{
private:
  iqs::tensor<double> data;

public:
  two_electron_integral( const int dim ) : data ( dim, dim, dim, dim ) { };
  ~two_electron_integral(){};

public:
  iqs::tensor<double>& get_data(){ return this->data; }
  double& operator() ( const int i, const int j, const int k, const int l ){ return this->data( i, j, k ,l ); }

public:
  void read_integral( const string filename );
  void read( const string filename );
  void read_r( const string filename );


};

#else

class two_electron_integral:
public iqs::tensor<double>
{

private:
  int norb_;

public:
  two_electron_integral( const int dim ) : iqs::tensor<double> ( dim, dim, dim, dim ){ this->norb_ = dim; }
  ~two_electron_integral(){};

public:
  void read_integral( const string filename );

};


#endif


} // end of matrix

} // end of iqs

#endif
