#ifndef EUCLIDEAN_DISTANCE_MATRIX_H
#define EUCLIDEAN_DISTANCE_MATRIX_H

/*
###################################################

  Euclidean distance matrix class

###################################################
*/

#include <stdlib.h>
#include <math.h>
#include <string>
#include <tuple>
#include <iostream>
#include "utilities/solid_gen/coordinate.h"
#include "utilities/solid_gen/atom.h"
#include "utilities/solid_gen/threed_space.h"
#include "blas/blas_interface.h"

using namespace std;

namespace iquads {

using namespace matrix;
using namespace threed_space;

namespace crystal {

// Euclidean distance matrix class
struct euclidean_distance_matrix
{
public:
  euclidean_distance_matrix(){
   this->n_element_ = 0;
   this->element_list.resize(0);
   this->is_diagonalized_ = false;
  }
  euclidean_distance_matrix( size_t n_element ){
   this->init( n_element );
  }

public:
  void init( size_t n_element ){
   this->n_element_ = n_element;
   this->distance_matrix.init( n_element, n_element );
   this->eigvec.init( n_element, n_element );
   this->eigval.init( n_element, 1 );
   this->element_list.resize( n_element );
   this->is_diagonalized_ = false;
  }
  void compose_from_atomlist( AtomList new_atom_list ){
   const size_t natom = new_atom_list.size();
   this->init( natom );
   for( size_t iatom = 0; iatom < natom; iatom++ ){
    this->set_element(iatom) = new_atom_list[iatom].get_element();
   }
   for( size_t iatom = 0; iatom < natom; iatom++ ){
    Coord coord_i = new_atom_list[iatom].get_coordinate_set();
    for( size_t jatom = 0; jatom < natom; jatom++ ){
     Coord coord_j = new_atom_list[jatom].get_coordinate_set();
     this->set_matrix_element( iatom, jatom ) 
        = compute_distance( coord_i, coord_j );
    }
   }
  }
  void diagonalise(){
   symmetric_diag( &(this->distance_matrix), &(this->eigvec), &(this->eigval) );
   this->is_diagonalized_ = true;
  };

  void print_eigen_pairs(){
   if( this->is_diagonalized_ == false ){
   }
  }
  void print_matrix(){
  }

public:
  vector<double> get_eigval() const { return this->eigval; }

public:
  double& operator() ( int i, int j ) 
   { return set_matrix_element( i, j ); }
  string& set_element( int i  ) 
   { return element.at(i); }

private:
  // element access
  double& set_matrix_element( int i, int j ) 
   { return distance_matrix(i * n_element + j); }

private:
  DMatrixHeap distance_matrix;   // 2-d array to store distance
  DMatrixHeap eigvec;
  DMatrixHeap eigval;
  vector<string> element_list;      // 1-d array to store elements
  size_t n_element_;        // length of this->element_list
  bool is_diagonalized_;

};

} // end of crystal

} // end of iquads

#endif
