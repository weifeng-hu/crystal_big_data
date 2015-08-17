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

#ifndef MANYBODY_EXPANSION_REPORT_H
#define MANYBODY_EXPANSION_REPORT_H

#include <vector>

using std::vector;

namespace iquads { 

namespace manybody_expansion {

struct Report {
public:
  typedef double energy_data_type;
  typedef vector< energy_data_type > energy_data_list_type;
  typedef size_t size_type;
  typedef size_t order_type;
  typedef bool condition_type;

public:
  void print(){}

public:
  const energy_data_type total_energy() const 
   { return this->total_energy_; }

private:
  energy_data_type total_energy_;
  energy_data_type total_monomer_energy_;
  energy_data_type total_interaction_energy_dimer_;
  energy_data_type total_interaction_energy_trimer_;
  energy_data_type total_interaction_energy_tetramer_;

  energy_data_list_type monomer_energy_;
  energy_data_list_type dimer_energy_;
  energy_data_list_type trimer_energy_;
  energy_data_list_type tetramer_energy_;

  energy_data_list_type interaction_energy_dimer_;
  energy_data_list_type interaction_energy_trimer_;
  energy_data_list_type interaction_energy_tetramer_;

  size_type n_monomer_per_cell_;
  size_type n_dimer_;
  size_type n_trimer_;
  size_type n_tetramer_;

  size_type n_untcell_;

  order_type total_order_;

}; // end of namespace Report

} // end of namespace manybody_expansion

} // end of namespace iquads

#endif
