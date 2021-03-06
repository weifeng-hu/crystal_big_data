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
#include <map>
#include <tuple>
#include <structure/molecule.hpp>
#include <electron_correlation/correlation_level.hpp>
#include <interface_to_third_party/external_program_report.hpp>

namespace iquads {

namespace electron_correlation {

/**
 *  This is a meta-data container for electron correlation data
 *  It purely contains quantities and soluions, independent of any 
 *  runtime choices. This is a struct since object intances are 
 *  not entities, there is no specific state to label an intance
 *  being at a valid state.
 *
 *  There is no standard way to constructor a energy report object
 *  Just some suggestions can be implemented.
 *  A brief list can be
 * 
 *   + Molecular info, including atom list, unit, charge, spin, etc.
 *     ( Raw data for a typical electron correlation calculation )
 * 
 *   + Different correlated level energies, like
 *     Hartree-Fock, DFT, MP2, CCSD, CI, DMRG, CASSCF, etc.,
 *     Accompanied with the name of the correlation.
 *  
 *  Other data members can be solution details, like
 * 
 *   + MO coefficients
 *   + CI wavefunction
 *   + DMRG wavefunction
 * 
 *  A suggested way is to create subreports for each method, and fill results if
 *  the calculation type was requested.
 *
 *  As a design point, this report serves as the "final" meta-data container.
 *  But for specific calculations which are run by the actual calculation agents,
 *  They can have specific runtime and result reports, which are different types 
 *  of objects from this one. A method in this class is responsible for convey 
 *  the data in those reports to this class, i.e., interface. And only this method 
 *  can change the data member in this class.
 * 
 */

using std :: string;
using std :: map;
using std :: tuple;
using std :: pair;
using std :: get;
using structure :: Molecule;
using interface_to_third_party :: ExternalProgramReport;

struct Report {
public:
  typedef Report                                            this_type;
  typedef string                                            molecule_name_type;
  typedef Molecule                                          molecule_obj_type;
  typedef molecule_obj_type :: atom_list_type               atom_list_type;
  typedef molecule_obj_type :: geometry_unit_type           geometry_unit_type;
  typedef tuple < molecule_name_type, molecule_obj_type >   molecule_info_type;
  typedef ExternalProgramReport                             external_report_type;
  typedef double                                            energy_data_type;
  typedef level_mask_type                                   correlation_level_type;

public:
  /**
   *  A sub-struct to store correlation energy information
   *  It stores a list of many kinds of energies, which can be 
   *  computed by actual correlated methods.
   */
  struct CorrelatedEnergyReport {
    public:
      typedef map< correlation_level_type, energy_data_type >   correlated_energy_list_type;
      typedef correlated_energy_list_type :: iterator           list_iterator_type;

