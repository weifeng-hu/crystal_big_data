#include <vector>
#include "tensor.h"
#include "scf.h"
#include "scf_class_input_ao.h"
#include "scf_class_SCF.h"


ithaca::scf::SCF::SCF( ithaca::scf::cmd_options cmd_opt) 
: ithaca::scf::Input_AO ( cmd_opt )
{

  this->C  = tensor( nbas*norb, this->C );
  this->E  = tensor( norb, this->E );

  ithaca::scf::scf_core( &nele, &norb, &nbas, &nuclear_repulsion, s, hcore_ao, eri_ao, C, E, &HF_energy );

  this->hcore_mo = tensor( nbas*nbas, this->hcore_mo );
  this->eri_mo   = tensor( nbas*nbas*nbas*nbas, this->eri_mo);

}

