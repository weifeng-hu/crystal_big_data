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

#ifndef ELECTRON_CORRELATION_LEVEL_HPP
#define ELECTRON_CORRELATION_LEVEL_HPP

#include <string>

namespace iquads {

  namespace electron_correlation {

  /**
   *
   *  Correlation level/method
   *
   *    + single reference
   *      + mean field
   *        + HF
   *        + DFT
   *      + mollet plesset
   *        + mp2
   *        + mp3
   *        + mp4
   *      + ci
   *        + cis
   *        + cisd
   *      + coupled cluster
   *        + ccsd
   *        + ccsd(t)
   *        + ccsdt
   *        + ccsdt(q)
   *        + ccsdtq
   *
   *    + multi reference
   *      + ci
   *        + mrci
   *        + casci
   *      + mcscf
   *        + casscf
   *      + couple cluster
   *        + mrcc-sd
   *        + mrcc-sdt
   *      + dmrg
   *        + dmrgci
   *        + dmrgscf
   *
   *    + fci
   *
   *    + About correlation level mask
   *      0000 0000 0000 00000000 00000000 0000
   *                   ^        ^        ^    ^
   *                   |        |        |    |
   *                   |        |        |    single/multi/fci
   *                   |        |        mean field ... coupled claster
   *                   |        RHF...DFT
   *                   To be assigned
   */

    typedef unsigned long int level_mask_type;
    typedef string correlation_name_type;

    namespace single_reference {

      constexpr level_mask_type SINGLE_REFERENCE = 0x01 << 0; 

      namespace mean_field {
        constexpr level_mask_type MEAN_FIELD = 0x01 << 4;

        constexpr level_mask_type RHF = SINGLE_REFERENCE | MEAN_FIELD | ( 0x01 << 12 );
        constexpr level_mask_type UHF = SINGLE_REFERENCE | MEAN_FIELD | ( 0x01 << 13 );
        constexpr level_mask_type DFT = SINGLE_REFERENCE | MEAN_FIELD | ( 0x01 << 14 );
      } // end of namespace single_reference :: mean_field 

      namespace mollet_plesset {
        constexpr level_mask_type MOLLET_PLESSET = 0x01 << 5;
  
        constexpr level_mask_type MP2 = SINGLE_REFERENCE | MOLLET_PLESSET | ( 0x01 << 12 );
        constexpr level_mask_type MP3 = SINGLE_REFERENCE | MOLLET_PLESSET | ( 0x01 << 13 );
        constexpr level_mask_type MP4 = SINGLE_REFERENCE | MOLLET_PLESSET | ( 0x01 << 14 );
      } // end of namespace single_reference :: mollet_plesset
  
      namespace ci {
        constexpr level_mask_type CI = 0x01 << 6;
  
        constexpr level_mask_type CIS   = SINGLE_REFERENCE | CI | ( 0x01 << 12 );
        constexpr level_mask_type CISD  = SINGLE_REFERENCE | CI | ( 0x01 << 13 );
        constexpr level_mask_type CISDT = SINGLE_REFERENCE | CI | ( 0x01 << 14 );
        constexpr level_mask_type CISDTQ = SINGLE_REFERENCE | CI | ( 0x01 << 15 );
      } // end of namespace single_reference :: ci
  
      namespace coupled_cluster {
        constexpr level_mask_type CC = 0x01 << 7;
  
        constexpr level_mask_type CCSD    = SINGLE_REFERENCE | CC | ( 0x01 << 12 );
        constexpr level_mask_type CCSD_T  = SINGLE_REFERENCE | CC | ( 0x01 << 13 );
        constexpr level_mask_type CCSDT   = SINGLE_REFERENCE | CC | ( 0x01 << 14 );
        constexpr level_mask_type CCSDT_Q = SINGLE_REFERENCE | CC | ( 0x01 << 15 );
        constexpr level_mask_type CCSDTQ  = SINGLE_REFERENCE | CC | ( 0x01 << 16 );
      } // end of namespace single_reference :: coupled_cluster
  
    }
  
    namespace multi_reference {
  