    public:
    /**
     *  This list is pre-set as the instance initialized by this default constructor.
     *  We can add many other kinds of correlated energy types into this list.
     */
      CorrelatedEnergyReport() {
        using namespace electron_correlation :: single_reference :: mean_field;
        using namespace electron_correlation :: single_reference :: mollet_plesset;
        using namespace electron_correlation :: single_reference :: coupled_cluster;
        using namespace electron_correlation :: multi_reference :: ci;
        using namespace electron_correlation :: multi_reference :: scf;
        using namespace electron_correlation :: multi_reference :: dmrg;
        using namespace electron_correlation :: fci;
        using std :: make_pair;
        this->correlated_energy_list_.insert( pair< correlation_level_type, energy_data_type > ( RHF, 0.0e0 ) );
        this->correlated_energy_list_.insert( pair< correlation_level_type, energy_data_type > ( UHF, 0.0e0 ) );
        this->correlated_energy_list_.insert( pair< correlation_level_type, energy_data_type > ( DFT, 0.0e0 ) );
        this->correlated_energy_list_.insert( pair< correlation_level_type, energy_data_type > ( DF_RHF, 0.0e0 ) );
        this->correlated_energy_list_.insert( pair< correlation_level_type, energy_data_type > ( MP2, 0.0e0 ) );
        this->correlated_energy_list_.insert( pair< correlation_level_type, energy_data_type > ( DF_MP2, 0.0e0 ) );
        this->correlated_energy_list_.insert( pair< correlation_level_type, energy_data_type > ( DF_LMP2, 0.0e0 ) );
        this->correlated_energy_list_.insert( pair< correlation_level_type, energy_data_type > ( CCSD_T, 0.0e0 ) );
        this->correlated_energy_list_.insert( pair< correlation_level_type, energy_data_type > ( CCSDT, 0.0e0 ) );
        this->correlated_energy_list_.insert( pair< correlation_level_type, energy_data_type > ( CCSDT_Q, 0.0e0 ) );
        this->correlated_energy_list_.insert( pair< correlation_level_type, energy_data_type > ( LCCSD, 0.0e0 ) );
        this->correlated_energy_list_.insert( pair< correlation_level_type, energy_data_type > ( LCCSD_T, 0.0e0 ) );
        this->correlated_energy_list_.insert( pair< correlation_level_type, energy_data_type > ( LCCSDT, 0.0e0 ) );
        this->correlated_energy_list_.insert( pair< correlation_level_type, energy_data_type > ( CASCI, 0.0e0 ) );
        this->correlated_energy_list_.insert( pair< correlation_level_type, energy_data_type > ( CASSCF, 0.0e0 ) );
        this->correlated_energy_list_.insert( pair< correlation_level_type, energy_data_type > ( DMRG, 0.0e0 ) );
        this->correlated_energy_list_.insert( pair< correlation_level_type, energy_data_type > ( FCI, 0.0e0 ) );
      }

    public:
    /**
     *  Accessors and mutators
     *  Here we provide methods directly to the actual energy data
     */
    energy_data_type correlated_energy_of( correlation_level_type correlation_level ) {
      list_iterator_type list_iterator = this->correlated_energy_list_.find( correlation_level );
      return (*list_iterator).second;
    }

    energy_data_type& set_correlated_energy_of( correlation_level_type correlation_level ) {
      list_iterator_type list_iterator = this->correlated_energy_list_.find( correlation_level );
      
      return list_iterator->second;
    }

    energy_data_type lowest_energy() {
      energy_data_type retval = 0.0e0;
      for( list_iterator_type it = this->correlated_energy_list_.begin();
                              it != this->correlated_energy_list_.end(); ++it ) {
        if( retval > it->second ) {
          retval = it->second;
        }
      }
      return retval;
    }

    private:
      correlated_energy_list_type correlated_energy_list_;

  }; // end of sub struct CorrelatedEnergyReport

public:
  typedef CorrelatedEnergyReport correlated_energy_report_type;

public:
  /**
   *  Only this function can to manipulate data members in this struct
   */
  void collect_data_from_external_report( external_report_type external_report );

public:
  /**
   *  Accessors - no mutators since we don't allow changes of data once they are filled
   */
  this_type raw() const 
    { return *this; }
  external_report_type raw_external() const
    { return this->external_report_; }
  molecule_info_type molecule_info() const 
    { return this->molecule_info_; }
  energy_data_type energy() 
    { return this->correlated_energy_report_.lowest_energy(); }

  /**
   *  Auxiliary accessors 
   */
  molecule_name_type molecule_name() const 
    { return get<0>( this->molecule_info_ ); }
  molecule_obj_type molecule_obj() const 
    { return get<1>( this->molecule_info_ ); }
  atom_list_type atom_list() const 
    { return this->molecule_obj().atom_list(); }
  geometry_unit_type geometry_unit() const
    { return this->molecule_obj().geometry_unit(); }

private:
  external_report_type           external_report_;
  molecule_info_type             molecule_info_;
  correlated_energy_report_type  correlated_energy_report_;

}; // end of struct Report

} // end of namespace electron_correlation

} // end of namespace iquads

#endif
