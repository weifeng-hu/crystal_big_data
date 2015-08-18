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

#ifndef ELECTRON_CORRELATION_CLIENT_H
#define ELECTRON_CORRELATION_CLIENT_H

#include <electron_correlation/electron_correlation_report.h>
#include <interface_to_third_party/external_program_request.h>
#include <interface_to_third_party/external_program_report.h>
#include <interface_to_third_party/external_program_agent_base.h>
#include <interface_to_third_party/external_program_agent_factory.h>

namespace iquads {

namespace electron_correlation {

class Client {
public:
  typedef double energy_data_type;
  typedef Report report_type;
  typedef iquads :: interface_to_third_party :: ExternalProgramRequest external_request_type;
  typedef iquads :: interface_to_third_party :: ExternalProgramReport external_report_type;
  typedef iquads :: interface_to_third_party :: ExternalProgramAgent_Factory external_agent_factory_type;
  typedef iquads :: interface_to_third_party :: ExternalProgramAgent_Base external_base_agent_type;
  typedef external_base_agent_type* external_base_agent_ptr;

public:
  report_type internal_solve()
   { /* to be implemented */ }
  request_type file_external_request()
   { /* to be implemented */ }
  void driver( settings )
   {
     if( settings.use_external_solver() == false ){
      this->report_ = internal_solve();
     }
     else{
      external_request_type external_request = this->file_external_request( settings );
      external_base_agent_ptr agent_ptr;
       = this->agent_factory().get_agent( settings.external_agent_mask() );
      external_report_type external_report
       = agent_ptr->accept_request_and_process( external_request );
      this->report().collect_from_external_report( external_report );
     }
   } // end of driver()

public:
  const external_agent_factory_type external_agent_factory() const 
   { return this->external_agent_factory_; }
  const report_type report() const 
   { return this->report_; }

private:
  external_agent_factory_type external_agent_factory_;
  report_type report_;

}; // end of class Client

} // end of namespace interface_to_third_party

} // end of namespace iquads

#endif
