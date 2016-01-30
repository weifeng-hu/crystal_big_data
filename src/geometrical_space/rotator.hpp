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

#include <array>
#include <geometrical_space/coordinate.hpp>
#include <geometrical_space/threed_space_function.hpp>
#include <geometrical_space/rotation_matrix.hpp>

namespace iquads {

namespace geometrical_space {

  /**
   *  The Rotator class:
   *
   *  Given any two vectors r1, r2 in the 3D space, in the cartesian coordinates,
   *  the rotator generates the sequence to rotate vector r1 to r2.
   *
   *  In principle, this can be done in arbitary ways. This rotator uses a 2-step
   *  rotation sequence from r1 to r2, assembling the parametrization of the 
   *  spherical coordinate system angles.
   *
   *  1. it rotates r1 to the xz plane, get r1'
   *  2. it rotates r1' to the r2's rotation result r2'(just direction) in the xz plane,
   *  3. it rotates r1' from the xz plane to the direction of r2.
   *
   *  This procedure separates the angle phi in the spherical parameterization in step 1 and 3,
   *  and operate the angle theta in step 2.
   *  The initial step would be to calculate the angle for rotating r1 to xz plane, and the angle
   *  for rotating r2 to xz plane(and then take the minus of this angle in step 3).
   *
   *  The Rotator will be a 3-step matrix multiplication operation on vector r1, or any vector 
   *  which will use the 3-step matrix multiplication set up by r1, and r2.
   *
   *  The input will be r1, and r2, in cartesian coordinates
   *  The constructor performs the calculation of needed angles, and the resulted 3x3 rotation matrices.
   *  So, there are 3 angles to compute, and 3 rotation matrices to store.
   *  And an operation which allow arbitrary vector to be rotated using these matrices.
   *
   */

using threed_space :: pi;

class Rotator {
public:
  typedef iquads :: geometrical_space :: RotationMatrix_x rotation_matrix_x_type;
  typedef iquads :: geometrical_space :: RotationMatrix_y rotation_matrix_y_type;
  typedef iquads :: geometrical_space :: RotationMatrix_z rotation_matrix_z_type;
  typedef iquads :: geometrical_space :: CartesianCoordinate3D coordinate_type;
  typedef std :: array < double, 3 > threed_vector_type;
  typedef double angle_data_type;

public:
  Rotator( const threed_vector_type& r_from, const threed_vector_type& r_to ) {
    // compute the rotation matrix from r_from_in_xy to e_x
    threed_vector_type r_from_proj_in_xy; 
    r_from_proj_in_xy[0] = r_from[0];
    r_from_proj_in_xy[1] = r_from[1];
    r_from_proj_in_xy[2] = 0.0e0;
    this->angle_1_ 
     = iquads :: geometrical_space :: threed_space :: compute_angle_between_two_vectors
              ( r_from_proj_in_xy, iquads :: geometrical_space :: threed_space :: e_x );
    if( r_from[1] >= 0.0e0 ) { this->angle_1_ *= -1.0e0; } else {  }
    this->R_1_ = rotation_matrix_z_type( this->angle_1_ );
    std :: cout << this->angle_1_ << std :: endl;

    // compute the rotation matrix from e_x to r_to_in_xy
    threed_vector_type r_to_proj_in_xy;
    r_to_proj_in_xy[0] = r_to[0];
    r_to_proj_in_xy[1] = r_to[1];
    r_to_proj_in_xy[2] = 0.0e0;
    this->angle_3_ 
     = iquads :: geometrical_space :: threed_space :: compute_angle_between_two_vectors
              ( r_to_proj_in_xy, iquads :: geometrical_space :: threed_space :: e_x );
    if( r_to[1] >= 0.0e0 ) { } else { this->angle_3_ *= -1.0e0; }
    std :: cout <<  this->angle_3_ << std :: endl;
    this->R_3_ = rotation_matrix_z_type( this->angle_3_ );

    // compute the angle in the xz plane
    // compute the resulted vector by rotating r_from to xz plane, around the z axes
    threed_vector_type r_from_to_xz;
    r_from_to_xz.fill(0.0e0);
    r_from_to_xz = this->R_1_ * r_from;

    // compute the resulted vector by rotation r_to to xz plane, around the z axes
    threed_vector_type r_to_to_xz;
    r_to_to_xz.fill(0.0e0);
    rotation_matrix_z_type R_to_to_xz( -1.0e0 * this->angle_3_ );
    r_to_to_xz = R_to_to_xz * r_to;

    // compute the resulted angle between these two new vectors in the xz plane
    // Note that we cannot simply directly compute the angle directly with these two vectors, 
    // because without a reference, we cannot figure the final sign of the rotation
    // the reference here, is set to +z.
    double angle_minus_z_to_r_from 
      = iquads :: geometrical_space :: threed_space :: compute_angle_between_two_vectors
               ( r_from_to_xz, iquads :: geometrical_space :: threed_space :: e_z );
    double angle_minus_z_to_r_to
      = iquads :: geometrical_space :: threed_space :: compute_angle_between_two_vectors
               ( r_to_to_xz, iquads :: geometrical_space :: threed_space :: e_z );
    this->angle_2_ = angle_minus_z_to_r_to - angle_minus_z_to_r_from;
    std :: cout << this->angle_2_ << std :: endl;
    this->R_2_ = rotation_matrix_y_type( this->angle_2_ );
  } 

public:
  threed_vector_type operator* ( const threed_vector_type& vector ) {
    threed_vector_type r_1 = this->R_1_ * vector;
    threed_vector_type r_2 = this->R_2_ * r_1;
    threed_vector_type r_3 = this->R_3_ * r_2;
    return r_3;
  }

  coordinate_type operator* ( const coordinate_type& coordinate ) {
    threed_vector_type r_of_coordinate = { std :: get<0> ( coordinate ),
                                           std :: get<1> ( coordinate ), 
                                           std :: get<2> ( coordinate ) };
    threed_vector_type new_r = (*this) * r_of_coordinate;
    return std :: make_tuple( new_r[0], new_r[1], new_r[2] );
  }

private:
  rotation_matrix_z_type R_1_;
  rotation_matrix_y_type R_2_;
  rotation_matrix_z_type R_3_;
  angle_data_type angle_1_;
  angle_data_type angle_2_;
  angle_data_type angle_3_;

}; // end of class Rotator

} // end of namespace geometrical_space

} // end of namespace iquads
