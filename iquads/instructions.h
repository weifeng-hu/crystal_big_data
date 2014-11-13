#ifndef IQUADS_INSTRUCTION_H
#define IQUADS_INSTRUCTION_H

#include <string>
#include <tuple>
#include "iquads/instruction_bit.h"

using namespace std;

namespace iquads{

struct instruction
{
public:
  instruction(){};
  ~instruction(){};

public:
  void init()
  {
    this->instruct_name		= "not set";
    this->instruct_code		= 0;

    this->quantum_mechanics	= false;

    this->mean_field		= false;
    this->multi_reference	= false;
    this->nonlinear_wavefunction= false;
    this->multi_state		= false;

    this->orbital_optimization	= false;
    this->linear_response	= false;
    this->energy_gradient	= false;
    this->multi_perturbation	= false;
    this->electron_relaxation	= false;
    this->nuclei_relaxation	= false;

    this->quantum_dynamics	= false;
    this->nonadiabatic		= false;

    this->instruct_code = this->compute_code();
  } // end of init
  unsigned int compute_code()
  {

    unsigned int code = 0;

    if( this->quantum_mechanics == true ){
      code = code | instruct_bit::QUANTUM_MECH;
    }
    if( this->mean_field == true ){
      code = code | instruct_bit::MEAN_FIELD;
    }
    if( this->multi_reference == true ){
      code = code | instruct_bit::MR;
    }
    if( this->nonlinear_wavefunction == true ){
      code = code | instruct_bit::NONLINEAR_WF;
    }
    if( this->multi_state == true ){
      code = code | instruct_bit::MULTI_STATE;
    }
    if( this->orbital_optimization == true ){
      code = code | instruct_bit::ORBITAL_OPT;
    }
    if( this->linear_response == true ){
      code = code | instruct_bit::LINEAR_RESPONSE;
    }
    if( this->energy_gradient == true ){
      code = code | instruct_bit::ENERGY_GRAD;
    }
    if( this->multi_perturbation == true ){
      code = code | instruct_bit::MULTI_PERTURB;
    }
    if( this->electron_relaxation == true ){
      code = code | instruct_bit::ELECTRON_RELAX;
    }
    if( this->nuclei_relaxation == true ){
      code = code | instruct_bit::NUCLEI_RELAX;
    }
    if( this->quantum_dynamics == true ){
      code = code | instruct_bit::QUANTUM_DYN;
    }
    if( this->nonadiabatic == true ){
      code = code | instruct_bit::NON_ADIABATIC;
    }

    return code;

  } // end of compute_code()


public:
  const string get_instruct_name() const 
    { return this->instruct_name; }
  string get_instruct_name()
    { return this->instruct_name; }
  string& set_instruct_name() 
    { return this->instruct_name; }

  const unsigned int get_instruct_code() const
    { return this->instruct_code; }
  unsigned int get_instruct_code()
    { return this->instruct_code; }
  unsigned int& set_instruct_code() 
    { return this->instruct_code; }

  const bool use_quantum_mechanics() const 
    { return this->quantum_mechanics; }
  bool use_quantum_mechanics()
    { return this->quantum_mechanics; }
  void request_quantum_mechanics()
    { this->quantum_mechanics = true; }

  const bool mean_field_requested() const 
    { return this->mean_field; }
  bool mean_field_requested() 
    { return this->mean_field; }
  void request_mean_field()
    { this->mean_field = true; }

  const bool multi_reference_requested() const
    { return this->multi_reference; }
  bool multi_reference()
    { return this->multi_reference; }
  void request_multi_reference()
    { this->multi_reference = true; }

  const bool nonlinear_wavefunction_requested() const 
    { return this->nonlinear_wavefunction; }
  bool nonlinear_wavefunction_requested() 
    { return this->nonlinear_wavefunction; }
  void request_nonlinear_wavefunction()
    { this->nonlinear_wavefunction = true; }

  const bool multi_state_requested() const 
    { return this->multi_state; }
  bool multi_state_requested() 
    { return this->multi_state; }
  void request_multi_state()
    { this->multi_state = true; }

  const bool orbital_optimization_requested() const 
    { return this->orbital_optimization; }
  bool orbital_optimization_requested() 
    { return this->orbital_optimization; }
  void request_orbital_optimization()
    { this->orbital_optimization = true; }

  const bool linear_response_requested() const 
    { return this->linear_response; }
  bool linear_response_requested() 
    { return this->linear_response; }
  void request_linear_response()
    { this->linear_response = true; }

  const bool energy_gradient_requested() const 
    { return this->energy_gradient; }
  bool energy_gradient_requested() 
    { return this->energy_gradient_requested; }
  void request_energy_gradient()
    { this->energy_gradient = true; }

  const bool multi_perturbation_requested() const 
    { return this->multi_perturbation; }
  bool multi_perturbation_requested() 
    { return this->multi_perturbation; }
  void request_multi_perturbation()
    { this->multi_perturbation = true; }

  const bool electron_relaxation_requested() const 
    { return this->electron_relaxation; }
  bool electron_relaxation_requested() 
    { return this->electron_relaxation; }
  void request_electron_relaxation()
    { this->electron_relaxation = true; }

  const bool nuclei_relaxation_requested() const 
    { return this->nuclei_relaxation; }
  bool nuclei_relaxation_requested()
    { return this->nuclei_relaxation; }
  void request_nuclei_relaxation()
    { this->nuclei_relaxation = true; }

  const bool time_evolved_requested() const 
    { return this->time_evolved_requested; }
  bool time_evolved_requested() 
    { return this->time_evolved_requested; }
  void request_time_evolved()
    { this->time_evolved = true; }

  const bool quantum_dynamics_requested() const 
    { return this->quantum_dynamics; }
  bool quantum_dynamics_requested() 
    { return this->quantum_dynamics; }
  void request_quantum_dynamics()
    { this->quantum_dynamics = true; }

  const bool nonadiabatic_requested() const 
    { return this->nonadiabatic; }
  bool nonadiabatic_requested() 
    { return this->nonadiabatic; }
  void request_nonadiabatic()
    { this->nonadiabatic = true; }
  
private:
   string instruct_name;
   unsigned int instruct_code;

   bool quantum_mechanics;

   bool mean_field;
   bool multi_reference;
   bool nonlinear_wavefunction;
   bool multi_state;

   bool orbital_optimization;
   bool linear_response;
   bool energy_gradient;
   bool multi_perturbation;

   bool electron_relaxation;
   bool nuclei_relaxation;
   bool time_evolved;
   bool quantum_dynamics;

   bool nonadiabatic;

}; // end of struct instruction

} // end of iquads

#endif
