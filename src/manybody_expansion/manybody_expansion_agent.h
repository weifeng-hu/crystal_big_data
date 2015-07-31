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

#ifndef MANYBODY_EXPANSION_AGENT_H
#define MANYBODY_EXPANSION_AGENT_H

#include <memory>
#include <manybody_expansion/manybody_expansion_config.h>

using std::shared_ptr;

namespace iquads {

namespace manybody_expansion {

class ManyBodyExpansionAgent
{
public:
  typedef ManyBodyExpansionConfig config_type;
  typedef shared_ptr<config_type> config_shared_pointer_type;
  typedef unsigned int order_type;

public:
  int execute();

private:
  int execute_general();
  int execute_periodic();

public:
  const config_shared_pointer_type config_shared_pointer() const
   { return this->config_shared_pointer_; }

private:
  config_shared_pointer_type config_shared_pointer_;
  order_type order_;

}; // end of class ManyBodyExpansionAgent

} // end of namespace manybody_expansion

} // end of namespace iquads

#endif
