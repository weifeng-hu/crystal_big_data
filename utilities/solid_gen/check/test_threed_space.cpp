#include <iostream>
#include "utilities/solid_gen/threed_space.h"
#include "utilities/solid_gen/threed_space_function.h"

int main( int argc, char* argv[] ){

  using namespace iquads :: threed_space;

  std::cout << "test threed space functionalities" << std::endl;
  std::cout << "print unit vectors in the cartesian coordinate system" << std::endl;
  std::cout << "e_x: ";
  std::cout << get<0>(iquads::threed_space::e_3d.at(0)) << " ";
  std::cout << get<1>(iquads::threed_space::e_3d.at(0)) << " ";
  std::cout << get<2>(iquads::threed_space::e_3d.at(0)) << " ";
  std::cout << std::endl;

  std::cout << "e_y: ";
  std::cout << get<0>(iquads::threed_space::e_3d.at(1)) << " ";
  std::cout << get<1>(iquads::threed_space::e_3d.at(1)) << " ";
  std::cout << get<2>(iquads::threed_space::e_3d.at(1)) << " ";
  std::cout << std::endl;

  std::cout << "e_z: ";
  std::cout << get<0>(iquads::threed_space::e_3d.at(2)) << " ";
  std::cout << get<1>(iquads::threed_space::e_3d.at(2)) << " ";
  std::cout << get<2>(iquads::threed_space::e_3d.at(2)) << " ";
  std::cout << std::endl;

  std::cout << "test operator* for 3d vector" << std::endl;
  std::cout << "initial vector = [ 1 2 3 ] " << std::endl;
  std::cout << "multiplyer = 3.0" << std::endl;
  array<double, 3> vec = { 1.0e0, 2.0e0, 3.0e0 };
  array<double, 3> vecxa = vec * 3.0e0;
  std::cout << "final vector = [ " << vecxa.at(0) << " " << vecxa.at(1) <<
 " " << vecxa.at(2) << " ]" << std::endl;

  return 0;

}
