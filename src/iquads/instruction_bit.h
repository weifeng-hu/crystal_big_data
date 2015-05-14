#ifndef IQUADS_INSTRUCT_BIT_H
#define IQUADS_INSTRUCT_BIT_H

namespace iquads{

namespace instruct_bit{

const unsigned int QUANTUM_MECH			= 1<<0;

const unsigned int MEAN_FIELD			= 1<<1;
const unsigned int MR				= 1<<2;
const unsigned int NONLINEAR_WF			= 1<<3;
const unsigned int MULTI_STATE			= 1<<4;

const unsigned int ORBITAL_OPT			= 1<<5;
const unsigned int LINEAR_RESPONSE		= 1<<6;
const unsigned int ENERGY_GRAD			= 1<<7;
const unsigned int MULTI_PERTURB		= 1<<8;

const unsigned int ELECTRON_RELAX		= 1<<9;
const unsigned int NUCLEI_RELAX			= 1<<10;
const unsigned int TIME_EVOVLE			= 1<<11;
const unsigned int QUANTUM_DYN			= 1<<12;
const unsigned int NON_ADIABATIC		= 1<<13;

} // end of instruct_bit

} // end of iquads;

#endif
