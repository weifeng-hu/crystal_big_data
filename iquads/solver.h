#include "iquads/solver_base.h"

namespace iquads {

typedef solver< scf_condition, scf      , orb_solution > scf_solver;
typedef solver< scf_condition, orca_scf , orb_solution > scf_solver_orca;

typedef solver< fci_condition, fci      , fci_solution > fci_solver;
typedef solver< fci_condition, orca_fci , fci_solution > fci_solver_orca;

typedef solver< , casscf      , casscf_solution > casscf_solver;
typedef solver< , orca_casscf , casscf_solution > casscf_solver_orca;

typedef solver< dmrg_condition, dmrg       , mps_solution > dmrg_solver;
typedef solver< dmrg_condition, block_dmrg , mps_solution > dmrg_solver_block;

typedef solver< , dmrgscf       , dmrgscf_solution > dmrgscf_solver;
typedef solver< , block_dmrgscf , dmrgscf_solution > dmrgscf_solver_block;

typedef solver< , scfgrad      , energy_gradient > scfgrad_solver;
typedef solver< , orca_scfgrad , energy_graident > scfgrad_solver_orca;

typedef solver< , casscfgrad      , energy_gradient > casscfgrad_solver;
typedef solver< , orca_casscfgrad , energy_gradient > casscfgrad_solver_orca;

typedef solver< , dmrggrad      , energy_gradient > dmrggrad_solver;
typedef solver< , orca_dmrggrad , energy_gradient > dmrggrad_solver_orca;

typedef solver< , dmrgscfgrad      , energy_gradient > dmrgscfgrad_solver;
typedef solver< , orca_dmrgscfgrad , energy_gradient > dmrgscfgrad_solver_orca;

typedef solver< , cphf_to_x      , orblr_to_x > cphf_to_x_solver;
typedef solver< , orca_cphf_to_x , orblr_to_x > cphf_to_x_solver_orca;

typedef solver< , cpdmrg_to_x       , mps_to_x > cpdmrg_to_x_solver;
typedef solver< , block_cpdmrg_to_x , mps_to_x > cpdmrg_to_x_solver_block;

typedef solver< , cpdmrgscf_to_x    , mpsscf_to_x > cpdmrgscf_to_x_solver;

typedef solver< , geostep, displacement > geostep_solver;
typedef solver< , orca_geostep, displacement > geostep_solver_orca;

} // end of iquads
