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

#include <fstream>
#include <string>
#include <manybody_expansion/request.hpp>

namespace iquads {

namespace manybody_expansion {

typedef Request request_type;

void request_type :: read_input_file( file_name_type input_filename ) {

  using std::ifstream;
  ifstream ifs( input_filename.c_str(), std::ios::in );
  string entry;
  while( !ifs.eof() )
    {
      ifs >> entry;
      /**
       *  standard input keywords and procedures
       */
      if( entry == "lattice" ) // ifs >> this->lattice_info_;
      if( entry == "bulk" ) // ifs >> this->bulk_info_;
      if( entry == "basis" ) ifs >> this->basis_set_name_;
      if( entry == "correlation" ) ifs >> this->correlation_name_;
      if( entry == "order" ) ifs >> this->expansion_order_;
      if( entry == "run" ) ifs >> this->run_mode_name_;
      if( entry == "external_program" ) ifs >> this->external_program_name_;
      if( entry == "scratch" ) ifs >> this->scratch_name_;
      if( entry == "job" || entry == "jobname" ) ifs >> this->job_name_;

      /**
       *  keyword shortcuts - basis set name
       */
      if( entry == "sto-3g" ) this->basis_set_name_ = "sto-3g";
      if( entry == "6-31g" ) this->basis_set_name_ = "6-31g";
      if( entry == "cc-pvdz" ) this->basis_set_name_ = "6-31g";

      /**
       *  keyword shortcuts - correlation 
       */
      if( entry == "hf" || entry == "rhf" ) this->correlation_name_ = "rhf";
      if( entry == "mp2" ) this->correlation_name_ = "mp2";
      if( entry == "fci" ) this->correlation_name_ = "fci";
      if( entry == "dmrg" ) this->correlation_name_ = "dmrgci";
      if( entry == "ccsd" ) this->correlation_name_ = "ccsd";
      if( entry == "ccsd(t)" ) this->correlation_name_ = "ccsd(t)";
      if( entry == "ccsdt" ) this->correlation_name_ = "ccsdt";
      if( entry == "casscf" ) this->correlation_name_ = "casscf";

      /**
       *  keyword shortcuts - run mode
       */
      if( entry == "local" ) this->run_mode_name_ = "local";
      if( entry == "pbs" ) this->run_mode_name_ = "pbs";
      if( entry == "sbatch" ) this->run_mode_name_ = "sbatch";
      if( entry == "harvest" || entry == "collect" ) this->run_mode_name_ = "harvest";
      if( entry == "dryrun" ) this->run_mode_name_ = "dryrun";

      /**
       *  keyword shortcuts - external program
       */
      if( entry == "molpro" ) this->external_program_name_ = "molpro";
      if( entry == "orca" ) this->external_program_name_ = "orca";
      if( entry == "self" || entry == "iquads" ) this->external_program_name_ = "self";
    }
  ifs.close();

}; // end of read_input_file()

} // end of namespace manybody_expansion

} // end of namespace iquads
