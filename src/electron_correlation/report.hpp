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

#ifndef ELECTRON_CORRELATION_REPORT_HPP
#define ELECTRON_CORRELATION_REPORT_HPP

#include <string>
#include <structure/molecule.hpp>
#include <interface_to_third_party/external_program_report.hpp>

using std::string;

namespace iquads {

using structure :: Molecule;
using interface_to_third_party :: ExternalProgramReport;

namespace electron_correlation {

struct Report
{
public:
  typedef Molecule molecule_info_type;
  typedef ExternalProgramReport external_report_type;
  typedef double energy_data_type;

public:
  void collect_data_from_external_report( external_report_type external_report );

public:
  const molecule_info_type molecule_info() const 
   { return this->molecule_info_; }
  const energy_data_type energy() const 
   { return this->energy_; }

private:
  molecule_info_type molecule_info_;
  energy_data_type energy_;
  /*
   *
   * Other data members can be wavefunctions, MO coefficients, etc.
   *
   */

}; // end of struct Report

} // end of namespace electron_correlation

} // end of namespace iquads

#endif
