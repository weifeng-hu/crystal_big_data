namespace cphf {

class geometry_searching
{
public:
  geometry_searching( cphf::qcread::psiread psird, cphf::scf scf_data );
  ~geometry_searching(){};

public:
  int ncoord,natom;
  int nbas, norb,nocc;
  double* grad_enuc;
  double** hcore_deriv1;
  double** eri_deriv1;
  double** s_deriv1;
  double* c;
  double* OrbEns;
  double** coord;

  double* f;
  double* hessian;
  double* q;
  double** q1;

  double* distance;

public:

}; // end of geometry_searching

} // end of cphf
