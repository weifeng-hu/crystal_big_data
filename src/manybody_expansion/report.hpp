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
#include <manybody_expansion/polymer_report_omni_instant.hpp>

namespace iquads {

namespace manybody_expansion {

  /**
   *   A meta-data to contain results from many body expansion calculations
   *
   *   We include all possible types of data types and sub reports (which are 
   *   implemented as templates) in this Report object. Therefore this Report 
   *   object can serve for both periodic and non-periodic calculations.
   *
   *   Data members are (both for periodic and non-periodic):
   *   + A list of single report objects for 
   *     + monomers
   *     + dimers
   *     + trimers
   *     + tetramers.
   *   And each piece of the report object in a report list contains 
   *   calculation results of quantities, e.g., energies, input geometries,
   *   runtime variables, etc.
   *   See "Implementation 4" below for detailed design notes.
   */

using std :: vector;
using std :: array;

  /**
   *   About using template template class
   *
   *   Since the actual report type may depend on whether the calculation 
   *   is for a periodic system or not, the report struct can be templated
   *   using the periodicity as the parameter. Also the report depends on 
   *   another parameter which is the size of the polymers, but this parameter 
   *   more or less belongs the the actual sub-reports. In all, it is possible
   *   to design a template template class for the report to be like
   *   Report< Periodicity< N > >.
   *
   *   There is no problem to do this, also this can help avoid registering 
   *   possible sub-report types. The payoff is to write out the explicit 
   *   instantiation head files, also the method to use an actual templated class 
   *   must also be templated.
   *
   *   There are two ways to implement this kind of templated template report class, 
   *   though essentially they are the same.
   *   
   */

  /**
   *   Implementation 1
   */
  /**
   template < template < size_t N> class PolymerOmniReport_Type > struct Report {
     public:
       typedef PolymerOmniReport_Type<1> monomer_report_type;
       typedef PolymerOmniReport_Type<2> dimer_report_type;
       typedef PolymerOmniReport_Type<3> trimer_report_type;
       typedef PolymerOmniReport_Type<4> tetramer_report_type; // we should include the size_t N here since it has been declared for typename PolymerOmniReport_Type
     private:
       monomer_report_type  monomer_report;
       dimer_report_type    dimer_report;
       trimer_report_type   trimer_report;
       tetramer_report_type tetramer_report;
   };

   Report< PolymerOmniReportPeriodic >  report;  // We should not indicate the parameter size_t N since it is invible to object Report in definition.
   */

  /**
   *   Implementation 2
   */
  /**
   template < template < size_t > class PolymerOmniReport_Type, size_t N > struct Report {
     public:
       typedef PolymerOmniReport_Type monomer_report_type;
       typedef PolymerOmniReport_Type dimer_report_type;
       typedef PolymerOmniReport_Type trimer_report_type;
       typedef PolymerOmniReport_Type tetramer_report_type;  // we should not include the size_t N here since it has not been declared for typename PolymerOmniReport_Type
     private:
       monomer_report_type  monomer_report;
       dimer_report_type    dimer_report;
       trimer_report_type   trimer_report;
       tetramer_report_type tetramer_report;
   };
   
   Report< PolymerOmniReportPeriodic, 1 > report; // size_t N now is a template parameter so we have to include it.
   */

  /**
   *   Implementation 3
   *   This implementation is trivial compared to previous two cases
   */
  /**
   template < class PolymerOmniReport_Type > struct Report {
     public:
       typedef PolymerOmniReport_Type monomer_report_type;
       typedef PolymerOmniReport_Type dimer_report_type;
       typedef PolymerOmniReport_Type trimer_report_type;
       typedef PolymerOmniReport_Type tetramer_report_type;
     private:
       monomer_report_type  monomer_report;
       dimer_report_type    dimer_report;
       trimer_report_type   trimer_report;
       tetramer_report_type tetramer_report;
   };
   
   Report< PolymerOmniReportPeriodic<1> > report; // 1 is a template parameter of PolymerOmniReportPeriodic so we have to include it
   */

  /**
   *   Implementation 4
   *   We do not use template class for Report, and we include all explicitly instantiated 
   *   template as member types and members. This won't bring too much waste of resource since 
   *   the individual subreport are of finite size and the data array container std :: vector
   *   is chosen to use with being initialized as with size 0 (by GNU C++ compiler). But we
   *   have to implement methods to choose the use of subreport members at runtime. The runtime 
   *   choice can be implemented by virtual methods, which we should try to avoid here, because 
   *   this generally implies a mix of dynamic polymorphism(virtual methods) and static polymorphism
   *   (templated data members) and will not in general result in a good design.
   *
   *   The main reason to use non-templated design is that the stategies to use a "Report" object, 
   *   by agents and clients, are strongly run-time dependent(like the choice of periodicity) 
   *   and non-generic, implying a static polymorphism not an agile design. Another reason is that
   *   since this report object is a meta-data type it is more reasonable to include all kinds 
   *   of possible information in this object.
   *
   */

struct Report {
public:
  typedef double energy_data_type;
  typedef size_t mbe_order_type;
  typedef bool condition_type;

public:
  typedef PolymerOmniReportGeneral<1>   non_periodic_monomer_report_type;
  typedef PolymerOmniReportGeneral<2>   non_periodic_dimer_report_type;
  typedef PolymerOmniReportGeneral<3>   non_periodic_trimer_report_type;
  typedef PolymerOmniReportGeneral<4>   non_periodic_tetramer_report_type;
  typedef vector< non_periodic_monomer_report_type >    non_periodic_monomer_report_list_type;
  typedef vector< non_periodic_dimer_report_type >      non_periodic_dimer_report_list_type;
  typedef vector< non_periodic_trimer_report_type >     non_periodic_trimer_report_list_type;
  typedef vector< non_periodic_tetramer_report_type >   non_periodic_tetramer_report_list_type;

