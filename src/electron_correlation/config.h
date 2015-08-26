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

#ifndef ELECTRON_CORRELATION_CONFIG_H
#define ELECTRON_CORRELATION_CONFIG_H

#include <electron_correlation/method_bitmask.h>

namespace iquads {

namespace electron_correlation {

struct Config
{
public:
  typedef unsigned int condition_type;
  typedef condition_type& condition_ref;

public:
  Config()
   {
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
  const condition_type hf_requested() const
   { return ( this->total_correlation_mask_ & RHF ); }
  const condition_type mp2_requested() const 
   { return ( this->total_correlation_mask_ & MP2 ); }
  const condition_type ccsd_requested() const 
   { return ( this->total_correlation_mask_ & CCSD ); }
  const condition_type ccsdt_requested() const 
   { return ( this->total_correlation_mask_ & CCSDT ); }
  const condition_type dmrg_requested() const
   { return ( this->total_correlation_mask_ & DMRG ); }

private:
  bitmask_type total_correlation_mask_;

}; // end of struct Config

} // end of namespace electron_correlation

} // end of namespace iquads

#endif
