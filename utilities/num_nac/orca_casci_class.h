#ifndef ORCA_INPUT_H
#define ORCA_INPUT_H

#include <string>
#include <vector>
#include "utilities/num_nac/atom.h"

using namespace std;

namespace iquads{

namespace num_nac{

struct orca_casci
{
public:
  orca_casci()
  {
   atomlist.resize(0);
   weights.resize(0);
   orca_exe = "not set";
   orca_input = "not set";
   nelec = -1;
   norb = -1;
   mult = -1;
   nroots = -1;
   maxiter = -1;
  }

public:
  void set_casci( vector<int> weights_, int nele_, int norb_, int, s_ )
  {
    this->weights = weights_;
    this->nroots = weights_.size();
    this->nelec = nele_;
    this->norb = norb_;
    this->mult = s_;
    this->maxiter = 1;
  }
  void write_orca_input( string filename );

private:
  vector<atom> atomlist;
  vector<double> weights;
  string orca_exe;
  string orca_input;
  int nelec;
  int norb;
  int mult;
  int nroots;
  int maxiter;

};

}

}

#endif
