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
using std::size_t;

namespace iquads { 

namespace interface_to_third_party { 

struct Block_Config
{
public:
  typedef bool condition_type;
  typedef size_t iteration_index_type;
  typedef size_t M_type;
  typedef double tolerance_type;
  typedef double noise_type;
  typedef double weight_type;
  typedef vector< weight_type > weights_type;
  typedef size_t number_type;
  typedef string file_name_type;

public:
  struct ScheduleSet
  {
  public:
    iteration_index_type iteration_index_;
    M_type M_;
    tolerance_type david_tol_;
    noise_type noise_;
  }; // end of structure schedule

  typedef Schedule_Set schedule_set_type;
  typedef vector<schedule_set_type> schedule_type;

public:
  void set_defaults();

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
