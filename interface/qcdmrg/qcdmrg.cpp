#include <iostream>
#include <string>
#include "interface/qcdmrg/qcdmrg.h"

using namespace std;

namespace ithaca { namespace interface {

//int qcdmrg( TOrcaInfo DAT, DCASSCFINP DCAS)
int run_dmrg( ithaca::interface::qcdmrg dmrg_data )
{

// use directly running DMRG from command line
  dmrg_input( dmrg_data );

// set command line for running dmrg
  {
   std::string cmd;
   cmd = dmrg_data.exec_path + " " + dmrg_data.conf;
   char* _cmd = (char*) cmd.c_str();
   system(cmd);
  }

// set command line for running genblock
  {
   std::string cmd;
   cmd = dmrg_data.exec_path + "  " + dmrg_data.conf_genblock;
   char* _cmd = (char*) cmd.c_str();
   system(cmd);
  }

// set command line for running pdms
  {
   std::string cmd;
   cmd = dmrg_data.exec_path + "  " + dmrg_data.conf_onepdm;
   char* _cmd = (char*) cmd.c_str();
   system(cmd);
  }

  {
   std::string cmd;
   cmd = dmrg_data.exec_path + "  " + dmrg_data.conf_twopdm;
   char* _cmd = (char*) cmd.c_str();
   system(cmd);
  }


/*
  nmult = ;
  DMRG = new TDMRG[nmult];

  char* xsym = ;
  char* xBaseName = DAT.BaseName;
  int xNEL = DCAS.NEL;
  int xNORB = DCAS.NORB;

  char* xUserConfigName = ConfigFile;
  double xSweepTol = SweepTol;  
  for( int imult = 0; imult < NMULT; imult++ ){

// Initialize DMRG module
    int xMULT = DCAS.MULT[imult];
    int xNROOTS = DCAS.NROOTS[imult];
    int xIRREP  = DCAS.IRREP[imult];
    res = DMRG[imult].Initialze( DAT, xsymm, xBaseName, xNEL, xNORB, xMULT, xNROOTS, xIRREP, xUserConfigName, xSweepTol );
// Set Integral files
    double xE0 = E0;
    TRMatrixSym xH = &FACT;
    TRMatrixSym xG = &DPQRS;
    TIMatrixSym xIPQRS = &IPQRS;
    int* xOrbIRREP = &( IRREP[0][DCAS.MORANGES[2]] );
    DMRG[imult].SetIntegrals( xE0, xH, xG, xIPQRS, xOrbIRREP );
// Run DMRG
    DMRG[imult].Solve();
// Calculate RDMs
    TRVector W = WEIGHTS;
    TRMatrixSym G1;
    TRMatrix G2;
    TRMatrix D1;
    TRMatrix D2; 
    DMRG[imult].CalcDens( W, D1, D2);
    for( int i = 0; i < G1.row; i++ ){
     for( int j = 0; j <= i; j++ ){
      G1(i,j) = 0.5e0 * ( TEMP_G1(i,j) + TEMP_G1(j,i) );
     }
    }
    BLAS_Mat_p_Mat( G2, G2, 1.0, TEMP_G2);
// put RDMs into qcdmrg class

  }
*/

};

} }
