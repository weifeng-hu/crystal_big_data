#include <array>
#include <iostream>
#include <algorithm>

using namespace std;

namespace fci{

struct op
{
public:
  op(){};
  ~op(){};

public:
  int get_len(){ return this->len; }
  int get_dim(){ return this->dim; }

  const int get_len() const { return this->len; }
  const int get_dim() const { return this->dim; }

  array<int, 4> get_store_p() { return this->store_p; }
  const array<int, 4> get_store_p() { return this->store_p; }

  array<int, 4> get_store_sz() { return this->store_sz; }
  const array<int, 4> get_store_sz() const { return this->store_sz; }

  void set_store_d( const array< double, 16 > store ){
   if( store.size() != this->len ){
     std::cout << " incompatible operator length" << std::endl;
   }
   std::copy( store.begin(), store.end(), this->store_d.begin() );
  }

  // return an operator which is designated for orbital i
  const virtual_op operator() ( const int i ){
   return virtual_op( *this, i );
  }

private:
  array<double, 16> store_d;
  const array<int, 4> store_p = { 0, 1, 1, 2 };
  const array<int, 4> store_sz = { 0, 1, -1, 0 };
  const int len = 16;
  const int dim = 4;

};

}
