#ifndef TRANSFORM_INFO_H
#define TRANSFORM_INFO_H

#include <map>
#include <array>
#include <vector>
#include <iostream>
#include <string>
#include "parameters.h"
#include "pdm.h"
#include "mo_coefficients.h"
#include "overlap_matrix.h"

using namespace std;

namespace ph_analysis{

struct transform_info
{

public:
  transform_info( string inputfile );
  transform_info(){};
  ~transform_info(){};

public:
  int read( std::string inputfile ){ 
   this->read(); 
   return 0;
  }

private:
  int read();

public:
  const mo_coefficients get_c_mo() const { return this->c_mo; }
  mo_coefficients& set_c_mo(){ return this->c_mo; }

  const mo_coefficients get_c_lmo() const { return this->c_lmo; }
  mo_coefficients& set_c_lmo(){ return this->c_lmo; }

  const mo_coefficients get_s_ov() const { return this->s_ov; }
  mo_coefficients& set_s_ov(){ return this->s_ov; }

  const overlap_matrix get_s_full() const { return this->s_full; }
  overlap_matrix& set_s_full(){ return this->s_full; }

  const mo_coefficients get_u_tr() const { return this->u_tr; }
  mo_coefficients& set_u_tr(){ return this->u_tr; }

  const array<int, NMO_THRESH> get_active_space() const { return this->active_space; }
  array< int, NMO_THRESH >& set_active_space() { return this->active_space; }

  onepdm& get_gamma1() { return this->gamma1; }
  twopdm& get_gamma2() { return this->gamma2; }
  const onepdm get_gamma1() const { return this->gamma1; }
  const twopdm get_gamma2() const { return this->gamma2; }

  const double get_t1_thresh() const { return this->t1_thresh; }
  double& set_t1_thresh() { return this->t1_thresh; }
  const double get_t1_thresh_in() const { return this->t1_thresh_in; }
  double& set_t1_thresh_in() { return this->t1_thresh_in; }

  const double get_t2_thresh() const { return this->t2_thresh; }
  double& set_t2_thresh() { return this->t2_thresh; }
  const double get_t2_thresh_in() const { return this->t2_thresh_in; }
  double& set_t2_thresh_in() { return this->t2_thresh_in; }

  const int get_norb() const { return this->norb; }
  int& set_norb() { return this->norb; }

  const int get_nact() const { return this->nact; }
  int& set_nact() { return this->nact; }

  const int get_solve_u() const { return this->solve_u; }
  bool set_solve_u() { return this->solve_u; }

  const string get_basename() const { return this->basename; }
  string& set_basename() { return this->basename; }

  const string get_prefix() const { return this->prefix; }
  string& set_prefix() { return this->prefix; }

  const int get_compute_s_only() const { return this->compute_s_only; }
  int& set_compute_s_only() { return this->compute_s_only; }

  const int get_trans_onepdm() const { return this->trans_onepdm; }
  int& set_trans_onepdm() { return this->trans_onepdm; }
  const int get_trans_onepdm_element() const { return this->trans_onepdm_element; }
  int& set_trans_onepdm_element() { return this->trans_onepdm_element; }

  const int get_trans_twopdm() const { return this->trans_twopdm; }
  int& set_trans_twopdm() { return this->trans_twopdm; }
  const int get_trans_twopdm_element() const { return this->trans_twopdm_element; }
  int& set_trans_twopdm_element() { return this->trans_twopdm_element; }
 
private:
  onepdm gamma1;
  twopdm gamma2;
  mo_coefficients c_mo;
  mo_coefficients c_lmo;
  mo_coefficients s_ov;
  overlap_matrix s_full;
  mo_coefficients u_tr;

  array<int, NMO_THRESH> active_space;

  string configfile;
  string basename;
  string prefix;
  string p1_filename;
  string p2_filename; 
  string s_filename;
  string c_filename;
  string cl_filename;
  string u_filename;
  string act_filename;

  double t1_thresh, t2_thresh;
  double t1_thresh_in, t2_thresh_in;
  int norb;
  int nocc;
  int nact;
  int solve_u;
  int compute_s_only;
  int trans_onepdm;
  int trans_onepdm_element;
  int trans_twopdm;
  int trans_twopdm_element;

};

} // end of namespace ph_analysis

#endif
