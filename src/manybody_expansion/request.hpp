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
#include <structure/bulk_instant.hpp>
#include <manybody_expansion/order_mask.hpp>

namespace iquads {

namespace manybody_expansion {

  /**
   *  A meta-data struct as a request for general many body expansion
   *  calculations.
   *
   *  This request is set as a struct since it is usually not an entity.
   *  The many body expansion calculation request is an object to be 
   *  initialized by the a many body expansion client object at runtime.
   *
   *  The request object will be submitted to a many body expansion agent 
   *  object which actually invokes the many body expansion formalism.
   *
   *  The information of a request should be general, and the data in this
   *  request can be set by an actual user, but need to be properly defined.
   *  Information in the request should be understandable by human, following 
   *  the actual scientific terminology for the many body expansion formalism.
   *
   *  The request object does not have any runtime settings or information to 
   *  control the runtime sequence, which will actually be handled by the 
   *  config structure. The config structure can contain actual technical 
   *  information which are related to the actual calculation but not related 
   *  to the general result of a calculation.
   *
   *  Data members of this request struct are:
   *   + the lattice info/bulk info, i.e. geometrical structure
   *     Note: this request object holds info for both a lattice and a bulk.
   *           Although only one data member will be filled in each use,
   *           We keep both here, just waste some quite little amount of memory.
   *           For the simplicity of the code, we plan not to use boost::any or 
   *           c++0x unions currently for the time-being, but can be future options.
   *   + for a many body expansion calculation, order of the truncation
   *   + correlation method, basis set
   *   + external program
   *   + file path info
   *
   *  Since this struct is an interface between the program and an user, we use literal
   *  data type, i.e., string, integer for data members, althrough they will be further
   *  translated to masks in later stages.
   */

using std :: string;
using std :: tuple;
using std :: get;
using structure :: MolecularLattice;
using structure :: MolecularBulk;

struct Request {
public:
  typedef string                                     lattice_name_type;
  typedef MolecularLattice                           lattice_type;
  typedef tuple< lattice_name_type, lattice_type >   lattice_info_type;
  typedef string                                     bulk_name_type;
  typedef MolecularBulk                              bulk_type;
  typedef tuple< bulk_name_type, bulk_type >         bulk_info_type;
  typedef order :: expansion_order_type              expansion_order_type;
  typedef string    correlation_name_type;
  typedef string    external_program_name_type;
  typedef string    file_name_type;
  typedef string    path_name_type;
  typedef string    job_name_type;
  typedef string    basis_set_name_type;
  typedef string    run_mode_name_type;
  typedef bool      condition_type;

public:
  /**
   *  Default constructor
   *  --- make everything undefined
   */
  Request()
    {
      get<0> ( this->lattice_info_ ) = "not set";
      get<0> ( this->bulk_info_ ) = "not set";
      this->expansion_order_ = 0;
      this->correlation_name_ = "not set";
      this->external_program_name_ = "not set";
      this->basis_set_name_ = "not set";
      this->run_mode_name_ = "not set";
      this->job_name_ = "not set";
      this->input_name_ = "not set";
      this->scratch_name_ = "not set";
      this->output_name_ = "not set";
    }
  /**
   *  We allow an initialize list constructor if user wants to initiate a calculation directly from code
   */
  Request( lattice_info_type lattice_info_obj,
           bulk_info_type    bulk_info_obj,
           expansion_order_type expansion_order_value,
           correlation_name_type correlation_name_value,
           external_program_name_type external_program_name_value,
           basis_set_name_type basis_set_name_value,
           run_mode_name_type run_mode_name_value,
           job_name_type job_name_value,
           path_name_type input_path,
           path_name_type scratch_path,
           path_name_type output_path ) :
     lattice_info_ ( lattice_info_obj ), bulk_info_ ( bulk_info_obj ),
     expansion_order_ ( expansion_order_value ),
     correlation_name_ ( correlation_name_value ),
     external_program_name_ ( external_program_name_value ),
     basis_set_name_ ( basis_set_name_value ),
     run_mode_name_ ( run_mode_name_value ),
     job_name_ ( job_name_value ),
     input_name_ ( input_path ),
     scratch_name_ ( scratch_path ),
     output_name_ ( output_path ) { }

public:
  /**
   *  + read_input_file()
   */
  void read_input_file( file_name_type input_filename );
  /**
   *  + check_sanity()
   *    This function is only responsible for checking
   *    the essential data for a calculation
   */
  condition_type check_sanity();

public:
  /**
   *  Accessors
   */
  lattice_info_type lattice_info() const 
    { return this->lattice_info_; }
  bulk_info_type bulk_info() const 
    { return this->bulk_info_; }
  expansion_order_type expansion_order() const 
    { return this->expansion_order_; }
  external_program_name_type external_program_name() const 
    { return this->external_program_name_; }
  basis_set_name_type basis_set_name() const
    { return this->basis_set_name_; }
  correlation_name_type correlation_name() const
    { return this->correlation_name_; }
  job_name_type job_name() const 
    { return this->job_name_; }
  path_name_type scratch_name() const 
    { return this->scratch_name_; }
  run_mode_name_type run_mode_name() const
    { return this->run_mode_name_; }

  /**
   *  Mutators - none
   *  A request should not be changed once setup
   */

private:
  lattice_info_type            lattice_info_;
  bulk_info_type               bulk_info_;
  expansion_order_type         expansion_order_;
  correlation_name_type        correlation_name_;
  external_program_name_type   external_program_name_;
  basis_set_name_type          basis_set_name_;
  run_mode_name_type           run_mode_name_;
  job_name_type                job_name_;
  path_name_type               input_name_;
  path_name_type               scratch_name_;
  path_name_type               output_name_;

}; // end of struct Request

} // end of namespace manybody_expansion

} // end of namespace iquads

#endif
