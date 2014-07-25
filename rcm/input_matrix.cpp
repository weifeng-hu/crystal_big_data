#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cmath>
#include <fstream>
#include "matrix/square_matrix.h"
#include "boost/algorithm/string.hpp"

using namespace std;

namespace iqs {

namespace rcm {

iqs::matrix::square_matrix input_matrix( string filename, const char type )
{

   int dim;

   ifstream file;
   file.open( filename.c_str(), std::ios::in );
   string entry;
   char sbuf[512];

   file.getline( sbuf, 512 );
   entry = sbuf;
   vector<string> fields;
   split( fields, entry, boost::algorithm::is_any_of("=, \t"), boost::algorithm::token_compress_on );

   for( int i = 0; i < fields.size(); i++ ){
    if( fields.at(i) == "NORB" ){ dim = atoi( fields.at(i+1).c_str() ); break; }
   }

   while( file >> entry ){ if( entry == "&END" || entry == "/" ) break; }

   iqs::matrix::square_matrix square_mat( dim );
   for( int i = 0; i < dim; i++ ){ for (int j = 0; j < dim; j++ ){ square_mat(i,j) = 0.0e0; } }

   double val; int p1, p2, p3, p4;
   if ( type == 'h' ){
    while( file >> val >> p1 >> p2 >> p3 >> p4 ){
       if( p1 != 0 && p2 != 0 && p3 == 0 && p4 == 0 ) square_mat( p1-1, p2-1) = val; //cout << p1 << " " << p2 << " " <<square_mat(p1-1,p2-1) << endl;
    }
   }
   else if ( type == 'e' )
   {
    while( file >> val >> p1 >> p2 >> p3 >> p4 ){
       if( ( p1 != 0 && p2 != 0 && p3 != 0 && p4 != 0 ) && ( p1 == p3 && p2 == p4 ) ) square_mat( p1-1, p2-1 ) = val;
    }
   }
   else if ( type == 'c' )
   {
    while( file >> val >> p1 >> p2 >> p3 >> p4 ){
       if( ( p1 !=0 && p2 != 0 && p3 != 0 && p4 != 0 ) && ( p1 == p2 && p3 == p4 ) ) square_mat( p1-1, p3-1 ) = val;
    }
   }
   file.close();

   for( int i = 0; i < dim; i++ ){
    for( int j = 0; j <= i; j++ ){
      if( fabs(square_mat(i,j) - square_mat(j,i) ) >= 1.0e-16 ){
        if( fabs( square_mat(i,j) ) > 1.0e-15 && fabs( square_mat(j,i) ) < 1.0e-15 ){
          square_mat(j,i) = square_mat(i,j);
        }
        else if( fabs( square_mat(i,j) ) < 1.0e-15 && fabs( square_mat(j,i) ) > 1.0e-15 ) 
        {
          square_mat(i,j) = square_mat(j,i);
        }
        
      }
    }
   }

   return square_mat;

}

} // end of rcm

} // end of iqs
