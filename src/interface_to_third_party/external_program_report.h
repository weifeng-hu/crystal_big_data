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

#ifndef EXTERNAL_PROGRAM_REPORT_H
#define EXTERNAL_PROGRAM_REPORT_H

namespace iquads {

namespace interface_to_third_party {

struct ExternalProgramReport {
public:
  struct EnergyReport;
  struct GradientReport;

public:
  typedef ExternalProgramReport parent_report_type;
  typedef ExternalProgramReport :: EnergyReport energy_report_t;
  typedef ExternalProgramReport :: GradientReport gradient_report_t;

public:
  void accept_new_step_data( energy_report_t energy_report )
   {}
  void accept_new_step_data( gradient_report_t gradient_report )
   {}

}; // end of struct ExternalProgramReport

struct ExternalProgramReport :: EnergyReport {

};

struct ExternalProgramReport :: GradientReport {

};

} // end of namespace interface_to_third_party

} // end of namespace iquads

#endif
