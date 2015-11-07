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

#ifndef EUCLIDEAN_DISTANCE_MATRIX_HPP
#define EUCLIDEAN_DISTANCE_MATRIX_HPP

#include <stdlib.h>
#include <math.h>
#include <string>
#include <tuple>
#include <iostream>
#include <geometrical_space/threed_space_function.hpp>
#include <structure/atom.hpp>
#include <blas/blas_interface.h>
#include <matrix/matrix_typedef.hpp>
#include <matrix/matrix_function.hpp>

namespace iquads {

namespace structure {

// Euclidean distance matrix class
struct EuclideanDistanceMatrix {
public:
  typedef matrix :: DMatrixHeap matrix_type;
  typedef std :: vector< std :: string > element_name_list_type;

public:
  EuclideanDistanceMatrix() {
    this->element_name_list_.resize(0);
    this->is_diagonalized_ = false;
  }
  EuclideanDistanceMatrix( size_t n_element ) {
    this->distance_matrix_.resize( n_element, n_element );
    this->eigvec_.resize( n_element, n_element );
    this->eigval_.resize( n_element, 1 );
    this->element_name_list_.resize( n_element );
    this->is_diagonalized_ = false;
  }

public:
  void compose_from_atomlist( const AtomList& atom_list_obj ) {
    const size_t natom = atom_list_obj.size();
    this->resize( natom );
   // std :: cout << "natom " << natom << std :: endl;
    for( size_t iatom = 0; iatom < natom; iatom++ ) {
      this->set_element_name(iatom) = atom_list_obj[iatom].element_name();
    }
    for( size_t iatom = 0; iatom < natom; iatom++ ) {
      iquads :: geometrical_space :: threed_space :: Coord coord_i = atom_list_obj[iatom].coordinate();
      const int charge_i = atom_list_obj[iatom].charge();
      for( size_t jatom = 0; jatom < natom; jatom++ ) {
        iquads :: geometrical_space :: threed_space :: Coord coord_j = atom_list_obj[jatom].coordinate();
        const int charge_j = atom_list_obj[jatom].charge();
        this->at( iatom, jatom ) = iquads :: geometrical_space :: threed_space :: compute_distance( coord_i, coord_j );
        // this->at( iatom, jatom ) 
        //  = compute_charge_weighted_distance( coord_i, coord_j, charge_i, charge_j );
      }
    }
  }
  void diagonalise() {
    iquads :: matrix :: symmetric_diag_big( this->distance_matrix_, this->eigvec_, this->eigval_ );
    this->is_diagonalized_ = true;
  }
  void print_eigval() {
    for( size_t i = 0; i < this->eigval_.nrow(); i++ ) {
      double value = this->eigval_(i, 0);
      std :: cout << value << " ";
    }
    std :: cout << std :: endl;
  }

public:
  matrix_type distance_matrix() const
    { return this->distance_matrix_; }
  matrix_type eigval() const
    { return this->eigval_; }
  matrix_type eigvec() const
    { return this->eigvec_; }
  element_name_list_type element_name_list() const
    { return this->element_name_list_; }
  void resize( size_t i ) {
    this->distance_matrix_.resize( i, i );
    this->eigvec_.resize( i, i );
    this->eigval_.resize( i, 1 );
    this->element_name_list_.resize( i );
    this->is_diagonalized_ = false;
  }
  std :: string& set_element_name( int i  )
    { return this->element_name_list_.at(i); }
  double& at( size_t i, size_t j ) 
    { return this->distance_matrix_( i , j ); }

private:
  matrix_type distance_matrix_;               // 2-d array to store distance
  matrix_type eigvec_;
  matrix_type eigval_;
  element_name_list_type element_name_list_;  // 1-d array to store elements
  bool is_diagonalized_;

}; // end of struct EuclideanDistanceMatrix

} // end of namespace crystal

} // end of namespace iquads

#endif
