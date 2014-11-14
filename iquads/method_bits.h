#ifndef IQUADS_METHOD_BITMASK_H
#define IQUADS_METHOD_BITMASK_H

namespace iquads {

namespace method_bitmask {

// method name 
//   essentially the module name, not dependent on solution type
//   takes 8 bits( 2 hex digits ), 255 methods
const unsigned int SCF      = 0x01;
const unsigned int ORCA_SCF = SCF + 1;
const unsigned int DFT      = ORCA_SCF + 1;
const unsigned int ORCA_DFT = DFT + 1;
const unsigned int MP2      = ORCA_DFT + 1;
const unsigned int ORCA_MP2 = MP2 + 1 ;
const unsigned int CASSCF   = ORCA_MP2 + 1 ;
const unsigned int ORCA_CASSCF = CASSCF + 1;

const unsigned int FCI      = ORCA_CASSCF + 1;
const unsigned int ORCA_FCI = FCI + 1;

const unsigned int DMRG       = ORCA_FCI + 1;
const unsigned int BLOCK_DMRG = DMRG + 1;

const unsigned int SCFGRAD      = BLOCK_DMRG + 1;
const unsigned int ORCA_SCFGRAD = SCFGRAD + 1;
const unsigned int DFTGRAD      = ORCA_SCFGRAD + 1;
const unsigned int ORCA_DFTGRAD = DFTGRAD + 1;
const unsigned int DMRGGRAD     = ORCA_DFTGRAD + 1;
const unsigned int ORCA_DMRGGRAD = DMRGGRAD + 1;

const unsigned int CPHF = ORCA_DMRGGRAD + 1;
const unsigned int ORCA_CPHF = CPHF + 1;
const unsigned int CPCI = ORCA_CPHF + 1;
const unsigned int ORCA_CPCI = CPCI + 1;
const unsigned int CPDMRG = ORCA_CPCI + 1;
const unsigned int CPDMRG_BLOCK = CPDMRG + 1;

const unsigned int GSTEP        = CPDMRG_BLOCK + 1;
const unsigned int GSTEP_ORCA   = GSTEP + 1 ;
const unsigned int MECISTEP     = GSTEP_ORCA + 1;
const unsigned int MECISTEP_ORCA= MECISTEP + 1;

} // end of namespace method_mask

} // end of namespace iquads

#endif
