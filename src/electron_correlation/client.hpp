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
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * @section DESCRIPTION
 *
 *
 */

#ifndef ELECTRON_CORRELATION_CLIENT_HPP
#define ELECTRON_CORRELATION_CLIENT_HPP

#include <structure/molecule.hpp>
#include <interface_to_third_party/external_program_request.hpp>
#include <interface_to_third_party/external_program_agent_factory.hpp>
#include <electron_correlation/report.hpp>
#include <electron_correlation/setting.hpp>

namespace iquads {

namespace electron_correlation {

  /**
   *  A client class for general electron correlation calculations
   *  As like in the OOP convention, thi client will summon an agent,
   *  which knows the actual sequence for a specific type of electron 
   *  correlation calculation. Also all this client wants to get is a 
   *  calculation report, thus the report is the ONLY data member 
   *  of this class.
   */

using interface_to_third_party :: ExternalProgramRequest;
using interface_to_third_party :: ExternalProgramAgent_Factory;

class Client {
public:
  typedef double      energy_data_type;
  typedef Report      report_type;
  typedef Setting     setting_type;
  typedef ExternalProgramRequest              external_request_type;
  typedef ExternalProgramAgent_Factory        external_agent_factory_type;

  typedef report_type :: molecule_info_type   molecule_info_type;

public:
  /**
   *  + internal_solve()
   *    This function implements the actual method to use the self(iquads) solvers
   *    to do electron correlation calculations. To be implemented. Compared to the 
   *    external agents, I may design a separate sequence pattern. But I 
   *    haven't decided yet.
   */
  report_type internal_solve()
    {/* return Report(); */ }

  /**
   *  + file_external_requestion()
   *    The method to construct an request to external calculation agents, which are 
   *    in the namespace interface_to_third_party.
   */
  external_request_type file_external_request( molecule_info_type molecule_info, setting_type settings );

  /**
   *  + driver()
   *    This is a driver depending on other information.
   *    The actual top level method to do an electron correlation calculation.
   *    The general sequence is to fork between using external and internal solvers, since they 
   *    may use different actual methods. 
   *    The definition of the method is kind of constant so we write it here in the head file.
   *    The only strange place in this function is that the driver still needs to know the Setting
   *    which is not offered by any of member functions in this Client class. This is the incomplete 
   *    part of this design, also due to the real cases in which electron correlation calculations 
   *    are dependent on other higher level tasks which needs correlation information, and the Setting
   *    will be decided by the actual higher level task variables.
   */
  void driver( molecule_info_type molecule_info, setting_type setting ) {
    this->set_report() = Report( molecule_info );
    if( setting.use_internal_solver() == false ) {
      this->report_ = internal_solve();
    }
    else {
      std :: cout << "we are in" << std :: endl;
      external_request_type external_request = this->file_external_request( molecule_info, setting );
      this->set_report().collect_data_from_external_report( ( this->agent_factory_.get_agent( setting.external_program() ) )->accept_request_and_process( external_request ) );
    }
  } // end of driver()

public:
  /**
   *  Accessors and mutators
   */
  report_type report() const 
    { return this->report_; }
  report_type& set_report()
    { return this->report_; }

private:
  report_type report_;
  external_agent_factory_type agent_factory_;

}; // end of class Client

} // end of namespace interface_to_third_party

} // end of namespace iquads

#endif
