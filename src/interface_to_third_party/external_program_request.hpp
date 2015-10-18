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

#ifndef EXTERNAL_PROGRAM_REQUEST_HPP
#define EXTERNAL_PROGRAM_REQUEST_HPP

#include <tuple>
#include <vector>
#include <string>
#include <iquads/sequence.hpp>
#include <interface_to_third_party/program_mask.hpp>
#include <structure/molecule.hpp>
#include <electron_correlation/correlation_level.hpp>

namespace iquads {

namespace interface_to_third_party {

/**
 *
 *  External Program Request 
 *  As a request to external program agents, it should contain at least these information:
 *   + the external program to use
 *   + A copy of the molecule info
 *   + calculation type
 *   + method request, basis set
 *   + runtime requests: local? server? dryrun? any detailed directory requests? (mode)
 *
 *  This request instance will be created by any "client" objects, and handed over to 
 *  an external program agent. The agent knows how to use a specific external prorgram.
 * 
 */

using std :: vector;
using std :: string;
using std :: make_tuple;
using std :: get;
using structure :: Molecule;
using namespace sequence;

struct ExternalProgramRequest {
public:
  typedef string                                           basis_set_name_type;
  typedef string                                           molecule_name_type;
  typedef string                                           dir_name_type;
  typedef Molecule                                         molecule_obj_type;
  typedef tuple< molecule_name_type, molecule_obj_type >   molecule_info_type;
  typedef program :: program_mask_type                     external_program_type;
  typedef mode :: mode_mask_type                           mode_type;
  typedef calculation :: calculation_mask_type             calculation_type;
  typedef electron_correlation :: level_mask_type          method_type;
  typedef vector< method_type >                            method_list_type;

public:
  /**
   *  Initialize list constructor
   *  This is the only method which can manipulate data members in this struct.
   *  Developers must make every data member well-defined prior to call the agent.
   */
  ExternalProgramRequest( molecule_name_type     molecule_name,
                          molecule_obj_type      molecule_obj,
                          basis_set_name_type    basis_set_name,
                          size_t                 spin_value,
                          size_t                 sym_value,
                          external_program_type  external_program,
                          mode_type              mode,
                          calculation_type       calculation,
                          method_type            method,
                          dir_name_type          input_directory, 
                          dir_name_type          scratch_directory,
                          dir_name_type          output_directory ) : 
    molecule_info_ ( make_tuple( molecule_name, molecule_obj ) ), basis_set_name_ ( basis_set_name ),
    spin_ ( spin_value ), sym_ ( sym_value ),
    external_program_ ( external_program ), mode_ ( mode ), calculation_ ( calculation ),
    method_( method ), input_dir_(input_directory), scratch_dir_(scratch_directory), output_dir_(output_directory) { };

public:
  /**
   *  Accessors
   */
  molecule_info_type molecule_info() const
    { return this->molecule_info_; }
  basis_set_name_type basis_set_name() const
    { return this->basis_set_name_; }
  external_program_type external_program() const
    { return this->external_program_; }
  size_t spin() const
    { return this->spin_; }
  size_t sym() const 
    { return this->sym_; }
  mode_type mode() const
    { return this->mode_; }
  calculation_type calculation() const
    { return this->calculation_; }
  method_type method() const
    { return this->method_; }
  dir_name_type input_dir() const
    { return this->input_dir_; }
  dir_name_type scratch_dir() const
    { return this->scratch_dir_; }
  dir_name_type output_dir() const
    { return this->output_dir_; }

  /**
   *  Auxiliary accessors
   */
  molecule_name_type molecule_name() const
    { return get<0>( this->molecule_info_ ); }
  molecule_obj_type molecule_obj() const
    { return get<1>( this->molecule_info_ ); }

  /**
   *  Mutators - None
   *  A request is not allowed to be changed once setup
   */

private:
  molecule_info_type      molecule_info_;
  size_t                  spin_;
  size_t                  sym_;
  basis_set_name_type     basis_set_name_;
  external_program_type   external_program_;
  mode_type               mode_;
  calculation_type        calculation_;
  method_type             method_;
  dir_name_type           input_dir_;
  dir_name_type           scratch_dir_;
  dir_name_type           output_dir_;

}; // end of struct ExternalProgramRequest

} // end of namespace interface_to_third_party

} // end of namespace iquads

#endif
