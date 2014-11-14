#ifndef IQUADS_SOLVER_BITMASK_H
#define IQUADS_SOLVER_BITMASK_H

#include "iquads/condition_bits.h"
#include "iquads/method_bits.h"
#include "iquads/solution_bits.h"

namespace iquads {

namespace solver_bitmask {

using namespace iquads::condition_bitmask;
using namespace iquads::method_bitmask;
using namespace iquads::solution_bitmask;

const unsigned int SCF_SOLVER      = MEANFIELD_CONDITION | SCF      | ORB_SOLUTION ;
const unsigned int SCF_SOLVER_ORCA = MEANFILED_CONDITION | ORCA_SCF | ORB_SOLUTION ;

const unsigned int FCI_SOLVER      = CI_CONDITION        | FCI      | CI_SOLUTION  ;
const unsigned int FCI_SOLVER_ORCA = CI_CONDITION        | ORCA_FCI | CI_SOLUTION  ;

const unsigned int CASSCF_SOLVER   = CI_CONDTION         | CASSCF   | CI_SOLUTION ;
const unsigned int CASSCF_SOLVER_ORCA = CI_CONDITION     | ORCA_CASSCF | CI_SOLUTION ;

const unsigned int DMRG_SOLVER = MPS_CONDITION | DMRG | MPS_SOLUTION ;
const unsigned int DMRG_SOLVER_BLOCK = MPS_CONDITION | BLOCK_DMRG | MPS_SOLUTION;
const unsigned int DMRGSCF_SOLVER = MPS_CONDITION | DMRGSCF | MPS_SOLUTION ;

const unsigned int SCFGRAD_SOLVER = ENGRAD_CONDITION | SCFGRAD | ENGRAD ;
const unsigned int SCFGRAD_SOLVER_ORCA = ENGRAD_CONDITION | SCFGRAD_ORCA | ENGRAD;
const unsigned int DMRGGRAD_SOLVER = ENGRAD_CONDITION | DMRGGRAD | ENGRAD;
const unsigned int DMRGGRAD_SOLVER_ORCA = ENGRAD_CONDITION | ORCA_DMRGGRAD | ENGRAD;

const unsigned int CPHF_SOLVER = ORBLR_CONDITION | CPHF | ORBLR ;
const unsigned int CPHF_SOLVER_ORCA = ORBLR_CONDITION | ORCA_CPHF | ORBLR ;
const unsigned int CPDMRG_SOLVER = MPSLR | CPDMRG | MPSLR ;
const unsigned int CPDMRG_SOLVER_BLOCK = MPSLR | CPDMRG_BLOCK | MPSLR ;

const unsigned int GSTEP_SOLVER = DX_CONDITION | GSTEP | DX ;
const unsigned int GSTEP_SOLVER_ORCA = DX_CONDITION | GSTEP_ORCA | DX;
const unsigned int MECISTEP_SOLVER = DX_CONDITION | MECISTEP | DX;
const unsigned int MECISTEP_SOLVER_ORCA = DX_CONDITION | MECISTEP_ORCA | DX;

} // end of namespace solver_bitmask

} // end of namespace iquads

#endif
