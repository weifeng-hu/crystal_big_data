#include <string>
#include <fstream>
#include "utilities/solid_gen/molecule.h"
#include "utilities/solid_gen/molecular_crystal_info.h"

using namespace std;

namespace iquads {

namespace crystal {

void crystal_info::read( string input )
{

  ifstream ifs;
  ifs.open( input.c_str(), ios::in );
  while( ifs.eof() == false ){
   string entry;
   ifs >> entry;
   if( entry == "radius" ) ifs >> this->cutoff;
   if( entry == "sizes" ){
    int a, b, c;
    ifs >> a >> b >> c;
    this->sizes = { a, b, c };
   }
   if( entry == "constants" ){
    double la, lb, lc;
    double aa, ab, ac;
    ifs >> la >> lb >> lc >> aa >> ab >> ac;
    this->lengths = { la, lb, lc };
    this->angles  = { aa, ab, ac };
   }
   if( entry == "unit_cell" ){
    size_t n_molecule_;
    ifs >> n_molecule_;
    this->primitive.resize(n_molecule_);
    for( size_t imole  = 0; imole < n_molecule_; imole++ ){
     molecule mole_i;
     ifs >> mole_i;
     this->primitive.add_node( mole_i );
    }
   }
  }
 
  cout << " radius: " << this->radius << endl;
  cout << " sizes: " << a << " " << b << " " << c << endl;
  this->primitive.print_info();

} // end of crystal_info :: read()

} // end of namespace crystal

} // end of namespace iquads
