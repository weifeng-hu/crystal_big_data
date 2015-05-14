#include <string>
#include <vector>
#include "cmd_options.h"

using namespace std;

namespace ithaca { namespace scf {

#define DEFAULT_DIIS false
#define DEFAULT_SCF_TOL 1.0e-9
#define DEFAULT_GUESS "core"

struct coordinate
{
  std::string element;
  char* _element;
  double x,y,z;
};

class Input_AO {
public:
  Input_AO( ithaca::scf::cmd_options cmd_opt );
  ~Input_AO(){};

public:
  int natom;
  int nbas,norb;
  int nocc,nvir;
  int nele;
  double ns;
  int na,nb;

public:
  std::string unit;
  char* _unit;

public:
  int diis;
  double scf_tol;
  std::string init_guess;

  double nuclear_repulsion;
  double* s;
  double* hcore_ao;
  double* eri_ao;

public:
  std::vector<ithaca::scf::coordinate> coord;

}; // end of Input_AO

} } // end of ithaca::scf
