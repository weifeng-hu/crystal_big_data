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
#include <manybody_expansion/lattice.hpp>

using std::string;

namespace iquads {

namespace manybody_expansion {

struct Request {
public:
  typedef Lattice lattice_info_type;
  typedef size_t expansion_order_type;
  typedef string correlation_method_type;
  typedef string correlation_level_type;
  typedef string external_program_name_type;
  typedef bool condition_type;
  typedef unsigned int run_mode_type;
  typedef string file_name_type;
  typedef string prefix_type;
  typedef string job_name_type;

public:
  void read_input_file( file_name_type input_filename )
   { /* to be implemented */ };

private:
  lattice_info_type lattice_info_;
  expansion_order_type order_;
  correlation_level_type correlation_level_;
  correlation_method_type correlation_method_;
  condition_type use_external_energy_solver_;
  external_program_name_type external_program_name_;
  run_mode_type run_mode_;
  prefix_type prefix_;
  job_name_type job_name_;

}; // end of struct Request

} // end of namespace manybody_expansion

} // end of namespace iquads

#endif
