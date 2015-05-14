#include "operator.h"

namespace fci{

struct op
{
public:
  virtual_op(){};
  virtual_op( const op basis_op, const int ind ){
   this->optr = basic_op;
   this->ind_site = ind;
  }
  ~virtual_op(){};

public:
  const op get_basic_op() const { return this->basic_op; }
  op get_basic_op() { return this->basic_op; }
  const int get_ind_site() const { return this->ind_site; }
  int get_ind_site() { return this->ind_site; }

  void set_basic_op( const op basic_op ) { this->basic_op = basic_op; }
  void set_ind_site( const int ind ) { this->ind_site = ind; }

private:
  op basic_op;
  int ind_site;

};

}
