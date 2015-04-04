#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <boost/algorithm/string.hpp>
#include "utilities/num_nac/numnac_info.h"

using namespace std;

void numerical_nac_driver( vector<string> args )
{

  string molecule = args[1];
  double disp_b = atof( argv[2] );
  double disp = atof( argv[2] ) * R_bohr;

  cout << "molecule: " << molecule << endl;
  cout << " displacement: in bohr " << disp_b << "   in angs " << disp << endl;

  iquads::num_nac::numnac_calc nac_calculation;
  {
   string f_coord = molecule + ".coord";
   nac_calculation.read( f_coord );
  }

  if( restart == false ){
   nac_calculation.compute_reference();
   nac_calculation.compute_displacement();
  }
  nac_calculation.calc_numnac();

}