      constexpr level_mask_type MULTI_REFERENCE = 0x01 << 1; 
  
      namespace ci {
        constexpr level_mask_type CI = 0x01 << 4;
  
        constexpr level_mask_type CASCI = MULTI_REFERENCE | CI | ( 0x01 << 12 );
        constexpr level_mask_type MRCI  = MULTI_REFERENCE | CI | ( 0x01 << 13 );
      } // end of namespace multi_reference :: ci
  
      namespace scf { // 
        constexpr level_mask_type SCF = 0x01 << 5;

        constexpr level_mask_type CASSCF = MULTI_REFERENCE | SCF | ( 0x01 << 12 );
      } // end of namespace multi_reference :: scf
  
      namespace coupled_cluster {
        constexpr level_mask_type CC = 0x01 << 6;

        constexpr level_mask_type MRCC_SD  = MULTI_REFERENCE | CC | ( 0x01 << 12 );
        constexpr level_mask_type MRCC_SDT = MULTI_REFERENCE | CC | ( 0x01 << 13 );
      } // end of namespace multi_reference :: coupled_cluster
  
      namespace dmrg {
        constexpr level_mask_type DMRG = 0x01 << 7;

        constexpr level_mask_type DMRG_CI  = MULTI_REFERENCE | DMRG | ( 0x01 << 12 );
        constexpr level_mask_type DMRG_SCF = MULTI_REFERENCE | DMRG | ( 0x01 << 13 );
      } // end of namespace multi_reference :: dmrg
  
    } // end of namespace multi_reference

    namespace fci {

      constexpr level_mask_type FCI = 0x01 << 2;

    } // end of namespace fci

    const inline level_mask_type return_level_mask( correlation_name_type correlation_name ) {

      if( correlation_name == "hf" || correlation_name == "rhf" ) return single_reference :: mean_field :: RHF;
      if( correlation_name == "uhf" ) return single_reference :: mean_field :: UHF;
      if( correlation_name == "dft" ) return single_reference :: mean_field :: DFT;

      if( correlation_name == "mp2" ) return single_reference :: mollet_plesset :: MP2;
      if( correlation_name == "mp3" ) return single_reference :: mollet_plesset :: MP3;
      if( correlation_name == "mp4" ) return single_reference :: mollet_plesset :: MP4;

      if( correlation_name == "cis"    ) return single_reference :: ci :: CIS;
      if( correlation_name == "cisd"   ) return single_reference :: ci :: CISD;
      if( correlation_name == "cisdt"  ) return single_reference :: ci :: CISDT;
      if( correlation_name == "cisdtq" ) return single_reference :: ci :: CISDTQ;

      if( correlation_name == "ccsd"     ) return single_reference :: coupled_cluster :: CCSD;
      if( correlation_name == "ccsd(t)"  ) return single_reference :: coupled_cluster :: CCSD_T;
      if( correlation_name == "ccsdt"    ) return single_reference :: coupled_cluster :: CCSDT;
      if( correlation_name == "ccsdt(q)" ) return single_reference :: coupled_cluster :: CCSDT_Q;
      if( correlation_name == "ccsdtq"   ) return single_reference :: coupled_cluster :: CCSDTQ;

      if( correlation_name == "casci"   ) return multi_reference :: ci :: CASCI;
      if( correlation_name == "mrci"    ) return multi_reference :: ci :: MRCI;

      if( correlation_name == "casscf"  ) return multi_reference :: scf :: CASSCF;

      if( correlation_name == "mrccsd"  ) return multi_reference :: coupled_cluster :: MRCC_SD;
      if( correlation_name == "mrccsdt" ) return multi_reference :: coupled_cluster :: MRCC_SDT;

      if( correlation_name == "dmrgci"  ) return multi_reference :: dmrg :: DMRG_CI;
      if( correlation_name == "dmrgscf" ) return multi_reference :: dmrg :: DMRG_SCF;

      if( correlation_name == "fci" ) return fci :: FCI;

    }

  } // end of namespace electron_correlation

} // end of namespace iquads

#endif
