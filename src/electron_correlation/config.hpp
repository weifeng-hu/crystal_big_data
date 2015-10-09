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
 * the Free Software Foundation, either version 3 of the License, or
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

#ifndef ELECTRON_CORRELATION_CONFIG_HPP
#define ELECTRON_CORRELATION_CONFIG_HPP

#include <iquads/sequence.hpp>
#include <structure/molecule.hpp>

namespace iquads {

namespace electron_correlation {

struct Config {
public:
  typedef Molecule molecule_info_type;
  typedef bool condition_type;
  typedef condition_type& condition_ref;

public:
  Config() {
     this->total_correlation_mask_ = 0x00;
  }

public:
  void enable_hf()
   {
     this->total_correlation_mask_ = 
      ( this->total_correlation_mask_ | RHF );
   }
  void enable_mp2()
   {
     this->total_correlation_mask_ = 
      ( this->total_correlation_mask_ | RHF | MP2 );
   }
  void enable_ccsd()
   {
     this->total_correlation_mask_ = 
      ( this->total_correlation_mask_ | RHF | CCSD );
   }
  void enable_ccsdt()
   {
     this->total_correlation_mask_ = 
      ( this->total_correlation_mask_ | RHF | CCSDT );
   }
  void enable_dmrg()
   {
     this->total_correlation_mask_ = 
      ( this->total_correlation_mask_ | RHF | DMRG );
   }

public:
  condition_type hf_requested() const
    { return ( this->total_correlation_mask_ & RHF ); }
  condition_type mp2_requested() const 
    { return ( this->total_correlation_mask_ & MP2 ); }
  condition_type ccsd_requested() const 
    { return ( this->total_correlation_mask_ & CCSD ); }
  condition_type ccsdt_requested() const 
    { return ( this->total_correlation_mask_ & CCSDT ); }
  condition_type dmrg_requested() const
    { return ( this->total_correlation_mask_ & DMRG ); }

private:
  molecule_info_type molecule_info_;
  bitmask_type total_correlation_mask_;

}; // end of struct Config

} // end of namespace electron_correlation

} // end of namespace iquads

#endif
