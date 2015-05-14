#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include "read_output.h"

using namespace std;

int main( int argc, char* argv[] )
{

  int res;

  if( argc == 1 ){ cout << " error: molpro_read main: no targeted file " << endl; exit(1); }
  string target_file = argv[1];
  int natom = atoi(argv[2]);
  int start = atoi(argv[3]);
  cout << "molpro_read main(): molpro target file = " << target_file << endl;
  cout << " natom = " << natom << endl;

  res = read_output( target_file, natom, start);

  return 0;

}
