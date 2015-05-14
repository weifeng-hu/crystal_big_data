#ifndef IQUADS_COND_GRAD_H
#define IQUADS_COND_GRAD_H

namespace iquads {

struct condition_grad : public condition_base
{
private:
  molecule_info mol_info_;
  string perturb_type_;
  unsigned int npert_;

}; // end of struct condition_grad

struct condition_engrad : public condition_grad
{
private:
  vector<string> grad_filename_;
  string onepdm_name_;
  string twopdm_name_;
  unsigned int nroot_;
  unsigned int spin_;

}; // end of struct condition_grad

struct condition_scfgrad : public condition_enggrad
{
private:
  string basis_set_tag_;
  int scftype_;
}; // end of struct condition_scfgrad

struct condition_dmrgcigrad : public condition_enggrad
{
private:
  string orbgrad_file_;
}; // end of struct condition_dmrgcigrad

struct condition_dmrgscfgrad : public condition_enggrad
{

}; // end of struct condition_dmrgscfgrad

struct condition_wfgrad : public condition_grad
{

private:
  vector<string> wf_filename_;
  vector<string> grad_filename_;

};

struct condition_cphf
{
private:
};

struct condition_cpmps
{
private:
};

} // end of iquads

#endif
