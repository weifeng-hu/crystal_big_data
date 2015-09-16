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

void setting_type :: generate_from_config( mbe_config_type config ){

  this->mode_ = config.mode();
  this->use_external_ = config.use_external_solver();
  if( this->use_external_ == true ){
   this->external_program_ = config.external_program();
  }
  this->basis_set_name_ = config.basis_set_name();
  this->method_ = config.method();

} // end of function generate_from_config()

} // end of electron_correlation

} // end of namespace iquads
