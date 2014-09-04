#include <iostream>
#include <utility>
#include "fci.h"

using namespace std;

namespace fci {

wavefunction& wavefunction::multiplyQC()
{

  // one_electron term


  // two_electron term
  

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
