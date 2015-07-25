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

#ifndef ELECTRON_CORRELATION_REPORT_H
#define ELECTRON_CORRELATION_REPORT_H

namespace iquads {

namespace manybody_expansion {

namespace electron_correlation {

class ElectronCorrelationReport
{
public:
  typedef double energy_data_type;

public:
  const energy_data_type total_energy() const 
   { return this->total_energy_; }
  energy_data_type total_energy()
   { return this->total_energy_; }
  energy_data_type& set_total_energy()
   { return this->total_energy_; }

private:
  energy_data_type total_energy_;
  
}; // end of class ElectronCorrelationReport

} // end of namespace electron_correlation

} // end of namespace manybody_expansion

} // end of namespace iquads

#endif
