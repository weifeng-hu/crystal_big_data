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

#ifndef MOLPRO_CONFIG_HPP
#define MOLPRO_CONFIG_HPP

#include <stdlib.h>
#include <vector>
#include <tuple>
#include <iostream>
#include <string>
#include <structure/coordinate_representation.hpp>
#include <interface_to_third_party/external_program_config_base.hpp>

namespace iquads {

namespace interface_to_third_party {

using std::ostream;
using std::string;
using std::tuple;
using std::vector;
using namespace structure;

struct MolproConfig : public ExternalProgramConfig_Base
{
public:
  typedef MolproConfig parent_config_type;

public:
  /*
   * Design note:
   *  I wanted to use forward declaration for these SubClasses, but seems that it won't work.
   *  This compiler will complain about incomplete type for this main class member functions 
   *  which use these subclasses.
   */
  struct MemoryConfig : public memory_config_base_type {
    public:
      typedef MemoryConfig this_type;
    public:
      friend
      ostream& operator<< ( ostream& os, const this_type& object_ref )
       {
        using std::endl;
        os << "memory," << object_ref.memory_amount() << "," << object_ref.memory_unit() << endl;
        return os; 
       }
   /* Note:
    *   A const print() will not work with a non-const argument in operator<<
    *   since a const rvalue *this can be converted to a non-const lvalue.
    */
      void print( ostream& os ) const 
       {
        using std :: endl;
        os << *this << endl;
       }
    public:
      memory_amount_type memory_amount() const 
       { return this->memory_amount_; }
      memory_unit_type memory_unit() const 
       { return this->memory_unit_; }
    private:
      memory_amount_type memory_amount_;
      memory_unit_type memory_unit_;
  }; // enf of struct MolproConfig :: MemoryConfig

  struct BasisSetConfig : public basis_set_config_base_type {
    public:
      typedef BasisSetConfig this_type;
    public:
      friend 
      ostream& operator<< ( ostream& os, const this_type& object_ref )
       {
         using std::endl;
         os << "basis=" << object_ref.basis_set_name() << endl;
         return os;
       }
      void print( ostream& os ) const 
       {
        using std::endl;
        os << *this << endl;
       }
    public:
      const basis_set_name_type basis_set_name() const
       { return this->basis_set_name_; }
    private:
      basis_set_name_type basis_set_name_;
  }; // end of struct MolproConfig :: BasisSetConfig

  struct GeometryConfig : public geometry_config_base_type {
    public:
      typedef GeometryConfig this_type;
    public:
      friend 
      ostream& operator<< ( ostream& os, const this_type& object_ref )
       {
         try{
          using std::endl;
          os << object_ref.return_geom_unit_string() << endl;
          geometry_format_type geometry_format = object_ref.geometry_format();
          switch( geometry_format ) {
           case( coordinate_representation :: CARTESIAN ):
             os << "geomtyp=" << object_ref.return_geomtyp_string() << endl;
             os << "geometry={" << endl;
             for( size_t iatom = 0; iatom < object_ref.atomic_coord_list().size(); iatom++ ){
              using std::get;
              atomic_cartesian_coord_type atomic_coord = object_ref.atomic_coord_list().at(iatom);
              element_name_type element = get<0> ( atomic_coord );
              coord_value_type coord_val_x = get<1> ( atomic_coord );
              coord_value_type coord_val_y = get<2> ( atomic_coord );
              coord_value_type coord_val_z = get<3> ( atomic_coord );
              os << element << " " << coord_val_x << " " << coord_val_y << " " << coord_val_z << endl;
             }
             os << "}" << endl;
             break;
           case( coordinate_representation :: INTERNAL ):
             using std::cout;
             cout << "Internal geometry for molpro has not been implemented" << endl;
             abort();
             break;
          default:
             throw geometry_format;
             break;
          }
         }
         catch ( geometry_format_type unknown_geometry_format ) {
           using std::cout;
           using std::endl;
           cout << "unknown geometry type" << unknown_geometry_format << endl;
           abort();
         }
       } // end of GeometryConfig :: operator<< 
      void print( ostream& os ) const 
       {
         using std::endl;
         os << *this << endl;
       }
      const string return_geomtyp_string() const 
       {
        try {
         switch( this->geometry_format_ ){
          case( coordinate_representation :: CARTESIAN ):
           return "xyz";
           break;
          case( coordinate_representation :: INTERNAL ):
           return "internal"; // this is not actually used in molpro when using z-matrix
           break;
          default:
           throw this->geometry_format_;
           break;
         }
        } catch ( geometry_format_type unknown_geometry_format ) {
           using std::cout;
           using std::endl;
           cout << "unknown geometry format type" << unknown_geometry_format << endl;
        }
       }
      const string return_geom_unit_string() const
       {
        try {
         switch ( this->geometry_unit_ ){
          case( geometry_unit :: ANGSTROM ):
           return "angstrom";
           break;
          case( geometry_unit :: BOHR ):
           return "bohr";
           break;
          default:
           throw this->geometry_unit_;
           break;
         }
        }
        catch ( geometry_unit_type unknown_geometry_unit )
        {
          using std::cout;
          using std::endl;
          cout << "unknown geometry type code name " << unknown_geometry_unit << endl;
          abort();
        }
       }
      atomic_coord_list_type atomic_coord_list() const
       { return this->atom_list_; }
      geometry_format_type geometry_format() const 
       { return this->geometry_format_; }
      geometry_unit_type geometry_unit() const
       { return this->geometry_unit_; }
    private: 
      atomic_coord_list_type atom_list_;
      geometry_format_type geometry_format_;
      geometry_unit_type geometry_unit_;
  }; // end of MolproConfig :: GeometryConfig

