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

#ifndef LATTICE_PARAMETER_HPP
#define LATTICE_PARAMETER_HPP

#include <array>
#include <tuple>
#include <iostream>
#include <fstream>
#include <math.h>
#include <blas/blas_interface.h>
#include <geometrical_space/threed_space.hpp>


namespace iquads {

using namespace geometrical_space :: threed_space;

namespace structure {

using std::array;
using std::istream;
using std::ostream;
using std::tuple;
using std::get;
using std::make_tuple;

  /**
   *  A struct to store and lattice parameters
   *  with methods to manipulate them
   *  Data members are:
   *   + the a, b, c direction lattice constants (we can them length here)
   *   + the alpha, beta, gamma angles (we can them angle here)
   *
   *  This struct also serves as an calculator for the translation vectors, 
   *  expressed using ex, ey, ez as vector basis, and it will be computed 
   *  from the a, b, c and alpha, beta, gamma
   *   + also, geometry unit. It can be copied from the geometry unit info from
   *     the actual structural object
   *
   *  We use struct instead of class to define this object type, because this 
   *  object type is really a data holder rather than an entity object, i.e., 
   *  (generated) data are not guaranteed to be valid, even though 
   *  methods for data calculation are well-defined.
   */

struct LatticeParameter {
public:
  typedef LatticeParameter   this_type;
  typedef double             length_data_type;
  typedef double             angle_data_type;
  typedef tuple< length_data_type, length_data_type, length_data_type >   length_set_type;
  typedef tuple< angle_data_type, angle_data_type, angle_data_type >      angle_set_type;

  typedef array< double, 3 >               threed_vector_type;
  typedef array< threed_vector_type, 3 >   primitive_translation_vectors_type;
  typedef array< double, 9 >               translation_basis_matrix_type;
  typedef array< double, 3 >               coefficient_vector_type;
  typedef typename geometrical_space :: CartesianCoordinate3D   coordinate_type; 

  typedef length_set_type& length_set_ref;
  typedef angle_set_type&  angle_set_ref;

public:
  /**
   *  The default constructor sets everything to be zero.
   *  Here we still lack a working mechanism to check the validity of 
   *  the this object type, since zero lattice parameters are also a 
   *  valid in the real world, though kind of meaningless. 
   *  So developers need to know what this default constructor does 
   *  before they actually use it.
   */
  LatticeParameter()
    {
      this->length_set_ = make_tuple( 0.0e0, 0.0e0, 0.0e0 );
      this->angle_set_  = make_tuple( 0.0e0, 0.0e0, 0.0e0 );
    }

  /**
   *  The initialize list constructor eats the lengths and angles.
   *  Be careful! The unit format for input angles are degrees, always.
   */
  LatticeParameter( length_set_type length_set_obj,
                    angle_set_type  angle_set_obj ) :
    length_set_ (length_set_obj), angle_set_ (angle_set_obj) { }
  LatticeParameter( length_data_type a, length_data_type b, length_data_type c,
                    angle_data_type alpha, angle_data_type beta, angle_data_type gamma ):
    length_set_ ( make_tuple( a, b, c ) ), angle_set_ ( make_tuple( alpha*pi/180.0, beta*pi/180.0, gamma*pi/180.0 ) ) { }

public:
  /**
   *  Overloaded stream operator
   */

  /**
   *  + operator>> ()
   *    Overloaded insert stream operators
   */
  friend
  istream& operator>> ( istream& is, this_type& lattice_parameter_obj ) {
    length_data_type a, b, c;
    angle_data_type alpha, beta, gamma;
    is >> a >> b >> c >> alpha >> beta >> gamma;
    lattice_parameter_obj = LatticeParameter( make_tuple( a, b, c ), 
                                              make_tuple( alpha, beta, gamma ) );
    return is;
  }

  /**
   *  + operator<< ()
   *    Overloaded extraction stream operator.
   *    When we print out translational vectors, we do not perform range check
   *    since we know that the vectors are 3 dimensional arrays.
   */
  friend
  ostream& operator<< ( ostream& os, const this_type& lattice_parameter_obj ) {
    using std :: endl;
    primitive_translation_vectors_type translation_vectors 
      = lattice_parameter_obj.primitive_translation_vectors();
    os << " [ a b c ]: ";
    os << lattice_parameter_obj.a() << " ";
    os << lattice_parameter_obj.b() << " ";
    os << lattice_parameter_obj.c() << " ";
    os << endl;
    os << " [ alpha beta gamma ] ";
    os << lattice_parameter_obj.alpha() << " ";
    os << lattice_parameter_obj.beta() << " ";
    os << lattice_parameter_obj.gamma() << " ";
    os << endl;
    os << " vector a: ";
    os << translation_vectors[0][0] << " ";
    os << translation_vectors[0][1] << " ";
    os << translation_vectors[0][2] << " ";
    os << endl;
    os << " vector b: ";
    os << translation_vectors[1][0] << " ";
    os << translation_vectors[1][1] << " ";
    os << translation_vectors[1][2] << " ";
    os << endl;
    os << " vector c: ";
    os << translation_vectors[2][0] << " ";
    os << translation_vectors[2][1] << " ";
    os << translation_vectors[2][2] << " ";
    os << endl;
    return os;
  }

private:
  /**
   *  Calculation functions for the actual lattice parameters
   */

