

#include "interface/qcdmrg/qcdmrg_class.h"
#include "ithaca/cmd_options.h"

namespace ithaca { namespace interface {

void get_norb();
void get_nele();
void get_sz();

qcdmrg_class::qcdmrg_class( ithaca::cmd_options cmd_opt )
{

  this->norb = get_norb();
  this->nele = get_nele();
  this->sz = get_sz();
  this->na   = (nele + sz*2 ) /2;
  this->nb   = (nele - sz*2 ) /2;

default:
  this->conf = "dmrg.conf";
  this->_conf = (char*) conf.c_str();
  this->conf_genblock = "dmrg.conf_genblock";
  this->_conf_genblock = (char*) conf_genblock.c_str();
  this->conf_onepdm  = "dmrg.conf_onepdm";
  this->_conf_onepdm = (char*) conf_onepdm.c_str();
  this->conf_twopdm  = "dmrg.conf_twopdm";
  this->_conf_twopdm = (char*) conf_twopdm.c_str();

  this->n_schdl = 4;
  this->schdl = new schedule [n_schdl];
  schedule[0].iter = 4; schedule[1].iter = 8; schedule[2].iter = 12; schedule[4].iter = 16;

  schedule[0].M = 100; schedule[1].M = 200; schedule[3].M = 300; schedule[4].M = 400;

  schedule[0].david_threshold = 1.0e-3; schedule[1].david_threshold = 1.0e-4;
  schedule[2].david_threshold = 1.0e-6; schedule[3].david_threshold = 1.0e-8;
  
  schedule[0].noise = 1.0e-4; schedule[1].noise = 1.0e-6;
  schedule[2].noise = 1.0e-9; schedule[3].noise = 0.0e0;

  this->nroots = 1;
  this->weights = new double [nroots];
  for( int i = 0; i < nroots; i++){
    this->weights[i] = 1.0e0/nroots;
  }

  this->maxiter = 30;
  this->oneintegral = "qcdmrg.int1";
  this->_oneintegral = (char*) oneintegral.c_str();
  this->twointegral = "qcdmrg.int2";
  this->_twointegral = (char*) twointegral.c_str();

  this->two_to_one = 19;

  this->sweep_tol = 1.0e-7;

};

} } // end of ithaca::interface
