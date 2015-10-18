#ifndef WAVEFUNCTION_BASE_H
#define WAVEFUNCTION_BASE_H

namespace iquads {

class Wavefunction_Base
{

protected:
  virtual 
   WavefunctionTranspose_Base< Wavefunction_Base* > get_transpose()
  {  }

  virtual
   WavefunctionTranspose_Base< Wavefunction_Base* > 
    operator< ( Wavefunction_Base* wavefunction_ptr )
  {  }

  Wavefunction_Base* operator> () { return this; }

}; // end of class Wavefunction_Base

} // end of namespace iquads

#endif
