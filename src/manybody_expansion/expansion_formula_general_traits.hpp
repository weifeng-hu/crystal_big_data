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

#ifndef EXPANSION_FORMULA_GENERAL_TRAITS_HPP
#define EXPANSION_FORMULA_GENERAL_TRAITS_HPP

#include <manybody_expansion/config.hpp>
#include <manybody_expansion/report.hpp>

namespace iquads {

namespace manybody_expansion {

typedef double energy_data_type;
typedef Config config_type;
typedef Report report_type;
typedef report_type& report_ref;

template < size_t Order > class ExpansionFormulaGeneral {
public:
  energy_data_type compute( config_type config, report_ref report )
    {
    } // end of compute()

}; // end of class ExpansionFormulaPeriodic< Order >


template <> class ExpansionFormulaGeneral<1> {
public:
  energy_data_type compute( config_type config, report_ref report )
    {
    } // end of compute()

}; // end of class ExpansionFormulaPeriodic<1>


template <> class ExpansionFormulaGeneral<2> {
public:
  energy_data_type compute( config_type config, report_ref report )
    {
    } // end of compute()

}; // end of class ExpansionFormulaPeriodic<2>


template <> class ExpansionFormulaGeneral<3> {
public:
  energy_data_type compute( config_type config, report_ref report )
    {
    } // end of compute()

}; // end of class ExpansionFormulaPeriodic<3>


template <> class ExpansionFormulaGeneral<4> {
public:
  energy_data_type compute( config_type config, report_ref report )
    {
    } // end of compute()

}; // end of class ExpansionFormulaPeriodic<4>


} // end of manybody_expansion

} // end of namespace iquads

#endif
