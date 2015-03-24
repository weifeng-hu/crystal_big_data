#ifndef CRYSTAL_INFO_H
#define CRYSTAL_INFO_H

#include <tuple>
#include <string>
#include "utilities/solid_gen/unit_cell.h"

using namespace std;

namespace iquads{

namespace crystal{

struct crystal_info
{

public:
  void read( string input );

public:
  unit_cell get_unit_cell() const { return this->primitive; }
  unit_cell& set_unit_cell() { return this->primitive; }

  double get_cutoff() const { return this->cutoff; }
  double& set_cutoff() { return this->cutoff; }

  tuple<int, int, int> get_nunits() const { return this->n_units; }
  tuple<int, int, int>& set_nunits() { return this->n_units;}

  string get_cut_method() { return this->cut_method; }

private:
  unit_cell primitive;
  double cutoff;
  string cut_method;
  tuple<int, int, int> n_units; 

};

}

}

#endif
