#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <array>
#include <string>

using namespace std;

int main( int argc, char* argv[] )
{

  if( argc != 5 ){ std::cout << " insufficient arguments " << endl << " usage: hf_occ [norb] [nocc] [nhole] [ order_file ]" << endl; exit(1); }
  const int norb  = (const int) atoi( argv[1] );
  int nocc  = atoi( argv[2] );
  int nexcitation = atoi( argv [3] );
  string order_file = argv[4];

  const int N = 200;

  array<int, N> act_orb;
  FILE* fp = fopen( order_file.c_str(), "rt");
  int val;
  for( int i = 0; i < norb; i++ ){
   fscanf(fp,"%d,", &val);
   cout << val << " " ;
   act_orb[i] = val - 1;
  }
  fclose(fp);
  cout << endl;

  FILE* hf_occ = fopen( "hf_occ.dat","wt");
  for( int i = 0; i < norb; i++ ){
   if( act_orb.at(i) < nocc - nexcitation ){
     fprintf( hf_occ, "1 1 " );
   }
   else if( act_orb.at(i) >= nocc && act_orb.at(i) < nocc + nexcitation ){
     fprintf( hf_occ, "1 1 " );
   }
   else{
     fprintf( hf_occ, "0 0 " );
   }
  }
  fclose(hf_occ);

}
