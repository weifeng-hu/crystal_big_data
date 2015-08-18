#include <fstream>
#include <iostream>
#include <string>
#include "utilities/solid_gen/crystal_info.h"

using namespace std;
using namespace iquads::crystal;

int main( int argc, char* argv[] ){

  cout << "test crystal info object I/O" << endl;
  cout << " write input file" << endl;
  {
   ofstream ofs;
   string filename = "check/test.in";
   ofs.open( filename.c_str(), ios::out );
   ofs << "radius" << endl;
   ofs << "30.0e0" << endl;
   ofs << "sizes" << endl;
   ofs << " 5" << " 4" << " 3" << endl;
   ofs << "unit_cell" << endl;
   ofs << "2" << endl;
   ofs << "o2.1  2" << endl;
   ofs << "O  0.0 0.0 0.0 8" << endl;
   ofs << "O  1.0 0.0 0.0 8" << endl;
   ofs << "o2.2  2" << endl;
   ofs << "O  0.0 1.0 0.0 8" << endl;
   ofs << "O  1.0 1.0 0.0 8" << endl;
   ofs << "1.5  1.5  1.5  120  90  90" << endl;
   ofs.close();
  }

  molecular_crystal_info info;
  info.read("check/test.in");

}
