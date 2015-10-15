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

#ifndef ELECTRON_CORRELATION_SETTING_HPP
#define ELECTRON_CORRELATION_SETTING_HPP

#include <iostream>
#include <string>
#include <iquads/sequence.hpp>
#include <structure/molecule.hpp>
//#include <electron_correlation/config.hpp>
#include <manybody_expansion/config.hpp>
#include <interface_to_third_party/program_mask.hpp>

namespace iquads {

namespace electron_correlation {

  /**
   *  A electron correlation calculation "setting" object
   *  is some object to store general environment variables.
   *  These variables, can be universal for a lot of similar 
   *  calculations, like a series of calculations in crystal 
   *  lattice energy ones. Therefore, these instances do not 
   *  have the data of any actual molecule information, since 
   *  molecule information can change from one calculation to 
   *  another.
   *
   *  This definition is different from the one of Config object,
   *  which is designed to strongly depend on individual calculation.
   *  Config struct has molecule information.
   *
   *  A general view about what data this struct can hold (and can be
   *  kind of universal for a large amount of calculations) are:
   *   + Run mode (dryrun, remote, etc. )
   *   + basis set info
   *   + external program info
   *   + main directories
   *
   *  There are duplicated functionalities between Setting
   *  and Config. But they are designed for different purposes.
   *
   */

using namespace iquads :: sequence;
using namespace iquads :: interface_to_third_party;
using std :: string;
using std :: ostream;

struct Setting {
public:
  typedef Setting                        this_type;
  typedef string                         basis_set_name_type;
  typedef string                         path_name_type;
  typedef program :: program_mask_type   external_program_type;
  typedef mode :: mode_mask_type         mode_type;
//  typedef electron_correlation :: Config config_type;
  typedef manybody_expansion :: Config   mbe_config_type;
  typedef bool condition_type;

public:
  /**
   *  Default constructor
   */
  Setting()
    {
      this->mode_ = mode :: UNKNOWN;
      this->basis_set_name_ = "not set";
      /**
       *  We don't have UNKNOWN for program
       *  since IQUADS solvers should always be ready.
       */
      this->external_program_ = program :: IQUADS;
      this->input_path_ = "not set";
      this->scratch_path_ = "not set";
      this->output_path_ = "not set";
    }
  /**
   *  Initialize list constructor
   */
  Setting( mode_type mode,
           basis_set_name_type basis_set_name,
           size_t spin,
           size_t sym,
           external_program_type external_program,
           path_name_type input_path,
           path_name_type scratch_path,
           path_name_type output_path ) :
    mode_ ( mode ), basis_set_name_ ( basis_set_name ), 
    spin_ ( spin ), sym_ ( sym ),
    external_program_ ( external_program ),
    input_path_   ( input_path ),
    scratch_path_ ( scratch_path ),
    output_path_  ( output_path ) { }

public:
  /**
   *  Overloaded functions generate_from()
   *  To generate this struct instance from various external info
   *  As interface between this object and other external info objects
   *  + manybody_expansion Config, holds universal settings for 
   *    all fragment calculations
   *  + Other
   *  Only this function can modify the data members of this struct
   */
//  void generate_from( config_type config ) {}
  void generate_from( mbe_config_type config );

public:
  /**
   *  Stream operators
   */
  /**
   *  + operator <<
   */
  friend
  ostream& operator<< ( ostream& os, this_type& setting_obj ) {
    using std :: cout;
    using std :: endl;
    os << "run mode: "          << setting_obj.mode()              << endl;
    os << "basis set: "         << setting_obj.basis_set_name()    << endl;
    os << "spin: "              << setting_obj.spin()              << endl;
    os << "sym: "               << setting_obj.sym()               << endl;
    os << "external program: "  << setting_obj.external_program()  << endl;
    os << "input path: "        << setting_obj.input_path()        << endl;
    os << "scratch path: "      << setting_obj.scratch_path()      << endl;
    os << "output path: "       << setting_obj.output_path()       << endl;
    return os;
  } // end of operator<<

  /**
   *  Accessors
   */
  mode_type mode() const
    { return this->mode_; }
  basis_set_name_type basis_set_name() const
    { return this->basis_set_name_; }
  size_t spin() const
    { return this->spin_; }
  size_t sym() const
    { return this->sym_; }
  external_program_type external_program() const 
    { return this->external_program_; }
  path_name_type input_path() const
    { return this->input_path_; }
  path_name_type scratch_path() const
    { return this->scratch_path_; }
  path_name_type output_path() const
    { return this->output_path_; }

  /**
   *  Auxiliary accessors
   */
  condition_type use_internal_solver() const 
    { return external_program_ == program :: IQUADS ? true : false; }

private:
  mode_type              mode_;
  basis_set_name_type    basis_set_name_;
  size_t                 spin_;
  size_t                 sym_;
  external_program_type  external_program_;
  path_name_type         input_path_;
  path_name_type         scratch_path_;
  path_name_type         output_path_;

}; // end of struct Setting

} // end of namespace electron_correlation

} // end of namespace iquads 

#endif
