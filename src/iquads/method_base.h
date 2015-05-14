#include <string>

using namespace std;

namespace iquads{

class method_base
{
public:
  string get_method_tag() const
    { return this->method_tag_; }
  string& method_tag()
    { return this->method_tag_; }

  string get_input_name() const 
    { return this->input_name_; }
  string& input_name()
    { return this->input_name_; }

  string get_output_name() const
    { return this->output_name_; }
  string& output_name()
    { return this->output_name_; }

  bool is_ready() const 
    { return this->is_read_; }
  void set_ready( const bool ready )
    { this->is_ready_ = ready; }
  bool is_external() const 
    { return this->is_external_; } 
  void set_external( const bool external )
    { this->is_external_ = external; }

private:
  string method_type_;
  string input_name_;
  string output_name_;
  bool is_ready_;
  bool is_external_;

}

}
