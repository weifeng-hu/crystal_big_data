namespace cphf { 

class cscphf{
public:
  cscphf( cphf::qcread::psiread psird, cphf::scf scf_data);
  ~cscphf(){};

public:
  int ncoord;
  int nbas, norb;
  int nocc, nvir;

  double* s;
  double* hcore_mo;
  double* eri_mo;
  double* OrbEns;

  double* c;

  double** s_deriv1;
  double** sa_mo;

  double** t_deriv1;
  double** v_deriv1;
  double** hcore_deriv1;

  double** ha_mo;
  double** eri_deriv1;
  double** eria_mo;

  double** Fa;
  double* A;
  double** B;
  double** U;
  double* E;

  double* a;
  double* x;
  double* b;

};

}
