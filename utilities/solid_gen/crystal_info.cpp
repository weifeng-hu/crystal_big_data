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
  if( entry == "crystal_const" ){
   double la, lb, lc;
   ifs >> la >> lb >> lc;
   this->primitive.set_a() = la;
   this->primitive.set_b() = lb;
   this->primitive.set_c() = lc;
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
    primitive.set_store().at(i).set_x() = x;
    primitive.set_store().at(i).set_y() = y;
    primitive.set_store().at(i).set_z() = z;
    primitive.set_store().at(i).set_element() = element;
    primitive.set_store().at(i).set_charge() = charge;
   }
  }
 }

 cout << " cutoff = " << cutoff << endl;
 cout << " duplicate by " << endl;
 cout << "  " << get<0>( n_units ) << " " << get<1>( n_units ) << " " << get<2>( n_units ) << endl;
 primitive.print();

} // end of crystal_info :: read()

} // end of namespace crystal

} // end of namespace iquads