  typedef PolymerOmniReportPeriodic<1>   periodic_monomer_report_type;
  typedef PolymerOmniReportPeriodic<2>   periodic_dimer_report_type;
  typedef PolymerOmniReportPeriodic<3>   periodic_trimer_report_type;
  typedef PolymerOmniReportPeriodic<4>   periodic_tetramer_report_type;
  typedef vector< periodic_monomer_report_type >    periodic_monomer_report_list_type;
  typedef vector< periodic_dimer_report_type >      periodic_dimer_report_list_type;
  typedef vector< periodic_trimer_report_type >     periodic_trimer_report_list_type;
  typedef vector< periodic_tetramer_report_type >   periodic_tetramer_report_list_type;

public:
  void print() const;

public:
  energy_data_type return_one_body_energy_per_unit_cell()
    {
      energy_data_type retval = 0.0e0;
      for( size_t i = 0; i < this->non_periodic_monomer_report_list_.size(); i++ ){
        retval += this->non_periodic_monomer_report_list_[i].total_energy();
      }
      return retval;
    }
  energy_data_type return_two_body_interaction_energy_per_unit_cell()
    {
      energy_data_type retval = 0.0e0;
      for( size_t i = 0; i < this->non_periodic_dimer_report_list_.size(); i++ ) {
        retval += this->non_periodic_dimer_report_list_[i].interaction_energy();
      }
      return retval;
    }
  energy_data_type return_three_body_interaction_energy_per_unit_cell()
    {
      energy_data_type retval = 0.0e0;
      for( size_t i = 0; i < this->non_periodic_trimer_report_list_.size(); i++ ) {
        retval += this->non_periodic_trimer_report_list_[i].interaction_energy();
      }
      return retval;
    }
  energy_data_type return_four_body_interaction_energy_per_unit_cell()
    {
      energy_data_type retval = 0.0e0;
      for( size_t i = 0; i < this->non_periodic_tetramer_report_list_.size(); i++ ) {
        retval += this->non_periodic_tetramer_report_list_[i].interaction_energy();
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
  void add_monomer_data_to_sym_noneq_list(){}
  void add_dimer_data_to_sym_noneq_list(){}
  void add_trimer_data_to_sym_noneq_list(){}
  void add_tetramer_data_to_sym_noneq_list(){}

  void attach_new_monomer_report( periodic_monomer_report_type monomer_report )
    { this->periodic_monomer_report_list_.push_back( monomer_report ); }
  void attach_new_dimer_report( periodic_dimer_report_type dimer_report )
    { this->periodic_dimer_report_list_.push_back( dimer_report ); }
  void attach_new_trimer_report( periodic_trimer_report_type trimer_report )
    { this->periodic_trimer_report_list_.push_back( trimer_report ); }
  void attach_new_tetramer_report( periodic_tetramer_report_type tetramer_report )
    { this->periodic_tetramer_report_list_.push_back( tetramer_report ); }

  void attach_new_monomer_report( non_periodic_monomer_report_type monomer_report )
    { this->non_periodic_monomer_report_list_.push_back( monomer_report ); }
  void attach_new_dimer_report( non_periodic_dimer_report_type dimer_report )
    { this->non_periodic_dimer_report_list_.push_back( dimer_report ); }
  void attach_new_trimer_report( non_periodic_trimer_report_type trimer_report )
    { this->non_periodic_trimer_report_list_.push_back( trimer_report ); }
  void attach_new_tetramer_report( non_periodic_tetramer_report_type tetramer_report )
    { this->non_periodic_tetramer_report_list_.push_back( tetramer_report ); }

private:
  /*
   *  list of monomer info
   *  list of dimer info
   *  list of trimer info
   *  list of tetramer info
   *  Periodicity allows the use of fragment identifier
   *  manybody expansion order, here we have implemented MBE formula for order<=4
   */
  non_periodic_monomer_report_list_type    non_periodic_monomer_report_list_;
  non_periodic_dimer_report_list_type      non_periodic_dimer_report_list_;
  non_periodic_trimer_report_list_type     non_periodic_trimer_report_list_;
  non_periodic_tetramer_report_list_type   non_periodic_tetramer_report_list_;

  periodic_monomer_report_list_type    periodic_monomer_report_list_;
  periodic_dimer_report_list_type      periodic_dimer_report_list_;
  periodic_trimer_report_list_type     periodic_trimer_report_list_;
  periodic_tetramer_report_list_type   periodic_tetramer_report_list_;

  mbe_order_type              mbe_order_;

}; // end of struct Report

} // end of namespace manybody_expansion

} // end of namespace iquads

#endif
