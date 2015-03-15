#ifndef CRYSTAL_INFO_H
#define CRYSTAL_INFO_H

#include <tuple>
#include <string>
#include "structure.h"

namespace iquads {

namespace crystal {

struct crystal_info
{
using namespace std;
public:
  void read( string input ){};

public:
  unit_cell get_unit_cell() const { return this->unit_cell; }
  unit_cell& set_unit_cell() { return this->unit_cell; }

  double get_cutoff() const { return this->cutoff; }
  double& set_cutoff() { return this->cutoff; }

  tuple<int, int, int> get_times() const { return this->times; }
  tuple<int, int, int>& set_times() { return this->times;}

private:
  unit_cell primary;
  double cutoff;
  tuple<int, int, int> times; 

};

}

}

#endif
