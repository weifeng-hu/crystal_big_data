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

#ifndef ROTATION_MATRIX_BASE_HPP
#define ROTATION_MATRIX_BASE_HPP

#include <array>
#include <math.h>

namespace iquads {

namespace geometrical_space {

class RotationMatrixBase {
public:
  typedef std :: array< double, 9 > store_type;
  typedef double angle_data_type;
  typedef std :: array< double, 3 > threed_vector_type;

public:
  threed_vector_type operator* ( const threed_vector_type& vec ) {
    threed_vector_type new_vec;
    new_vec[0] = (*this)( 0, 0 ) * vec[0] + (*this)( 0, 1 ) * vec[1] + (*this)( 0, 2 ) * vec[2];
    new_vec[1] = (*this)( 1, 0 ) * vec[0] + (*this)( 1, 1 ) * vec[1] + (*this)( 1, 2 ) * vec[2];
    new_vec[2] = (*this)( 2, 0 ) * vec[0] + (*this)( 2, 1 ) * vec[1] + (*this)( 2, 2 ) * vec[2];
    return new_vec;
  }

protected:
  RotationMatrixBase() {
    this->store_.fill(0.0e0);
    this->at(0,0) = 1.0e0;
    this->at(1,1) = 1.0e0;
    this->at(2,2) = 1.0e0;
  }

protected:
  double& at( const size_t i, const size_t j ) 
    {  return this->store_.at( i * 3 + j ); }
  double& operator() ( const size_t i, const size_t j )
    {  return this->store_[ i * 3 + j ]; }
  angle_data_type angle() const
    {  return this->angle_; }

protected:
  store_type store_;
  angle_data_type angle_;

}; // end of class RotationMatrixBase

} // end of namespace geometrical_space

} // end of namespace iquads

#endif
