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
#include <structure/coordinate_representation.hpp>
#include <structure/atom_list.hpp>
#include <electron_correlation/quantity.hpp>
#include <electron_correlation/correlation_level.hpp>

namespace iquads {

namespace interface_to_third_party {

  /**
   *  A base struct for third party configuration
   *
   *  There is no fixed way to design a runtime configuration data set 
   *  like this. But for general external quantum chemistry software, 
   *  sub-datasets to run a calculation can be:
   *
   *   + memory usage control
   *   + parallelization control
   *   + file I/O control
   *   + basis set info
   *   + geometry info
   *   + Hatree Fock control
   *   + MP2 control
   *   + Kohn-Sham DFT control
   *   + MCSCF/CASSCF control
   *   + CC control
   *   etc.
   *
   *  So in this struct, base struct for sub-configs are included.
   *  These sub-config are responsible to hold the actual data members,
   *  WHICH SHOULD BE GENERAL FOR ALL QUANTUM CHEMISTRY PACKAGES,
   *  and let the derived struct to manipulate them using virtual methods.
   *  Derived sub-configures can have additional data member but should not
   *  duplicate the functionality to already-have data.
   *
   */

using std :: tuple;
using std :: string;
using std :: vector;
using std :: ostream;
using namespace structure;
using namespace electron_correlation;

struct ExternalProgramConfig_Base {
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
  typedef quantity ::  quantity_mask_type solution_tag_type;
  typedef level_mask_type  correlation_tag_type;

public:
  struct MemoryConfig_Base {
    public:
      typedef parent_config_base_type :: size_type memory_amount_type;
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
      virtual void print() const = 0;
    public:
      virtual memory_amount_type memory_amount() const = 0;
      virtual memory_unit_type memory_unit() const = 0;
      virtual memory_amount_type& set_memory_amount() = 0;
      virtual memory_unit_type& set_memory_unit() = 0;
    /**
     * Design note:
     *  About user-defined copy assignment operator=
     *  
     *  In the end we want to copy assgin the derived class object using 
     *  mutator with return type derived&, and the mutator is used by 
     *  a parent base class reference/or derived class reference, which is 
     *  actually referred to a parent base class object (as what the compiler can
     *  see):
     *    base_parent_config_pointer->set_memory_config() = Derived_memory_config( ... );
     *                                      ^                        ^
     *                                      |                        |
     *                compiler sees a base memory config ref  compiler sees a derived memory config object rvalue.
     *
     *  In this case, the inheritance works for set_memory_config(), since it return a reference to
     *  MemoryConfig_Base(or MemoryConfig_Derived). Moreover, we have defined the set_memory_config()
     *  in the parent config class scope as a virtual pure method, it essentially means in reality use of this
     *  function will always return a derived class ref, i.e., it will always invokes the derived parent class
     *  overloaded function set_memory_config(). Note that we set the return value in the derived parent config
     *  as derived_memory_config&, but this won't affect the actual behavior.
     *
     *  The question is then about the assignment operator =, which takes the form
     *     Class_Type& operator= ( Class );
     *     Class_Type& operator= ( const Class& class_obj );
     *  By default, since the base and derived memory classes are assignable, so the compiler will
     *  generate assignment operator= individually for each of them, and the derived operator= inherits
     *  the base operator= somehow.
     *
     *  But, since the compiler sees a base memory config ref here, in the above demo code,
     *  the compiler will use the base class assignment operator= in this place. The base 
     *  memory config class has no information how to "copy and swap" data member since
     *  it has no idea what data members are, since they are in the derived class.
     *  In this case, the compiler assigns a default implicit assignment operator,
     *  is
     *    Class_Base& operator= ( const Class_Base& class_obj )
     *  but it won't automatically define the "copy and swap" operations for data members.
     *  It uses const Class_Base& class_obj, as the second operand, because it detects 
     *  the right hand side of = is a Class_Derived rvalue, which can be type casted to (using,e.g., static_cast<>), 
     *  or binded to(without doing anything for developer), a const Class_Base& type. 
     *  This means, the code is legal, and compiles, but the operator= is dummy for Derived class, 
     *  when we use a mututator which returns Class_Type& to do the assignment.
     *
     *  There are several workarounds still to make it work. 
     *  1. The direct method is to user-define the operator= body, using pure virtual functions to
     *  manipulate the data members in derived class. Using non-pure virtual functions will
     *  fail, because the compiler will take the base class functions, but base class has in-scope
     *  data members to manipulate. This method should be considered as the cleanest way, to 
     *  restore the normal functioning of operator=.
     *
     *  2. Write a pure virtual mutator in the derived parent class, like:
     *     void set_memory_config() { ... }
     *     and in the { } to define detailed manipulation of data members.
     *     This will work, but it makes the derived parent class a lot of code ( which can be done
     *     without writing additional codes out of the actual memory config class.
     *
     *  3. Directly manipulate the data members in external functions, by double layer mutator
     *     style:
     *        base_class_pointer->set_memory_config().set_memory_unit() = ...(some rvalue);
     *     This is the easiest way. But, it exposes data members, and actual manipulation 
     *     sequence of memory config, outside the class scope.
     *
     *  4. Define additional operator=.
     *       Class_Base& operator= ( Class_Derived& class_obj ) {...}
     *     But, looks like this doesn't work in the current design. Because, compiler will always
     *     take the base class default operator= first(when it sees the current code), because
     *     it knows how to define it. If we explicit delete the base class operator=, the compiler
     *     cannot find a valid operator= for this line of code, and will give an error message.
     *
     *     If the base class operator= can be deleted, and if the compiler knows to find another 
     *     operator= to use, then the use of additional operator= above can be done.
     *     
     *  5. There are some other issues:
     *     use keyword using to pull in the additional defined operator= (after deleting default base class 
     *     operator= ) does not work on g++. The compiler still gives an error of "trying to use 
     *     deleted operator=".
     *     
     *     Forward-declaring the operator= in the class scope then define it in the caller scope
     *     doesn't work either, same reason.
     *
     *     Forward-declaring also implementing operator= outside the class scope is not allowed, 
     *     because otherwise it will allow adding functions to the class anywhere. The 
     *     operator= is a non-static function by the C++ standard. So neither this will work.
     *
     */
      MemoryConfig_Base& operator= ( const MemoryConfig_Base& mem_conf_ref ) {
        this->set_memory_amount() = mem_conf_ref.memory_amount();
        this->set_memory_unit()   = mem_conf_ref.memory_unit();
      }
  };

