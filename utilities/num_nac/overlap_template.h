#ifndef OVERLAP_TEMPLATE_H
#define OVERLAP_TEMPLATE_H

namespace iquads {

template < class Wavefunction_Type,
           bool bra_perturbable = false, bool ket_perturbable = false, 
           class Value_Type = double >
class Overlap
{
public:
  friend 
   Overlap_Base< Wavefunction_Type >
   operator| ( Wavefunction_Type bra, Wavefunction_Type ket )
  {
    Overlap_Base< Wavefunction_Type > retval;
    retval.set_bra() = bra;
    retval.set_ket() = ket;
    retval.set_value() = (<bra) | (ket>) ;
    return retval;
  }

  void solve( ElectronicStateInfo info )
  {
    Wavefunction_Type state_bra;
    Wavefunction_Type state_ket;

    const int state_id_bra = info.get->lower();
    const int state_id_ket = info.get->higher();
    EigenSpectrum< Wavefunction_Type > eigen_spectrum;
    eigen_spectrum.solve( info );
    state_bra = eigen_spectrum.get_state( state_id_bra );
    state_ket = eigen_spectrum.get_state( state_id_ket );

    this->value_ = ( state_bra | state_ket ); // must include rephase
  }

private:
  shared_ptr<Wavefunction_Type> bra_;
  shared_ptr<Wavefunction_Type> ket_;
  ValueType value_;
  const bool bra_perturbable_;
  const bool ket_perturbable_;

}; // end of template class Overlap

} // end of namespace iquads

#endif
