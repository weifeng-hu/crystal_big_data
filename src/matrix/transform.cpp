#include <iostream>
#include "square_matrix.h"

namespace iqs {

namespace matrix {

extern "C"
{
 void oei_transform_( int* nbas, int* norb, double* u, double* oei1, double* oei2 );
}

square_matrix square_matrix::transform( square_matrix& u_mtr )
{

  int nbas = this->get_dim();
  int norb = u_mtr.get_dim();

  iqs::matrix::square_matrix new_mtr( this->get_dim() );

  double* oei1 = new double [ nbas*nbas ]; for( int i = 0; i < nbas; i++ ){ for( int j = 0; j < nbas; j++ ){ oei1[ i * nbas + j ] = this->data.at(i).at(j); }}
  double* u = new double [ nbas*nbas ]; for( int i = 0; i < nbas; i++ ){ for( int j = 0; j < nbas; j++ ){ u[ i * nbas + j ] = u_mtr(i,j); }}
  double* oei2 = new double [ nbas*nbas ];

  oei_transform_( &nbas, &norb, u, oei1, oei2 );
  for( int i = 0; i < nbas; i++ ){ for( int j = 0; j < nbas; j++ ){  new_mtr(i,j) = oei2[ i * nbas + j ]; }}

//  cout << "new mtr element " << new_mtr( 81, 81 ) << endl;

  return new_mtr;
}

}

}
