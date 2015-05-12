
namespace iquads {

class Wavefunction_Orbital : public Wavefunction_Base
{

private:
  DMatrixHeap orbital_coefficients_;
  AtomicBasis atomic_basis_;

}; // end of class Wavefunction_Orbital

} // end of namespace iquads
