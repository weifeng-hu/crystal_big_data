#include <fstream>
#include <iostream>
#include <string>
#include "utilities/solid_gen/crystal_info.h"

using namespace std;

int main( int argc, char* argv[] ){

  cout << "test crystal info object I/O" << endl;
  cout << " write input file" << endl;
  {
   ofstream ofs;
   string filename = "./test.in";
   ofs.open( filename.c_str(), ios::in );
   ofs << "radius" << "  " << "30.0e0" << endl;
   ofs << "sizes" << " 5 " << " 4" << " 3" << endl;
   ofs << "constants" << "  1.5  1.5  1.5  120  90  90" << endl;
   ofs << "unit_cell" << endl;
   ofs << "" << endl;
  }

}
