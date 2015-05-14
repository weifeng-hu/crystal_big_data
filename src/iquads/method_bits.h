#ifndef IQUADS_METHOD_BITMASK_H
#define IQUADS_METHOD_BITMASK_H

namespace iquads {

namespace method_bitmask {

// method name 
//   essentially the module name, not dependent on solution type
//   takes 8 bits( 2 hex digits ), 255 methods
const unsigned int SCF			=	0x01;
const unsigned int SCF_ORCA		=	SCF		+	1;
const unsigned int DFT			=	SCF_ORCA	+	1;
const unsigned int DFT_ORCA		=	DFT		+	1;
const unsigned int MP2			=	DFT_ORCA	+	1;
const unsigned int MP2_ORCA		=	MP2		+	1;
const unsigned int CASSCF		=	MP2_ORCA	+	1;
const unsigned int CASSCF_ORCA		=	CASSCF		+	1;

const unsigned int FCI			=	CASSCF_ORCA	+	1;
const unsigned int FCI_ORCA		=	FCI		+	1;

const unsigned int DMRG			=	FCI_ORCA	+	1;
const unsigned int DMRG_BLOCK		=	DMRG		+	1;

const unsigned int SCFGRAD		=	DMRG_BLOCK	+	1;
const unsigned int SCFGRAD_ORCA		=	SCFGRAD		+	1;
const unsigned int DFTGRAD		=	SCFGRAD_ORCA	+	1;
const unsigned int DFTGRAD_ORCA		=	DFTGRAD		+	1;
const unsigned int DMRGGRAD		=	DFTGRAD_ORCA	+	1;
const unsigned int DMRGGRAD_ORCA	=	DMRGGRAD	+	1;

const unsigned int CPHF			=	DMRGGRAD_ORCA	+	1;
const unsigned int CPHF_ORCA		=	CPHF		+	1;
const unsigned int CPCI			=	CPHF_ORCA	+	1;
const unsigned int CPCI_ORCA		=	CPCI		+	1;
const unsigned int CPDMRG		=	CPCI_ORCA	+	1;
const unsigned int CPDMRG_BLOCK		=	CPDMRG		+	1;

const unsigned int GSTEP		=	CPDMRGBLOCK	+	1;
const unsigned int GSTEP_ORCA		=	GSTEP		+	1;
const unsigned int MECISTEP		=	GSTEP_ORCA	+	1;
const unsigned int MECISTEP_ORCA	=	MECISTEP	+	1;

} // end of namespace method_mask

} // end of namespace iquads

#endif
