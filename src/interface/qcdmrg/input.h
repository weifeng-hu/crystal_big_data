// input.h
// header for Class Input
// Stores the options and write the Input file for QCDMRG module

namespace ithaca { namespace interface { namespace qcdmrg {

struct schedule{
  int iter_index;
  int M;
  double david_tol;
  double noice;
}; // end of structure schedule

class Input
{
public:
  Input( ithaca::interfaces::qcdmrg::cmd_options cmd_opt ) : ithaca::dmrg::Input( cmd_opt ) 
  ~Input();


// Essential parameters for QCDMRG Input files
public:
  bool defaulthf;
  bool bigdavid;
  bool docd;
  bool onepdm;
  bool twopdm;

  int norb;
  int na,nb;
  int num_schedule;
  int nroot;
  int maxiter
  int twodot_to_onedot;

  float* weights;
  double* sweep_tol;

  std::string file_one_int;
  std::string file_two_int;

  schedule* iter;

public:
  int write_config();

}; // end of class Input

} } } // end of ithaca::interface::qcdmrg
