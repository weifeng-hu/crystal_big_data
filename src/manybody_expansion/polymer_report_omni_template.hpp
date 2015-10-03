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
 *
 */

#ifndef MANYBODY_EXPANSION_POLYMER_OMNI_REPORT_HPP
#define MANYBODY_EXPANSION_POLYMER_OMNI_REPORT_HPP

#include <manybody_expansion/polymer_report_template.hpp>
#include <manybody_expansion/polymer_report_subgroup_traits.hpp>

namespace iquads {

namespace manybody_expansion {

/**
 *  This is the actual meta-data of MBE calculation results
 *
 *  Note:
 *  After I completed the design this template framework, I realized that 
 *  I have actually created a CRTP (Curiously recurring template pattern),
 *  though I've never planned to understand it. But now I understand that 
 *  this pattern is really useful.
 *
 *  A CRTP pattern is to make something like this,
 *
 *  template < class T > class Base {}
 *  class Derived : public Base< Derived > {}
 *
 *  The important feature is that the Derived objects can use the method 
 *  created in the Base class. And this is the purpose of this Polymer
 *  report class.
 *
 *  PolymerOmniReportGeneral is a meta-data object to store all information 
 *  about a polymer calculated by the solvers. It contains:
 *   + PolymerReport, for the polymer itself.
 *   + All subgroup, or subfragment reports.
 *     Subfragment reports can also be PolymerOmniReportGeneral, thereby 
 *     subgroup reports contains information of sub-sub groups.
 *
 *  An important design goal is that we don't have to use virtual methods
 *  to access those subgroup report members, therefore the best way is to
 *  use the public inheritance. We want the omni report can use subgroup report 
 *  functions, which will be further used to access the data member of 
 *  data type of omni report (with a lower number of parameter). 
 *  However, since subgroup reports also contain this PolymerOmniReportGeneral, 
 *  this will create a recursive, and infinite definition of these two 
 *  classes. Therefore a strategy is to leave the type of actual omni 
 *  reports in subgroup reports as "not specified", i.e., a template 
 *  typename. By using the inheritance with the actual specialization 
 *  of subgroup report with this concrete omni report type, this allows that
 *  all naming can be found within the same name scope.
 */ 

/**
 *  A general version
 */
template < size_t NUM > struct PolymerOmniReportGeneral : public PolymerReport<NUM>, public PolymerSubGroupReport< PolymerOmniReportGeneral, NUM> {
public:
  typedef PolymerReport<NUM> polymer_report_type;
  typedef PolymerSubGroupReport< PolymerOmniReportGeneral, NUM > polymer_subgroup_report_type;
  typedef double weight_factor_type;

public:
  void set_report_cover( polymer_report_type report )
    {
      this->fragment_name_ = report.fragment_name();
      this->atom_list_ = report.atom_list();
      this->geometry_unit_ = report.geometry_unit();
      this->composition_list_ = report.composition_list();
      this->fragment_energy_ = report.fragment_energy();
      this->interaction_energy_ = report.interaction_energy();
      this->electron_correlation_report_ = report.electron_correlation_report();
      this->external_program_report_ = report.external_program_report();
    }

public:
  typename polymer_report_type :: energy_data_type total_energy() const
    { return this->fragment_energy(); }
  weight_factor_type weight_factor() const
    { return 1.0e0; }

}; // end of template struct PolymerOmniReportGeneral<NUM>

//template <> struct PolymerOmniReportGeneral<0> {};

/**
 *
 *  In this peridic version, inherited from the general version, 
 *  fragment list is enabled due to the periodicity in real systems
 *
 */

template < size_t NUM > struct PolymerOmniReportPeriodic : public PolymerReport<NUM>, PolymerSubGroupReport< PolymerOmniReportPeriodic, NUM> {
public:
  typedef PolymerReport<NUM> polymer_report_type;
  typedef PolymerSubGroupReport< PolymerOmniReportPeriodic, NUM> polymer_subgroup_report_type;
  typedef vector< typename polymer_report_type :: composition_list_type > fragment_list_type;
  typedef double weight_factor_type;

public:
  const typename polymer_report_type :: energy_data_type total_energy() const 
   { return this->weight_factor_ * this->fragment_energy(); }

public:
  fragment_list_type fragment_list() const
    { return this->fragment_list_; }
  weight_factor_type weight_factor() const
    { return this->weight_factor_; }

protected:
  fragment_list_type fragment_list_;
  weight_factor_type weight_factor_;

}; // end of template struct PolymerOmnoReportPeriodic<NUM>

} // end of namespace manybody_expansion

} // end of namespace iquads

#endif 
