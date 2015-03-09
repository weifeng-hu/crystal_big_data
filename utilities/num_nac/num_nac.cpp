#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

double R_bohr = 5.291772109217e-1;
string orca_exe = "/home/wh288/Development/orca_dyn/x86_exe/orca";
string fci_exe = "/home/wh288/Development/fci_6/Be";
bool execution = true;

void write_orca_input( string filename, vector<string> atoms, vector< vector<double> > coord, int nel, int norb, int s )
{

    ofstream ofs;
    ofs.open( filename.c_str(), std::ios::out );

    const int natom = coord.size();
    char comma = '"' ;
    ofs << "%" << "coords" << endl;
    ofs << " ctyp xyz" << endl;
    ofs << " units angs" << endl;
    ofs << " coords" << endl;
    ofs.precision(10);
    for( size_t i = 0; i < natom; i++ ){
     ofs << atoms.at(i) << " " << scientific << coord.at(i).at(0) << " " << coord.at(i).at(1) << " " << coord.at(i).at(2) << endl;
    }
    ofs << " end" << endl;
    ofs << "end" << endl;
    ofs << "!rhf 6-31g tightscf" << endl;

    ofs << "$new_job" << endl;
    ofs << "%" << "coords" << endl;
    ofs << " ctyp xyz" << endl;
    ofs << " units angs" << endl;
    ofs << " coords" << endl;
    ofs.precision(10);
    for( size_t i = 0; i < natom; i++ ){
     ofs << atoms.at(i) << " " << scientific << coord.at(i).at(0) << " " << coord.at(i).at(1) << " " << coord.at(i).at(2) << endl;
    }
    ofs << " end" << endl;
    ofs << "end" << endl;
    ofs << "!casscf 6-31g tightscf" << endl;
    ofs << "%" << "casscf nel " << nel << endl;
    ofs << "       norb " << norb << endl;
    ofs << "       mult " << 2*s+1 << endl;
    ofs << "       nroots 2" << endl;
    ofs << "       weights[0] = 1, 1" << endl;
    ofs << "       cistep dmrg" << endl;
    ofs << "       maxiter 1" << endl;
    ofs << " dmrg_para" << endl;
    ofs << "       sweeptol 1.0e-12" << endl;
    ofs << "       new_version true" << endl;
    ofs << "       nroots 2" << endl;
    ofs << "       weights = 0.5e0, 0.5e0" << endl;
    ofs << "       irrep 0" << endl;
    ofs << "       mult " << 2*s+1 << endl;
    ofs << "       use_mpi true" << endl;
    ofs << "       use_host false" << endl;
    ofs << "       np 1" << endl;
    ofs << "       pathname " << comma << "/home/wh288/Development/Block_stracking/block.spin_adapted" << comma << endl;
    ofs << "       nschedule 1" << endl;
    ofs << "       m = 200 " << endl;
    ofs << "       iteration = 0" << endl;
    ofs << "       david_tol = 1.0e-8" << endl;
    ofs << "       noise = 0.0e0" << endl;
    ofs << "       twodot true" << endl;
    ofs << "       twodot_to_onedot 4" << endl;
    ofs << "       maxiter 0" << endl;
    ofs << "       restart false" << endl;
    ofs << "       reset_iter false" << endl;
    ofs << "       savetransf false" << endl;
    ofs << "       mom false" << endl;
    ofs << "       prefix " << comma << "./" << comma << endl;
    ofs << "       hostfile " << comma << "hosts" << comma << endl;
    ofs << " end" << endl;
    ofs << "end" << endl;

    ofs.close();

}

void write_fci_input( string fci_input, string subdir, string molecule, int nel, int norb, int sz, int s_sq, int guess )
{

  double nel_d = nel;
  double sz_d = sz;
  double s_sq_d = s_sq;

  ofstream ofs;
  ofs.open( fci_input.c_str(), std::ios::out );
  ofs << subdir << endl;
  ofs << molecule << endl;
  ofs << scientific << nel_d << endl;
  ofs << scientific << sz_d << endl;
  ofs << scientific << s_sq_d << endl;
  ofs << guess << endl;
  ofs.close();

}

void compute_wave( vector<string> atoms, vector<vector<double> > new_coord, string molecule, string target_dir, int nel, int norb, int sz, int guess )
{

   int s = fabs(sz);
   string command;

   command = "mkdir ";
   command += target_dir;
   cout << command << endl;
   system( command.c_str() );

   // dump integral
   string orca_input = target_dir;
   orca_input += molecule;
   orca_input += ".inp";
   write_orca_input( orca_input, atoms, new_coord, nel, norb, s);
   string orca_output = target_dir;
   orca_output += "test.1";
   command = orca_exe;
   command += " ";
   command += orca_input;
   command += ">";
   command += orca_output;
   cout << command << endl;
   if( execution == true )system(command.c_str());

   if( guess == 2 ){
    // copy ref wv to target_dir
     string ref_wav = "./ref";
     ref_wav += "/wave.1";
     command = "cp ";
     command += ref_wav;
     command += " ";
     command += target_dir;
     command += "/";
     cout << command << endl;
     if( execution == true ) system(command.c_str());
   }

   // fci wave
   string fci_input = "input.txt";
   int s_sq = s * ( s + 1 );
   write_fci_input( fci_input, target_dir, molecule, nel, norb, sz, s_sq, guess );
   string fci_output = target_dir;
   fci_output += "fci.out";
   command = fci_exe;
   command += ">";
   command += fci_output;
   cout << command << endl; 
   if( execution == true ) system(command.c_str());

}

