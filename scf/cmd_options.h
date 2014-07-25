#include "../ithaca/cmd_options.h"

namespace ithaca { namespace scf {

class cmd_options : public ithaca::cmd_options
{
public:
  cmd_options( int argc, char* argv[] );
  ~cmd_options(){};

public:
  bool diis;
  std::string scf_tol;
  std::string init_guess;

public:
  bool diis_is_set;
  bool scf_tol_is_set;
  bool init_guess_is_set;

};

} }  // end of ithaca::scf
