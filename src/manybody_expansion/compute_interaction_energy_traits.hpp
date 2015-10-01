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

#ifndef COMPUTE_INTERACTION_ENERGY_TRAITS_HPP
#define COMPUTE_INTERACTION_ENERGY_TRAITS_HPP

#include <structure/molecule.hpp>
#include <structure/polymer_template.hpp>
#include <electron_correlation/setting.hpp>
#include <electron_correlation/client.hpp>
#include <manybody_expansion/polymer_report_omni_template.hpp>

namespace iquads {

using structure :: Molecule;
typedef Molecule molecule_info_type;

template < size_t NUM > 
using polymer_type = typename structure :: Polymer < NUM >;

typedef electron_correlation :: Client molecular_energy_client_type;
typedef electron_correlation :: Setting energy_calc_setting_type;

namespace manybody_expansion {

typedef double energy_data_type;

template < size_t Order > inline energy_data_type compute_interaction_energy( polymer_type<Order> x, energy_calc_setting_type settings, PolymerOmniReportGeneral<Order>& report )
  { return 0.0e0; } // end of function compute_interaction_energy<Order>

template <> inline energy_data_type compute_interaction_energy<1> ( polymer_type<1> x, energy_calc_setting_type settings, PolymerOmniReportGeneral<1>& report ) {

  energy_data_type energy_monomer_0;
  {
    molecule_info_type molecule = convert_polymer_to_molecule<1>( x );
    molecular_energy_client_type client;
//    client.driver( molecule, settings );
    energy_monomer_0 = client.report().energy();
    PolymerReport<1> report_local( client.report().molecule_name(), 
                                       client.report().atom_list(),
                                       client.report().geometry_unit(),
                                       report.composition_list(),
                                       client.report().energy(),
                                       0.0e0,
                                       client.report().raw(),
                                       client.report().raw_external());
    report.set_report_cover( report_local );
  }
  return energy_monomer_0;

}; // end of function compute_interaction_energy<1>

template <> inline energy_data_type compute_interaction_energy<2>( polymer_type<2> x, energy_calc_setting_type settings, PolymerOmniReportGeneral<2>& report ) {

  energy_data_type energy_dimer_01;
  {
    molecule_info_type molecule_01 = convert_polymer_to_molecule<2> ( x );
    molecular_energy_client_type client;
//    client.driver( molecule_01, settings );
    energy_dimer_01 = client.report().energy();
  }

  energy_data_type energy_monomer_0 = compute_interaction_energy<1> ( x.at(0), settings, report.monomer_reports().at(0) );
  energy_data_type energy_monomer_1 = compute_interaction_energy<1> ( x.at(1), settings, report.monomer_reports().at(1) );

  PolymerReport<2> report_local( client.report().molecule_name(),
                                     client.report().atom_list(),
                                     client.report().geometry_unit(),
                                     report.composition_list(),
                                     client.report().energy(),
                                     energy_dimer_01 - energy_monomer_0 - energy_monomer_1,
                                     client.report().raw(),
                                     client.report().raw_external() );
  report.set_report_cover( report_local );
  return energy_dimer_01 - energy_monomer_0 - energy_monomer_1;

}; // end of function compute_interaction_energy<2>

template <>
inline energy_data_type compute_interaction_energy<3>( polymer_type<3> x, energy_calc_setting_type settings, PolymerOmniReportGeneral<3>& report )
{

  energy_data_type energy_trimer_012;
  {
    molecule_info_type molecule_012 = convert_polymer_to_molecule<3> ( x );
    molecular_energy_client_type client;
//    client.driver( molecule_012, settings );
    energy_trimer_012 = client.report().energy();
  }

  energy_data_type energy_monomer_0 = compute_interaction_energy<1> ( x.at(0), settings, report.monomer_reports().at(0) );
  energy_data_type energy_monomer_1 = compute_interaction_energy<1> ( x.at(1), settings, report.monomer_reports().at(1) );
  energy_data_type energy_monomer_2 = compute_interaction_energy<1> ( x.at(2), settings, report.monomer_reports().at(2) );

  energy_data_type interaction_energy_dimer_01 = compute_interaction_energy<2>( x.at(0) + x.at(1), settings, report.dimer_reports().at(0) );
  energy_data_type interaction_energy_dimer_02 = compute_interaction_energy<2>( x.at(0) + x.at(2), settings, report.dimer_reports().at(1) );
  energy_data_type interaction_energy_dimer_12 = compute_interaction_energy<2>( x.at(1) + x.at(2), settings, report.dimer_reports().at(2) );

  energy_data_type interaction_energy = energy_trimer_012 - 
                                        energy_monomer_0 - energy_monomer_1 - energy_monomer_2 - 
                                        interaction_energy_dimer_01 - interaction_energy_dimer_02 - interaction_energy_dimer_12;

  PolymerReport<3> report_local( client.report().molecule_name(),
                                     client.report().atom_list(),
                                     client.report().geometry_unit(),
                                     report.composition_list(),
                                     client.report().energy(),
                                     interaction_energy,
                                     client.report().raw(),
                                     client.report().raw_external() );
  report.set_report_cover( report_local );
  return interaction_energy;

}; // end of function compute_interaction_energy<3>

template <> inline energy_data_type compute_interaction_energy < 4 > ( polymer_type<4> x, energy_calc_setting_type settings, PolymerOmniReportGeneral<4> report ) {

  energy_data_type energy_tetramer_0123;
  {
    molecule_info_type molecule_0123 = convert_polymer_to_molecule<4> ( x );
    molecule_energy_client_type client;
//    client.driver( molecule_0123, settings );
    energy_tetramer_0123 = client.report().energy();
  }

  energy_data_type energy_monomer_0 = compute_interaction_energy<1> ( x.at(0), settings, report.monomer_reports().at(0) );
  energy_data_type energy_monomer_1 = compute_interaction_energy<1> ( x.at(1), settings, report.monomer_reports().at(1) );
  energy_data_type energy_monomer_2 = compute_interaction_energy<1> ( x.at(2), settings, report.monomer_reports().at(2) );
  energy_data_type energy_monomer_3 = compute_interaction_energy<1> ( x.at(3), settings, report.monomer_reports().at(3) );

  energy_data_type interaction_energy_dimer_01 = compute_interaction_energy<2> ( x.at(0) + x.at(1), settings, report.dimer_reports().at(0) );
  energy_data_type interaction_energy_dimer_02 = compute_interaction_energy<2> ( x.at(0) + x.at(2), settings, report.dimer_reports().at(1) );
  energy_data_type interaction_energy_dimer_03 = compute_interaction_energy<2> ( x.at(0) + x.at(3), settings, report.dimer_reports().at(2) );
  energy_data_type interaction_energy_dimer_12 = compute_interaction_energy<2> ( x.at(1) + x.at(2), settings, report.dimer_reports().at(3) );
  energy_data_type interaction_energy_dimer_13 = compute_interaction_energy<2> ( x.at(1) + x.at(3), settings, report.dimer_reports().at(4) );
  energy_data_type interaction_energy_dimer_23 = compute_interaction_energy<2> ( x.at(2) + x.at(3), settings, report.dimer_reports().at(5) );

  energy_data_type interaction_energy_trimer_012 = compute_interaction_energy<3>(x.at(0)+x.at(1)+x.at(2), settings, report.trimer_reports.at(0) );
  energy_data_type interaction_energy_trimer_013 = compute_interaction_energy<3>(x.at(0)+x.at(1)+x.at(3), settings, report.trimer_reports.at(1) );
  energy_data_type interaction_energy_trimer_023 = compute_interaction_energy<3>(x.at(0)+x.at(2)+x.at(3), settings, report.trimer_reports.at(2) );
  energy_data_type interaction_energy_trimer_123 = compute_interaction_energy<3>(x.at(1)+x.at(2)+x.at(3), settings, report.trimer_reports.at(3) );

  energy_data_type interaction_energy =  energy_tetramer_0123 -
                                         energy_monomer_0 - energy_monomer_1 - energy_monomer_2 - energy_monomer_3 -
                                         interaction_energy_dimer_01 - interaction_energy_dimer_02 - interaction_energy_dimer_03 -
                                         interaction_energy_dimer_12 - interaction_energy_dimer_13 - 
                                         interaction_energy_dimer_23 -
                                         interaction_energy_trimer_012 - interaction_energy_trimer_013 - 
                                         interaction_energy_trimer_023 - interaction_energy_trimer_123;

  PolymerReport<4> report_local( client.report().molecule_name(),
                                 client.report().atom_list(),
                                 client.report().geometry_unit(),
                                 report.composition_list(),
                                 client.report().energy(),
                                 interaction_energy,
                                 client.report().raw(),
                                 client.report().raw_external() );
  report.set_report_cover( report_local );
  return interaction_energy;
 
}; // end of function compute_interaction_energy < 4 >

} // end of namespace manybody_expansion

} // end of namespace iquads

#endif
