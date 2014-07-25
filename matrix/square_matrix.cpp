#include "square_matrix.h"

using namespace std;

namespace iqs {

namespace matrix {

void square_matrix :: read_matrix( string filename )
{

  ifstream file;
  file.open( filename.c_str(), std::ios::in );
  file.precision(16);
  int p1, p2; double val;
  while( file.good() ){
    file >> p1 >> p2 >> val;
    this->get_element( p1, p2 ) = val;
  }
  file.close();

} // end of read_matrix

square_matrix::square_matrix( int d )
{

  this-> dim = d;
  data.resize( d );
  for( int i = 0; i < d; i++ ){ data.at(i).resize(d); }
  for( int i = 0; i < d; i++ ){ for( int j = 0; j < d; j++ ){ data.at(i).at(j) = 0.0e0; } }

}

} // end of matrix

} // end of iqs