  struct HartreeFockConfig : public hartree_fock_config_base_type {
    public:
      typedef HartreeFockConfig this_type;
      typedef typename parent_config_type :: number_type nelec_type;
      typedef typename parent_config_type :: number_type spin_type;
      typedef typename parent_config_type :: number_type sym_type;
    public:
      friend 
      ostream& operator<< ( ostream& os, const this_type& object )
       {
         using std::endl;
         os << "{hf;" << endl;
         os << "wf," << object.nelec() << "," << object.sym() << "," << object.spin() << endl;
         os << "}" << endl;
       } // end of operator<<
      void print( ostream& os ) const 
       {
         using std::endl;
         os << *this << endl;
       }
      nelec_type nelec() const 
       { return this->nelec_; }
      spin_type spin() const
       { return this-> spin_; }
      sym_type sym() const 
       { return this->sym_; }
    private:
      nelec_type nelec_;
      spin_type  spin_;
      sym_type   sym_;
  }; // end of struct MolproConfig :: HartreeFockConfig

  struct MP2Config : public mp2_config_base_type {
    public:
      typedef MP2Config this_type;
    public:
      void print( ostream& os ) const { }
      /* to be implemented */
    private:
  }; // end of struct MolproConfig :: MP2Config

  struct MultiConfig : public casscf_config_base_type {
    public:
     /* to be implemented */
    public:
      void print( ostream& os ) const {}
    private:
  }; // end of struct MolproConfig :: MultiConfig

public:
  typedef MemoryConfig      this_memory_config_type;
  typedef BasisSetConfig    this_basis_set_config_type;
  typedef GeometryConfig    this_geometry_config_type;
  typedef HartreeFockConfig this_hf_config_type;
  typedef MP2Config         this_mp2_config_type;
  typedef MultiConfig       this_casscf_config_type;

public:
  memory_config_base_type& memory_config()
   { return this->memory_config_; }
  this_basis_set_config_type& basis_set_config()
   { return this->basis_set_config_; }
  this_geometry_config_type& geometry_config()
   { return this->geometry_config_; }
  this_hf_config_type& hartree_fock_config() 
   { return this->hf_config_; }
  this_mp2_config_type& mp2_config()
   { return this->mp2_config_; }
  this_casscf_config_type& casscf_config()
   { return this->multi_config_; }

private:
  this_memory_config_type memory_config_;
  this_basis_set_config_type basis_set_config_;
  this_geometry_config_type geometry_config_;
  this_hf_config_type hf_config_;
  this_mp2_config_type mp2_config_;
  this_casscf_config_type multi_config_;

}; // end of struct MolproConfig

} // end of namespace interface_to_third_party

} // end of namespace iquads

#endif
