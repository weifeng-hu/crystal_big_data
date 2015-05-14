#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <algorithm>

#define PI 3.1415926535897932e0

using namespace std;

int main( int argc, char* argv[] )
{

  string input;
  double theta;
  int ncoord = 0;

  input = argv[1];
  theta = atof( argv[2] );
  
  // read coords
  vector< string > elements;
  vector< array< double, 3 > > coord;
  vector< array< double, 3 > > new_coord;
  {

   ifstream ifs;
   ifs.open( input.c_str(), std::ios::in );
   ifs >> ncoord;

   elements.resize( ncoord );
   coord.resize( ncoord );

   for( int i = 0; i < ncoord; i++ ){
    string elemt;
    double x, y, z;
    ifs >> elemt >> x >> y >> z;
    elements.at(i) = elemt; 
    coord[i].at(0) = x;
    coord[i].at(1) = y;
    coord[i].at(2) = z;
   }
   ifs.close();

  }

  // perform rotation
  // rotation matrix
  // [ cos(theta)  -sin(theta)  0 ]
  // [ sin(theta)   cos(theta)  0 ]
  // [     0            0       1 ]
  {
   array< double, 9 > rot_mat;
   rot_mat.at(0) = cos( theta * PI / 180.0e0 );
   rot_mat.at(1) = -1.0e0 * sin( theta * PI / 180.0e0 );
   rot_mat.at(2) = 0.0e0;
   rot_mat.at(3) = sin( theta * PI/ 180.0e0 );
   rot_mat.at(4) = cos( theta * PI / 180.0e0 );
   rot_mat.at(5) = 0.0e0;
   rot_mat.at(6) = 0.0e0;
   rot_mat.at(7) = 0.0e0;
   rot_mat.at(8) = 1.0e0;

   new_coord.resize(ncoord);
   for( int i = 0; i < ncoord; i++ ){
    //apply the rotation
    array< double, 3 > new_coord_atom; new_coord_atom.fill(0.0e0);
    {
     array< double, 3 > coord_atom; copy( coord[i].begin(), coord[i].end(), coord_atom.begin() );
     for( int m = 0; m < 3; m++ ){
      for( int n = 0; n < 3; n++ ){
       const int ind = m * 3 + n;
       new_coord_atom[m] += rot_mat[ind] * coord_atom[n];
      }
     }
    }
    copy( new_coord_atom.begin(), new_coord_atom.end(), new_coord[i].begin() );
   }

  }

  // print out new coordinate
  {
    FILE* fout = fopen("new_coords.txt", "wt");
    for( int i = 0; i < ncoord; i++ ){
     fprintf( fout, "%s %20.16lfe0 %20.16lfe0 %20.16fe0\n", elements[i].c_str(), new_coord[i].at(0), new_coord[i].at(1), new_coord[i].at(2) );
    }
    fclose(fout);
  }

}
