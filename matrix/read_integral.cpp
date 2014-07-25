#include <fstream>
#include <cmath>
#include "matrix/mo_coeff.h"
#include "matrix/one_electron_integral.h"
#include "matrix/two_electron_integral.h"
#include "boost/algorithm/string.hpp"

namespace iqs {

namespace matrix {

void two_electron_integral::read_integral( const string filename )
{

  ifstream file;
  file.open( filename.c_str(), std::ios::in );
  string entry;
  char sbuf[512];

  file.getline( sbuf, 512 ); 
  entry = sbuf;
  vector<string> fields;
  split( fields, entry, boost::algorithm::is_any_of("=, \t"), boost::algorithm::token_compress_on );

  int dim;
  for( int i = 0; i < fields.size(); i++ ){
   if( fields.at(i) == "NORB" ){ dim = atoi( fields.at(i+1).c_str() ); break; }
  }

  for( int i = 0; i < data.dimensions().at(0); i++ ){
   for( int j = 0; j < data.dimensions().at(0); j++ ){
    for( int k = 0; k < data.dimensions().at(0); k++ ){
     for( int l = 0; l < data.dimensions().at(0); l++ ){
        data( i,j,k,l)=0.0e0;
     }
    }
   }   
  }

  while( file >> entry ){ if( entry == "&END" || entry == "/" ) break; }

  double val; int p1, p2, p3, p4;
  while( file >> val >> p1 >> p2 >> p3 >> p4 ){
    if( p1 != 0 && p2 != 0 && p3 != 0 && p4 != 0 ){ 
      data( p1-1 , p2-1, p3-1, p4-1 ) = val;
      data( p2-1 , p1-1, p3-1, p4-1 ) = val;
      data( p1-1 , p2-1, p4-1, p3-1 ) = val;
      data( p2-1 , p1-1, p4-1, p3-1 ) = val;
//      data( p3-1 , p4-1, p1-1, p2-1 ) = val;
//      data( p3-1 , p4-1, p2-1, p1-1 ) = val;
//      data( p4-1 , p3-1, p1-1, p2-1 ) = val;
//      data( p4-1 , p3-1, p2-1, p1-1 ) = val;
//     if( fabs((*this)(p1-1,p2-1,p3-1,p4-1) - data(p1-1,p2-1,p3-1,p4-1)) > 1.0e-17 ){ cout << p1 << " " << p2 << " " << p3 << " " << p4 << " " << val << endl; }
    }
  }
  file.close();

}

void two_electron_integral::read( const string filename )
{
  ifstream file;
  file.open( filename.c_str(), ios::in );
  double val; int p1, p2, p3, p4;
  while( file >> val >> p1 >> p2 >> p3 >> p4  ){
   data( p1-1, p2-1, p3-1, p4-1 ) = val;
   data( p2-1, p1-1, p3-1, p4-1 ) = val;
   data( p1-1, p2-1, p4-1, p3-1 ) = val;
   data( p2-1, p1-1, p4-1, p3-1 ) = val;
   data( p3-1, p4-1, p1-1, p2-1 ) = val;
   data( p3-1, p4-1, p2-1, p1-1 ) = val;
   data( p4-1, p3-1, p1-1, p2-1 ) = val;
   data( p4-1, p3-1, p2-1, p1-1 ) = val;
 //  if( p1 == 192 && p2 == 192  ){ cout << p1 << " " << p2 << " " << p3 << " " << p4 << endl;}
  }
  file.close();

}

void one_electron_integral::read( const string filename )
{

  ifstream file;
  file.open( filename.c_str(), ios::in );
  double val; int p1, p2;
  while( file >>  val >> p1 >> p2 ){
   data( p1-1, p2-1 ) = val;
   data( p2-1, p1-1 ) = val;
  }
  file.close();
 
}

void mo_coeff::read( const string filename )
{
  ifstream file;
  file.open( filename.c_str(), ios::in );
  double val; int p1, p2;
  while( file >> p1 >> p2 >> val ){
   data( p1-1, p2-1 ) = val;
  }
  file.close();
}

void two_electron_integral::read_r( const string filename )
{
  ifstream file;
  file.open( filename.c_str(), ios::in );
  double val; int p1, p2, p3, p4;
  while( file >> p1 >> p2 >> p3 >> p4 >> val ){
   data( p1-1, p2-1, p3-1, p4-1 ) = val;
   data( p2-1, p1-1, p3-1, p4-1 ) = val;
   data( p1-1, p2-1, p4-1, p3-1 ) = val;
   data( p2-1, p1-1, p4-1, p3-1 ) = val;
   data( p3-1, p4-1, p1-1, p2-1 ) = val;
   data( p3-1, p4-1, p2-1, p1-1 ) = val;
   data( p4-1, p3-1, p1-1, p2-1 ) = val;
   data( p4-1, p3-1, p2-1, p1-1 ) = val;
 //  if( p1 == 192 && p2 == 192  ){ cout << p1 << " " << p2 << " " << p3 << " " << p4 << endl;}
  }
  file.close();

}

void one_electron_integral::read_r( const string filename )
{

  ifstream file;
  file.open( filename.c_str(), ios::in );
  double val; int p1, p2;
  while( file >>  p1 >> p2 >> val ){
   data( p1-1, p2-1 ) = val;
   data( p2-1, p1-1 ) = val;
  }
  file.close();
 
}

void mo_coeff::read_r( const string filename )
{
  ifstream file;
  file.open( filename.c_str(), ios::in );
  double val; int p1, p2;
  while( file >> p1 >> p2 >> val ){
   data( p2-1, p1-1 ) = val;
  }
  file.close();
}

} // end of matrix

} // end of iqs