  struct BasisSetConfig_Base {
    public:
      typedef string basis_set_name_type;
    public:
      virtual void print( ostream& os ) const = 0;
      virtual void print() const = 0;
    public:
      virtual basis_set_name_type basis_set_name() const = 0;
      virtual basis_set_name_type& set_basis_set_name() = 0;
    public:
      BasisSetConfig_Base& operator= ( const BasisSetConfig_Base& basis_conf_ref ) {
        this->set_basis_set_name() = basis_conf_ref.basis_set_name();
        return *this;
      }
  };

  struct GeometryConfig_Base {
    public:
      typedef parent_config_base_type :: precise_number_type coord_value_type;
      typedef string element_name_type;
      typedef coordinate_representation :: representation_mask_type  geometry_format_type; 
      typedef geometry_unit :: unit_mask_type geometry_unit_type;
      typedef tuple< element_name_type, tuple< coord_value_type, coord_value_type, coord_value_type > >  atomic_cartesian_coord_type;
      typedef vector< atomic_cartesian_coord_type > atomic_coord_list_type;
    public:
      virtual void print( ostream& os ) const = 0;
      virtual void print() const = 0;
    public:
      virtual atomic_coord_list_type atomic_coord_list() const = 0;
      virtual geometry_format_type geometry_format() const = 0;
      virtual geometry_unit_type geometry_unit() const = 0;

      virtual atomic_coord_list_type& set_atomic_coord_list() = 0;
      virtual geometry_format_type& set_geometry_format() = 0;
      virtual geometry_unit_type& set_geometry_unit() = 0;

      GeometryConfig_Base& operator= ( const GeometryConfig_Base& base_ref ) {
        this->set_atomic_coord_list() = base_ref.atomic_coord_list();
        this->set_geometry_unit()     = base_ref.geometry_unit();
        this->set_geometry_format()   = base_ref.geometry_format();
        return *this;
      };
  };

  struct HartreeFockConfig_Base {
    public:
      typedef typename parent_config_base_type :: number_type nelec_type;
      typedef typename parent_config_base_type :: number_type spin_type;
      typedef typename parent_config_base_type :: number_type sym_type;
    public:
      virtual void print( ostream& os ) const = 0;
      virtual void print() const = 0;
    public:
      virtual nelec_type nelec() const = 0;
      virtual spin_type spin() const = 0;
      virtual sym_type sym() const = 0;
      virtual nelec_type& set_nelec() = 0;
      virtual spin_type& set_spin() = 0;
      virtual sym_type& set_sym() = 0;
    public:
      HartreeFockConfig_Base& operator= ( const HartreeFockConfig_Base& hf_conf_ref ) {
        this->set_nelec() = hf_conf_ref.nelec();
        this->set_spin()  = hf_conf_ref.spin();
        this->set_sym()   = hf_conf_ref.sym();
        return *this;
      }
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
  virtual memory_config_base_type& set_memory_config() = 0;
  virtual basis_set_config_base_type& set_basis_set_config() = 0;
  virtual geometry_config_base_type& set_geometry_config() = 0;
  virtual hartree_fock_config_base_type& set_hartree_fock_config() = 0;
  virtual mp2_config_base_type& set_mp2_config() = 0;
  virtual casscf_config_base_type& set_casscf_config() = 0;

public:
  /**
   *  Special functionalities
   */
  virtual size_t check_spin( size_t spin, size_t nelec ) = 0;

public:
  solution_tag_type solution_tag() const
    { return this->solution_tag_; }
  correlation_tag_type correlation_tag() const
    { return this->correlation_tag_; }
  file_extension_type file_extension() const 
    { return this->file_extension_; }
  molecule_name_type molecule_name() const 
    { return this->molecule_name_; }
  work_path_type input_path() const
    { return this->input_path_; }
  work_path_type scratch_path() const
    { return this->scratch_path_; }
  work_path_type output_path() const
    { return this->output_path_; }

public:
  solution_tag_type& set_solution_tag()
    { return this->solution_tag_; }
  correlation_tag_type& set_correlation_tag()
    { return this->correlation_tag_; }
  file_extension_type& set_file_extension()
    { return this->file_extension_; }
  molecule_name_type& set_molecule_name()
    { return this->molecule_name_; }
  work_path_type& set_input_path()
    { return this->input_path_; }
  work_path_type& set_scratch_path()
    { return this->scratch_path_; }
  work_path_type& set_output_path()
    { return this->output_path_; }

private:
  solution_tag_type            solution_tag_;
  correlation_tag_type         correlation_tag_;
  file_extension_type          file_extension_;
  molecule_name_type           molecule_name_;
  work_path_type               input_path_;
  work_path_type               scratch_path_;
  work_path_type               output_path_;

}; // end of struct ExternalProgramConfig_Base

} // end of namespace interface_to_third_party

} // end of namespace

#endif
