

namespace iquads {

template class WavefunctionOverlap_Base< CI_Wavefunction, double >;

using WavefunctionOverlap_Base< CI_EigenPair, double > = CI_WavefunctionOverlap_Base;

class CI_Overlap_Bra_Perturbale : public CI_WavefunctionOverlap_Base
{
public:
  void apply_difference( AtomicCoordinateDisplacement displacement ){
   this->bra_.apply_difference( displacement );
  }

};

} // end of namespace iquads
