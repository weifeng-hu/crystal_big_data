#include <overlap_instant.h>

namespace iquads {

  typedef Overlap< Wavefunction_Orbital > Overlap_Orbital;
  typedef Overlap< Wavefunction_Config > Overlap_Configuration;
  typedef Overlap< Wavefunction_CI > Overlap_CI;

  typedef Overlap< Wavefunction_Orbital, true, false > Overlap_Orbital_Bra_Perturbable;
  typedef Overlap< Wavefunction_Config, true, false> Overlap_Config_Bra_Perturbable;
  typedef Overlap< Wavefunction_CI, true, false> Overlap_CI_Bra_Perturbable;

} // end of namespace iquads
