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

namespace iquads {

namespace electron_correlation {

struct Setting {
public:
  typedef unsigned int bitmask_type;
  typedef bool condition_type;

public:
  const condition_type use_external_solver() const
   { return this->use_external_solver_; }
  const bitmask_type external_agent_mask() const 
   { return this->external_agent_mask_; }

private:
  condition_type use_external_solver_;
  bitmask_type external_agent_mask_;

}; // end of struct Setting

} // end of namespace electron_correlation

} // end of namespace iquads 

#endif
