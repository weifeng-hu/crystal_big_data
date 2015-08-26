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
#include <structure/molecule.h>
#include <interface_to_third_party/external_program_report.h>

using std::string;

namespace iquads {

namespace electron_correlation {

struct Report
{
public:
  typedef iquads :: structure :: Molecule molecule_type;
  typedef double energy_data_type;
  typedef string correlation_level_type;
  typedef string correlation_method_type;
  typedef iquads :: interface_to_third_party :: ExternalProgramReport external_report_type;

public:
  void collect_data_from_external_report( external_report_type external_report )
   { /* to be implemented */ }

public:
  const energy_data_type energy() const 
   { return this->energy_; }

private:
  molecule_type molecule_;
  correlation_level_type correlation_level_;
  correlation_method_type correlation_method_;
  energy_data_type energy_;
  energy_data_type hf_energy_;

}; // end of struct Report

} // end of namespace electron_correlation

} // end of namespace iquads

#endif
