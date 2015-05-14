#ifndef IQUADS_CONDITION_BITMASK_H
#define IQUADS_CONDITION_BITMASK_H

namespace iquads {

namespace condition_bitmask {

const unsigned int CONDITION_MEANFIELD	= 0x01 << 16 ;
const unsigned int CONDITION_CI		= 0x02 << 16 ;
const unsigned int CONDITION_MPS	= 0x03 << 16 ;
const unsigned int CONDITION_ENGRAD	= 0x04 << 16 ;
const unsigned int CONDITION_ORBLR	= 0x05 << 16 ;
const unsigned int CONDITION_CILR	= 0x06 << 16 ;
const unsigned int CONDITION_MPSLR	= 0x07 << 16 ;
const unsigned int CONDITION_DX		= 0x08 << 16 ;

} // end of namespace condition_bitmask

} // end of namespace iquads

#endif
