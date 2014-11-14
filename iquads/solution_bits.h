#ifndef IQUADS_SOLUTION_BITMASK_H
#define IQUADS_SOLUTION_BITMASK_H

namespace iquads {

namespace solution_bitmask {

// quantities, vector, scalar, functional
// takes 4 bits ( 1 hex bit ), totally 15 slots
const unsigned int TIME     = 0x01 ;
const unsigned int POSITION = 0x02 ;
const unsigned int MOMENTUM = 0x03 ;

const unsigned int ENG = 0x04 ;
const unsigned int ORB = 0x05 ;
const unsigned int CI  = 0x06 ;
const unsigned int MPS = 0x07 ;

// types
// takes 4 bits ( 1 hex bit ), totally 15 slots
const unsigned int SPACE = 0x01 << 4 ;
const unsigned int EIGEN = 0x02 << 4 ;
const unsigned int GRAD  = 0x03 << 4 ;
const unsigned int DELTA = 0x04 << 4 ;

// combination of quantities and types, 225 possiblities

const unsigned int ORB_SOLUTION = EIGEN | ORB ;
const unsigned int CI_SOLUTION  = EIGEN | CI  ;
const unsigned int MPS_SOLUTION = EIGEN | MPS ;

// gradient, linear response
const unsigned int ENGRAD = GRAD | ENG ;
const unsigned int ORBLR  = GRAD | ORB ;
const unsigned int CILR   = GRAD | CI  ;
const unsigned int MPSLR  = GRAD | MPS ;
// displacement of quantities
const unsigned short int DX = DELTA | POSITION;

} // end of namespace solution_bitmask

} // end of namespace iquads

#endif
