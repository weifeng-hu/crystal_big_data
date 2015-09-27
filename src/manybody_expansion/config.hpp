/**
 * @file
 * @author Weifeng Hu
 *
 * @section LICENSE
 *
 * Copyright (C) 2013, 2014, 2015  Weifeng Hu
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @section DESCRIPTION
 *
 *
 */

#ifndef MANYBODY_EXPANSION_CONFIG_HPP
#define MANYBODY_EXPANSION_CONFIG_HPP

#include <string>
#include <iquads/sequence.hpp>
#include <structure/lattice_instant.hpp>
#include <structure/bulk_instant.hpp>
#include <electron_correlation/correlation_level.hpp>
#include <interface_to_third_party/program_mask.hpp>
#include <manybody_expansion/order_mask.hpp>

namespace iquads {

namespace manybody_expansion {


  /**
   *  A meta-data struct as a config for general many body expansion
   *  calculations.
   *
   *  This request is set as a struct since it is usually not an entity.
   *  The many body expansion calculation config is an object to be 
   *  initialized by a many body expansion agent object at runtime.
   *
   *  This config will be used in the actual procedures of a many body
   *  expansion calculation since it is responsible to hold critial 
   *  information about how calculations should be handled. These information
   *  are not necessary to be known to clients, for example, clients
   *  don't need to know how many CPU cores are on a machine, since the 
   *  agent will detect it and write it to the config. But a client can 
   *  tell, from a request, that  whether the calculation needs one more
   *  core so that the agent can handle it and optimize the performance.
   *
   *  Data member of this config struct are:
   *   + the lattice info/bulk, i.e., geometrical structure.
   *     This information can be directly copied from the 
   *     the request struct.
   *   + order of the expansion
   *   + external program info
   *   + whether the calculation is periodic
   *     The agent will check whether information of lattice, or bulk is
   *     filled to judge this point.
   *   + correlation method sequence.
   *   + basis set
   *   + runtime path info, if the request didn't specify them, then
   *     the agent should figure out the most proper values for them.
   *   Other information can be included (in future):
   *   Parallelization?
   */


using std :: string;
using structure :: MolecularLattice;
using structure :: MolecularBulk;
using namespace interface_to_third_party;
using namespace iquads :: sequence;

struct Config {
public:
  /**
   *  In principle, many of these type definition are for know types.
   *  But here we do not cross refer defined types from other classes where
   *  these types where first defined or declared, since we want to make 
   *  sure that the code is type safe. Any change of the types in this class 
   *  may mean the change of the design and we enforce the adjustment of design of 
   *  other classes.
   */
  typedef string                                     lattice_name_type;
  typedef MolecularLattice                           lattice_type;
  typedef tuple< lattice_name_type, lattice_type >   lattice_info_type;
  typedef string                                     bulk_name_type;
  typedef MolecularLattice                           bulk_type;
  typedef tuple< bulk_name_type, bulk_type >         bulk_info_type;
  typedef electron_correlation :: level_mask_type    correlation_method_type;
  typedef order :: order_mask_type                   expansion_order_type;
  typedef program :: program_mask_type               program_type;
  typedef mode :: mode_mask_type                     run_mode_type;
  typedef string   basis_set_name_type;
  typedef string   file_name_type;
  typedef string   job_name_type;
  typedef string   path_name_type;
  typedef bool     condition_type;

  typedef lattice_info_type&        lattice_info_ref;
  typedef bulk_info_type&           bulk_info_ref;
  typedef correlation_method_type&  correlation_method_ref;
  typedef expansion_order_type&     expansion_order_ref;
  typedef program_type&             program_ref;
  typedef condition_type&           condition_ref;
  typedef basis_set_name_type&      basis_set_name_ref;
  typedef job_name_type&            job_name_ref;
  typedef path_name_type&           path_name_ref;
  typedef run_mode_type&            run_mode_ref;

public:
  /**
   *  Accessors
   */
  lattice_info_type lattice_info() const
    { return this->lattice_info_; }
  bulk_info_type set_bulk_info() const
    { return this->bulk_info_; }
  expansion_order_type expansion_order() const
    { return this->expansion_order_; }
  condition_type is_periodic() const
    { return this->is_periodic_; }
  program_type program() const
    { return this->program_; }
  basis_set_name_type basis_set_name() const
    { return this->basis_set_name_; }
  job_name_type job_name() const
    { return this->job_name_; }
  path_name_type scratch_name() const
    { return this->scratch_name_; }
  correlation_method_type correlation_method() const
    { return this->correlation_method_; }
  run_mode_type run_mode() const
    { return this->run_mode_; }

  /**
   *  Mutators
   *  A agent is allowed to change the config at runtime for
   *  adjustment of a calculation. But the agent is responsible to 
   *  reflect the change in the report!
   */
  lattice_info_ref set_lattice_info() 
   { return this->lattice_info_; }
  bulk_info_ref set_bulk_info() 
   { return this->bulk_info_; }
  expansion_order_ref set_expansion_order() 
   { return this->expansion_order_; }
  condition_ref set_is_periodic() 
   { return this->is_periodic_; }
  program_ref set_program() 
   { return this->program_; }
  basis_set_name_ref set_basis_set_name() 
   { return this->basis_set_name_; }
  job_name_ref set_job_name() 
   { return this->job_name_; }
  path_name_ref set_scratch_name() 
   { return this->scratch_name_; }
  correlation_method_ref set_correlation_method()
   { return this->correlation_method_; }
  run_mode_ref set_run_mode()
   { return this->run_mode_; }

private:
  lattice_info_type        lattice_info_;
  bulk_info_type           bulk_info_;
  expansion_order_type     expansion_order_;
  condition_type           is_periodic_;
  program_type             program_;
  correlation_method_type  correlation_method_;
  basis_set_name_type      basis_set_name_;
  job_name_type            job_name_;
  path_name_type           scratch_name_;
  run_mode_type            run_mode_;

}; // end of class Config

} // end of namespace manybody_expansion

} // end of namespace iquads

#endif
