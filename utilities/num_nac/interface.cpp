#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <math.h>

namespace iquads{

namespace num_nac{

vector<double> compute_wave( vector<string> atoms, vector<vector<double> > new_coord, string molecule, string target_dir, int nel, int norb, int sz, int guess )
{

   int s = fabs(sz);
   string command;

   command = "mkdir ";
   command += target_dir;
//   cout << command << endl;
   system( command.c_str() );

   // dump integral
   orca_casci orca_calc;
   string orca_input = target_dir;
   orca_input += molecule;
   orca_input += ".inp";
   orca_calc.write_orca_input( orca_input );
   string orca_output = target_dir;
   orca_output += "test.1";
   command = orca_exe;
   command += " ";
   command += orca_input;
   command += ">";
   command += orca_output;
//   cout << command << endl;
   if( execution == true )system(command.c_str());

   if( guess == 2 ){
    // copy ref wv to target_dir
     cout << " using reference lower energy as guess " << endl;
     string ref_wav = "./ref";
     ref_wav += "/wave.1";
     command = "cp ";
     command += ref_wav;
     command += " ";
     command += target_dir;
     command += "/";
//     cout << command << endl;
     if( execution == true ) system(command.c_str());
   }

   // fci wave
   fci_calculation fci_calc;
   string fci_input = "input.txt";
   int s_sq = s * ( s + 1 );
   fci_calc.write_input( target_dir );
   fci_calc.run();
   string fci_output = target_dir;
   fci_output += "fci.out";
   command = fci_exe;
   command += ">";
   command += fci_output;
//   cout << command << endl; 
   if( execution == true ) system(command.c_str());

   ifstream ifs;
   ifs.open( fci_output.c_str(), std::ios::in );
   int iroot = 0;
   vector< double > energies;
   energies.resize(2);
   energies.at(0) = -10.0e0;
   energies.at(1) = 10.0e0;
   while( iroot < 2 ){
    char sbuf[256];
    ifs.getline( sbuf, 256 );
    string entry(sbuf);
    vector<string> fields;
    boost::algorithm::split( fields, entry, boost::algorithm::is_any_of("=, \t"), boost::algorithm::token_compress_on);
    double energy, na, nb, sz, s_sq;
    iroot = iroot + 1;
    for( size_t i = 0; i < fields.size(); i++ ){
     if( fields[i] == "energy"){
      energy = atof( fields[i+1].c_str() );
      energies.at(iroot-1) = energy;
     }
     else if( fields[i] == "Na" ){
      na = atof( fields[i+1].c_str() );
     }
     else if( fields[i] == "Nb" ){
      nb = atof( fields[i+1].c_str() );
     }
     else if( fields[i] == "Sz" ){
      sz = atof( fields[i+1].c_str() );
     }
     else if( fields[i] == "S^2") {
      s_sq = atof( fields[i+1].c_str() );
     }
    }
    cout.precision(16);
    cout << "  root[" << iroot << "]: " << " en = " << energy << "  na = " << na << "  nb = " << nb << "  sz = " << sz << "  s_sq = " << s_sq << endl;
   }
   ifs.close();

   return energies;

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

}

}
