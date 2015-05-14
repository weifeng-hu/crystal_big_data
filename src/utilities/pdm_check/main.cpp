#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <cmath>

using namespace std;

void onepdm_check( int norb )
{

  vector<double> value;
  {
   string orca_tpdm_file = "orca.onepdm";
   ifstream ifs;
   ifs.open( orca_tpdm_file.c_str(), std::ios::in );
   for( int i = 0; i < norb*norb; i++ ){
    int p1, p2;
    double val;
    ifs >> p1 >> p2 >> val; 
    value.push_back( val );
   }
   ifs.close();
  }

  cout.precision(10);
  {
   string dmrg_tpdm_file = "spatial_onepdm.0.1";
   ifstream ifs;
   ifs.open( dmrg_tpdm_file.c_str(), std::ios::in );
   vector<double> dmrg_value;
   cout << "results:" << endl;
   while( ifs.good() ){
    int p1, p2;
    double val;
    ifs >> p1 >> p2 >> val; // 1 2 3 4
    int index = p1 * norb + p2;
    double val_ref = value.at(index);
    if( fabs( val - val_ref ) > 2.0e-5  ){
     cout << " dmrg pdm: " << p1 << " " << p2 << " " << val << " != ref " << val_ref << endl;
    }
   }
   ifs.close();
   cout << "end" << endl;
  }

}

void twopdm_check( int norb )
{

  vector<double> value;
  {
   string orca_tpdm_file = "orca.twopdm";
   ifstream ifs;
   ifs.open( orca_tpdm_file.c_str(), std::ios::in );
   for( int i = 0; i < norb*norb*norb*norb; i++ ){
    int p1, p2, p3, p4;
    double val;
    ifs >> p1 >> p2 >> p3 >> p4 >> val; // 1 4 2 3
    value.push_back( val );
   }
   ifs.close();
  }

  cout.precision(10);
  {
   string dmrg_tpdm_file = "spatial_twopdm.0.1";
   ifstream ifs;
   ifs.open( dmrg_tpdm_file.c_str(), std::ios::in );
   vector<double> dmrg_value;
   cout << "results:" << endl;
   while( ifs.good() ){
    int p1, p2, p3, p4;
    double val;
    ifs >> p1 >> p2 >> p3 >> p4 >> val; // 1 2 3 4
    int index = p1 * norb * norb * norb + p4 * norb * norb + p2 * norb + p3;
    double val_ref = value.at(index);
    if( fabs( val - val_ref ) > 2.0e-5  ){
     if( fabs( -val - val_ref ) < 2.0e-5 ) {
      cout << " dmrg pdm: " << p1 << " " << p2 << " " << p3 << " " << p4 << " " << val << " != ref " << val_ref << "\t sign "<< endl;
     }
     else{
      cout << " dmrg pdm: " << p1 << " " << p2 << " " << p3 << " " << p4 << " " << val << " != ref " << val_ref << "\t operator" << endl;
     }
    }
   }
   cout << "end" << endl;
   ifs.close();
  }

}

int main( int argc, char* argv[] )
{

   int norb = atoi(argv[1]);
   onepdm_check( norb );
//   twopdm_check( norb );

}
