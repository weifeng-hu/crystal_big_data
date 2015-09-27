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

#ifndef MANYBODY_EXPANSION_REPORT_HPP
#define MANYBODY_EXPANSION_REPORT_HPP

#include <vector>
#include <array>
#include <manybody_expansion/polymer_report_omni_template.hpp>

using std::vector;
using std::array;

namespace iquads {

namespace manybody_expansion {

template < template < class > class PolyerOmniReport_Type > struct Report {
public:
  typedef double energy_data_type;
  typedef size_t mbe_order_type;
  typedef bool condition_type;

public:
  typedef PolymerOmniReport_Type monomer_report_type;
  typedef PolymerOmniReport<2> dimer_report_type;
  typedef PolymerOmniReport<3> trimer_report_type;
  typedef PolymerOmniReport<4> tetramer_report_type;
  typedef vector< monomer_report_type >  monomer_report_list_type;
  typedef vector< dimer_report_type >    dimer_report_list_type;
  typedef vector< trimer_report_type >   trimer_report_list_type;
  typedef vector< tetramer_report_type > tetramer_report_list_type;

public:
  void print() const;

public:
  energy_data_type return_one_body_energy_per_unit_cell()
   {
     energy_data_type retval = 0.0e0;
     for( size_t i = 0; i < this->monomer_report_list_.size(); i++ ){
      retval += this->monomer_report_list_[i].total_energy();
     }
     return retval;
   }
  energy_data_type return_two_body_interaction_energy_per_unit_cell()
   {
     energy_data_type retval = 0.0e0;
     for( size_t i = 0; i < this->dimer_report_list_.size(); i++ ){
      retval += this->dimer_report_list_[i].interaction_energy();
     }
     return retval;
   }
  energy_data_type return_three_body_interaction_energy_per_unit_cell()
   {
     energy_data_type retval = 0.0e0;
     for( size_t i = 0; i < this->trimer_report_list_.size(); i++ ){
      retval += this->trimer_report_list_[i].interaction_energy();
     }
     return retval;
   }
  energy_data_type return_four_body_interaction_energy_per_unit_cell()
   {
     energy_data_type retval = 0.0e0;
     for( size_t i = 0; i < this->tetramer_report_list_.size(); i++ ){
      retval += this->tetramer_report_list_[i].interaction_energy();
     }
     return retval;
   }
  energy_data_type return_total_energy_per_unit_cell()
   {
     energy_data_type retval = 0.0e0;
     if( this->mbe_order >= 1 ) retval += this->return_one_body_energy_per_unit_cell();
     if( this->mbe_order >= 2 ) retval += this->return_two_body_interaction_per_unit_cell();
     if( this->mbe_order >= 3 ) retval += this->return_three_body_interaction_per_unit_cell();
     if( this->mbe_order >= 4 ) retval += this->return_four_body_interaction_per_unit_cell();
     return retval;
   }
  
public:
  void add_monomer_data_to_sym_noneq_list(){}
  void add_dimer_data_to_sym_noneq_list(){}
  void add_trimer_data_to_sym_noneq_list(){}
  void add_tetramer_data_to_sym_noneq_list(){}

  void attach_new_monomer_report( monomer_report_type monomer_report )
   { this->monomer_report_list_.push_back( monomer_report ); }
  void attach_new_dimer_report( dimer_report_type dimer_report )
   { this->dimer_report_list_.push_back( dimer_report ); }
  void attach_new_trimer_report( trimer_report_type trimer_report )
   { this->trimer_report_list_.push_back( trimer_report ); }
  void attach_new_tetramer_report( tetramer_report_type tetramer_report )
   { this->tetramer_report_list_.push_back( tetramer_report ); }

private:
  /*
   *  list of monomer info
   *  list of dimer info
   *  list of trimer info
   *  list of tetramer info
   *  Periodicity allows the use of fragment identifier
   *  manybody expansion order, here we have implemented MBE formula for order<=4
   */
  monomer_report_list_type    monomer_report_list_;
  dimer_report_list_type      dimer_report_list_;
  trimer_report_list_type     trimer_report_list_;
  tetramer_report_list_type   tetramer_report_list_;
  mbe_order_type              mbe_order_;

}; // end of struct Report

} // end of namespace manybody_expansion

} // end of namespace iquads

#endif
