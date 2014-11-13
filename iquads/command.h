#include "iquads/coordinate.h"
#include "iquads/instruction.h"

using namespace std;

namespace iquads {

struct command
{
public:
  command()
  {
    this->coord.init();
    this->instruct.init();
    this->instruct_key.resize(0);
    this->op_code_name = "iquads";
    this->coord_is_set = false;
    this->instruct_key_is_set = false;
    this->input = "not set";
    this->wordir = "not set";
  };
  ~command(){};

public:
  void read_input( const string input );
  void setup_instructions();

public:
  const coordinate get_coordinate() const 
    { return this->coordinate; }
  coordinate get_coordinate() 
    { return this->coordinate; }
  coordinate& set_coordinate() 
    { return this->coordinate; }

  const string get_op_code_name() const
    { return this->op_code_name; }
  string get_op_code_name()
    { return this->op_code_name; }
  string& set_op_code_name()
    { return this->op_code_name; }

  const string get_input() const 
    { return this->input; }
  string get_input() 
    { return this->input; }
  string& set_input() 
    { return this->input; }

  const string get_workdir() const 
    { return this->workdir; }
  string get_workdir() 
    { return this->workdir; }
  string& set_workdir() 
    { return this->workdir; }

  const bool coordinate_is_set() const 
    { return this->coord_is_set; }
  bool coordinate_is_set() 
    { return this->coord_is_set; }

  const bool instruction_key_is_set() const 
    { return this->instruct_key_is_set; }
  bool instruction_key_is_set() 
    { return this->instruction_key_is_set; }

private:
  coordinate coord;
  instruction instruct;
  vector< string > instruct_key;
  string op_code_name;
  string input;
  string workdir;

  bool coord_is_set;
  bool instruct_key_is_set;

};

} // end of iquads::cmd_options
