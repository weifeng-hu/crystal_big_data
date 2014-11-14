#ifndef IQUADS_CONDITION_BITMASK_H
#define IQUADS_CONDITION_BITMASK_H

namespace iquads {

namespace condition_bitmask {

const unsigned int MEANFIELD_CONDITION = 0x01 << 16 ;
const unsigned int CI_CONDITION       = 0x02 << 16 ;
const unsigned int MPS_CONDITION      = 0x03 << 16 ;
const unsigned int ENGRAD_CONDITION   = 0x04 << 16 ;
const unsigned int ORBLR_CONDITION   = 0x05 << 16;
const unsigned int CILR_CONDITION    = 0x06 << 16;
const unsigned int MPSLR_CONDITION   = 0x07 << 16;
const unsigned int DX_CONDITION     = 0x08 << 16 ;

} // end of namespace condition_bitmask

} // end of namespace iquads

#endif
