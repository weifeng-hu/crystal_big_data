#include <string>
#include <fstream>
#include "utilities/solid_gen/crystal_info.h"

using namespace std;

namespace iquads{

namespace crystal{

void crystal_info::read( string input )
{

 ifstream ifs;
 ifs.open( input.c_str(), ios::in );
 while( ifs.eof() == false ){
  string entry;
  ifs >> entry;
  if( entry == "cutoff" ) ifs >> this->cutoff;
  if( entry == "nunits" ){
   int a, b, c;
   ifs >> a >> b >> c;
   this->n_units = make_tuple ( a, b, c );
  }
  if( entry == "unit_cell" ){
   int natom;
   ifs >> natom;
   this->primitive.resize(natom);
   for( size_t i = 0; i < natom; i++ ){
    string element;
    double x, y, z;
    int charge;
    ifs >> element >> x >> y >> z >> charge;
    primitive.get_store().at(i).set_x() = x;
    primitive.get_store().at(i).set_y() = y;
    primitive.get_store().at(i).set_z() = z;
    primitive.get_store().at(i).set_element() = element;
    primitive.get_store().at(i).set_charge() = charge;
   }
  }
 }

}

}

}
