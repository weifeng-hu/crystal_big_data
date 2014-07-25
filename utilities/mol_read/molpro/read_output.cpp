#include <stdio.h>
#include <cstdlib>
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

   string str;

   ifstream file;
   file.open( target_file.c_str(), ios::in );
   if( !file.is_open() ){ cout << " read_input(): cannot open target file " << target_file << endl; exit(1); }

   char line[256];
   int count = start;
   while( !file.eof() )
   {
     int count_in_meci = 0;
     while(true){
       file.getline( line, 256 );  // cout << line << endl;
       if( strcmp( line,  " Current geometry (xyz format, in Angstrom)" ) == 0 ){
//        if( count_in_meci == 0 ){ ++count_in_meci; }
//        else if( count_in_meci == 1 ){ break; }
          break;
       }
//       if( strcmp( line,  "                             ****ORCA TERMINATED NORMALLY****") == 0  )return 0;
     }
     file.getline( line, 256);   // cout << line << endl;
     file.getline( line, 256);   // cout << line << endl;
     file.getline( line, 256);   // cout << line << endl;

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
      cout.precision(10);
//      cout <<  element << x << " " << y << " " <<  z << endl;
     }

     ofstream outfile;
     string cnt;      ostringstream covert;  covert << count; cnt = covert.str();
     string outfile_name;
     if( count  >= 10000 && count < 100000 ){
      outfile_name = outfile_name + "geofile.step." + cnt + ".gjf";
     }
     else if( count >= 1000 && count < 10000 ){
      outfile_name  = outfile_name + "geofile.step." + "0" + cnt + ".gjf" ;
     }
     else if( count >= 100 && count < 1000 ){
      outfile_name  = outfile_name + "geofile.step." + "00" + cnt + ".gjf" ;
     }
     else if( count >= 10 && count < 100 ){
      outfile_name  = outfile_name + "geofile.step." + "000" + cnt + ".gjf" ;
     }
     else if( count < 10 ){
      outfile_name = outfile_name + "geofile.step." + "0000" + cnt + ".gjf";
     }
     outfile.open( outfile_name.c_str(), ios::out );
     outfile << "%chk=step." << count << ".chk" << endl;
     outfile << "# hf/3-21g" << endl;
     outfile << endl;
     outfile << "Title Card Required" << endl;
     outfile << endl;
     outfile << "0 1"<< endl;
     outfile << endl;
     outfile.precision(9);
     for( int i = 0; i < natom; i++ ){
      outfile << molecule.coord.at(i).element << "\t" << molecule.coord.at(i).x << "\t" << molecule.coord.at(i).y << "\t" << molecule.coord.at(i).z << endl;
     }
     outfile << endl;
     outfile.close();

     count = count + 1;

     cout << count << endl;
    }

    file.close();
//  cout << "file closed" << endl;
  return 0;

}
