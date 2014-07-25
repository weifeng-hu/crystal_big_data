#ifndef FC_FORT_H
#define FC_FORT_H

namespace iqs { namespace matrix {

extern "C"
{
  void eigtql2_( int* dim, double* eigvec, double* eigval );
  void oei_transform_( int* nbas, int* norb, double* c, double* oei1, double* oei2 );
  void tei_transform_( int* nbas, int* norb, double* c, double* tei1, double* tei2 );
}

} } // end of iqs::matrix 

#endif
