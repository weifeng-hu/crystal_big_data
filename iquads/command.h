#include <string>
#include <vector>

using namespace std;

namespace iquads {

void print_little_help( int iopt );
void print_help();

struct instruction
{

private:
  string instruct_name;


};

class cmd_options {

public:
  cmd_options( int argc, char* argv[] );
  ~cmd_options(){};

public:
  setup_instructions();

private:
  vector< instruction > instruct;
  
  std::string path_exec;
  std::string dir_exec;

  std::string input_filename;
  char* _input_filename;
  bool input_is_set;

  std::string output_filename;
  char* _output_filename;
  bool output_is_set;

  std::string infile_path;
  char* _infile_path;

  std::string dir_work;
  char* _dir_work;
  bool dir_work_is_set;
  std::string get_workdir();

  std::string dir_scratch;
  char* _dir_scratch;
  bool dir_scratch_is_set;

};

} // end of iquads::cmd_options
