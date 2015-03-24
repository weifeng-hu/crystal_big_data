#ifndef FRAGMENT_H
#define FRAGMENT_H

#include <vector>
#include <tuple>
#include <string>
#include "utilities/solid_gen/atom.h"

using namespace std;

namespace iquads{

namespace crystal{

struct fragment{

public:
 vector<atom>& set_store(){ return this->store_; }

 string get_element ( size_t i ){
  return store_.at(i).get_element();
 }
 tuple< double, double, double > get_coord( size_t i )
 {
  double x = store_.at(i).get_x();
  double y = store_.at(i).get_y();
  double z = store_.at(i).get_z();
  tuple< double, double, double > retval = 
     make_tuple (x, y, z);
  return retval;
 }

private:
 vector<atom> store_;

};

}

}

#endif
