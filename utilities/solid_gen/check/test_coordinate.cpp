#include <iostream>
#include "utilities/solid_gen/coordinate.h"

using namespace iquads :: basic;

int main( int argc, char* argv[] )
{

  std::cout << " test coordinate.h" << std::endl;
  std::cout << " coordinate set to 1.0e0, 2.0e0, 3.0e0 " << std::endl;

  std::cout << " creating coordinate obj" << std::endl;
  std::cout << " filling elements" << std::endl;
  Coord new_coord = std::make_tuple( 1.0e0, 2.0e0, 3.0e0 );
  std::cout << " output coordinate object" << std::endl;
  std::cout << " x = " << std::get<0>(new_coord) << std::endl;
  std::cout << " y = " << std::get<1>(new_coord) << std::endl;
  std::cout << " z = " << std::get<2>(new_coord) << std::endl;

  std::cout << " test CoordList" << std::endl;
  CoordList new_coordlist;
  new_coordlist.push_back( new_coord );
  std::cout << " print CoordList obj" << std::endl;
  std::cout << " x = " << std::get<0>( new_coordlist.at(0) ) << std::endl;
  std::cout << " y = " << std::get<1>( new_coordlist.at(0) ) << std::endl;
  std::cout << " z = " << std::get<2>( new_coordlist.at(0) ) << std::endl;

}
