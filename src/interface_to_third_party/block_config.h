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
 */

#ifndef BLOCK_CONFIG_H
#define BLOCK_CONFIG_H

#include <vector>
#include <string>

using std::vector;
using std::string;

namespace iquads { 

namespace interface_to_third_party { 

struct Block_Config
{
public:
  typedef bool condition_type;
  typedef condition_type& condition_reference;
  typedef size_t iteration_index_type;
  typedef iteration_index_type& iteration_index_reference;
  typedef size_t M_type;
  typedef M_type& M_reference;
  typedef double tolerance_type;
  typedef tolerance_type& tolerance_reference;
  typedef double noise_type;
  typedef noise_type& noise_reference;
  typedef double weight_type;
  typedef weight_type& weight_reference;
  typedef vector< weight_type > weights_type;
  typedef weights_type& weights_reference;
  typedef size_t number_type;
  typedef number_type& number_reference;
  typedef string file_name_type;
  typedef file_name_type& file_name_reference;

public:
  struct ScheduleSet
  {
  public:
    const iteration_index_type iteration_index() const 
     { return this->iteration_index_; }
    iteration_index_reference set_iteration_index()
     { return this->iteration_index_; }
    const M_type M() const
     { return this->M_; }
    M_reference set_M()
     { return this->M_; }
    const tolerance_type david_tol() const
     { return this->david_tol_; }
    tolerance_referance set_david_tol()
     { return this->david_tol_; }
    const noise_type noise() const 
     { return this->noise_; }
    noise_reference set_noise()
     { return this->noise_; }

  private:
    iteration_index_type iteration_index_;
    M_type M_;
    tolerance_type david_tol_;
    noise_type noise_;
  }; // end of structure schedule

  typedef Schedule_Set schedule_set_type;
  typedef vector<schedule_set_type> schedule_type;

public:
  void set_defaults();

public:
  const schedule_type schedule() const 
   { return this->schedule_; }
  schedule_reference set_schedule()
   { return this->schedule_; }
  const condition_type do_cd() const 
   { return this->do_cd_; }
  condition_reference set_do_cd()
   { return this->do_cd_; }
  const condition_type do_onepdm() const 
   { return this->do_onepdm_; }
  conditon_reference set_do_onepdm()
   { return this->do_onepdm_; }
  const condition_type do_twopdm() const
   { return this->do_twopdm_; }
  condition_reference set_do_twopdm()
   { return this->do_twopdm_; }
  const number_type norb() const
   { return this->norb_; }
  number_reference set_nor()
   { return this->norb_; }
  const number_type na() const
   { return this->na_; }
  number_reference set_na()
   { return this->na_; }
  const number_type nb() const
   { return this->nb_; }
  number_reference set_nb()
   { return this->nb_; }
  const number_type number_schedule() const
   { return this->number_schedule_; }
  number_reference set_number_schedule()
   { return this->number_schedule_; }
  const number_type nroot() const
   { return this->nroot_; }
  number_reference set_nroot()
   { return this->nroot_; }
  const iteration_index_type maxiter() const 
   { return this->maxiter_; }
  iteration_index_reference set_maxiter()
   { return this->maxiter_; }
  const iteration_index_type twodot_to_onedot() const
   { return this->twodot_to_onedot_; }
  iteration_index_reference set_twodot_to_onedot()
   { return this->twodot_to_onedot_; }
  const weights_type weights() const 
   { return this->weights_; }
  weights_reference set_weights()
   { return this->weight_; }
  const tolerance_type sweep_tol() const 
   { return this->sweep_tol_; }
  tolerance_reference set_sweep_tol()
   { return this->sweep_tol_; }
  const file_name_type fcidump() const
   { return this->fcidump_; }
  file_name_reference set_fcidump()
   { return this->fcidump_; }

private:
  schedule_type schedule_;
  condition_type do_cd_;
  condition_type do_onepdm_;
  condition_type do_twopdm_;
  number_type norb_;
  number_type na_, nb_;
  number_type num_schedule_;
  number_type nroot_;
  iteration_index_type maxiter_;
  iteration_index_type twodot_to_onedot_;
  weights_type weights;
  tolerance_type sweep_tol_;
  file_name_type fcidump_;

}; // end of class Block_Config

} // end of namespace interface_to_third_party

} // end of namespace iquads

#endif
