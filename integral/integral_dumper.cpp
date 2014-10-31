#include "integral/electron_integral_class.h"
#include <iostream>
#include <fstream>

using namespace std;

namespace iquads {

namespace integral{

void integral_dump( te_int& v2, oe_int& v1, const string filename )
{

  {
   const int norb1 = v1.get_norb();
   const int norb2 = v2.get_norb();
   if( norb1 != norb2 ){
    cout << " error: norb of one- and two-electron integrals are different " << endl;
    abort();
   }
  }

  {
   ofstream f_fcidump;
   f_fcidump.open( filename.c_str(), std::ios::out );
   {
    const int norb = v1.get_norb();
    ofstream << " &FCI  NORB= " << norb << " NELEC= 0, MS2= 0" << endl;
    ofstream << "  ORBSYM= "; for( int i = 0; i < norb; i++ ){ ofstream << "1,"; }; ofstream << endl;
    ofstream << "  ISYM=1" << endl;
    ofstream << "  /" << endl;
    ofstream.precision(16);
    for( int i = 0; i < norb; i++ ){
     for( int j = 0; j < norb; j++ ){
      for( int k = 0; k < norb; k++ ){
       for( int l = 0; l < norb; l++ ){
         ofstream << v2(l, k, j, i) << "\t" << l+1 << " " << k+1 << " " << j+1 << " " << i+1 << endl;
       }
      }
     }
    }
    for( int i = 0; i < norb; i++ ){
     for( int j = 0; j < norb; j++ ){
       ofstream << v1(j, i) << "\t" << j+1 << " " << i+1 << " 0 0" << endl;
     }
    }
    ofstream << core_energy << endl;
   }
   f_fcidump.close();
  }

}

} // end of integral

} // end of iquads
