#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <iostream>
#include <vector>

#include "integral.h"

using namespace std;

namespace fci{

struct block{
public:
  block(){};
  block( const int _nroots ){
   this->resize( _nroots );
  }
  ~block(){};

public:
  void resize( const int _nroots ){
    this->nroots = _nroots;
    this->energy.resize(nroots);
  }

public:
  const vector<double> get_energy() const { return this->energy; }
  vector<double>& set_energies() { return this->energy; }

  const int get_particle() const { return this->particle; }
  int& set_particle() { return this->particle; }

  const int get_sz() const { return this->sz; }
  int& set_sz() { return this->sz; }

  const int get_nroots() const { return this->nroots; }
  int& set_nroots() { return this->nroots; }

private:
  vector<double> energy;
  int particle;
  int sz;
  int nroots;

}

struct config
{
public:
  config(){};
  config( string _configfile );
  ~config(){};

private:
  void read();
  void read_integral();

public:
  const two_integral get_two_integral() const { return this->v2; }
  two_integral& set_two_integral(){ return this->v2; }
  const one_integral get_one_integral() const { return this->v1; }
  one_integral& set_one_integral(){ return this->v1; }

  const double get_core_energy() const { return this->core_energy; }
  double& set_core_energy() { return this->core_energy; }

  const string get_dumpfile() const { return this->dumpfile; }
  string& set_dumpfile() { return this-dumpfile; }

  const vector<block> get_blocks() const { return this->blocks; }
  vector<block>& set_blocks() const { return this->blocks; }

  const int get_norb() { return this->norb; }
  int& set_norb() { return this->norb; }

  const int nblock() { return this->nblock; }
  int& nblock(){ return this->nblock; }
  
private:
  two_integral v2;
  one_integral v1;
  double core_energy;

  vector<block> blocks;
  string configfile;
  string dumpfile;
  double lanczos_tol;
  int norb;
  int nblock;

};

}

#endif
