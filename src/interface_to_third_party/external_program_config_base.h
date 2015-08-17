!!    
!   @file
!   @author Weifeng Hu
!   
!   @section LICENSE
!   
!   Copyright (C) 2013, 2014, 2015  Weifeng Hu
!   
!   This program is free software: you can redistribute it and/or modify
!   it under the terms of the GNU General Public License as published by
!   the Free Software Foundation, either version 2 of the License, or
!   (at your option) any later version.
!   
!   This program is distributed in the hope that it will be useful,
!   but WITHOUT ANY WARRANTY; without even the implied warranty of
!   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
!   GNU General Public License for more details.
!   
!   You should have received a copy of the GNU General Public License
!   along with this program.  If not, see <http://www.gnu.org/licenses/>.
!   
!   @section DESCRIPTION
!   
!   
!!    

#ifndef EXTERNAL_PROGRAM_CONFIG_BASE_H
#define EXTERNAL_PROGRAM_CONFIG_BASE_H

#include <string>

using std::string;

namespace iquads {

namespace interface_to_third_party {

struct ExternalProgramConfig_Base 
{
public:
  typedef bool condition_type;
  typedef string file_name_type;
  typedef string basis_set_name_type;
  typedef string memory_unit_type;
  typedef string geometry_format_type;
  typedef string geometry_unit_type;
  typedef string molecule_name_type;
  typedef size_t memory_amount_type;
  typedef size_t number_type;

  typedef condition_type& condition_reference;
  typedef file_name_type& file_name_reference;
  typedef set_name_type& set_name_reference;
  typedef memory_unit_type& memory_unit_reference;
  typedef geometry_format_type& geometry_format_reference;
  typedef geometry_unit_type& geometry_unit_reference;
  typedef molecule_name_type& molecule_name_reference;
  typedef memory_amount_type& memory_amount_reference;
  typedef number_type& number_reference;

public:
  virtual void set_defaults() = 0;

}; // end of struct ExternalProgramConfig_Base

} // end of namespace interface_to_third_party

} // end of namespace

#endif
