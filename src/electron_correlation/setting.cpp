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

#include <electron_correlation/setting.hpp>

namespace iquads {

namespace electron_correlation {

typedef Setting setting_type;

  /**
   *  + generate_from_config()
   *    Generate a computation environment setting from the many body expansion
   *    configuration object.
   *    This is an interface function. It translates the information from config 
   *    to this object.
   *
   */
void setting_type :: generate_from( mbe_config_type config ){

  this->mode_ = config.run_mode();
  this->external_program_ = config.program();
  this->basis_set_name_ = config.basis_set_name();
//  this->method_ = config.correlation_method();
//  this->input_path_   = config.input_path();
  this->scratch_path_ = config.scratch_name();
//  this->output_path_  = config.output_path();

} // end of function generate_from_config()

} // end of electron_correlation

} // end of namespace iquads
