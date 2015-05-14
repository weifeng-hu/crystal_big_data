
namespace ithaca { namespace anaytical { 

class cmd_options
{
public:
  cmd_options( int argc, char* argv[] );
  ~cmd_options(){};

public:
  std::string exec_path;
  char* _exec_path;
  bool exec_path_is_set;

  std::string work_dir;
  char* _work_dir;
  bool work_dir_is_set;

  std::string scratch_dir;
  char* _scratch_dir;
  bool scratch_dir_is_set;

  std::string dmrg_exec;
  char* _dmrg_exec;
  bool dmrg_exec_is_set;

};


} }
