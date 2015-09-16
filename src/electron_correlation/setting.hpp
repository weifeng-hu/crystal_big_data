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

#include <string>
#include <iquads/sequence.hpp>
#include <structure/molecule.hpp>
#include <manybody_expansion/config.hpp>
#include <interface_to_third_party/program_mask.hpp>

namespace iquads {

namespace electron_correlation {

struct Setting {
public:
  typedef structure :: Molecule molecule_info_type;
  typedef string basis_set_name_type;
  typedef typename interface_to_third_party :: program :: program_mask_type external_program_type;
  typedef typename sequence :: mode :: mode_mask_type mode_type;
  typedef manybody_expansion :: Config mbe_config_type;
  typedef bool condition_type;

public:
  void generate_from_config( mbe_config_type config );
  const condition_type use_internal_solver() const 
    { return external_program_ == interface_to_third_party :: program :: IQUADS ? true : false; }
  const external_program_type external_program() const 
    { return this->external_program_; }
  const mode_type mode() const { return this->mode_; }
  const basis_set_name_type basis_set_name() const { return this->basis_set_name_; }

private:
  mode_type mode_;
  molecule_info_type molecule_info_;
  basis_set_name_type basis_set_name_;
  external_program_type external_program_;

}; // end of struct Setting

} // end of namespace electron_correlation

} // end of namespace iquads 

#endif
