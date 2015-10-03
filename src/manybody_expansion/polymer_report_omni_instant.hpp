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

#ifndef MANYBODY_EXPANSION_POLYMER_REPORT_OMNI_INSTANT_HPP
#define MANYBODY_EXPANSION_POLYMER_REPORT_OMNI_INSTANT_HPP

#include <manybody_expansion/polymer_report_omni_template.hpp>

namespace iquads {

namespace manybody_expansion {

  template struct PolymerOmniReportGeneral<1>;
  template struct PolymerOmniReportGeneral<2>;
  template struct PolymerOmniReportGeneral<3>;
  template struct PolymerOmniReportGeneral<4>;

//  template struct PolymerOmniReportPeriodic<1>;
//  template struct PolymerOmniReportPeriodic<2>;
//  template struct PolymerOmniReportPeriodic<3>;
//  template struct PolymerOmniReportPeriodic<4>;

} // end of namespace manybody_expansion

} // end of namespace iquads

#endif
