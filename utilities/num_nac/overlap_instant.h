#include <overlap_template.h>

namespace iquads {

  // Bra and ket unperturable overlaps
  template class Overlap< Wavefunction_Orbital >;
  template class Overlap< Wavefunction_Config >;
  template class Overlap< Wavefunction_CI >;

  // Bra perturbable overlaps
  template class Overlap< Wavefunction_Orbital, true, false >;
  template class Overlap< Wavefunction_Config, true, false>;
  template class Overlap< Wavefunction_CI, true, false>;

} // end of namespace iquads
