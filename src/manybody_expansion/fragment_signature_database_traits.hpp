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

#ifndef FRAGMENT_SIGNATURE_DATABASE_TRAITS_HPP
#define FRAGMENT_SIGNATURE_DATABASE_TRAITS_HPP

#include <tuple>
#include <string>
#include <structure/lattice_instant.hpp>
#include <manybody_expansion/fragment_group_info.hpp>

namespace iquads {

namespace manybody_expansion {

  template < size_t Order > struct FragmentSignatureDataBase {
    public:
      std :: tuple < std :: string, iquads :: structure :: MolecularLattice > lattice_info_type;
    public:
      void bulid( lattice_info_type lattice_info ){}
  };

  template <> struct FragmentSignatureDataBase<1> {
    public:
      typedef FragmentGroupInfo<1> monomer_signature_database_type;
      std :: tuple < std :: string, iquads :: structure :: MolecularLattice > lattice_info_type;
    public:
      void build( lattice_info_type lattice_info ) {
        this->monomer_signature_database_.build( lattice_info );
      }
    private:
      monomer_signature_database_type monomer_signature_database_;
  };

  template <> struct FragmentSignatureDataBase<2> {
    public:
      typedef FragmentGroupInfo<1> monomer_signature_database_type;
      typedef FragmentGroupInfo<2> dimer_signature_database_type;
      std :: tuple < std :: string, iquads :: structure :: MolecularLattice > lattice_info_type;
    public:
      void build( lattice_info_type lattice_info ) {
        this->monomer_signature_database_.build( lattice_info );
        this->dimer_signature_database_.build( lattice_info );
      }
    private:
      monomer_signature_database_type monomer_signature_database_;
      dimer_signature_database_type dimer_signature_database_;
  };

  template <> struct FragmentSignatureDataBase<3> {
    public:
      typedef FragmentGroupInfo<1> monomer_signature_database_type;
      typedef FragmentGroupInfo<2> dimer_signature_database_type;
      typedef FragmentGroupInfo<3> trimer_signature_database_type;
      std :: tuple < std :: string, iquads :: structure :: MolecularLattice > lattice_info_type;
    public:
      void build( lattice_info_type lattice_info ) {
        this->monomer_signature_database_.build( lattice_info );
        this->dimer_signature_database_.build( lattice_info );
        this->trimer_signature_database_.build( lattice_info );
      }
    private:
      monomer_signature_database_type monomer_signature_database_;
      dimer_signature_database_type dimer_signature_database_;
      trimer_signature_database_type trimer_signature_database_;
  };

  template <> struct FragmentSignatureDataBase<4> {
    public:
      typedef FragmentGroupInfo<1> monomer_signature_database_type;
      typedef FragmentGroupInfo<2> dimer_signature_database_type;
      typedef FragmentGroupInfo<3> trimer_signature_database_type;
      typedef FragmentGroupInfo<4> tetramer_signature_database_type;
      std :: tuple < std :: string, iquads :: structure :: MolecularLattice > lattice_info_type;
    public:
      void build( lattice_info_type lattice_info ) {
        this->monomer_signature_database_.build( lattice_info );
        this->dimer_signature_database_.build( lattice_info );
        this->trimer_signature_database_.build( lattice_info );
        this->tetramer_signature_database_.build( lattice_info );
      }
    private:
      monomer_signature_database_type monomer_signature_database_;
      dimer_signature_database_type dimer_signature_database_;
      trimer_signature_database_type trimer_signature_database_;
      tetramer_signature_database_type tetramer_signature_database_;
  };

} // end of namespace manybody_expansion

} // end of namespace iquads

#endif
