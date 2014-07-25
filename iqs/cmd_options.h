// cmd_options.h
// header for cmd_options
// 

#include <string>

namespace ithaca { 

void print_little_help( int iopt );
void print_help();

// ithaca::cmd_options is the most primary command option
// class in the whole program package, it defines the essential 
// prameters including, the path of executive, the working and 
// scratch directories and input/output files.
//
// it is the parent class for other command option class 
// in other parts of the program package

class cmd_options {

public:
  cmd_options( int argc, char* argv[] );
  ~cmd_options(){};

public:
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

} // end of ithaca::cmd_options
