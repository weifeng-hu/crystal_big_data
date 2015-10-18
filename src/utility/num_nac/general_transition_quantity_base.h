#include <memory>

using namespace std;

namespace iquads {

template 
< class Wavefunction_Type, class Mechanics_Operator_Type, class Quantity_Type >
class general_transition_quantity_base
{
public:
  void compute(){
   Quantity_Type result 
    =  (*(this->wavefunction_bra_ptr)) | (*(this->mechanics_operator_ptr)) | (*(this->wavefunction_ket_ptr)) ;
   this->store = result;
  }

  friend 
  Quantity_Type operator+ ( Quantity_Type q1, Quantity_Type q2 ){
   return q1 + q2;
  }

private:
  Quantity_Type store;
  shared_ptr<Mechanics_Operator_Type> mechanics_operator_ptr;
  shared_ptr<Wavefunction_Type> wavefunction_bra_ptr;
  shared_ptr<Wavefunction_Type> wavefunction_ket_ptr;

};

} // end of namespace iquads
