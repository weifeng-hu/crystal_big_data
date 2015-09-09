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
 * the Free Software Foundation, either version 3 of the License, or
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

#ifndef MANYBODY_EXPANSION_CONFIG_HPP
#define MANYBODY_EXPANSION_CONFIG_HPP

#include <string>
#include <memory>
#include <electron_correlation/config.hpp>

using std::string;
using std::shared_ptr;

namespace iquads {

namespace manybody_expansion {

class Config
{
public:
  typedef iquads :: electron_correlation :: Config electron_correlation_config_type;
  typedef string file_name_type;
  typedef string program_name_type;
  typedef bool condition_type;
  typedef unsigned int bitmask_type;
  typedef unsigned int order_type;

  typedef condition_type& condition_ref;

public:
  const bitmask_type total_order_mask() const 
   { return this->total_order_mask_; }
  const condition_type is_periodic() const 
   { return this->is_periodic_; }
  condition_ref set_is_periodic()
   { return this->is_periodic_; }
  const condition_type to_set_up_only() const
   { return this->to_set_up_only_; }
  condition_ref set_to_set_up_only()
   { return this->to_set_up_only_; }
  const bitmask_type external_program_mask() const
   { return this->external_program_mask_; }
  const order_type order() const 
   { return this->order_; }

private:
  electron_correlation_config_type electron_correlation_config_;

  condition_type first_order_requested_;
  condition_type second_order_requested_;
  condition_type third_order_requested_;
  condition_type forth_order_requested_;
  condition_type fifth_order_requested_;
  bitmask_type total_order_mask_;
  order_type order_;

  condition_type is_periodic_;
  condition_type to_set_up_only_;
  program_name_type external_program_name_;
  bitmask_type external_program_mask_;

}; // end of class Config

} // end of namespace manybody_expansion

} // end of namespace iquads

#endif
