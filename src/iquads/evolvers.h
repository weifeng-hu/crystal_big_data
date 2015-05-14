#include "iquads/evolver_base.h"

namespace iquads {

typedef evolver< energy_min_nr,   mol_info_hf > geo_optimizer_nr_hf;
typedef evolver< energy_min_diis, mol_info_hf > geo_optimizer_diis_hf;

typedef evolver< energy_min_nr, mol_info_dmrg  > geo_optimizer_nr_dmrg;
typedef evolver< energy_min_diis, mol_info_dmrg > geo_optimizer_diis_dmrg;

typedef evolver< meci_todd, mol_info_dmrg > meci_optimizer_ener_dmrg;
typedef evolver< meci_nona, mol_info_dmrg > meci_optimizer_nona_dmrg;

typedef evolver< classical_time, mol_info_dmrg > bomd_dmrg;

typedef evolver< quantum_time, mol_info_dmrg > tddmrg;

} // end of iquads
