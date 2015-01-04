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

const unsigned int SOLVER_SCF		=	CONDITION_MEANFIELD	|	SCF		|	SOLUTION_ORB;
const unsigned int SOLVER_SCF_ORCA	=	CONDITION_MEANFIELD	|	SCF_ORCA	|	SOLUTION_ORB;

const unsigned int SOLVER_FCI		=	CI_CONDITION		|	FCI		|	SOLUTION_CI;
const unsigned int SOLVER_FCI_ORCA	=	CI_CONDITION		|	FCI_ORCA	|	SOLUTION_CI;

const unsigned int SOLVER_CASSCF	=	CONDITION_CI		|	CASSCF		|	SOLUTION_CI;
const unsigned int SOLVER_CASSCF_ORCA	=	CONDITION_CI		|	CASSCF_ORCA	|	SOLUTION_CI;

const unsigned int SOLVER_DMRG		=	CONDITION_MPS		|	DMRG		|	SOLUTION_MPS;
const unsigned int SOLVER_DMRG_BLOCK	=	CONDITION_MPS		|	DMRG_BLOCK	|	SOLUTION_MPS;
const unsigned int SOLVER_DMRGSCF	=	CONDITION_MPS		|	DMRGSCF		|	SOLUTION_MPS;

const unsigned int SOLVER_SCFGRAD	=	CONDITION_ENGRAD	|	SCFGRAD		|	SOLUTION_ENGRAD;
const unsigned int SOLVER_SCFGRAD_ORCA	=	CONDITION_ENGRAD	|	SCFGRAD_ORCA	|	SOLUTION_ENGRAD;
const unsigned int SOLVER_DMRGGRAD	=	CONDITION_ENGRAD	|	DMRGGRAD	|	SOLUTION_ENGRAD;
const unsigned int SOLVER_DMRGGRAD_ORCA	=	CONDITION_ENGRAD	|	DMRGGRAD_ORCA	|	SOLUTION_ENGRAD;

const unsigned int SOLVER_CPHF		=	CONDITION_ORBLR		|	CPHF		|	SOLUTION_ORBLR;
const unsigned int SOLVER_CPHF_ORCA	=	CONDITION_ORBLR		|	CPHF_ORCA	|	SOLUTION_ORBLR;
const unsigned int SOLVER_CPDMRG	=	CONDITION_MPSLR		|	CPDMRG		|	SOLUTION_MPSLR;
const unsigned int SOLVER_CPDMRG_BLOCK 	=	CONDITION_MPSLR		|	CPDMRG_BLOCK	|	SOLUTION_MPSLR;

const unsigned int SOLVER_GSTEP		=	CONDITION_DX		|	GSTEP		|	SOLUTION_DX;
const unsigned int SOLVER_GSTEP_ORCA	=	CONDITION_DX		|	GSTEP_ORCA	|	SOLUTION_DX;
const unsigned int SOLVER_MECISTEP	=	CONDITION_DX		|	MECISTEP	|	SOLUTION_DX;
const unsigned int SOLVER_MECISTEP_ORCA	=	CONDITION_DX		|	MECISTEP_ORCA	|	SOLUTION_DX;

} // end of namespace solver_bitmask

} // end of namespace iquads

#endif
