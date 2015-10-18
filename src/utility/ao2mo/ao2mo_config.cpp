#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "utilities/ao2mo/ao2mo_config.h"

using namespace std;

namespace iqs { namespace utilities {

ao2mo_config::ao2mo_config( string input )
{

  this->nbas = 0;
  this->norb = 0;
  this->nocc = 0;
  this->nele = 0;
  this->ns   = 0;
  this->nucl_rep = 0.0e0;
  this->orbital_window.resize(6);
  this->c_file = "undefined";
  this->one_integral_file = "undefined";
  this->two_integral_file = "undefined";

  ifstream file;
  file.open( input.c_str(), ios::in );
  if( !file.good() ){ cout << "cannot open " << input << endl; exit(1); }
  file.precision(16);
  string entry;
  while( file >> entry ){
    if( entry == "nbas" ) file >> nbas;
    if( entry == "norb" ) file >> norb;
    if( entry == "nocc" ) file >> nocc;
    if( entry == "nele" ) file >> nele;
    if( entry == "ns" ) file >> ns;
    if( entry == "orb_win" ) file >> orbital_window.at(0) >> orbital_window.at(1) >> orbital_window.at(2) >> orbital_window.at(3) >> orbital_window.at(4) >> orbital_window.at(5);
    if( entry == "nuclear_rep" ) file >> nucl_rep;
    if( entry == "c" ) file >> c_file;
    if( entry == "v1" ) file >> one_integral_file;
    if( entry == "v2" ) file >> two_integral_file;
  }

}

} } // end of iqs :: utilities
