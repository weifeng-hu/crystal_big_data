#include <string>

namespace iquads {

// provide data structure for different types of solutions
struct solution_base
{
public:
  solution_base( const string tag )
  {
    this->typetag = tag;
    this->solved = false;
  }

public:
  string get_typetag() const 
    { return this->solution_type_tag; }
  string& set_typetag()
    { return this->solution_type_tag; }
  bool is_solved() const
    { return this->solved; }
  void is_solved()
    { this->solved = true; }

protected:
  string typetag_;
  bool is_solved_;

}; // end of solution_base

} // end of iquads
