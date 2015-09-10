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

#ifndef MANYBODY_EXPANSION_POLYMER_SUBGROUP_REPORT_TRAITS_HPP
#define MANYBODY_EXPANSION_POLYMER_SUBGROUP_REPORT_TRAITS_HPP

#include <array>
#include <manybody_expansion/polymer_report_template.hpp>

using std::array;

namespace iquads {

namespace manybody_expansion {

template < size_t N > struct PolymerSubGroupReport { };
  // end of template struct PolymerSubGroupReport general definition


template <> struct PolymerSubGroupReport<2> {
  public:
    typedef PolymerReport<1> monomer_report_type;

  public:
    const array< monomer_report_type, 2 >& monomer_reports() const 
     { return this->monomer_reports_; }

  protected:
    array< monomer_report_type, 2 > monomer_reports_;

}; // end of template struct trait PolymerSubGroupReport<2>


template <> struct PolymerSubGroupReport<3> {
  public:
    typedef PolymerReport<1> monomer_report_type;
    typedef PolymerReport<2> dimer_report_type;

  public:
    const array< monomer_report_type, 3 >& monomer_reports() const 
     { return this->monomer_reports_; }
    const array< dimer_report_type, 3 >& dimer_reports() const 
     { return this->dimer_reports_; }

  protected:
    array< monomer_report_type, 3 > monomer_reports_;
    array< dimer_report_type, 3 > dimer_reports_;

}; // end of template struct trait PolymerSubGroupReport<3>


template <> struct PolymerSubGroupReport<4> {
  public:
    typedef PolymerReport<1> monomer_report_type;
    typedef PolymerReport<2> dimer_report_type;
    typedef PolymerReport<3> trimer_report_type;

  public:
    const array< monomer_report_type, 4 >& monomer_reports() const 
     { return this->monomer_reports_; }
    const array< dimer_report_type, 6 >& dimer_reports() const 
     { return this->dimer_reports_; }
    const array< trimer_report_type, 4 >& trimer_reports() const 
     { return this->trimer_reports_; }

  protected:
    array< monomer_report_type, 4 > monomer_reports_;
    array< dimer_report_type, 6 > dimer_reports_;
    array< trimer_report_type, 4 > trimer_reports_;

}; // end of template struct trait PolymerSubGroupReport<3>

}  // end of namespace manybody_expansion

}  // end of namespace iquads

#endif
