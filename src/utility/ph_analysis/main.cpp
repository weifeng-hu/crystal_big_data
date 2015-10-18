// Program to transform MO space transition pdms to real space
// 
// real space can be AO or localized MO
// here we do localized MO
//
// Required files:
//  U matrix from canonical to localized orbitals
//  (transition) one pdm file
//  (transition) two pdm file
//  
// Possibly required files:
//  S matrix of AO
//  C matrix of canonical orbitals
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "transform_info.h"
#include "ph_analysis.h"

using namespace std;

int main( int argc, char* argv[] )
{

  if( argc != 2 ){ 
   cout << " wrong number of arguments " << endl; 
   cout << " usage: ph_trans <input file> " << endl;
   exit(1); 
  }

  string input_file = argv[1];
  ph_analysis::transform_info trans_info( input_file );

  ph_analysis::transform_main( trans_info );

  return 0;

}
