#include <iostream>
#include <utility>
#include "fci.h"

using namespace std;

namespace fci {

wavefunction& wavefunction::multiplyQC()
{

  // wavefunction
  wavefunction Hv;

  // one_electron term
  {
   wavefunction cdv;
   for( int i = 0; i < nsite; i++ ){
    wavefunction dv;
    for( int j = 0; j < nsite; j++ ){
      double int_v = v1( i, j );
      dv += int_v * des(j) * v;
    }
    cdv += cre(i) * dv;
   }
  Hv += cdv;
  }

  // two_electron term
  {
   wavefunction ccddv;
   for( int i = 0; i < nsite; i++ ){
    wavefunction cddv;
    for( int j = 0; j < nsite: j++ ){
     wavefunction ddv;
     for( int k = 0; k < nsite; k++ ){
      wavefunction dv;
      for( int l = 0; l < nsite; l++ ){
       double int_v = v2(i, j, k, l);
       dv += des(l) * v;
      }
      ddv += des(k) * dv;
     }
     cddv += cre(j) * ddv;
    }
    ccddv += cre(i) * cddv;
   }
  Hv += ccddv;
  }

  return Hv;

}

wavefunction& wavefunction::multiplyPPP()
{

  cout << " multiplyH for PPP not implemented " << endl;
  abort();

}

wavefunction& wavefunction::multiplyHBD()
{

  cout << " multimpyH for Hubbard not implmented " << endl;
  abort();

}

wavefunction& wavefunction::multiplyH( const int h_type )
{

  wavefunction wf( this->norb, this->particle, this->sz );

  if( h_type == QC ){
   retval = multiplyQC();
  }
  else if( h_type == PPP ){
   retval = multiplyPPP():
  }
  else if( h_type == HUBBARD ){
   retval = multiplyHBD( this );
  }

  return std::move( wf );

}
