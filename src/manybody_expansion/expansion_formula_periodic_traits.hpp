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

#ifndef EXPANSION_FORMULA_PERIODIC_TRAITS_HPP
#define EXPANSION_FORMULA_PERIODIC_TRAITS_HPP

#include <manybody_expansion/config.hpp>
#include <manybody_expansion/report.hpp>
#include <manybody_expansion/compute_expansion_term_periodic_traits.hpp>

namespace iquads {

namespace manybody_expansion {

  /**
   *  Explicit instantiation of many body expansion formulas (as class objects) for
   *  periodic systems
   *
   *  The only method of these formula classes needs an input config and manipulates
   *  the report as the output.
   *
   */
  typedef double energy_data_type;
  typedef Config config_type;
  typedef Report report_type;
  typedef report_type& report_ref;
  using manybody_expansion :: compute_expansion_term_periodic;

  /**
   *  Default instanitation
   */
  template < size_t Order > class ExpansionFormulaPeriodic {
    public:
      energy_data_type compute( config_type config, report_ref report )
        { return compute_expansion_term_periodic<0>( config, report ); }
  }; // end of class ExpansionFormulaPeriodic< Order >

  /**
   *  instanitation for first order formula
   *  contains:
   *  + total monomer energy
   */
  template <> class ExpansionFormulaPeriodic<1> {
    public:
      energy_data_type compute( config_type config, report_ref report ) 
        { return compute_expansion_term_periodic<1>( config, report ); } 
  }; // end of class ExpansionFormulaPeriodic<1>

  /**
   *  instanitation for second order formula
   *  contains:
   *  + total monomer energy
   *  + total dimer interaction energy
   */
  template <> class ExpansionFormulaPeriodic<2> {
    public:
      energy_data_type compute( config_type config, report_ref report ) {
        return compute_expansion_term_periodic<1>( config, report ) +
               compute_expansion_term_periodic<2>( config, report );
      }
  }; // end of class ExpansionFormulaPeriodic<2>

  /**
   *  instanitation for third order formula
   *  contains:
   *  + total monomer energy
   *  + total dimer interaction energy
   *  + total trimer interaction energy
   */
  template <> class ExpansionFormulaPeriodic<3> {
    public:
      energy_data_type compute( config_type config, report_ref report ) {
        return compute_expansion_term_periodic<1>( config, report ) +
               compute_expansion_term_periodic<2>( config, report ) +
               compute_expansion_term_periodic<3>( config, report );
      }
  }; // end of class ExpansionFormulaPeriodic<3>

  /**
   *  instanitation for fourth order formula
   *  contains:
   *  + total monomer energy
   *  + total dimer interaction energy
   *  + total trimer interaction energy
   *  + total tetramer interaction energy
   */
  template <> class ExpansionFormulaPeriodic<4> {
    public:
      energy_data_type compute( config_type config, report_ref report ) {
        return compute_expansion_term_periodic<1>( config, report ) +
               compute_expansion_term_periodic<2>( config, report ) +
               compute_expansion_term_periodic<3>( config, report ) +
               compute_expansion_term_periodic<4>( config, report ); 
      }
  }; // end of class ExpansionFormulaPeriodic<4>

} // end of manybody_expansion

} // end of namespace iquads

#endif
