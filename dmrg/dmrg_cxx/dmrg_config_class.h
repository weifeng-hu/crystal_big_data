#include "dmrg/cmd_option.h"

#ifndef DMRG_CONF_H
#define DMRG_CONF_H

using namespace std;

namespace iqs { namespace dmrg {

struct sweep_schedule
{

  int sweep_;
  int m_;
  double david_tol_;
  double noise_;

public:
  int& sweep() { return this->sweep_; }
  int& m() { return this->m_; }
  double& david_tol() { return this->david_tol_; }
  double& noise() { return this->noise_; }

  const int get_sweep() const { return this->sweep_; }
  const int get_m() const { return this->m_; }
  const double get_david_tol() { return this->david_tol_; }
  const double get_noise() { return this->noise_; }

public:
   void operator= ( sweep_schedule s ){
   this->sweep()     = s.sweep();
   this->m()         = s.m();
   this->david_tol() = s.david_tol();
   this->noise()     = s.noise();
  }

};

class config
{
private:
  int nsite_;
  int np_;
  int na_,nb_;
  int ns_;

  int nroot_;
  vector<double> weights_;

  int nschedule_;
  vector< sweep_schedule > schedule_;
  int max_sweep_;

  bool twodot_;
  int two_to_one_;

  string integral_file_;

public:
  int& nsite() { return this->nsite_; }
  int& np() { return this->np_; }
  int& na() { return this->na_; }
  int& nb() { return this->nb_; }
  int& ns() { return this->ns_; }

  int& nroot(){ return this->nroot_; }
  vector<double>& weights(){ return this->weights_; }

  int& nschedule() { return this->nschedule_; }
  vector< sweep_schedule >& schedule() { return this->schedule_; }
  int& max_sweep(){ return this->max_sweep_; }
  bool& twodot(){ return this->twodot_; }
  int& two_to_one(){ return this->two_to_one_; }

  string& integral_file(){ return this->integral_file_; }
  
public:
  const int get_nsite() const { return this->nsite_; }
  const int get_np() const { return this->np_; }
  const int get_na() const { return this->na_; }
  const int get_nb() const { return this->nb_; }
  const int get_ns() const { return this->ns_; }

  const int get_nroot() const { return this->nroot_; }
  const vector<double> get_weight() const { return this->weights_; }

  const int get_nschedule() const { return this->nschedule_; }
  const vector< sweep_schedule > get_schedule() const { return this->schedule_; }
  const int get_max_sweep() const { return this->max_sweep_; }
  const bool get_twodot() const { return this->twodot_; }
  const int get_two_to_one() const { return this->two_to_one_; }

  const string get_integral_file() const { return this->integral_file_; }

public:
  config(){};
  config( iqs::dmrg::cmd_option cmd_opt );
  ~config(){};

public:
  void set_default();
  void input_python( string conf_file );
  void input( string conf_file );
  void check_conf();

};

} }  // end of iqs::dmrg

#endif
