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
#include <memory>
#include <iquads/sequence.hpp>
#include <structure/lattice_instant.hpp>
#include <structure/molecule_bulk.hpp>
#include <electron_correlation/level.hpp>
#include <manybody_expansion/order_mask.hpp>
#include <interface_to_third_party/program_mask.hpp>

using std::string;
using std::shared_ptr;

namespace iquads {

using structure :: molecular_lattice;
using structure :: MoleculeBulk;
//using namespace interface_to_third_party :: program;

namespace manybody_expansion {

class Config
{
public:
  typedef molecular_lattice     lattice_info_type;
  typedef MoleculeBulk                  bulk_info_type;
  typedef typename electron_correlation :: level_mask_type correlation_method_type;
  typedef typename order :: order_mask_type                expansion_order_type;
  typedef typename interface_to_third_party :: program :: program_mask_type            program_type;
  typedef typename sequence :: mode :: mode_mask_type run_mode_type;
  typedef string                        basis_set_name_type;
  typedef string                        file_name_type;
  typedef string                        job_name_type;
  typedef string                        path_name_type;
  typedef bool condition_type;

  typedef lattice_info_type&     lattice_info_ref;
  typedef bulk_info_type&        bulk_info_ref;
  typedef correlation_method_type& correlation_method_ref;
  typedef expansion_order_type&  expansion_order_ref;
  typedef program_type&          program_ref;
  typedef condition_type&        condition_ref;
  typedef basis_set_name_type&   basis_set_name_ref;
  typedef job_name_type&         job_name_ref;
  typedef path_name_type&        path_name_ref;
  typedef run_mode_type&         run_mode_ref;

public:
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
  correlation_method_ref& set_correlation_method()
   { return this->correlation_method_; }
  run_mode_ref set_run_mode()
   { return this->run_mode_; }

  const expansion_order_type expansion_order() const 
   { return this->expansion_order_; }
  const condition_type is_periodic() const
   { return this->is_periodic_; }

private:
  lattice_info_type      lattice_info_;
  bulk_info_type         bulk_info_;
  expansion_order_type   expansion_order_;
  condition_type         is_periodic_;
  program_type           program_;
  correlation_method_type correlation_method_;
  basis_set_name_type    basis_set_name_;
  job_name_type          job_name_;
  path_name_type         scratch_name_;
  run_mode_type          run_mode_;

}; // end of class Config

} // end of namespace manybody_expansion

} // end of namespace iquads

#endif