  /**
   *  Functions to calculate the a, b, c vectors from lattice constants 
   *  and angles.
   *   - a_vec()
   *   - b_vec()
   *   - c_vec()
   *   - alpha is angle between a and c
   *   - beta is angle between b and c
   *   - gamma is angle between a and b
   *   some other literatures reverses the alpha and beta
   *   This is translation from lattice constant to cartesian translational vectors, also called fractional coordinate translations.
   */
  threed_vector_type a_vec() const {
    threed_vector_type retval = { this->a(), 0.0e0, 0.0e0 };
    return retval;
  }

  threed_vector_type b_vec() const {
    threed_vector_type retval = { this->b() * cos( gamma() ), this->b() * sin( this->gamma() ), 0.0e0 };
    return retval;
  }

  threed_vector_type c_vec() const {
    threed_vector_type retval;
    retval.at(0) = this->c() * cos( this->alpha() );
    {
     retval.at(1) = 1.0e0/ ( this->b() * sin( this->gamma() ) ) *
      ( this->c() * this->b() * cos( this->beta() ) - 
        this->c() * this->b() * cos( this->gamma() ) * cos( this->alpha() ) );
    }
    retval.at(2) 
     = sqrt( pow( this->c(), 2 ) - pow( retval.at(0), 2) - pow( retval.at(1), 2 ) );
    return retval;
  }

public:
  /**
   *   + compute_translation_coefficient_for_point()
   *     Given the coordinate of an arbitrary point in the space,
   *     compute and return the coefficients of basis vectors.
   *     Invokes the ax_b() function to actually solve the coefficients.
   */
  coefficient_vector_type 
  compute_translational_coeffcient_for_point( coordinate_type coordinate ) const {
    threed_vector_type coordinate_copy;
    coordinate_copy[0] = get<0>( coordinate );
    coordinate_copy[1] = get<1>( coordinate );
    coordinate_copy[2] = get<2>( coordinate );
    coefficient_vector_type  coefficient_vector;
    coefficient_vector.fill(0.0e0);
    translation_basis_matrix_type basis_matrix
      = translation_basis_matrix();
    ax_b( basis_matrix.data(), coordinate_copy.data(), 
          coefficient_vector.data(), 3 );
    return coefficient_vector;
  }

public:
  /**
   *  Accessors 
   */
  length_set_type length_set() const
    { return this->length_set_; }
  angle_set_type  angle_set()  const
    { return this->angle_set_; }

  /**
   *  Auxiliary accessors (actually can be more useful)
   */
  length_data_type a() const 
    { return get<0> ( this->length_set_ ); }
  length_data_type b() const 
    { return get<1> ( this->length_set_ ); }
  length_data_type c() const 
    { return get<2> ( this->length_set_ ); }
  angle_data_type alpha() const 
    { return get<0> ( this->angle_set_ ); }
  angle_data_type beta() const 
    { return get<1> ( this->angle_set_ ); }
  angle_data_type gamma() const 
    { return get<2> ( this->angle_set_ ); }


  /**
   *   + primtive_translational_vectors()
   *     Computes primitive translational vectors on the fly
   *     from the lattice constants and angles.
   *     Invokes the a, b, c algorithms.
   */
  primitive_translation_vectors_type primitive_translation_vectors() const {
    // the order must be maintained
    threed_vector_type a_vec = this->a_vec();
    threed_vector_type b_vec = this->b_vec();
    threed_vector_type c_vec = this->c_vec();
    return array < threed_vector_type, 3 > { a_vec, b_vec, c_vec };
  }

  /**
   *   These functions return a component of the 
   *   primitive translation vectors, but rely on a 
   *   call to the actual computing function primitive_translation_vectors()
   */
  threed_vector_type a_vector() 
    { return this->primitive_translation_vectors().at(0); }
  threed_vector_type b_vector()
    { return this->primitive_translation_vectors().at(1); }
  threed_vector_type c_vector()
    { return this->primitive_translation_vectors().at(2); }

  /**
   *   This function converts the translation vectors to a 3 x 3 matrix
   *   to be store in array< double, 9 >.
   *   It is an interface function for matrix manipulations;
   */
  translation_basis_matrix_type translation_basis_matrix() const {
    primitive_translation_vectors_type translation_vectors 
      = this->primitive_translation_vectors();
    translation_basis_matrix_type basis_matrix = 
      { translation_vectors[0][0], translation_vectors[0][1], translation_vectors[0][2],
        translation_vectors[0][0], translation_vectors[0][1], translation_vectors[0][2],
        translation_vectors[0][0], translation_vectors[0][1], translation_vectors[0][2] };
    return basis_matrix;
  }

  /**
   *  Mutators
   *  Once the data are changed, the output translational vectors will also 
   *  change. But we allow developers to change change these data.
   */
  length_set_ref set_length_set()
    { return this->length_set_; }
  angle_set_ref set_angle_set()
    { return this->angle_set_; }

private:
  /**
   *  Here we only store the lattice constants and angles
   *  Translational vectors will be computed on the fly, so that 
   *  we don't have verbose storage of data, a 3 x 3 matrix 
   *  creates very little overhead.
   */
  length_set_type                     length_set_;
  angle_set_type                      angle_set_;

}; // end of struct LatticeParameter

} // end of namespace structure

} // end of namespace iquads

#endif
