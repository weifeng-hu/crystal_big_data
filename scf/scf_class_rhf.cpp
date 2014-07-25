#include <iostream>
#include <string>
#include <vector>
#include "scf_class_rhf.h"

using namespace std;

namespace ithaca { namespace scf {

rhf::rhf( ithaca::scf::Input_AO scf_inp )
{

  this->nao = scf_inp.nbas;
  this->nmo = scf_inp.norb;

  this->c       = new dtensor( nao, nmo );
  this->epsilon = new dtensor( nmo );
  this->p       = new dtensor( nao, nao );

  this->x      = new dtensor( nao, nao );
  this->s_sqrt = new dtensor( nao, nao );
  this->fock   = new dtensor( nao, nao );
  this->g      = new dtensor( nao, nao );

}

} } // end of ithaca::scf
