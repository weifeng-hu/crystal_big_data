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

#include <string>
#include <molecule.h>

using std::string;

namespace iquads {

namespace electron_correlation {

struct Report
{
public:
  typedef molecule molecule_type;
  typedef double energy_data_type;
  typedef string correlation_level_type;
  typedef string correlation_method_type;

private:
  molecule_type molecule_;
  correlation_level_type correlation_level_;
  correlation_method_type correlation_method_;
  energy_data_type total_energy_;
  energy_data_type hf_energy_;

}; // end of struct Report

} // end of namespace electron_correlation

} // end of namespace iquads

#endif
