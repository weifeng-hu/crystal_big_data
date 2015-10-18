#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include <string>
#include <sstream>
#include <cstring>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "molecule_geom.h"

using namespace std;

int read_output( string target_file , int natom, int start )
{

   vector<molecule_geom> steps;

   string str;
   ifstream file;
   file.open( target_file.c_str(), ios::in );
   if( !file.is_open() ){ cout << " read_input(): cannot open target file " << target_file << endl; exit(1); }

   char line[256];
   while( !file.eof() )
   {
     while(true){
       file.getline( line, 256 ); //  cout << line << endl;
       if( strcmp( line,  "CARTESIAN COORDINATES (ANGSTROEM)" ) == 0 ){
//        if( count_in_meci == 0 ){ ++count_in_meci; }
//        else if( count_in_meci == 1 ){ break; }
          break;
       }
       if( strcmp( line,  "                             ****ORCA TERMINATED NORMALLY****") == 0  )return 0;
       if( strcmp( line,  "ABORTING THE RUN") == 0  )goto next;
     }
     file.getline( line, 256);   // cout << line << endl;
//     file.getline( line, 256);   // cout << line << endl;

     molecule_geom molecule( natom );
     char element[2];
     float x,y,z;
     file.precision(9);
     for( int i = 0 ; i < natom; i++ ){
      file >> element >> x  >>  y >>  z ;
      molecule.coord.at(i).element = element;
      molecule.coord.at(i).x = x;
      molecule.coord.at(i).y = y;
      molecule.coord.at(i).z = z;
      cout.precision(9);
//      cout <<  element << x << " " << y << " " <<  z << endl;
     }
     steps.push_back(molecule);
    }
next:
    file.close();

    cout << "[ read done ]" << endl;
//  cout << "file closed" << endl;

    vector<double> rms_all;
    {
     molecule_geom reference = steps.at(0);
     for( size_t istep = 1; istep < steps.size(); istep++ ){
      molecule_geom current = steps.at(istep);
      double square_sum = 0.0e0;
      for( size_t iatom = 0; iatom < current.coord.size(); iatom++ ){
       const double x_0 = reference.coord.at(iatom).x;
       const double y_0 = reference.coord.at(iatom).y;
       const double z_0 = reference.coord.at(iatom).z;
       const double x_i = current.coord.at(iatom).x;
       const double y_i = current.coord.at(iatom).y;
       const double z_i = current.coord.at(iatom).z;
       const double delta_x = x_i - x_0;
       const double delta_y = y_i - y_0;
       const double delta_z = z_i - z_0;
       square_sum += pow( delta_x, 2) + pow( delta_y, 2 ) + pow( delta_z, 2 );
      }
      double rms_current = square_sum/current.coord.size()/3.0e0;
      rms_current = sqrt( rms_current );
      rms_all.push_back( rms_current );
     }
    }

    for( size_t i = 0; i < rms_all.size(); i++ ){
     cout << " rms[ " << i << " ] = " << rms_all.at(i)  << endl;
    }

  return 0;

}
