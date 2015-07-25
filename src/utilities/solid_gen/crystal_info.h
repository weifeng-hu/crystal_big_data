/*
 *  This source code applies all the terms in 
 *  GNU GENERAL PUBLIC LICENSE (GPL), Version3, 29 June 2007.
 *
 *  Copyright (C) 2013-2015 Weifeng Hu, all rights reserved.
 *  
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef CRYSTAL_INFO_H
#define CRYSTAL_INFO_H

#include <tuple>
#include <string>
#include "utilities/solid_gen/unit_cell.h"

using std::tuple;
using std::string;

namespace iquads {

namespace crystal {

struct molecular_crystal_info
{
public:
  molecular_crystal_info(){
   this->reset();
  }

private:
  void reset(){
   this->radius_ = 0.0e0;
   this->short_range_radius_ = 0.0e0;
   this->long_range_radius_ = 0.0e0;
   this->short_range_requested_ = false;
   this->long_range_requested_ = false;
   this->dimer_requested_ = false;
   this->trimer_requested_ = false;
   this->tetramer_requested_ = false;
   this->visualization_ = false;
   this->n_fragment_type_ = 0;
   this->sizes = make_tuple( 0, 0, 0 );
  }

public:
  void read( string input );

public:
  molecular_ucell get_molecular_cell() const 
   { return this->primitive_; }

  double get_radius() const 
   { return this->radius_; }
  double get_short_range_radius() const 
   { return this->short_range_radius_; }
  double get_long_range_radius() const
   { return this->long_range_radius_; }

  bool short_range_requested() const 
   { return this->short_range_requested_; }
  bool long_range_requested() const
   { return this->long_range_requested_; }
  bool dimer_requested() const 
   { return this->dimer_requested_; }
  bool trimer_requested() const 
   { return this->trimer_requested_; }
  bool tetramer_requested() const 
   { return this->tetramer_requested_; }
  bool visual_requested() const 
   { return this->visualization_; }
  size_t get_n_fragment_type() const 
   { return this->n_fragment_type_; }
  size_t& get_n_fragment_type()
   { return this->n_fragment_type_; }
  int get_center_index() const 
   { return this->center_index_; }
  tuple< size_t, size_t, size_t > get_sizes() const 
   { return this->sizes; }

private:
  molecular_ucell primitive_;
  double radius_;
  double short_range_radius_;
  double long_range_radius_;
  bool short_range_requested_;
  bool long_range_requested_;
  bool dimer_requested_;
  bool trimer_requested_;
  bool tetramer_requested_;
  bool visualization_;
  size_t n_fragment_type_;
  int center_index_;
  tuple< size_t, size_t, size_t > sizes;
  array<double, 3> angles;
  array<double, 3> lengths;

}; // end of struct molecular_crystal_info

} // end of namespace crystal

} // end of namespace iquads

#endif
