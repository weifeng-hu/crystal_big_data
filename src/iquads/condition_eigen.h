#ifndef IQUADS_CONDITION_EIGEN_H
#define IQUADS_CONDITION_EIGEN_H

#include <string>
#include <vector>
#include "iquads/condition_base.h"

namespace iquads {

struct condition_eigen : public condition_base
{
public:
  condition_eigen()
   {
    this->eigpair_filenames_.resize(0);
    this->onepdm_filenames_.resize(0);
    this->twopdm_filenames_.resize(0);
    this->weights_.resize(0);
    this->irrep_tag_ = "unset";
    this->nroot_ = -1;
    this->spin_ = -1;
   }

protected:
  bool is_eigen_allset();
   {
    if( this->is_base_allset() == false )
     { return false; }
    if( this->mole_info_.is_ok() == false; )
     { return false; }
    if( this->weights_.size() == 0 )
     { return false; }
    if( this->eigpair_filenames_.size() == 0 )
     { return false; }
    if( this->onepdm_filenames_.size() == 0 )
     { return false; }
    if( this->twopdm_filenames_.size() == 0 )
     { return false; }
    if( this->irrep_tag_ == "unset" )
     { return false; }
    if( this->nroot_ == -1 )
     { return false; }
    if( this->spin_ == -1 )
     { return false; }
    return true;
   }

public:
  // non-const member access method
  molecule_info& mol_info()
   { return this->mol_info_; }
  vector<string>& eigpair_filenames()
   { return this->eigpair_filenames_; }
  vector<string>& onepdm_filenames()
   { return this->onepdm_filenames_; }
  vector<string>& twopdm_filenames()
   { return this->twopdm_filenames_; }
  vector<double>& weights()
   { return this->weights_; }
  string& irrep_tag()
   { return this->irrep_tag_; }
  int& nroot()
   { return this->nroot_; }
  int& spin()
   { return this->spin_; }

  // const member access method
  const molecule_info& mol_info() const 
   { return this->mol_info_; }
  const vector<string>& eigpair_filenames() const 
   { return this->eigpair_filenames_; }
  const vector<string>& onepdm_filenames() const 
   { return this->onepdm_filenames_; }
  const vector<string>& twopdm_filenames() const 
   { return this->twopdm_filenames_; }
  const vector<double>& weights() const 
   { return this->weights_; }
  const string& irrep_tag() const 
   { return this->irrep_tag_; }
  const int& nroot() const 
   { return this->nroot_; }
  const int& spin() const 
   { return this->spin_; }

private:
  molecule_info mol_info_;
  vector<string> eigpair_filenames_;
  vector<string> onepdm_filenames_;
  vector<string> twopdm_filenames_;
  vector<double> weights_;
  string irrep_tag_;
  int nroot_;
  int spin_;

}; // end of struct condition_eigen

struct condition_scf : public condition_eigen
{
public:
  void set_conditions()
   { /* to be defined*/ }

private:
  string basis_set_tag_;
  int scftype_;
  bool use_soscf_;
  bool use_parallel_;
}; // end of struct scf

struct condition_fci : public condition_eigen
{
private:
  string fcidump_name_;
  bool use_fcidump_;
}; // end of struct condition_fci

struct condition_dmrg : public condition_eigen
{
  typedef tuple< size_t, size_t, double, double > schedule_step;
  typedef vector< schedule_step > schedule;

public:
  schedule& dmrg_schedule()
    { return this->dmrg_schedule_; }

  const schedule& dmrg_schedule() const
    { return this->dmrg_schedule_; }

private:
  schedule dmrg_schedule_;
  string fcidump_name_;
  int twodot_to_onedot_;
  bool onedot_only_;
  bool twodot_only_;
  bool use_fcidump_;
  bool restart_;
  bool reset_iterations_;
  bool fullrestart_;

}; // end of struct condition_dmrg

} // end of iquads

#endif
