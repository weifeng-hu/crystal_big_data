#include <vector>
#include <string>
#include "utilities/num_nac/vec_math.h"
#include "utilities/num_nac/atom.h"
#include "utilities/num_nac/numnac_calc_class.h"

namespace iquads {

namespace num_nac {

void numnac_calc :: read( string filename )
{

   ifstream ifs;
   ifs.open( filename.c_str(), std::ios::in );
   ifs >> nelec >> norb >> sz >> s_square; 
   ifs >> natom;
   molecule.resize( natom );
   for( size_t iatom = 0; iatom < natom; iatom++ ){
    ifs >> molecule.at(i).set_element();
    ifs >> molecule.at(i).set_x(); 
    ifs >> molecule.at(i).set_y();
    ifs >> molecule.at(i).set_z();
   }
   ifs.close();

   cout << " coordinate file " << filename << endl;
   cout << "  natom = " << natom << endl;
   cout << "  targeted state: " << endl;
   cout << "   nelc = " << nel << " norb = " << norb << " sz = " << sz << " s_square = " << s_square << endl;

   this->eng_disp.resize( natom );
   for( size_t iatom = 0; iatom < natom; iatom++ ){
    this->eng_disp.at(iatom).resize(3);
   }

}

void numnac_calc :: compute_reference()
{

   cout << " reference: " << endl;
   string dir = "./ref/";
   eng_ref = compute_wave( atoms, coord, molecule, dir, nel, norb, sz, 1 );

}

void numnac_calc :: compute_displacement()
{

  // displacements
   for( size_t iatom = 0; iatom < natom; iatom++ ){
    for( size_t icop = 0; icop < 3; icop++ ){
     cout << " displacement " << iatom << "." << icop << ":" << endl;
     vector< vector<double> > new_coord;
     char line[100];
     string dir;
     string ref_wav;
     string command;
     // plus
      new_coord = coord;
      new_coord.at(iatom).at(icop) = new_coord.at(iatom).at(icop) + disp;
      sprintf( line, "./%i.%i.p/", iatom, icop );
      dir = line;
      eng_disp.at(iatom).at(icop).push_back( compute_wave( atoms, new_coord, molecule, dir, nel, norb, sz, 1 ) );
     
     // minus
      new_coord = coord;
      new_coord.at(iatom).at(icop) = new_coord.at(iatom).at(icop) - disp;
      sprintf( line, "./%i.%i.m/", iatom, icop );
      dir = line;
      eng_disp.at(iatom).at(icop).push_back( compute_wave( atoms, new_coord, molecule, dir, nel, norb, sz, 1 ) );
    }
   }

}

void numnac_calc :: calc_numnac()
{

  for( size_t iatom = 0; iatom < natom; iatom++ ){
   for( size_t icop = 0; icop < 3; icop++ ){

/*
    if( fabs( eng_ref.at(0) - eng_disp.at(iatom).at(icop).at(0).at(0) ) > 1.0e-3 
      ||fabs( eng_ref.at(0) - eng_disp.at(iatom).at(icop).at(0).at(1) ) > 1.0e-3 ){
     cout << " displaced energy is wrong; skipping " << endl;
     continue;
    }
    if( fabs( eng_ref.at(1) - eng_disp.at(iatom).at(icop).at(1).at(0) ) > 1.0e-3 
      ||fabs( eng_ref.at(1) - eng_disp.at(iatom).at(icop).at(1).at(1) ) > 1.0e-3 ){
     cout << " displaced energy is wrong; skipping "  << endl;
     continue;
    }
*/
    cout << iatom << "." << icop << ":" << endl;
    const int len = pow(4, norb );

    string dir_ref = "./ref/";
    char line[100];
    sprintf( line, "./%i.%i.p/", iatom, icop );
    string dir_p = line;
    sprintf( line, "./%i.%i.m/", iatom, icop );
    string dir_m = line;

    // <d psi_1/da | psi_2 > -- read 
    vector<double> wave_1_p = read_wave( dir_p, len, 1 );
    vector<double> wave_1_m = read_wave( dir_m, len, 1 );
    vector<double> wave_2   = read_wave( dir_ref, len, 2 );
    
    // < psi_1 | d psi_2/da > -- read
    vector<double> wave_2_p = read_wave( dir_p, len, 2 );
    vector<double> wave_2_m = read_wave( dir_m, len, 2 );
    vector<double> wave_1   = read_wave( dir_ref, len, 1 );

    // some sanity check
    double ov_r = product( wave_1, wave_2 );
    double ov_p = product( wave_1_p, wave_2_p );
    double ov_m = product( wave_1_m, wave_2_m );
    double ov_rp_1 = product( wave_1, wave_1_p );
    double ov_rm_1 = product( wave_1, wave_1_m );
    double ov_pm_1 = product( wave_1_p, wave_1_m );
    double ov_rp_2 = product( wave_2, wave_2_p );
    double ov_rm_2 = product( wave_2, wave_2_m );
    double ov_pm_2 = product( wave_2_p, wave_2_m );

    double ov_r1_p2 = product( wave_1, wave_2_p );
    double ov_r1_m2 = product( wave_1, wave_2_m );
    double ov_p1_m2 = product( wave_1_p, wave_2_m );
    double ov_m1_p2 = product( wave_1_m, wave_2_p );

    double ov_r2_p1 = product( wave_2, wave_1_p );
    double ov_r2_m1 = product( wave_2, wave_1_m );
    double ov_p2_m1 = product( wave_2_p, wave_1_m );
    double ov_m2_p1 = product( wave_2_m, wave_1_p );

    if( verbose == true ){
     cout.precision(8);
     cout << "  < 1 | 2 > = " << ov_r << "\t" << " < 1+ | 2+ > = " << ov_m << "\t" << " < 1- | 1- > = " << ov_p << endl;
     cout << "  < 1 | 1+ > = " << ov_rp_1 << "\t" << " < 1 | 1- > = " << ov_rm_1 << "\t" << " < 1+ | 1- > = " << ov_pm_1 << endl;
     cout << "  < 2 | 2+ > = " << ov_rp_2 << "\t" << " < 2 | 2- > = " << ov_rm_2 << "\t" << " < 2+ | 2- > = " << ov_pm_2 << endl;
     cout << "  < 1 | 2+ > = " << ov_r1_p2 << "\t" << " < 1 | 2- > = " << ov_r1_m2 << "\t" << " < 1+ | 2- > = " << ov_p1_m2 << "\t" << " < 1- | 2+ > = " << ov_m1_p2 << endl;
     cout << "  < 2 | 1+ > = " << ov_r2_p1 << "\t" << " < 2 | 1- > = " << ov_r2_m1 << "\t" << " < 2+ | 1- > = " << ov_p2_m1 << "\t" << " < 2- | 1+ > = " << ov_m2_p1 << endl;
    }

    if( fabs( ov_rp_1 ) < 0.5e0 || fabs( ov_rm_1 ) < 0.5e0 || fabs( ov_pm_1 ) < 0.5e0 ){
     cout << "  detect substantial wavefunction change for this disp; trying to switch roots " << endl;
     if( fabs( ov_r1_p2 ) > 0.5e0 ){
      if( verbose == true ) cout << "   switching | 1+ > with | 2+ > " << endl;
      vector<double> wave_tmp = wave_2_p;
      wave_2_p = wave_1_p;
      wave_1_p = wave_tmp;
     }
     if( fabs( ov_r1_m2 ) > 0.5e0 ){
      if( verbose == true ) cout << "   switching | 1- > with | 2- > " << endl;
      vector<double> wave_tmp = wave_2_m;
      wave_2_m = wave_1_m;
      wave_1_m = wave_tmp;
     }
//     continue;
     if( verbose == true ) cout << "  recheck overlaps " << endl;
     ov_r = product( wave_1, wave_2 );
     ov_p = product( wave_1_p, wave_2_p );
     ov_m = product( wave_1_m, wave_2_m );
     ov_rp_1 = product( wave_1, wave_1_p );
     ov_rm_1 = product( wave_1, wave_1_m );
     ov_pm_1 = product( wave_1_p, wave_1_m );
     ov_rp_2 = product( wave_2, wave_2_p );
     ov_rm_2 = product( wave_2, wave_2_m );
     ov_pm_2 = product( wave_2_p, wave_2_m );
 
     ov_r1_p2 = product( wave_1, wave_2_p );
     ov_r1_m2 = product( wave_1, wave_2_m );
     ov_p1_m2 = product( wave_1_p, wave_2_m );
     ov_m1_p2 = product( wave_1_m, wave_2_p );
  
     ov_r2_p1 = product( wave_2, wave_1_p );
     ov_r2_m1 = product( wave_2, wave_1_m );
     ov_p2_m1 = product( wave_2_p, wave_1_m );
     ov_m2_p1 = product( wave_2_m, wave_1_p );

     if( verbose == true ){
      cout.precision(8);
      cout << "  < 1 | 2 > = " << ov_r << "\t" << " < 1+ | 2+ > = " << ov_m << "\t" << " < 1- | 1- > = " << ov_p << endl;
      cout << "  < 1 | 1+ > = " << ov_rp_1 << "\t" << " < 1 | 1- > = " << ov_rm_1 << "\t" << " < 1+ | 1- > = " << ov_pm_1 << endl;
      cout << "  < 2 | 2+ > = " << ov_rp_2 << "\t" << " < 2 | 2- > = " << ov_rm_2 << "\t" << " < 2+ | 2- > = " << ov_pm_2 << endl;
      cout << "  < 1 | 2+ > = " << ov_r1_p2 << "\t" << " < 1 | 2- > = " << ov_r1_m2 << "\t" << " < 1+ | 2- > = " << ov_p1_m2 << "\t" << " < 1- | 2+ > = " << ov_m1_p2 << endl;
      cout << "  < 2 | 1+ > = " << ov_r2_p1 << "\t" << " < 2 | 1- > = " << ov_r2_m1 << "\t" << " < 2+ | 1- > = " << ov_p2_m1 << "\t" << " < 2- | 1+ > = " << ov_m2_p1 << endl;
     }
    }

    if( fabs( ov_rp_2 ) < 0.5e0 || fabs( ov_rm_2 ) < 0.5e0 || fabs( ov_pm_2 ) < 0.5e0 ){
     cout << "  still detect substantial wavefunction change for this disp; skipping " << endl;
     continue;
    }

    if( ov_rp_1 < 0.0e0 ){ scale( wave_1_p, -1.0e0 ); }
    if( ov_rm_1 < 0.0e0 ){ scale( wave_1_m, -1.0e0 ); }
    if( ov_rp_2 < 0.0e0 ){ scale( wave_2_p, -1.0e0 ); }
    if( ov_rm_2 < 0.0e0 ){ scale( wave_2_m, -1.0e0 ); }

    // <d psi_1/da | psi_2 > -- read 
    double cp_d1_2 = 1.0e0/( 2.0e0 * disp_b ) * ( product( wave_1_p, wave_2 ) - product( wave_1_m, wave_2 ) );
    cout << "\t" << "< d psi_1/da | psi_2 > = " << cp_d1_2 << "\t"; 
    // < psi_1 | d psi_2/da > -- read
    double cp_1_d2 = 1.0e0/( 2.0e0 * disp_b ) * ( product( wave_1, wave_2_p ) - product( wave_1, wave_2_m ) );
    cout << "\t" << "< psi_1 | d psi_2/da > = " << cp_1_d2 << "\t";
    cout << " d< psi_1 | psi_2 >/da = " << cp_d1_2 + cp_1_d2 << endl;
   }
  }

}

}

}
