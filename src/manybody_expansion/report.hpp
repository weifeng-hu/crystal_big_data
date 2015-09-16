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

/**
 * Design note:
 * Since we have different polymer report types: General and Periodic, both are templated,
 * making this final Report type to be a templated class will be an option.
 *
 * However, this means that this Report class will be a template template class,
 * and there are several downsides.
 * 1. The design goal of this meta-data comtainer is to be simple, with less
 *    compile-time or run-time polymorphism, less confusion, though we sacrifice 
 *    a little genericity. 
 * 2. Typedef of template parameters of a template template class cannot be implemented 
 *    in a clean way like typedef template parameters for template classes. It 
 *    is not well-supported by the standard so far. Making in-class structures and putting  
 *    typedef parameters will be a dirty workaround.
 * 
 *
 */

struct Report {
public:
  typedef double energy_data_type;
  typedef size_t mbe_order_type;
  typedef bool condition_type;

public:
  typedef PolymerOmniReportGeneral<1> monomer_general_report_type;
  typedef PolymerOmniReportGeneral<2> dimer_general_report_type;
  typedef PolymerOmniReportGeneral<3> trimer_general_report_type;
  typedef PolymerOmniReportGeneral<4> tetramer_general_report_type;
  typedef vector< monomer_general_report_type >  monomer_general_report_list_type;
  typedef vector< dimer_general_report_type >    dimer_general_report_list_type;
  typedef vector< trimer_general_report_type >   trimer_general_report_list_type;
  typedef vector< tetramer_general_report_type > tetramer_general_report_list_type;

public:
  void print() const;

public:
  energy_data_type return_one_body_energy_per_unit_cell()
   {
     energy_data_type retval = 0.0e0;
     for( size_t i = 0; i < this->monomer_general_report_list_.size(); i++ ){
      retval += this->monomer_general_report_list_[i].total_energy();
     }
     return retval;
   }
  energy_data_type return_two_body_interaction_energy_per_unit_cell()
   {
     energy_data_type retval = 0.0e0;
     for( size_t i = 0; i < this->dimer_general_report_list_.size(); i++ ){
      retval += this->dimer_general_report_list_[i].interaction_energy();
     }
     return retval;
   }
  energy_data_type return_three_body_interaction_energy_per_unit_cell()
   {
     energy_data_type retval = 0.0e0;
     for( size_t i = 0; i < this->trimer_general_report_list_.size(); i++ ){
      retval += this->trimer_general_report_list_[i].interaction_energy();
     }
     return retval;
   }
  energy_data_type return_four_body_interaction_energy_per_unit_cell()
   {
     energy_data_type retval = 0.0e0;
     for( size_t i = 0; i < this->tetramer_general_report_list_.size(); i++ ){
      retval += this->tetramer_general_report_list_[i].interaction_energy();
     }
     return retval;
   }
  energy_data_type return_total_energy_per_unit_cell()
   {
     energy_data_type retval = 0.0e0;
     if( this->mbe_order_ >= 1 ) retval += this->return_one_body_energy_per_unit_cell();
     if( this->mbe_order_ >= 2 ) retval += this->return_two_body_interaction_energy_per_unit_cell();
     if( this->mbe_order_ >= 3 ) retval += this->return_three_body_interaction_energy_per_unit_cell();
     if( this->mbe_order_ >= 4 ) retval += this->return_four_body_interaction_energy_per_unit_cell();
     return retval;
   }

public:
  void save(){}
  void add_monomer_data_to_sym_noneq_list(){}
  void add_dimer_data_to_sym_noneq_list(){}
  void add_trimer_data_to_sym_noneq_list(){}
  void add_tetramer_data_to_sym_noneq_list(){}

  void attach_new_monomer_report( monomer_general_report_type monomer_report )
   { this->monomer_general_report_list_.push_back( monomer_report ); }
  void attach_new_dimer_report( dimer_general_report_type dimer_report )
   { this->dimer_general_report_list_.push_back( dimer_report ); }
  void attach_new_trimer_report( trimer_general_report_type trimer_report )
   { this->trimer_general_report_list_.push_back( trimer_report ); }
  void attach_new_tetramer_report( tetramer_general_report_type tetramer_report )
   { this->tetramer_general_report_list_.push_back( tetramer_report ); }

private:
  /*
   *  list of monomer info
   *  list of dimer info
   *  list of trimer info
   *  list of tetramer info
   *  Periodicity allows the use of fragment identifier
   *  manybody expansion order, here we have implemented MBE formula for order<=4
   */
  monomer_general_report_list_type    monomer_general_report_list_;
  dimer_general_report_list_type      dimer_general_report_list_;
  trimer_general_report_list_type     trimer_general_report_list_;
  tetramer_general_report_list_type   tetramer_general_report_list_;
  mbe_order_type                      mbe_order_;

}; // end of struct Report

} // end of namespace manybody_expansion

} // end of namespace iquads

#endif
