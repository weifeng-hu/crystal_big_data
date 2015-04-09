#ifndef CRYSTAL_INFO_H
#define CRYSTAL_INFO_H

#include <tuple>
#include <string>
#include "utilities/solid_gen/unit_cell.h"

using namespace std;

namespace iquads {

namespace crystal {

struct molecular_crystal_info
{
public:

private:
  void reset(){
   this->cell_type_ = "not set"
   this->radius_ = 0.0e0;
  }

public:
  void read( string input );

public:
  molecular_cell get_molecular_cell() const 
   { return this->primitive; }

  double get_radius() const 
   { return this->Radius; }

  array< int, 3 > get_sizes() const 
   { return this->sizes; }

private:
  molecular_cell primitive_;
  string cell_type_;
  double radius_;
  array<int, 3> sizes;
  array<double, 3> angles;
  array<double, 3> lengths;

}; // end of struct molecular_crystal_info

} // end of namespace crystal

} // end of namespace iquads

#endif
