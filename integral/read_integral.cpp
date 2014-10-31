#include <fstream>
#include <cmath>
#include <string>
#include <vector>
#include <iostream>
#include "integral/electron_integral_class.h"
#include "boost/algorithm/string.hpp"

using namespace std;

namespace iquads {

namespace integral {

void te_int :: read_fcidump( const string filename )
{

  ifstream f_fcidump;
  f_fcidump.open( filename.c_str(), std::ios::in );
  string entry;
  char sbuf[512];

  f_fcidump.getline( sbuf, 512 ); 
  entry = sbuf;

  {
    vector<string> fields;
    split( fields, entry, boost::algorithm::is_any_of("=, \t"), boost::algorithm::token_compress_on );

    for( int i = 0; i < fields.size(); i++ ){
     if( fields.at(i) == "NORB" ){ this->norb = atoi( fields.at(i+1).c_str() ); break; }
    }

    if( this->norb != this->dimensions[0] ){
     cout << " integral reading error: norb in FCIDUMP not equal to pre-allocated dimension " << endl;
     abort();
    }
  }

  while( f_fcidump >> entry ){ if( entry == "&END" || entry == "/" ) break; }

  {
   double val; int p1, p2, p3, p4;
   while( f_fcidump >> val >> p1 >> p2 >> p3 >> p4 ){
    if( p1 != 0 && p2 != 0 && p3 != 0 && p4 != 0 ){ 
      *this( p1-1 , p2-1, p3-1, p4-1 ) = val;
      *this( p2-1 , p1-1, p3-1, p4-1 ) = val;
      *this( p1-1 , p2-1, p4-1, p3-1 ) = val;
      *this( p2-1 , p1-1, p4-1, p3-1 ) = val;
    }
   }
  }

  f_fcidump.close();

}

void te_int::read_txt( const string filename )
{

  ifstream f_txt;
  f_txt.open( filename.c_str(), ios::in );
  double val; int p1, p2, p3, p4;
  while( f_txt >> val >> p1 >> p2 >> p3 >> p4  ){
   *this( p1-1, p2-1, p3-1, p4-1 ) = val;
   *this( p2-1, p1-1, p3-1, p4-1 ) = val;
   *this( p1-1, p2-1, p4-1, p3-1 ) = val;
   *this( p2-1, p1-1, p4-1, p3-1 ) = val;
   *this( p3-1, p4-1, p1-1, p2-1 ) = val;
   *this( p3-1, p4-1, p2-1, p1-1 ) = val;
   *this( p4-1, p3-1, p1-1, p2-1 ) = val;
   *this( p4-1, p3-1, p2-1, p1-1 ) = val;
  }
  f_txt.close();

}


void oe_int :: read_fcidump( const string filename )
{

  ifstream f_fcidump;
  f_fcidump.open( filename.c_str(), std::ios::in );
  string entry;
  char sbuf[512];

  f_fcidump.getline( sbuf, 512 ); 
  entry = sbuf;

  {
    vector<string> fields;
    split( fields, entry, boost::algorithm::is_any_of("=, \t"), boost::algorithm::token_compress_on );

    for( int i = 0; i < fields.size(); i++ ){
     if( fields.at(i) == "NORB" ){ this->norb = atoi( fields.at(i+1).c_str() ); break; }
    }

    if( this->norb != this->dimensions[0] ){
     cout << " integral reading error: norb in FCIDUMP not equal to pre-allocated dimension " << endl;
     abort();
    }
  }

  while( f_fcidump >> entry ){ if( entry == "&END" || entry == "/" ) break; }

  {
   double val; int p1, p2, p3, p4;
   while( f_fcidump >> val >> p1 >> p2 >> p3 >> p4 ){
    if( p1 != 0 && p2 != 0 && p3 == 0 && p4 == 0 ){ 
      *this( p1-1 , p2-1 ) = val;
      *this( p2-1 , p1-1 ) = val;
    }
   }
  }

  f_fcidump.close();

}

void oe_int::read_txt( const string filename )
{

  ifstream f_txt;
  f_txt.open( filename.c_str(), ios::in );
  double val; int p1, p2, p3, p4;
  while( f_txt >> val >> p1 >> p2 >> p3 >> p4  ){
   *this( p1-1, p2-1 ) = val;
   *this( p2-1, p1-1 ) = val;
  }
  f_txt.close();

}

} // end of matrix

} // end of iqs
