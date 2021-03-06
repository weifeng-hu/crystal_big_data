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

#ifndef COMPUTE_INTERACTION_ENERGY_WITH_FRAGMENT_IDENTIFICATION_TRAITS_HPP
#define COMPUTE_INTERACTION_ENERGY_WITH_FRAGMENT_IDENTIFICATION_TRAITS_HPP

#include <string>
#include <structure/molecule.hpp>
#include <structure/polymer_template.hpp>
#include <manybody_expansion/fragment_signature_database.hpp>
#include <manybody_expansion/polymer_report_omni_instant.hpp>

namespace iquads {

using structure :: Molecule;
typedef Molecule molecule_obj_type;
typedef std :: string polymer_name_type;
typedef iquads :: manybody_expansion :: FragmentSignatureDataBase database_type;
typedef std :: tuple < std :: tuple< int, int, int >, int > lattice_index_type;

template < size_t NUM > 
using polymer_type = typename structure :: Polymer < NUM >;

namespace manybody_expansion {

  /**
   *  We have to have an additional protrocol to test whether the calculations of a
   *  certain fragment has been done already.
   *
   */
typedef double energy_data_type;

template < size_t Order > inline energy_data_type compute_interaction_energy_with_fragment_identification( std :: array< lattice_index_type, Order > x, polymer_name_type polymer_name, const database_type& database, PolymerOmniReportGeneral<Order>& report )
  { return 0.0e0; } // end of function compute_interaction_energy_with_fragment_identification<Order>

template <> inline energy_data_type compute_interaction_energy_with_fragment_identification<1> ( std :: array< lattice_index_type, 1 > x, polymer_name_type polymer_name, const database_type& database, PolymerOmniReportGeneral<1>& report ) {

  energy_data_type energy_monomer_0;
  std :: string molecule_name = std :: string ( polymer_name + std :: string( "_molecule" ) );
  PolymerReport<1> report_from_database = database.get_report_by_lattice_index<1>( x );
  energy_monomer_0 = report_from_database.fragment_energy();

  /*
  PolymerReport<1> report_local( molecule_name, 
                                 report_from_database.atom_list(),
                                 report_from_database.geometry_unit(),
                                 report_from_database.composition_list(),
                                 report_from_database.fragment_energy(),
                                 0.0e0,
                                 report_from_database.electron_correlation_report(),
                                 report_from_database.external_program_report());
  report.set_report_cover( report_local );
  */
  return energy_monomer_0;

}; // end of function compute_interaction_energy_with_fragment_identification<1>

template <> inline energy_data_type compute_interaction_energy_with_fragment_identification<2>( std :: array< lattice_index_type, 2 > x, polymer_name_type polymer_name, const database_type& database, PolymerOmniReportGeneral<2>& report ) {

  energy_data_type energy_dimer_01;
  std :: string dimer_name = std :: string ( polymer_name + std :: string( "_moleculeAB" ) );
  PolymerReport<2> report_from_database = database.get_report_by_lattice_index<2>( x );
  energy_dimer_01 = report_from_database.fragment_energy();

  std :: string monomer_name_1 = std :: string( polymer_name + std :: string( "_moleculeA" ) );
  std :: string monomer_name_2 = std :: string( polymer_name + std :: string( "_moleculeB" ) );
  energy_data_type energy_monomer_0 = compute_interaction_energy_with_fragment_identification<1> ( std :: array< lattice_index_type, 1 > { x[0] }, monomer_name_1, database, report.set_monomer_reports().at(0) );
  energy_data_type energy_monomer_1 = compute_interaction_energy_with_fragment_identification<1> ( std :: array< lattice_index_type, 1 > { x[1] }, monomer_name_2, database, report.set_monomer_reports().at(1) );

  /*
  PolymerReport<2> report_local( dimer_name,
                                 report_from_database.atom_list(),
                                 report_from_database.geometry_unit(),
                                 report_from_database.composition_list(),
                                 report_from_database.fragment_energy(),
                                 energy_dimer_01 - energy_monomer_0 - energy_monomer_1,
                                 report_from_database.electron_correlation_report(),
                                 report_from_database.external_program_report() );
  report.set_report_cover( report_local );
  */

  // std :: cout << "\tinteraction energy:\t" << energy_dimer_01 - energy_monomer_0 - energy_monomer_1 << std :: endl;
  return energy_dimer_01 - energy_monomer_0 - energy_monomer_1;

}; // end of function compute_interaction_energy_with_fragment_identification<2>

template <> inline energy_data_type compute_interaction_energy_with_fragment_identification<3>( std :: array< lattice_index_type, 3 > x, polymer_name_type polymer_name, const database_type& database, PolymerOmniReportGeneral<3>& report ) {

  energy_data_type energy_trimer_012;
  std :: string trimer_name = std :: string( polymer_name + std :: string( "_moleculeABC" ) );
  PolymerReport<3> report_from_database = database.get_report_by_lattice_index<3>( x );
  energy_trimer_012 = report_from_database.fragment_energy();

  std :: string monomer_name_1 = std :: string( polymer_name + std :: string( "_moleculeA" ) );
  std :: string monomer_name_2 = std :: string( polymer_name + std :: string( "_moleculeB" ) );
  std :: string monomer_name_3 = std :: string( polymer_name + std :: string( "_moleculeC" ) );
  energy_data_type energy_monomer_0 = compute_interaction_energy_with_fragment_identification<1> ( std :: array< lattice_index_type, 1 > { x[0] }, monomer_name_1, database, report.set_monomer_reports().at(0) );
  energy_data_type energy_monomer_1 = compute_interaction_energy_with_fragment_identification<1> ( std :: array< lattice_index_type, 1 > { x[1] }, monomer_name_2, database, report.set_monomer_reports().at(1) );
  energy_data_type energy_monomer_2 = compute_interaction_energy_with_fragment_identification<1> ( std :: array< lattice_index_type, 1 > { x[2] }, monomer_name_3, database, report.set_monomer_reports().at(2) );

  std :: string dimer_name_1 = std :: string( polymer_name + std :: string( "_moleculeAB" ) );
  std :: string dimer_name_2 = std :: string( polymer_name + std :: string( "_moleculeAC" ) );
  std :: string dimer_name_3 = std :: string( polymer_name + std :: string( "_moleculeBC" ) );
  energy_data_type interaction_energy_dimer_01 = compute_interaction_energy_with_fragment_identification<2>( std :: array< lattice_index_type, 2 > { x[0], x[1] }, dimer_name_1, database, report.set_dimer_reports().at(0) );
  energy_data_type interaction_energy_dimer_02 = compute_interaction_energy_with_fragment_identification<2>( std :: array< lattice_index_type, 2 > { x[0], x[2] }, dimer_name_2, database, report.set_dimer_reports().at(1) );
  energy_data_type interaction_energy_dimer_12 = compute_interaction_energy_with_fragment_identification<2>( std :: array< lattice_index_type, 2 > { x[1], x[2] }, dimer_name_3, database, report.set_dimer_reports().at(2) );

  energy_data_type interaction_energy = energy_trimer_012 - 
                                        energy_monomer_0 - energy_monomer_1 - energy_monomer_2 - 
                                        interaction_energy_dimer_01 - interaction_energy_dimer_02 - interaction_energy_dimer_12;
  /*
  PolymerReport<3> report_local( trimer_name,
                                 report_from_database.atom_list(),
                                 report_from_database.geometry_unit(),
                                 report_from_database.composition_list(),
                                 report_from_database.fragment_energy(),
                                 interaction_energy,
                                 report_from_database.electron_correlation_report(),
                                 report_from_database.external_program_report() );
  report.set_report_cover( report_local );
  */
  // std :: cout << "\tinteraction energy:\t" << interaction_energy << std :: endl;

  return interaction_energy;

}; // end of function compute_interaction_energy_with_fragment_identification<3>

template <> inline energy_data_type compute_interaction_energy_with_fragment_identification<4> ( std :: array< lattice_index_type, 4 > x, polymer_name_type polymer_name, const database_type& database, PolymerOmniReportGeneral<4>& report ) {

  energy_data_type energy_tetramer_0123;
  std :: string tetramer_name = std :: string( polymer_name + std :: string( "_moleculeABCD" ) );
  PolymerReport<4> report_from_database = database.get_report_by_lattice_index<4>( x );
  energy_tetramer_0123 = report_from_database.fragment_energy();
  
  std :: string monomer_name_1 = std :: string( polymer_name + std :: string( "_moleculeA" ) );
  std :: string monomer_name_2 = std :: string( polymer_name + std :: string( "_moleculeB" ) );
  std :: string monomer_name_3 = std :: string( polymer_name + std :: string( "_moleculeC" ) );
  std :: string monomer_name_4 = std :: string( polymer_name + std :: string( "_moleculeD" ) );
  energy_data_type energy_monomer_0 = compute_interaction_energy_with_fragment_identification<1> ( std :: array< lattice_index_type, 1 > { x[0] } , monomer_name_1, database, report.set_monomer_reports().at(0) );
  energy_data_type energy_monomer_1 = compute_interaction_energy_with_fragment_identification<1> ( std :: array< lattice_index_type, 1 > { x[1] } , monomer_name_2, database, report.set_monomer_reports().at(1) );
  energy_data_type energy_monomer_2 = compute_interaction_energy_with_fragment_identification<1> ( std :: array< lattice_index_type, 1 > { x[2] } , monomer_name_3, database, report.set_monomer_reports().at(2) );
  energy_data_type energy_monomer_3 = compute_interaction_energy_with_fragment_identification<1> ( std :: array< lattice_index_type, 1 > { x[3] } , monomer_name_4, database, report.set_monomer_reports().at(3) );

  std :: string dimer_name_1 = std :: string( polymer_name + std :: string( "_moleculeAB" ) );
  std :: string dimer_name_2 = std :: string( polymer_name + std :: string( "_moleculeAC" ) );
  std :: string dimer_name_3 = std :: string( polymer_name + std :: string( "_moleculeAD" ) );
  std :: string dimer_name_4 = std :: string( polymer_name + std :: string( "_moleculeBC" ) );
  std :: string dimer_name_5 = std :: string( polymer_name + std :: string( "_moleculeBD" ) );
  std :: string dimer_name_6 = std :: string( polymer_name + std :: string( "_moleculeCD" ) );
  energy_data_type interaction_energy_dimer_01 = compute_interaction_energy_with_fragment_identification<2> ( std :: array< lattice_index_type, 2 > { x[0] , x[1] }, dimer_name_1, database, report.set_dimer_reports().at(0) );
  energy_data_type interaction_energy_dimer_02 = compute_interaction_energy_with_fragment_identification<2> ( std :: array< lattice_index_type, 2 > { x[0] , x[2] }, dimer_name_2, database, report.set_dimer_reports().at(1) );
  energy_data_type interaction_energy_dimer_03 = compute_interaction_energy_with_fragment_identification<2> ( std :: array< lattice_index_type, 2 > { x[0] , x[3] }, dimer_name_3, database, report.set_dimer_reports().at(2) );
  energy_data_type interaction_energy_dimer_12 = compute_interaction_energy_with_fragment_identification<2> ( std :: array< lattice_index_type, 2 > { x[1] , x[2] }, dimer_name_4, database, report.set_dimer_reports().at(3) );
  energy_data_type interaction_energy_dimer_13 = compute_interaction_energy_with_fragment_identification<2> ( std :: array< lattice_index_type, 2 > { x[1] , x[3] }, dimer_name_5, database, report.set_dimer_reports().at(4) );
  energy_data_type interaction_energy_dimer_23 = compute_interaction_energy_with_fragment_identification<2> ( std :: array< lattice_index_type, 2 > { x[2] , x[3] }, dimer_name_6, database, report.set_dimer_reports().at(5) );

  std :: string trimer_name_1 = std :: string( polymer_name + std :: string( "_moleculeABC" ) );
  std :: string trimer_name_2 = std :: string( polymer_name + std :: string( "_moleculeABD" ) );
  std :: string trimer_name_3 = std :: string( polymer_name + std :: string( "_moleculeACD" ) );
  std :: string trimer_name_4 = std :: string( polymer_name + std :: string( "_moleculeBCD" ) );
  energy_data_type interaction_energy_trimer_012 = compute_interaction_energy_with_fragment_identification<3>( std :: array< lattice_index_type, 3 > { x[0] , x[1] , x[2] }, trimer_name_1, database, report.set_trimer_reports().at(0) );
  energy_data_type interaction_energy_trimer_013 = compute_interaction_energy_with_fragment_identification<3>( std :: array< lattice_index_type, 3 > { x[0] , x[1] , x[3] }, trimer_name_2, database, report.set_trimer_reports().at(1) );
  energy_data_type interaction_energy_trimer_023 = compute_interaction_energy_with_fragment_identification<3>( std :: array< lattice_index_type, 3 > { x[0] , x[2] , x[3] }, trimer_name_3, database, report.set_trimer_reports().at(2) );
  energy_data_type interaction_energy_trimer_123 = compute_interaction_energy_with_fragment_identification<3>( std :: array< lattice_index_type, 3 > { x[1] , x[2] , x[3] }, trimer_name_4, database, report.set_trimer_reports().at(3) );

  energy_data_type interaction_energy =  energy_tetramer_0123 -
                                         energy_monomer_0 - energy_monomer_1 - energy_monomer_2 - energy_monomer_3 -
                                         interaction_energy_dimer_01 - interaction_energy_dimer_02 - interaction_energy_dimer_03 -
                                         interaction_energy_dimer_12 - interaction_energy_dimer_13 - 
                                         interaction_energy_dimer_23 -
                                         interaction_energy_trimer_012 - interaction_energy_trimer_013 - 
                                         interaction_energy_trimer_023 - interaction_energy_trimer_123;
  /*
  PolymerReport<4> report_local( tetramer_name,
                                 report_from_database.atom_list(),
                                 report_from_database.geometry_unit(),
                                 report_from_database.composition_list(),
                                 report_from_database.fragment_energy(),
                                 interaction_energy,
                                 report_from_database.electron_correlation_report() ,
                                 report_from_database.external_program_report() );
  report.set_report_cover( report_local );
  */

  //std :: cout << "\tinteraction energy:\t" << interaction_energy << std :: endl;

  return interaction_energy;
 
}; // end of function compute_interaction_energy_with_fragment_identification<4>

} // end of namespace manybody_expansion

} // end of namespace iquads

#endif
