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

#ifndef FRAGMENT_SIGNATURE_DATABASE_HPP
#define FRAGMENT_SIGNATURE_DATABASE_HPP

#include <tuple>
#include <string>
#include <structure/lattice_instant.hpp>
#include <electron_correlation/setting.hpp>
#include <manybody_expansion/polymer_report_template.hpp>
#include <manybody_expansion/fragment_group_info.hpp>

namespace iquads {

namespace manybody_expansion {

struct FragmentSignatureDataBase {
public:
  typedef iquads :: electron_correlation :: Setting electron_calc_setting_type;
  typedef std :: tuple< std :: tuple < int, int, int >, int >  lattice_index_type;
  typedef FragmentGroupInfo<1> monomer_signature_database_type;
  typedef FragmentGroupInfo<2> dimer_signature_database_type;
  typedef FragmentGroupInfo<3> trimer_signature_database_type;
  typedef FragmentGroupInfo<4> tetramer_signature_database_type;
  std :: tuple < std :: string, iquads :: structure :: MolecularLattice > lattice_info_type;

public:
  void build( lattice_info_type lattice_info, double radius, electron_calc_setting_type setting ) {
    this->monomer_signature_database_.build( lattice_info, radius, setting );
    this->dimer_signature_database_.build( lattice_info, radius, setting );
    this->trimer_signature_database_.build( lattice_info, radius, setting );
    this->tetramer_signature_database_.build( lattice_info, radius, setting );
  }
  template < size_t NUM > PolymerReport<NUM> get_report_by_lattice_index( std :: array< lattice_index_type, NUM > lattice_index ) {
    const FragmentGroupInfo<NUM>& data_ref = this->fetch_database_reference<NUM>();
    PolymerReport<NUM> report = data_ref.get_report_by_lattice_index( lattice_index );
  }

private:
  template < size_t NUM > const FragmentGroupInfo<NUM>& fetch_database_reference() {
    return 0;
  }
  template <> const FragmentGroupInfo<1>& fetch_database_reference<1>() 
    { return this->monomer_signature_database_; }
  template <> const FragmentGroupInfo<2>& fetch_database_reference<2>() 
    { return this->dimer_signature_database_; }
  template <> const FragmentGroupInfo<3>& fetch_database_reference<3>() 
    { return this->trimer_signature_database_; }
  template <> const FragmentGroupInfo<4>& fetch_database_reference<4>() 
    { return this->tetramer_signature_database_; }

private:
  monomer_signature_database_type monomer_signature_database_;
  dimer_signature_database_type dimer_signature_database_;
  trimer_signature_database_type trimer_signature_database_;
  tetramer_signature_database_type tetramer_signature_database_;

};

} // end of namespace manybody_expansion

} // end of namespace iquads

#endif
