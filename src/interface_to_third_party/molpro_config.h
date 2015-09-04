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

#include <string>
#include <vector>
#include <tuple>

namespace iquads {

namespace interface_to_third_party {

using std::string;

struct MolproConfig
{
public:
  typedef unsigned int number_type;

  typedef MolproConfig this_type;
  typedef this_type :: HartreeFockConfig this_hf_config_type;
  typedef this_type :: MP2Config this_mp2_config_type;
  typedef bool condition_type;

  typedef string file_extension_type;
  typedef string molecule_name_type;
  typedef string file_name_type;
  typedef string work_path_type;
  typedef string basis_set_name_type;
  typedef string memory_unit_type;
  typedef string geometry_format_type;
  typedef string geometry_unit_type;
  typedef string molecule_name_type;
  typedef size_t memory_amount_type;
  typedef size_t number_type;

public:
  struct MemoryConfig
  {
   public:
    typedef typename this_type :: number_type memory_amount_type;
    typedef string memory_unit_type;
   private:
    memory_amount_type memory_amount_;
    memory_unit_type memory_unit_;
  };
  struct BasisSetConfig
  {
   public:
    typedef string basis_set_name_type;
   private:
    basis_set_name_type basis_set_name_;
  };
  struct GeometryConfig
  {
   public:
    typedef unsigned int geometry_format_type; 
    typedef unsigned int geometry_unit_type; 
    typedef vector< tuple< string, double, double, double > > cartesian_coord_list_type;
   private: 
    cartesian_coord_list_type cartesian_coord_list;
    geometry_format_type geometry_format;
    geometry_unit_type geometry_unit_;
  };
  struct HartreeFockConfig
  {
   typedef typename this_type :: number_type nelec_type;
   typedef typename this_type :: number_type spin_type;
   typedef typename this_type :: number_type sym_type;
   public:
     HartreeFockConfig( nelec_type nelec, spin_type sym, sym_type spin )
      {
       this->nelec_ = nelec;
       this->spin_ = spin;
       this->sym_ = sym;
      }

   public:
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
  };
  struct MP2Config
  {
  };
  struct MultiConfig
  {
  };

public:
  const file_extension_type file_extension() const 
   { return this->file_extension_; }
  const file_name_type input_filename() const
   { return this->input_filename_; }
  const work_path_type work_path() const
   { return this->work_path_; }

private:
  memory_unit_type memory_unit_;
  memory_amount_type memory_amount_;
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

} // end of namespace interface_to_third_party

} // end of namespace iquads

#endif
