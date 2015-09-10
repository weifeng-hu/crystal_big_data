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

#ifndef EXTERNAL_PROGRAM_CONFIG_BASE_HPP
#define EXTERNAL_PROGRAM_CONFIG_BASE_HPP

#include <vector>
#include <tuple>
#include <iostream>
#include <string>
#include <structure/geometry_settings.hpp>
#include <electron_correlation/quantity.hpp>

using std::tuple;
using std::string;
using std::vector;
using std::ostream;

namespace iquads {

using namespace structure :: geometry;
using namespace electron_correlation;

namespace interface_to_third_party {

struct ExternalProgramConfig_Base 
{
public:
  typedef ExternalProgramConfig_Base parent_config_base_type;

public:
  typedef unsigned int   number_type;
  typedef double         precise_number_type;
  typedef size_t         size_type; // the same backend data type as number_type
  typedef bool           condition_type;
  typedef string         file_extension_type;
  typedef string         file_name_type;
  typedef string         molecule_name_type;
  typedef string         work_path_type;
  typedef quantity :: quantity_mask_type solution_tag_type;
  typedef quantity :: energy :: energy_mask_type energy_solution_tag_type;
  typedef quantity :: gradient :: gradient_mask_type gradient_solution_tag_type;

public:
  struct MemoryConfig_Base {
    public:
      typedef typename parent_config_base_type :: size_type memory_amount_type;
      typedef string memory_unit_type;
   /*
    * Design note (for all these SubConfig classes):
    *  We can't easily use overloaded operator<< for a derived class object which is pointed by 
    *  a base class pointer to realize polymorphism for different derived classes, 
    *  for example when we write something like:
    *   cout << a_pointer_to_base_class_pointing_to_derived class << endl;
    *
    *  Reason:
    *  1. Detailed operations of operator<< will depend on the actual data members or methods
    *     of an implementation of this abstract base class, which may not be the same for different 
    *     implementations. So writing out all pure virtual method in this base abstract class trying to 
    *     cover all cases in different implementations will be really dirty.
    *  2. operator<< for the base class and operator<< for derived class are initialized differently
    *     because this initialization is static and depends on the actual object type. This is also 
    *     because the operator<< cannot be a virtual function since we usually implement it as a 
    *     friend function (which is never virtual since it is non-member). So if we implement operator<< 
    *     in a derived class using derived class reference, it cannot be initialized for a call if it 
    *     is fed with a base class reference (even if the base class points to a derived class object).
    *  3. Since operator<< is a friend function defined inside the class, the actual name lookup order 
    *     disables it to be seen outside the namespace scope. A work around is to declare it here inside 
    *     the base class, but further implement it in the derived class using the base class pointer/reference, 
    *     still, this means the base class needs to cover all possible virtual methods, which is dirty, as
    *     stated in 1.
    */
   // friend ostream& operator<< ( ostream& os, MemoryConfig_Base& object );
   public:
    /* 
     * Design note:
     *  continued:
     *  so a work around is to further use a virtual function print(), which can have polymorphism 
     *  for different derived classes, when it is invoked by a base class pointer/reference. We can 
     *  even overload operator<< inside this function.
     *  We make this print() method with a const signature, to align with the ref to const object argument 
     *  in an overloaded operator<<. A non-const print() will also work with a ref to const in operator<<
     *  but here we emphasize the const behavior of print().
     */
     virtual void print( ostream& os ) const = 0;
  };

  struct BasisSetConfig_Base {
    public:
      typedef string basis_set_name_type;
    public:
      virtual void print( ostream& os ) const = 0;
  };

  struct GeometryConfig_Base {
    public:
      typedef typename parent_config_base_type :: precise_number_type coord_value_type;
      typedef string element_name_type;
      typedef typename coordinate_system :: coordinate_mask_type  geometry_format_type; 
      typedef typename unit :: unit_mask_type geometry_unit_type;
      typedef tuple< element_name_type, coord_value_type, coord_value_type, coord_value_type > atomic_cartesian_coord_type;
      typedef vector< atomic_cartesian_coord_type > cartesian_coord_list_type;
    public:
      virtual void print( ostream& os ) const = 0;
  };

  struct HartreeFockConfig_Base {
    public:
      typedef typename parent_config_base_type :: number_type nelec_type;
      typedef typename parent_config_base_type :: number_type spin_type;
      typedef typename parent_config_base_type :: number_type sym_type;
    public:
      virtual void print( ostream& os ) const = 0;
  };

  struct MP2Config_Base {
    public:
      virtual void print( ostream& os ) const = 0;
  };

  struct CASSCFConfig_Base {
    public:
      virtual void print( ostream& os ) const = 0;
  };

public:
  typedef MemoryConfig_Base        memory_config_base_type;
  typedef BasisSetConfig_Base      basis_set_config_base_type;
  typedef GeometryConfig_Base      geometry_config_base_type;
  typedef HartreeFockConfig_Base   hartree_fock_config_base_type;
  typedef MP2Config_Base           mp2_config_base_type;
  typedef CASSCFConfig_Base        casscf_config_base_type;

public:
  virtual memory_config_base_type& memory_config() = 0;
  virtual basis_set_config_base_type& basis_set_config() = 0;
  virtual geometry_config_base_type& geometry_config() = 0;
  virtual hartree_fock_config_base_type& hartree_fock_config() = 0;
  virtual mp2_config_base_type& mp2_config() = 0;
  virtual casscf_config_base_type& casscf_config() = 0;

public:
  const solution_tag_type solution_tag() const
   { return this->solution_tag_; }
  const energy_solution_tag_type energy_solution_tag() const 
   { return this->energy_solution_tag_; }
  const gradient_solution_tag_type gradient_solution_tag() const
   { return this->gradient_solution_tag_; }
  const file_extension_type file_extension() const 
   { return this->file_extension_; }
  const molecule_name_type molecule_name() const 
   { return this->molecule_name_; }
  const work_path_type work_path() const
   { return this->work_path_; }

protected:
  solution_tag_type solution_tag_;
  energy_solution_tag_type energy_solution_tag_;
  gradient_solution_tag_type gradient_solution_tag_;
  file_extension_type file_extension_;
  molecule_name_type molecule_name_;
  work_path_type work_path_;

}; // end of struct ExternalProgramConfig_Base

} // end of namespace interface_to_third_party

} // end of namespace

#endif
