#include "../scf/scf.h"

namespace ithaca { namespace scf {

void scf_core( int* nele, int* norb, int* nbas, double* nuclear_repulsion,
               double* s, double* hcore, double* eri, double* c, double* E, double* HF_energy)
{
  scf_( nele, norb, nbas, nuclear_repulsion, s, hcore, eri, c, E, HF_energy ); 

}

}}
