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

#ifndef MOLPRO_CONFIG_H
#define MOLPRO_CONFIG_H

#include <stdlib.h>
#include <vector>
#include <tuple>
#include <iostream>
#include <string>
#include <structure/geometry_settings.h>

namespace iquads {

namespace interface_to_third_party {

using std::ostream;
using std::string;
using namespace iquads :: geometry;

struct MolproConfig
{
public:
  struct MemoryConfig;
  struct BaseSetConfig;
  struct GeometryConfig;
  struct HartreeFockConfig;
  struct MP2Config;
  struct MultiConfig;

public:
  typedef MolproConfig parent_config_type;
  typedef parent_config_type :: MemoryConfig      this_memory_config_type;
  typedef parent_config_type :: BasisSetConfig    this_basis_set_config_type;
  typedef parent_config_type :: GeometryConfig    this_geometry_config_type;
  typedef parent_config_type :: HartreeFockConfig this_hf_config_type;
  typedef parent_config_type :: MP2Config         this_mp2_config_type;
  typedef parent_config_type :: MultiConfig       this_casscf_config_type;

  typedef unsigned int number_type;
  typedef double       precise_number_type;
  typedef bool         condition_type;
  typedef string       file_extension_type;
  typedef string       molecule_name_type;
  typedef string       file_name_type;
  typedef string       work_path_type;
  typedef unsigned int number_type;
  typedef size_t       size_type;

public:
  void translate_config( general_config_type general_config )
   { /* to be implemented */ }

public:
  const file_extension_type file_extension() const 
   { return this->file_extension_; }
  const file_name_type input_filename() const
   { return this->input_filename_; }
  const work_path_type work_path() const
   { return this->work_path_; }

private:
  this_memory_config_type memory_config_;
  this_basis_set_config_type basis_set_config_;
  this_geometry_config_type geometry_config_;
  this_hf_config_type hf_config_;
  this_mp2_config_type mp2_config_;
  this_multi_config_type multi_config_;

  file_extension_type file_extension_;
  molecule_name_type molecule_name_;
  work_path_type work_path_;

}; // end of struct MolproConfig


struct MolproConfig :: MemoryConfig
{
public:
  typedef MolproConfig parent_config_type;
  typedef MemoryConfig this_type;
  typedef typename parent_config_type :: size_type memory_amount_type;
  typedef string memory_unit_type;

public:
  ostream& operator<< ( ostream& os, this_type& object )
   {
     os << "memory," << object.memory_amount() << "," << object.memory_unit() << endl;
     return os; 
   }

public:
  const memory_amount_type memory_amount() 
   { return this->memory_amount_; }
  const memory_unit_type memory_unit()
   { return this->memory_unit_; }

private:
  memory_amount_type memory_amount_;
  memory_unit_type memory_unit_;

}; // enf of struct MolproConfig :: MemoryConfig


struct MolproConfig :: BasisSetConfig
{
public:
  typedef MolproConfig parent_config_type;
  typedef BasisSetConfig this_type;
  typedef typename parent_config_type :: 
  typedef string basis_set_name_type;
  typedef 

public:
  ostream& operator<< ( ostream& os, this_type& object_ref )
   {
     os << "basis=" << object_ref.basis_set_name() << endl;
     return os;
   }

public:
  const basis_set_name_type basis_set_name()
   { return this->basis_set_name_; }

private:
  basis_set_name_type basis_set_name_;

}; // end of struct BasisSetConfig


struct MolproConfig :: GeometryConfig
{
public:
  typedef GeometryConfig this_type;
  typedef typename parent_config_type :: precise_number_type coord_value_type;
  typedef string element_name_type;
  typedef typename coordinate_system :: type_mask  geometry_format_type; 
  typedef typename unit :: type_mask geometry_unit_type;
  typedef tuple< element_name_type, coord_value_type, coord_value_type, coord_value_type > atomic_cartesian_coord_type;
  typedef vector< atomic_cartesian_coord_type > cartesian_coord_list_type;

public:
  ostream& operator<< ( ostream& os, this_type& object )
   {
     try{
      using std::endl;
      os << "geomtyp=" << object.return_geomtyp_string() << endl;
      os << object.return_geom_unit() << endl;
      if( object.geomtyp() == coorinate_system :: CARTESIAN ){
       os << "geometry={" << endl;
       for( size_t iatom = 0; iatom < object.cartesian_coord_list.size(); iatom++ ){
        using std::get;
        atomic_cartesian_coord_type atomic_coord = cartesian_coord_list[iatom];
        element_name_type element = get<0> ( atomic_coord );
        coord_value_type coord_val_x = get<1> ( atomic_coord );
        coord_value_type coord_val_y = get<2> ( atomic_coord );
        coord_value_type coord_val_z = get<3> ( atomic_coord );
        ofs << element << " " << coord_val_x << " " << cood_val_y << " " << coord_val_z << endl;
       }
       os << "}" << endl;
      }
      else if( object.geomtyp() == coordinate_system :: INTERNAL ){
       using std::cout;
       cout << "Internal geometry for molpro has not been implemented" << endl;
       abort();
      }
      else {
       throw object.geomtyp();
      }
     catch ( geometry_format_type type_code ) {
       using std::cout;
       using std::endl;
       cout << "unknown geometry type" << type_code << endl;
       abort();
     }
   } // end of GeometryConfig :: operator<< 
  const string return_geom_unit() const
   {
    try {
     if( this->geometry_unit_ == geometry :: unit :: ANGSTROM ){
      return "angstrom";
     }
     else if( this->geometry_unit_ == geometry :: unit :: BOHR ){
      return "bohr";
     }
     else{
      throw this->geometry_unit_;
     }
    } 
    catch ( geometry_unit_type geometry_unit )
    {
      using std::cout;
      using std::endl;
      cout << "unknown geometry type code name " << geometry_unit << endl;
      abort();
    }
   }

private: 
  cartesian_coord_list_type cartesian_coord_list;
  geometry_format_type geometry_format;
  geometry_unit_type geometry_unit_;

}; // end of struct GeometryConfig


struct MolproConfig :: HartreeFockConfig
{
public:
  typedef MolproConfig parent_type;
  typedef HartreeFockConfig this_type;
  typedef typename parent_type :: number_type nelec_type;
  typedef typename parent_type :: number_type spin_type;
  typedef typename parent_type :: number_type sym_type;

public:
  HartreeFockConfig( nelec_type nelec, spin_type sym, sym_type spin )
   {
    this->nelec_ = nelec;
    this->spin_ = spin;
    this->sym_ = sym;
   }

public:
  ostream& operator<< ( ostream& os, this_type& object )
   {
     using std::endl;
     os << "{hf;" << endl;
     os << "wf," << object.nelec() << "," << object.sym() << "," << object.spin() << endl;
     os << "}" << endl;
   } // end of operator<<
  const nelec_type nelec() const 
   { return this->nelec_; }
  const spin_type spin() const
   { return this-> spin_; }
  const sym_type sym() const 
   { return this->sym_; }

private:
  nelec_type nelec_;
  spin_type  spin_;
  sym_type sym_;

}; // end of struct MolproConfig :: HartreeFockConfig


struct MolproConfig :: MP2Config
{
public:
  typedef MolproConfig parent_type;
  typedef MP2Config this_type;
  /* to be implemented */
private:

}; // end of struct MolproConfig :: MP2Config


struct MolproConfig ::MultiConfig
{
public:
 /* to be implemented */
private:

}; // end of struct MolproConfig :: MultiConfig


} // end of namespace interface_to_third_party

} // end of namespace iquads

#endif