vector<double> read_wave( string dir, int len, int iroot )
{

  vector<double> wave;
  wave.resize( len );

  string filename = dir;
  filename += "/wave.";
  char line[10];
  sprintf( line, "%i", iroot);
  filename += line;

  ifstream ifs; 
  ifs.open( filename.c_str(), std::ios::in );
  for( size_t i = 0; i < len; i++ ){
   ifs >> wave.at(i);
  }
  ifs.close();

  return wave;

} 

double product( vector<double> wave1, vector<double> wave2 )
{

  double retval = 0.0e0;
  const int len = wave1.size();

  for( size_t i = 0; i < len; i++ ){
   retval += wave1.at(i) * wave2.at(i);
  }

  return retval;

}

void scale( vector<double>& wave, double scale )
{
  for( size_t i = 0; i < wave.size(); i++ ){
   wave.at(i) *= scale;
  }
}

int main( int argc, char* argv[] )
{

  string molecule = argv[1];
  string f_coord = molecule + ".coord";
  double disp_b = atof( argv[2] );
  double disp = atof( argv[2] ) * R_bohr;

  cout << "molecule: " << molecule << endl;
  cout << " displacement: in bohr " << disp_b << "   in angs " << disp << endl;

  vector< string > atoms;
  vector< vector<double> > coord;
  int nel, norb, sz;
  int natom;
  nel = 0; norb = 0; natom = 0; sz = 0;
  {
   ifstream ifs;
   ifs.open( f_coord.c_str(), std::ios::in );
   ifs >> nel >> norb >> sz; 
   ifs >> natom;
   atoms.resize( natom );
   coord.resize( natom );
   for( size_t i = 0; i < natom; i++ ){ coord.at(i).resize(3); }
   for( size_t i = 0; i < natom; i++ ){
    ifs >> atoms.at(i) >> coord.at(i).at(0) >> coord.at(i).at(1) >> coord.at(i).at(2);
   }
   ifs.close();
  }

  cout << " nel = " << nel << " norb = " << norb << " sz = " << sz << "  natom = " << natom << endl;
//  goto nac;
// reference geometry
  {
   string dir = "./ref/";
   compute_wave( atoms, coord, molecule, dir, nel, norb, sz, 1 );
  }

// displacements
  for( size_t iatom = 0; iatom < natom; iatom++ ){
   for( size_t icop = 0; icop < 3; icop++ ){
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
     compute_wave( atoms, new_coord, molecule, dir, nel, norb, sz, 2 );
     
    // minus
     new_coord = coord;
     new_coord.at(iatom).at(icop) = new_coord.at(iatom).at(icop) - disp;
     sprintf( line, "./%i.%i.m/", iatom, icop );
     dir = line;
     compute_wave( atoms, new_coord, molecule, dir, nel, norb, sz, 2 );
   }
  }

nac:
// numerical nac
  for( size_t iatom = 0; iatom < natom; iatom++ ){
   for( size_t icop = 0; icop < 3; icop++ ){
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

    cout.precision(8);
    cout << "  < 1 | 1+ > = " << ov_rp_1 << "\t" << " < 1 | 1- > = " << ov_rm_1 << "\t" << " < 1+ | 1- > = " << ov_pm_1 << endl;
    cout << "  < 2 | 2+ > = " << ov_rp_2 << "\t" << " < 2 | 2- > = " << ov_rm_2 << "\t" << " < 2+ | 2- > = " << ov_pm_2 << endl;
    cout << "  < 1 | 2+ > = " << ov_r1_p2 << "\t" << " < 1 | 2- > = " << ov_r1_m2 << "\t" << " < 1+ | 2- > = " << ov_p1_m2 << "\t" << " < 1- | 2+ > = " << ov_m1_p2 << endl;
    cout << "  < 2 | 1+ > = " << ov_r2_p1 << "\t" << " < 2 | 1- > = " << ov_r2_m1 << "\t" << " < 2+ | 1- > = " << ov_p2_m1 << "\t" << " < 2- | 1+ > = " << ov_m2_p1 << endl;

    if( fabs( ov_rp_1 ) < 0.5e0 || fabs( ov_rm_1 ) < 0.5e0 || fabs( ov_pm_1 ) < 0.5e0 ){
     cout << "  detect substantial wavefunction change for this disp; trying to switch roots " << endl;
     if( fabs( ov_r1_p2 ) > 0.5e0 ){
      cout << "   switching | 1+ > with | 2+ > " << endl;
      vector<double> wave_tmp = wave_2_p;
      wave_2_p = wave_1_p;
      wave_1_p = wave_tmp;
     }
     if( fabs( ov_r1_m2 ) > 0.5e0 ){
      cout << "   switching | 1- > with | 2- > " << endl;
      vector<double> wave_tmp = wave_2_m;
      wave_2_m = wave_1_m;
      wave_1_m = wave_tmp;
     }
//     continue;
    }
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
 
    cout.precision(8);
    cout << "  < 1 | 1+ > = " << ov_rp_1 << "\t" << " < 1 | 1- > = " << ov_rm_1 << "\t" << " < 1+ | 1- > = " << ov_pm_1 << endl;
    cout << "  < 2 | 2+ > = " << ov_rp_2 << "\t" << " < 2 | 2- > = " << ov_rm_2 << "\t" << " < 2+ | 2- > = " << ov_pm_2 << endl;
    cout << "  < 1 | 2+ > = " << ov_r1_p2 << "\t" << " < 1 | 2- > = " << ov_r1_m2 << "\t" << " < 1+ | 2- > = " << ov_p1_m2 << "\t" << " < 1- | 2+ > = " << ov_m1_p2 << endl;
    cout << "  < 2 | 1+ > = " << ov_r2_p1 << "\t" << " < 2 | 1- > = " << ov_r2_m1 << "\t" << " < 2+ | 1- > = " << ov_p2_m1 << "\t" << " < 2- | 1+ > = " << ov_m2_p1 << endl;

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
