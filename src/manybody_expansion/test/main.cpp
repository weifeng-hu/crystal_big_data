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

#include <manybody_expansion/request.hpp>
#include <manybody_expansion/config.hpp>
#include <manybody_expansion/report.hpp>
#include <manybody_expansion/agent.hpp>
#include <manybody_expansion/client.hpp>
#include <manybody_expansion/polymer_report_subgroup_traits.hpp>
#include <manybody_expansion/polymer_report_template.hpp>
#include <manybody_expansion/polymer_report_omni_template.hpp>

int main( int argc, char* argv[] ) {

  using iquads :: manybody_expansion :: Request;
  using iquads :: manybody_expansion :: Config;
  using iquads :: manybody_expansion :: Client;
  using iquads :: manybody_expansion :: Agent;
  using iquads :: manybody_expansion :: PolymerReport;
  using iquads :: manybody_expansion :: PolymerOmniReportGeneral;
  PolymerReport<1> monomer_report;
  PolymerOmniReportGeneral<1> report_x;
  

  using std :: cout;
  using std :: endl;
//  cout << trimer_report.composition_list().size() << endl;

  Request request;
  Config config;
  Client client;
  Agent agent;

} 
