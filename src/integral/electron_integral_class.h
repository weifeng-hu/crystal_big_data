#ifndef TWO_ELECTRON_INTEGRAL_H
#define TWO_ELECTRON_INTEGRAL_H

#include <string>
#include "tensor/tensor_class.h"

#define NLIMIT2 = NORB_LIMIT * NORB_LIMIT
#define NLIMIT4 = NORB_LIMIT * NORB_LIMIT * NORB_LIMIT * NORB_LIMIT

using namespace std;

namespace iquads {

namespace integral {

class oe_int : public iquads :: tensor< double, NLIMIT2 >
{
public:
  oe_int( const int dim ) : iquads :: tensor< double, NLIMIT > ( dim, dim )
  {
   this->norb = dim;
   this->store.fill(0.0e0);
  }
  ~oe_int(){};

public:
  void read_binary(){};
  void read_txt( const string filename );
  void read_fcidump( const string filename );

public:
  const int get_norb() const { return this->norb; }
  int get_norb() { return this->norb; }
  int& set_norb() { return this->norb; }

private:
  int norb;

}; // end of class oe_int

class te_int : public iquads :: tensor< double, NLIMIT4 >
{
public:
  te_int( const int dim ) : iquads :: tensor< double, NLIMIT > ( dim, dim, dim, dim )
  { 
   this->norb = dim;
   this->store.fill(0.0e0);
  }
  ~te_int(){};

public:
  void read_binary(){};
  void read_txt( const string filename );
  void read_fcidump( const string filename );

public:
  const int get_norb() const { return this->norb; }
  int get_norb() { return this->norb; }
  int& set_norb() { return this->norb; }

private:
  int norb;

}; // end of class te_int

} // end of integral

} // end of iquads

#endif
