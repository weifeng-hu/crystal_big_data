#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main( int argc, char* argv[] )
{

  int nact = 114;
  int norb = 132;
  vector<int> act_orb;
  FILE* fp = fopen( "reorder.txt", "rt");
  int val;
  for( int i = 0; i < nact; i++ ){
   fscanf(fp,"%d,", &val);
   cout << val << " " ;
   act_orb.push_back(val);
  }
  fclose(fp);

  cout << endl;


  for( int i = 0; i < nact; i++){
    act_orb.at(i) = act_orb.at(i) + 18 - 1;
    cout << act_orb.at(i) << " " ;
  }
  cout << endl;

//  fp = fopen( "genetic_reorder.dat", "wt ");

  system("mkdir reordered");

  for( int i = 0; i < nact; i++ ){
   char oldorb[20];  sprintf(oldorb,  "mo%i.gif", act_orb.at(i) );
   if( act_orb.at(i) < 10 ){
    sprintf(oldorb,  "mo00%i.gif", act_orb.at(i) );
   }else if( act_orb.at(i) >= 10 && act_orb.at(i) < 100 ){
    sprintf(oldorb,  "mo0%i.gif", act_orb.at(i) );
   }else if( act_orb.at(i) >= 100 ){
    sprintf(oldorb,  "mo%i.gif", act_orb.at(i) );
   }
   char neworb[20];  sprintf(neworb,  "%i.gif",   i+1);
   char cmd[100];    sprintf(cmd,     "cp %s reordered/%s",  oldorb, neworb);
   cout << cmd << endl;
   system(cmd);
//    fprintf(fp, "%i,", act_orb.at(i) - 4 + 1 );
  }
//  fclose(fp);

}
