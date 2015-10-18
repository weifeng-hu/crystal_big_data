
namespace iquads {

class Wavefunction_Vector : public Wavefunction_Base
{

private:
  DMatrixHeap ci_coefficients_;
  ConfigurationInfo configuration_;

}; // end of class Wavefunction_Vector

} // end of namespace iquads
