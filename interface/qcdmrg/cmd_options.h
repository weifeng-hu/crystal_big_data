#include <string>

namespace ithaca { namespace interface { namespace qcdmrg {

class cmd_options : public ithaca::cmd_options
{
public:
  cmd_options( int argc, char* argv[] );
  ~cmd_options(){};

public:
  std::string path_exec;

  std::string dmrg_input;
  char* _dmrg_input;
  bool dmrg_input_is_set;

  std::string dmrg_output;
  char* _dmrg_output;
  bool dmrg_output_is_set;

  std::string work_dir;

};

} } }  // end of ithaca::interface::qcdmrg
