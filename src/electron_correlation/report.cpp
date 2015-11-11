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

#include <tuple>
#include <iquads/sequence.hpp>
#include <electron_correlation/report.hpp>

namespace iquads {

namespace electron_correlation {

typedef Report  report_type;

void report_type :: collect_data_from_external_report( external_report_type external_report ) {

  switch( external_report.run_mode() ) {
    case( iquads :: sequence :: mode :: LOCAL_RUN ): {
      this->external_report_ = external_report;
      for( size_t i = 0; i < this->external_report_.energy_local_run_report_list().size(); i++ ) {
        this->correlated_energy_report_.set_correlated_energy_of( std :: get<0>( this->external_report_.energy_local_run_report_list()[i] ).energy_solution_tag() )
          = std :: get<0>( this->external_report_.energy_local_run_report_list()[i] ).energy();
      }
      this->molecule_info_ = std :: make_tuple( std :: get<0> ( this->external_report_.energy_local_run_report_list()[0] ).molecule_name(),
                                                std :: get<0> ( this->external_report_.energy_local_run_report_list()[0] ).molecule_obj()   );
    }
    break;
    case( iquads :: sequence :: mode :: WRITE_LOCAL_INPUT ): {
      this->external_report_ = external_report;
    }
    break;
    case( iquads :: sequence :: mode :: WRITE_PBS_INPUT ): {
      this->external_report_ = external_report;
    }
    break;
    case( iquads :: sequence :: mode :: WRITE_SBATCH_INPUT ): {
      this->external_report_ = external_report;
    }
    break;
    case( iquads :: sequence :: mode :: COLLECT_LOCAL_OUTPUT ): {
      this->external_report_ = external_report;
      for( size_t i = 0; i < this->external_report_.energy_harvest_run_report_list().size(); i++ ) {
        this->correlated_energy_report_.set_correlated_energy_of( std :: get<0>( this->external_report_.energy_harvest_run_report_list()[i] ).energy_solution_tag() )
          = std :: get<0>( this->external_report_.energy_harvest_run_report_list()[i] ).energy();
      }
      this->molecule_info_ = std :: make_tuple( std :: get<0> ( this->external_report_.energy_harvest_run_report_list()[0] ).molecule_name(),
                                                std :: get<0> ( this->external_report_.energy_harvest_run_report_list()[0] ).molecule_obj()   );
    }
    break;
  }

}; // end of function collect_data_from_external_report()

} // end of namespace electron_correlation

} // end of namespace iquads
