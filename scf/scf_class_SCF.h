
namespace ithaca { namespace scf {

class SCF : public ithaca::scf::Input_AO {

public:
  SCF( ithaca::scf::cmd_options cmd_opt );
  ~SCF(){ };

public:
  int nbas, norb;
  int nele;

  double* hcore_mo;
  double* eri_mo;

  double* C;
  double* F;
  double* E;

  double HF_energy;

}; // end of SCF

} } // end of ithaca::scf
