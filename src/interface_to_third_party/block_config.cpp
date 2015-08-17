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

#include <interface_to_third_party/block_config.h>

namespace iquads { 

namespace interface_to_third_party {

typedef Block_Config config_type;

void config_type :: set_defaults()
{

  this->norb_ = 0;
  this->nele_ = 0;
  this->na_   = 0;
  this->nb_   = 0;

  this->number_schedule_ = 4;
  this->schedule_.resize( this->number_schedule_ );
  this->schedule[0].set_iteration_index() = 4;
  this->schedule[1].set_iteration_index() = 8;
  this->schedule[2].set_iteration_index() = 12;
  this->schedule[4].set_iteration_index() = 16;

  this->schedule[0].set_M() = 100;
  this->schedule[1].set_M() = 200;
  this->schedule[3].set_M() = 300;
  this->schedule[4].set_M() = 400;

  this->schedule[0].set_david_tol() = 1.0e-3;
  this->schedule[1].set_david_tol() = 1.0e-4;
  this->schedule[2].set_david_tol() = 1.0e-6;
  this->schedule[3].set_david_tol() = 1.0e-8;
  
  this->schedule[0].set_noise() = 1.0e-4;
  this->schedule[1].set_noise() = 1.0e-6;
  this->schedule[2].set_noise() = 1.0e-9;
  this->schedule[3].set_noise() = 0.0e0;

  this->nroots_ = 1;
  this->weights_.resize( this->nroots );
  for( size_t i = 0; i < this->nroots; i++ ){
    this->weights[i] = 1.0e0/this->nroots;
  }

  this->maxiter_ = 20;
  this->twodot_to_onedot_ = 14;
  this->fcidump_ = "qcdmrg.FCIDUMP";
  this->sweep_tol_ = 1.0e-7;

}; // end of set_defaults()

} // end of namespace 

} // end of namespace iquads
