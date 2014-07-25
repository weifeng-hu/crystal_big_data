
namespace ithaca { namespace interface {

struct schedule{
 int iter;
 int M;
 double david_threshold;
 double noise;
}

class qcdmrg_class{
public:
  qcdmrg_class( ithaca::cmd_options cmd_opt );
  ~qcdmrg_class(){};

public:
  int norb, na, nb;
  int ncore, nact;

public:
  double* hcore_mo;
  double* eri_mo;

  double* one_pdm;
  double* two_pdm;

public:
  std::string conf;
  std::string conf_genblock;
  std::string conf_onepdm;
  std::string conf_twopdm;
  char* _conf;
  char* _conf_genblock;
  char* _conf_onepdm;
  char* _conf_twopdm;

public:
  int n_schdl;
  schedule* schdl;
  int nroots;
  double* weights;
  int maxiter;
  std::string oneintegral;
  char* _oneintegral;
  std::string twointegral;
  char* _twointegral;

  int two_to_one;
  double sweep_tol;

}; // end of qcdmrg_class

} } // end of ithaca::interface
