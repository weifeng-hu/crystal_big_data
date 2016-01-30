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

#ifndef MANYBODY_EXPANSION_TEMPLATE_HPP
#define MANYBODY_EXPANSION_TEMPLATE_HPP

#include <iquads/sequence.hpp>
#include <manybody_expansion/config.hpp>
#include <electron_correlation/setting.hpp>
#include <manybody_expansion/fragment_signature_database.hpp>
#include <manybody_expansion/report.hpp>
#include <manybody_expansion/expansion_formula_general_traits.hpp>
#include <manybody_expansion/expansion_formula_periodic_traits.hpp>
#include <manybody_expansion/expansion_formula_periodic_with_fragment_identification_traits.hpp>

namespace iquads {

namespace manybody_expansion {

  /**
   *  A class template for the top level many expansion expansion formulism
   *  Here we have two different classes: periodic and non-periodic.
   *  Periodic many body expansion uses the typename ManybodyExpansionPeriodic for 
   *  periodic but infinite lattice, and it can return a lattice energy PER UNIT CELL.
   *  The non-periodic version uses ManyBodyExpansionGeneral as the typename, which 
   *  can return a total energy or an averaged energy per node, e.g., a molecule.
   *
   *  The purpose of this template class is to give a object which represents the 
   *  "many body expansion system". Therefore, this class should have a method
   *  to use the actual formalism for a specific input target physical/chemical system.
   *
   *  Since different expansion order can give different numbers of terms when using
   *  many body expansion formalism, so the actual formula for different expansion orders
   *  in both the general expansion and periodic expansion schemes, are different.
   *  Instead of implementing distinct formalism objects for different expansion orders,
   *  here we use the template with the expansion order as the parameter, to define 
   *  a general purpose object for any order of expansion formalism. This enables the 
   *  same interface to invoke the actual formalism for a certain expansion order, though 
   *  formalism for different orders need to be implemented explicitly using traits, and 
   *  further explicitly instantiated at compile-time.
   *
   *  As a templated system object, it can either holds a templated member 
   *  function/method which will be differently instantiated for different orders.
   *  Or it can hold an actual formalism object which will be differently instantiated 
   *  for different orders, but provide the same interface to be invoked.
   *  We choose the latter way, by implementing a lower level object, the actual 
   *  fomulars, to enforece the concept "an actual computational system contains the 
   *  fomular but also should have other elements, like input and output".
   *
   *  This many body expansion system will be used by an agent, which passes in a config
   *  meta-data object and waits for the report object returned by this system.
   *  The report object is created outside the system, and use reference to be passed in,
   *  since it can contain a big amount of data and we avoid using the copy constructor.
   *  This system returns a final energy value but also manipulates the report data.
   *
   */

  /**
   *  Templated class ManyBodyExpansionGeneral
   *  for non-periodic calculations
   */
template < size_t Order > class ManyBodyExpansionGeneral {
public:
  typedef ExpansionFormulaGeneral<Order>  expansion_formula_type;
  typedef Config                          config_type;
  typedef Report                          report_type;
  typedef double                          energy_data_type;
  typedef bool                            condition_type;
  typedef report_type&                    report_ref;

public:
  energy_data_type
  compute_bulk_energy( config_type config, report_ref report )
    { return this->expansion_formula_.compute( config, report ); }

private:
  expansion_formula_type expansion_formula_;

}; // end of template class manybody_expansion_general

  /**
   *  Templated class ManyBodyExpansionPeriodic
   *  for periodic calculations
   */
template < size_t Order > class ManyBodyExpansionPeriodic {
public:
  typedef FragmentSignatureDataBase                                  fragment_signature_database_type;
  typedef ExpansionFormulaPeriodic<Order>                            expansion_formula_type;
  typedef ExpansionFormulaPeriodicWithFragmentIdentification<Order>  expansion_with_fragment_identif_formula_type;
  typedef Config                                                     config_type;
  typedef iquads :: electron_correlation :: Setting                  electron_calc_setting_type;
  typedef Report                                                     report_type;
  typedef double                                                     energy_data_type;
  typedef bool                                                       condition_type;
  typedef report_type&                                               report_ref;

public:
  energy_data_type 
  compute_lattice_energy_per_unit_cell( config_type config, report_ref report )
    { return this->expansion_formula_.compute( config, report ); }

  energy_data_type 
  compute_lattice_energy_per_unit_cell_with_fragment_identification( config_type config, report_ref report ) {
    electron_calc_setting_type setting;
    setting.generate_from( config );

    this->fragment_signature_database_.build( config.expansion_order(), config.lattice_info(), config.radius(), setting );

    if( config.run_mode() == iquads :: sequence :: mode :: LOCAL_RUN ||
        config.run_mode() == iquads :: sequence :: mode :: COLLECT_LOCAL_OUTPUT ) {
      return this->expansion_formula_with_fragment_identification_.compute( config, this->fragment_signature_database_, report );
    }
  }

public:
  const fragment_signature_database_type& fragment_sigature_database() const 
    { return this->fragment_signature_database_; }

private:
  expansion_formula_type                        expansion_formula_;
  expansion_with_fragment_identif_formula_type  expansion_formula_with_fragment_identification_;
  fragment_signature_database_type              fragment_signature_database_;

};// end of template class ManyBodyExpansionPeriodic

} // end of namespace manybody_expansion

} // end of namespace iquads

#endif
