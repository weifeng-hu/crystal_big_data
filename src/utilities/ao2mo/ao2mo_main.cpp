#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include "matrix/general_matrix.h"
#include "matrix/mo_coeff.h"
#include "matrix/one_electron_integral.h"
#include "matrix/two_electron_integral.h"
#include "utilities/ao2mo/ao2mo_config.h"
#include "matrix/fc_fortran.h"

using namespace std;

int main( int argc, char* argv[] )
{

  string input = argv[1];
  iqs::utilities::ao2mo_config config( input );

  int nbas = config.nbas;
  int norb = config.norb;
  int nocc = config.nocc;
  vector<int> orb_win = config.orbital_window;

  iqs::matrix::mo_coeff c_mtr( nbas, norb );
  c_mtr.read_r( config.c_file );

  iqs::matrix::two_electron_integral v2_ao( nbas );
  v2_ao.read_r( config.two_integral_file );

  iqs::matrix::two_electron_integral v2_mo( norb );
  cout << nbas << " " << norb << endl;
  iqs::matrix::tei_transform_( &nbas, &norb, c_mtr.get_data().get_data().data(), v2_ao.get_data().get_data().data(), v2_mo.get_data().get_data().data() );
//  v2_ao.~two_electron_integral();

  iqs::matrix::one_electron_integral v1_ao( nbas );
  v1_ao.read_r( config.one_integral_file );

  iqs::matrix::one_electron_integral v1_mo( norb );
  iqs::matrix::oei_transform_( &nbas, &norb, c_mtr.get_data().get_data().data(), v1_ao.get_data().get_data().data(), v1_mo.get_data().get_data().data() );
  for( int i = 0; i < norb; ++i ){
//   cout << v1_mo(i,i) << endl;
  }
//  exit(0);

  // calculate the fock matrix
  iqs::matrix::general_matrix fock_mo( norb, norb );
  for( int i = 0; i < norb; i++ ){
   for( int j = 0; j < norb; j++ ){
    fock_mo( i, j ) += v1_mo( i, j );
    for( int k = 0; k < nocc; k++ ){
     fock_mo( i, j ) += 2.0e0 * v2_mo( i, j, k, k ) - v2_mo( i, k, j, k );
    }
   }
  }
  vector<double> eigval; eigval.resize(norb);
  vector<double> eigvec = fock_mo.get_matrix();
  iqs::matrix::eigtql2_( &norb, (eigvec.data()), (eigval.data()) );

  cout.precision(16);
  for( int i = 0; i < norb; ++i ){
    cout << eigval.at(i) << endl;
  }
  
//  exit(0);
  // modifiy the one-electron integral
  int ncore = orb_win.at(2) - orb_win.at(0);
  int nact = orb_win.at(3) - orb_win.at(1);
  cout << orb_win.at(0) << " " << orb_win.at(1) << " " << orb_win.at(2) << " " << orb_win.at(3) << " " << orb_win.at(4) << " " << orb_win.at(5) << endl;
  cout << ncore << " " << nact << endl;

  // calculate the core energy
  cout.precision(16);
  double core_energy = config.nucl_rep;
  cout << " nucl_rep = " << core_energy << endl;
  for( int i = 0; i < ncore; ++i ){
    core_energy += 2.0e0 * v1_mo( i, i ); 
   for( int j = 0; j < ncore; ++j ){
     core_energy += 2.0e0 * v2_mo( i, i, j, j ) - v2_mo( i, j, i, j );
   }
  }

  iqs::matrix::one_electron_integral v1_cas( nact );
  for( int i = 0; i < nact; ++i ){
   for( int j = 0; j < nact; ++j ){
      v1_cas( i, j ) = v1_mo( ncore + i, ncore + j );
    for( int k = 0; k < ncore; ++k ){
      v1_cas( i, j ) = v1_cas( i, j ) + 2.0e0 * v2_mo( ncore + i, ncore + j, k, k ) - v2_mo( ncore + i , k , k , ncore + j );
    }
   }
  }

//  exit(0);
  int nele = config.nele;
  int ns   = config.ns;
  FILE* dump = fopen("qcdmrg.FCIDUMP", "wt" );
  fprintf( dump, " &FCI  NORB= %i NELEC= %i, MS2= %i,\n", nact, nele, ns );
  fprintf( dump, "  ORBSYM=" ); for( int i = 0; i < nact-1; ++i ){ fprintf( dump, "1,"); } fprintf( dump, "1\n" );
  fprintf( dump, "  ISYM=1\n" );
  fprintf( dump, " /\n" );


  double val;
  for( int i = 0; i < nact; ++i ){
   for( int j = 0; j < nact; ++j ){
    for( int k = 0; k < nact; ++k ){
     for( int l = 0; l < nact; ++l ){
       val = v2_mo( ncore + i, ncore + j , ncore + k, ncore + l );
       if(  i >= j && k >= l ){
//         if( fabs(val) >= 1.0e-16 )
         fprintf( dump, " %25.16e %i %i %i %i\n", val, i+1, j+1, k+1, l+1 );
       }
     }
    }
   }
  }
//  v2_mo.~two_electron_integral();

  for( int i = 0; i < nact; ++i ){
   for( int j = 0; j < nact; ++j ){
     val = v1_cas( i, j );
     if( i >= j ){
//      if( fabs(val) >= 1.0e-16 ){
       fprintf( dump, " %25.16e %i %i 0 0\n", val, i+1, j+1 );
//      }
     }
   }
  }
  fprintf( dump, " %25.16e 0 0 0 0\n", core_energy );
  fclose(dump);

}
