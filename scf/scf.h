// file scf.h 
// header for scf module

namespace ithaca { namespace scf {

const char * const module_name = "scf";

class Input_AO;
class SCF ;

extern "C" {
void scf_( int* nele, int* norb, int* nbas, double* nuclear_repulsion, double* s,double* hcore, double* eri, double* c, double* E, double* HF_energy );
}
void scf_core( int* nele, int* norb, int* nbas, double* nuclear_repulsion, double* s, double* hcore, double* eri, double* c, double* E, double* HF_energy); 

int rhf_main( Input_AO scf_inp );

} } // end of ithaca
