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

#include <string>
#include <fstream>
#include <interface_to_third_party/external_program_bitmask.h>
#include <manybody_expansion/config.h>

using std::string;

namespace iquads {

namespace manybody_expansion {

typedef Config config_type;

/*
void config_type :: read_config( config_type :: file_name_type input_filename )
{

  using std::ifstream;
  ifstream ifs( input_filename.c_str() );
  while( ifs.eof() == false )
  {
   string entry;
   ifs >> entry;
   if( entry == "correlation_method" ){
    string method;
    ifs >> method;
    if( method == "hf" ){
     this->electron_correlation_config_.enable_hf();
    }
    else if( method == "mp2" ){
     this->electron_correlation_config_.enable_mp2();
    }
    else if( method == "ccsd" ){
     this->electron_correlation_config_.enable_ccsd();
    }
    else if( method == "ccsdt" ){
     this->electron_correlation_config_.enable_ccsdt();
    }
    else if( method == "dmrg" ){
     this->electron_correlation_config_.enable_dmrg();
    }
   }
   else if( entry == "periodic" ){
    this->is_periodic_ = true;
   }
   else if( entry == "cell_size" ){

   }
   else if( entry == "dryrun" ){
    this->to_set_up_only_ = true;
   }
   else if( entry == "external_program" ){
    ifs >> this->external_program_name_;
    using interface_to_third_party :: retrieve_external_program_mask;
    this->external_program_mask_ 
      = retrieve_external_program_mask( this->external_program_name_ );
   }
  }
  ifs.close();

}; // end of read_config()
*/

} // end of manybody_expansion

} // end of namespace iquads
