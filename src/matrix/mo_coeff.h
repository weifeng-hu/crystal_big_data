#include <string>
#include "tensor/tensor_class.h"

#ifndef MO_COEFF_H
#define MO_COEFF_H

using namespace std;

namespace iqs { namespace matrix {

class mo_coeff
{
private:
  iqs::tensor<double> data;
  int nbas, norb;

public:
  mo_coeff( const int d1, const int d2 ) : nbas(d1), norb(d2), data( d1, d2 ) {}; 
  ~mo_coeff(){}

public:
  iqs::tensor<double>& get_data(){ return this->data; }
  double& operator() ( const int i, const int j ) { return this->data( i, j ); }

public:
  void read( const string filename );
  void read_r( const string filename );

};

} } // end of iqs::matrix

#endif
