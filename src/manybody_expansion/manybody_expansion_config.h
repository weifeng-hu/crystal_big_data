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

#ifndef MANYBODY_EXPANSION_CONFIG_H
#define MANYBODY_EXPANSION_CONFIG_H

#include <string>
#include <manybody_expansion/electron_correlation_config.h>

using std::string;

namespace iquads {

namespace manybody_expansion {

using electron_correlation :: ElectronCorrelation_Config;

class ManyBodyExpansionConfig
{
public:
  typedef string filename_type;
  typedef bool condition_type;
  typedef condition_type& condition_reference;
  typedef unsigned int bitmask_type;
  typedef bitmask_type& bitmask_reference;
  typedef ElectronCorrelation_Config electron_correlation_config_type;
  typedef electron_correlation_config_type& electron_correlation_config_reference;

public:
  // read config file, define in .cpp
  void read_config( filename_type filename );

public:
  const bitmask_type total_order_mask() const 
   { return this->total_order_mask_; }

  const condition_type is_periodic() const 
   { return this->is_periodic_; }
  condition_reference set_is_periodic()
   { return this->is_periodic_; }
  const condition_type to_set_up_only() const
   { return this->to_set_up_only_; }
  condition_reference set_to_set_up_only()
   { return this->to_set_up_only_; }

private:
  electron_correlation_config_type electron_correlation_config_;

  condition_type first_order_requested_;
  condition_type second_order_requested_;
  condition_type third_order_requested_;
  condition_type forth_order_requested_;
  condition_type fifth_order_requested_;
  bitmask_type total_order_mask_;

  condition_type is_periodic_;
  condition_type to_set_up_only_;

}; // end of class ManyBodyExpansionConfig

} // end of namespace manybody_expansion

} // end of manybody_expansion

#endif
