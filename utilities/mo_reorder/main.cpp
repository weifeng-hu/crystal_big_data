#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

int main( int argc, char* argv[] )
{

  int norb;;
  int norb2;;
  string fmo;
  string foldao;
  string fnewao;
  string fmo_new;

  const string input = argv[1];
  ifstream ifs; ifs.open( input.c_str(), std::ios::in );
  {
   string entry;
   while ( !ifs.eof() ){
    ifs >> entry;
    if( entry == "norb" ) ifs >> norb;
    if( entry == "fmo"  ) ifs >> fmo;
    if( entry == "foldao" ) ifs >> foldao;
    if( entry == "fnewao" ) ifs >> fnewao;
    if( entry == "fmo_new" ) ifs >> fmo_new;
   }
   norb2 = norb * norb;
  }

  vector<double> mo_coeff;
  {
   mo_coeff.resize(norb2);
   ifstream ifs;
   ifs.open( fmo.c_str(), std::ios::in );
   for( size_t i = 0; i < norb2; i++ ){
    int p1, p2; double val;
    ifs >> p1 >> p2 >> val;
    const size_t pos = (p1-1) * norb + p2-1;
    mo_coeff.at( pos ) = val;
   }
   ifs.close();
  }

  vector< string > ao_old;
  {
   ao_old.resize( norb );
   ifstream ifs;
   ifs.open( foldao.c_str(), std::ios::in );
   for( size_t i = 0; i < norb; i++ ){
    string x;
    ifs >> x;
    ao_old.at(i) = x;
   }
   ifs.close();
  }

  vector< string > ao_new;
  {
   ao_new.resize( norb );
   ifstream ifs;
   ifs.open( fnewao.c_str(), std::ios::in );
   for( size_t i = 0; i < norb; i++ ){
    string x;
    ifs >> x;
    ao_new.at(i) = x;
   }
  }

  vector<int> old_to_new;
  {
   old_to_new.resize(norb);
   for( size_t i = 0; i < norb; i++ ){
    string oldx = ao_old.at(i);
    for( size_t j = 0; j < norb; j++ ){
     string newx = ao_new.at(j);
     if( oldx == newx ){
      old_to_new.at(i) = j;
      break;
     }
    }
   }
  }


  vector<double> new_mo_coeff;
  new_mo_coeff.resize(norb2);
  {
   for( size_t i = 0; i < norb; i++ ){
    const int old_row = i;
    const int new_row = old_to_new.at(i);
    for( size_t j = 0; j < norb; j++ ){
     const int old_pos = j * norb + old_row;
     const int new_pos = j * norb + new_row;
     new_mo_coeff.at(new_pos) = mo_coeff.at(old_pos);
    }
   }
  }

  {
   ofstream ofs;
   ofs.open( fmo_new.c_str(), std::ios::out );
   ofs.precision(16);
   for( size_t i = 0; i < norb; i++ ){
    for( size_t j = 0; j < norb; j++ ){
     const int pos = i * norb + j;
     const double value = new_mo_coeff.at(pos);
     ofs << i+1 << "\t" << j+1 << "\t " << std::scientific << value << endl;
    }
   }
   ofs.close();
  }

};
