#include <vector>
#include "../tensor/tensorclass.h"
#include "scf_class_input_ao.h"

namespace ithaca { namespace scf {

class rhf
{
public:
  rhf( ithaca::scf::Input_AO scf_inp );
  ~rhf(){};

public:
  int nbas, norb;		// number of orbitals
  int nao, nmo;			// have the same meaning as above
  int nele;			// number of electrons
  int nocc, nvir;		// number of occupied, virtual orbitals

  int nirrep;			// number of irreducible representations
  std::vector<int> irreps;	// stores the irreducible representations, used for manipulating
  std::vector<char> _irreps;	// stores the name of irreducible representations, used for printing

  double nuclear_rep;		// nuclear repulsion energy

public:				// AO-based elements
   dtensor* s_ao;		// Overlap
   dtensor* hcore_ao;			// Core Hamiltonian
   dtensor* tei_ao;			// Two-electron repulsion integrals

public:	
   dtensor* c;
   dtensor* epsilon;
   dtensor* p;

public:				// Matrices used in calculation
   dtensor* x;
   dtensor* s_sqrt;
   dtensor* fock;
   dtensor* g;

public:
//  oe_matrix hcore_mo;
//  oe_matrix s_mo;
//  oe_matrix fock_mo;
//  te_tensor tei_mo;

public:
   void calc_p();
   void calc_g();
   void calc_fock();

};

} } // end of ithaca::scf
