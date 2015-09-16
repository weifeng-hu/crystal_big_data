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
 * the Free Software Foundation, either version 2 of the License, or
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

#ifndef MANYBODY_EXPANSION_REQUEST_HPP
#define MANYBODY_EXPANSION_REQUEST_HPP

#include <string>
#include <structure/lattice_instant.hpp>
#include <structure/molecule_bulk.hpp>

using std::string;

namespace iquads {

using structure :: molecular_lattice;
using structure :: MoleculeBulk;

namespace manybody_expansion {

struct Request {
public:
  typedef molecular_lattice lattice_info_type;
  typedef MoleculeBulk bulk_info_type;
  typedef string correlation_name_type;
  typedef string external_program_name_type;
  typedef string file_name_type;
  typedef string path_name_type;
  typedef string job_name_type;
  typedef string basis_set_name_type;
  typedef string run_mode_name_type;
  typedef size_t expansion_order_type;

public:
  void read_input_file( file_name_type input_filename );

public:
  const lattice_info_type lattice_info() const 
   { return this->lattice_info_; }
  const bulk_info_type bulk_info() const 
   { return this->bulk_info_; }
  const expansion_order_type expansion_order() const 
   { return this->expansion_order_; }
  const external_program_name_type external_program_name() const 
   { return this->external_program_name_; }
  const basis_set_name_type basis_set_name() const
   { return this->basis_set_name_; }
  const correlation_name_type correlation_name() const
   { return this->correlation_name_; }
  const job_name_type job_name() const 
   { return this->job_name_; }
  const path_name_type scratch_name() const 
   { return this->scratch_name_; }
  const run_mode_name_type run_mode_name() const
   { return this->run_mode_name_; }

private:
  lattice_info_type            lattice_info_;
  bulk_info_type               bulk_info_;
  expansion_order_type         expansion_order_;
  correlation_name_type      correlation_name_;
  external_program_name_type   external_program_name_;
  basis_set_name_type          basis_set_name_;
  run_mode_name_type           run_mode_name_;
  job_name_type                job_name_;
  path_name_type               scratch_name_;

}; // end of struct Request

} // end of namespace manybody_expansion

} // end of namespace iquads

#endif
