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

#ifndef EXPANSION_FORMULA_PERIODIC_TRAITS_H
#define EXPANSION_FORMULA_PERIODIC_TRAITS_H

#include <manybody_expansion/config.h>
#include <manybody_expansion/report.h>
#include <manybody_expansion/compute_expansion_term_periodic_traits.h>

namespace iquads {

namespace manybody_expansion {

typedef double energy_data_type;
typedef Config config_type;
typedef Report report_type;
typedef report_type& report_ref;

template < size_t Order >
class ExpansionFormulaPeriodic
{
public:
  energy_data_type compute( config_type config, report_ref report )
   {
     using manybody_expansion :: compute_expansion_term_periodic;
     return compute_expansion_term_periodic<0>( config, report );
   } // end of compute()

}; // end of class ExpansionFormulaPeriodic< Order >

template <>
class ExpansionFormulaPeriodic<1>
{
public:
  energy_data_type compute( config_type config, report_ref report )
   {
     using manybody_expansion :: compute_expansion_term_periodic;
     return compute_expansion_term_periodic<1>( config, report );
   } // end of compute()

}; // end of class ExpansionFormulaPeriodic<1>

template <>
class ExpansionFormulaPeriodic<2>
{
public:
  energy_data_type compute( config_type config, report_ref report )
   {
     using manybody_expansion :: compute_expansion_term_periodic;
     return compute_expansion_term_periodic<1>( config, report ) +
            compute_expansion_term_periodic<2>( config, report );
   } // end of compute()

}; // end of class ExpansionFormulaPeriodic<2>

template <>
class ExpansionFormulaPeriodic<3>
{
public:
  energy_data_type compute( config_type config, report_ref report )
   {
     using manybody_expansion :: compute_expansion_term_periodic;
     return compute_expansion_term_periodic<1>( config, report ) +
            compute_expansion_term_periodic<2>( config, report ) +
            compute_expansion_term_periodic<3>( config, report );
   } // end of compute()

}; // end of class ExpansionFormulaPeriodic<3>

template <>
class ExpansionFormulaPeriodic<4>
{
public:
  energy_data_type compute( config_type config, report_ref report )
   {
     using manybody_expansion :: compute_expansion_term_periodic;
     return compute_expansion_term_periodic<1>( config, report ) +
            compute_expansion_term_periodic<2>( config, report ) +
            compute_expansion_term_periodic<3>( config, report ) +
            compute_expansion_term_periodic<4>( config, report ); 
   } // end of compute()

}; // end of class ExpansionFormulaPeriodic<4>

} // end of manybody_expansion

} // end of namespace iquads

#endif
