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

#ifndef ROTATION_MATRIX_HPP
#define ROTATION_MATRIX_HPP

#include <geometrical_space/threed_space.hpp>
#include <geometrical_space/rotation_matrix_base.hpp>

namespace iquads {

namespace geometrical_space {

using threed_space :: pi;

class RotationMatrix_x : public RotationMatrixBase {
public:
  RotationMatrix_x() : RotationMatrixBase() {}
  RotationMatrix_x( double theta ) {
    this->angle_ = theta;
    const double theta_in_rad = theta/180.0e0 * pi;
    (*this)(0, 0) = 1.0e0;
    (*this)(0, 1) = 0.0e0;
    (*this)(0, 2) = 0.0e0;
    (*this)(1, 0) = 0.0e0;
    (*this)(1, 1) = cos( theta_in_rad );
    (*this)(1, 2) = -1.0e0 * sin( theta_in_rad );
    (*this)(2, 0) = 0.0e0;
    (*this)(2, 1) = sin( theta_in_rad );
    (*this)(2, 2) = cos( theta_in_rad );
  }

}; // end of class RotationMatrix_x

class RotationMatrix_y : public RotationMatrixBase {
public:
  RotationMatrix_y() : RotationMatrixBase() {}
  RotationMatrix_y( double theta ) {
    this->angle_ = theta;
    const double theta_in_rad = theta/180.0e0 * pi;
    (*this)(0, 0) = cos( theta_in_rad );
    (*this)(0, 1) = 0.0e0;
    (*this)(0, 2) = sin( theta_in_rad );
    (*this)(1, 0) = 0.0e0;
    (*this)(1, 1) = 1.0e0;
    (*this)(1, 2) = 0.0e0;
    (*this)(2, 0) = -1.0e0 * sin( theta_in_rad );
    (*this)(2, 1) = 0.0e0;
    (*this)(2, 2) = cos( theta_in_rad );
  }

}; // end of class RotationMatrix_y

class RotationMatrix_z : public RotationMatrixBase {
public:
  RotationMatrix_z() : RotationMatrixBase() {}
  RotationMatrix_z( double theta ) {
    this->angle_ = theta;
    const double theta_in_rad = theta/180.0e0 * pi;
    (*this)(0, 0) = cos( theta_in_rad );
    (*this)(0, 1) = -1.0e0 * sin( theta_in_rad );
    (*this)(0, 2) = 0.0e0;
    (*this)(1, 0) = sin( theta_in_rad );
    (*this)(1, 1) = cos( theta_in_rad );
    (*this)(1, 2) = 0.0e0;
    (*this)(2, 0) = 0.0e0;
    (*this)(2, 1) = 0.0e0;
    (*this)(2, 2) = 1.0e0;
  }

}; // end of class RotationMatrix_z

} // end of namespace geometrical_space

} // end of namespace iquads

#endif
