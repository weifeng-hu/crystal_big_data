#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <string>
#include <tuple>
#include <vector>
#include <stdlib.h>

using namespace std;

namespace iquads{

namespace crystal{

template< class unit_cell >
struct super_cell{
public:
 super_cell(){
  this->store_.resize(0);
  this->unit_cell_is_set_ = false;
 }

public:
 void recentralize();
 void set_primitive( unit_cell prim ){
  this->primitive = prim;
  this->unit_cell_is_set_ = true;
 }
 bool unit_cell_is_set() { return unit_cell_is_set_; }

public:
 void generate_cell( size_t la, size_t lb, size_t lc ){
  if( unit_cell_is_set_ == false ){
   cout << " error: unit cell is not defined " << endl;
   abort();
  }
  for( size_t i = 0; i < la; i++ ){
   for( size_t j = 0; j < lb; j++ ){
    for( size_t k = 0; k < lc; k++ ){
     tuple< int, int, int > direction = make_tuple( i, j, k );
     unit_cell cell_copy = primitive.duplicate( direction );
     store_.push_back( cell_copy );
    }
   }
  }
 }
 void generate( tuple<int, int, int> nunits ){
  size_t a = get<0>( nunits );
  size_t b = get<1>( nunits );
  size_t c = get<2>( nunits );
  generate_cell( a, b, c );
 }
 void generate( size_t l ){
  generate_cell( l, l, l );
 }
 void print(){
  cout << "======================================== " << endl;
  cout << " SUPER CELL INFO " << endl;
  for( size_t i = 0; i < store_.size(); i++ ){
   cout << " Unit Cell " << i << endl;
   store_.at(i).print();
  }
  cout << "======================================== " << endl;
 }

private:
 vector< unit_cell > store_;
 unit_cell primitive;
 double len_a, len_b, len_c;
 int na, nb, nc;
 bool unit_cell_is_set_;

};

} // end of crystal

} // end of iquads

#endif
