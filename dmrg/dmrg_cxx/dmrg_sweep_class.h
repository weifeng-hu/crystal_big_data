#ifndef DMRG_SWEEP_CLASS_H
#define DMRG_SWEEP_CLASS_H

namespace iqs { namespace dmrg {

class sweep_class
{

private:
  int nsite_;
  int np_;
  int ns_;
  vector<double> sweep_energy_;

private:
  int nsite_l_;
  int nsite_r_;
  int step_;

  bool converged_;

public:
  sweep_class (){};
  ~sweep_class(){};

// algorithms
public:
  void warm_up();
  void do_one_dot();
  void do_two_dot();
  void do_one_pdm();
  void do_two_pdm();

public:
  int& nsite(){ return this->nsite_; }
  int& np()   { return this->np_ ;   }
  int& ns()   { return this->ns_ ;   }
  vector<double>& sweep_energy(){ return this->sweep_energy_; }

};

} } // end of iqs::dmrg

#endif
