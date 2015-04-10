#ifndef NUMNAC_CALC_H
#define NUMNAC_CALC_H

#include <vector>
#include <string>
#include <iostream>
#include "utilities/num_nac/atom.h"

using namespace std;

namespace iquads{

namespace num_nac{

struct numnac_calc
{
public:
  numnac_calc(){
   eng_ref.resize(0);
   eng_disp.resize(0);
   this->molecule.resize(0);
   this->natom = -1;
   this->nelec = -1;
   this->norb  = -1;
   this->sz    = -1;
   this->s_square = -1;
  }

public:
  void read( string filename );
  void compute_reference();
  void compute_displacement();
  void calc_numnac();

public:
  vector<atom> get_molecule() const { return this->molecule; }
  int get_natom() const { return this->natom; }
  int get_nelec() const { return this->nelec; }
  int get_norb() const { return this->norb; }
  int get_sz() const { return this->sz; }
  int get_s_square() const { return this->s_square; }

private:
  vector<double> eng_ref;
  vector< vector< vector< vector<double> > > > eng_disp;
  vector<atom> molecule;
  int natom;
  int nelec;
  int norb;
  int sz;
  int s_square;

};

}

}

#endif
