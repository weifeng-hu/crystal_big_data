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

#ifndef ELECTRON_CORRELATION_REPORT_HPP
#define ELECTRON_CORRELATION_REPORT_HPP

#include <string>
#include <vector>
#include <tuple>
#include <structure/molecule.hpp>
#include <interface_to_third_party/external_program_report.hpp>

using std::string;

namespace iquads {

using structure :: Molecule;
using interface_to_third_party :: ExternalProgramReport;

namespace electron_correlation {

/**
 * This is a meta-data container for electron correlation data
 * It purely contains quantities and soluions, independent of any 
 * runtime choices
 *
 * A brief list can be
 *
 *  + Molecular info, including atom list, unit, charge, spin, etc.
 *    ( Raw data for a typical electron correlation calculation )
 *
 *  + Different correlated level energies, like
 *    Hartree-Fock, DFT, MP2, CCSD, CI, DMRG, CASSCF, etc.,
 *    Accompanied with the name of the correlation.
 * 
 * Other data members can be solution details, like
 *
 *  + MO coefficients
 *  + CI wavefunction
 *  + DMRG wavefunction
 *
 * A suggested way is to create subreports for each method, and fill results if
 * the calculation type was requested
 * 
 */

struct Report
{
public:
  typedef string molecule_name_type;
  typedef Molecule molecule_info_type;
  typedef ExternalProgramReport external_report_type;
  typedef double energy_data_type;

public:
  struct CorrelatedEnergyReport {
    public:
      typedef string correlation_name_type;
      typedef tuple< correlation_name_type, energy_data_type > correlated_energy_set_type;
      typedef vector< correlated_energy_set_type > correlated_energy_list_type;
    public:
      CorrelatedEnergyReport(){
        using std::make_tuple;
        correlated_energy_list_.push_back( make_tuple( "hf", 0.0e0 ) );
        correlated_energy_list_.push_back( make_tuple( "dft", 0.0e0 ) );
        correlated_energy_list_.push_back( make_tuple( "mp2", 0.0e0 ) );
        correlated_energy_list_.push_back( make_tuple( "ccsd", 0.0e0 ) );
        correlated_energy_list_.push_back( make_tuple( "ccsd(t)", 0.0e0 ) );
        correlated_energy_list_.push_back( make_tuple( "ccsdt", 0.0e0 ) );
        correlated_energy_list_.push_back( make_tuple( "ccsdt(q)", 0.0e0 ) );
        correlated_energy_list_.push_back( make_tuple( "casci", 0.0e0 ) );
        correlated_energy_list_.push_back( make_tuple( "casscf", 0.0e0 ) );
        correlated_energy_list_.push_back( make_tuple( "dmrg", 0.0e0 ) );
        correlated_energy_list_.push_back( make_tuple( "fci", 0.0e0 ) );
      }
    private:
      correlated_energy_list_type correlated_energy_list_;
  }; // end of sub struct CorrelatedEnergyReport

public:
  typedef CorrelatedEnergyReport correlated_energy_report_type;

public:
  void collect_data_from_external_report( external_report_type external_report );

public:
  const Report raw() const { return *this; }
  const molecule_info_type molecule_info() const 
   { return this->molecule_info_; }
  const energy_data_type energy() const 
   { return this->energy_; }

private:
  molecule_name_type molecule_name_;
  molecule_info_type molecule_info_;
  correlated_energy_report_type correlated_energy_report_;
  energy_data_type energy_;

}; // end of struct Report

} // end of namespace electron_correlation

} // end of namespace iquads

#endif
