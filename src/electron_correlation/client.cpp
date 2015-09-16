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

#include <electron_correlation/client.hpp>

namespace iquads {

namespace electron_correlation {

typedef Client client_type;


/**
 *
 *  << interface function >>
 *   file_external_request()
 *
 *   + translate a electron correlation setting content to 
 *     external program request, which will be later processed by external program agents
 *   + this method detail can vary so we put it as a separate compile .cpp unit.
 *   + A direct implementation is just to copy every content from a setting to a request
 *   + But further functionality can be followed
 *
 */

client_type :: external_request_type
 client_type :: file_external_request( molecule_info_type molecule_info, setting_type settings )
{

  external_request_type request;
  request.set_molecule_info() = molecule_info;
  request.set_mode() = settings.mode();
  request.set_basis_set_name() = settings.basis_set_name();
  request.set_external_program() = settings.external_program();

  return request;

}; // end of file_external_request

} // end of namespace electron_correlation

} // end of namespace iquads
