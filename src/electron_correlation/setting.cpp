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

  this->mode_             = config.run_mode();
  this->basis_set_name_   = config.basis_set_name();
  this->spin_             = -1; // always unknown and let the external program choose the lowest state 
  this->sym_              = 0; // from many body expansion, we always set symmetry to 0
  this->correlation_level_  = config.correlation_method();
  this->external_program_ = config.program();
  this->input_dir_        = std :: string("./") + config.job_name() + std :: string( "/input/" ); // as default
  this->scratch_dir_      = config.scratch_dir() + std :: string( "/" );
  this->output_dir_       = std :: string("./") + config.job_name() + std :: string( "/output/" ); // as default

} // end of function generate_from_config()

} // end of electron_correlation

} // end of namespace iquads
