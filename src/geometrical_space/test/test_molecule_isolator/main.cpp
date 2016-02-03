/**
 * @file
 * @author Weifeng Hu
 *
 * @section LICENSE
 *
 * Copyright (C) 2013, 2014, 2015  Weifeng Hu
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @section DESCRIPTION
 *
 *
 */

#include <iostream>
#include <geometrical_space/rotation_matrix.hpp>
#include <geometrical_space/rotator.hpp>

int main( int argc, char* argv[] ) {

  iquads :: geometrical_space :: RotationMatrix_x Rx(90.0e0);
  iquads :: geometrical_space :: RotationMatrix_y Ry(225.0);
  iquads :: geometrical_space :: RotationMatrix_z Rz(90.0e0);

  std :: array< double, 3 > vec = { 1.0e0, 0.0e0, 0.0e0 };

  std :: array< double, 3 > vec_rot;
  vec_rot = Rx * vec;
  std :: cout << vec_rot[0] << " " << vec_rot[1] << " " << vec_rot[2] << std :: endl;
  vec_rot = Ry * vec;
  std :: cout << vec_rot[0] << " " << vec_rot[1] << " " << vec_rot[2] << std :: endl;
  vec_rot = Rz * vec;
  std :: cout << vec_rot[0] << " " << vec_rot[1] << " " << vec_rot[2] << std :: endl;

  std :: array< double, 3 > vec_1 = { 1.0, 1.0, 1.0 };
  std :: array< double, 3 > vec_2 = { 0.0, -0.4, 0.0 };
  iquads :: geometrical_space :: Rotator Rn( vec_1, vec_2 ); 

  std :: array< double, 3 > vec_try = { 1.0e0, 1.0e0, 1.0e0 };
  std :: array< double, 3 > vec_try_rot;
  vec_try_rot = Rn * vec_try;
  std :: cout << vec_try_rot[0] << " " << vec_try_rot[1] << " " << vec_try_rot[2] << std :: endl;

}
