#include <string>
#include <fstream>
#include "utilities/solid_gen/crystal_info.h"

using namespace std;

namespace iquads {

namespace crystal {

void molecular_crystal_info::read( string input )
{

  ifstream ifs;
  ifs.open( input.c_str(), ios::in );
  char line[100];
  while( ifs.getline( line, 100 ) ){
   string entry;
   entry = line;
   if( entry == "radius" ) ifs >> this->radius_;
   if( entry == "sizes" ){
    size_t a, b, c;
    ifs >> a >> b >> c;
    this->sizes = make_tuple ( a, b, c );
   }
   if( entry == "constants" ){
    ifs >> this->primitive_.set_constants();
   }
   if( entry == "unit_cell" ){
    ifs >> this->primitive_;
   }
   if( entry == "short_range_radius"){
    ifs >> this->short_range_radius_;
    this->short_range_requested_ = true;
   }
   if( entry == "long_range_radius"){
    ifs >> this->long_range_radius_;
    this->long_range_requested_ = true;
   }
   if( entry == "request_dimer"){
    this->dimer_requested_ = true;
   }
   if( entry == "request_trimer" ){
    this->trimer_requested_ = true;
   }
   if( entry == "request_tetramer"){
    this->tetramer_requested_ = true;
   }
  }
  
  cout << " radius: " << this->radius_ << endl;
  cout << " short range radius: " << this->short_range_radius_ << endl;
  cout << " long range radius: " << this->long_range_radius_ << endl;
  cout << " sizes: " << get<0>( this->sizes ) << " " << get<1>( this->sizes) << " " << get<2>( this->sizes ) << endl;
  cout << " dimer requested? " << this->dimer_requested_ << endl;
  cout << " trimer requested? " << this->trimer_requested_ << endl;
  cout << " tetramer requested? " << this->tetramer_requested_ << endl;
  cout << " short range requested? " << this->short_range_requested_ << endl;
  cout << " long range requested? " << this->long_range_requested_ << endl;
  this->primitive_.print_info();

} // end of crystal_info :: read()

} // end of namespace crystal

} // end of namespace iquads
