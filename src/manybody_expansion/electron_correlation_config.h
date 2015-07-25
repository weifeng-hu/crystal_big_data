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

#include <manybody_expansion/electron_correlation_method_bitmask.h>

namespace iquads {

namespace manybody_expansion {

namespace electron_correlation {

struct ElectronCorrelation_Config
{
public:
  typedef bool condition_type;
  typedef condition_type& condition_reference;

public:
  ElectronCorrelation_Config()
   {
     this->hf_requested_ = false;
     this->mp2_requested_ = false;
     this->ccsd_requested_ = false;
     this->ccsdt_requested_ = false;
     this->dmrg_requested_ = false;
   }

public:
  void enable_hf()
   {
     this->hf_requested_ = true;
   }
  void enable_mp2()
   {
     this->hf_requested_ = true;
     this->mp2_requested_ = true;
   }
  void enable_ccsd()
   {
     this->hf_requested_ = true;
     this->ccsd_requsted_ = true;
   }
  void enable_ccsdt()
   {
     this->hf_requested_ = true;
     this->ccsdt_requested_ = true;
   }
  void enable_dmrg()
   {
     this->hf_requested_ = true;
     this->dmrg_requested_ = true;
   }

public:
  const condition_type hf_requested() const
   { return this->hf_requested_; }
  condition_reference set_hf_requested()
   { return this->hf_requested_; }

  const condition_type mp2_requested() const 
   { return this->mp2_requested_; }
  condition_reference set_mp2_requested() 
   { return this->mp2_requested_; }

  const condition_type ccsd_requested() const 
   { return this->ccsd_requested_; }
  condition_reference set_ccsd_requested()
   { return this->ccsd_requested_; }

  const condition_type ccsdt_requested() const 
   { return this->ccsdt_requested_; }
  condition_reference set_ccsdt_requested()
   { return this->ccsdt_requested_; }

  const condition_type dmrg_requested() const
   { return this->dmrg_requested_; }
  condition_reference set_dmrg_requested()
   { return this->dmrg_requested_; }

private:
  condition_type hf_requested_;
  condition_type mp2_requested_;
  condition_type ccsd_requested_;
  condition_type ccsdt_requested_;
  condition_type dmrg_requested_;

  bitmask_type total_correlation_mask_;

}; // end of class ElectronCorrelation_Config

} // end of namespace electron_correlation

} // end of namespace manybody_expansion

} // end of namespace iquads

#endif
