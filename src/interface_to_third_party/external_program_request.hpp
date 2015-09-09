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

#ifndef EXTERNAL_PROGRAM_REQUEST_HPP
#define EXTERNAL_PROGRAM_REQUEST_HPP

#include <vector>
#include <string>
#include <iquads/sequence.hpp>
#include <structure/molecule.hpp>

using std::vector;
using std::string;

namespace iquads {

using namespace sequence;

namespace interface_to_third_party {

struct ExternalProgramRequest {
public:
  typedef mode :: mode_mask_type mode_type;
  typedef calculation :: calculation_mask_type calculation_type;
  typedef string basis_set_name_type;
  typedef vector<string> method_keyword_list_type;
  typedef Molecule molecule_info_type;

public:
  const mode_type mode() const 
   { return this->mode_; }
  const calculation_type calculation() const
   { return this->calculation_; }

private:
  mode_type mode_;
  calculation_type calculation_;

  method_keyword_list_type method_keyword_list_;
  string basis_set_name_;
  molecule_info_type molecule_info_;

}; // end of struct ExternalProgramRequest

} // end of namespace interface_to_third_party

} // end of namespace iquads

#endif
