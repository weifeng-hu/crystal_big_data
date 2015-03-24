#ifndef ECLIDEAN_DISTANCE_MAT_H
#define ECLIDEAN_DISTANCE_MAT_H

#include <stdlib.h>
#include <math.h>
#include <string>
#include <tuple>
#include <iostream>
#include "utilities/solid_gen/atom.h"
#include "utilities/solid_gen/fragment.h"
#include "blas/blas_interface.h"

using namespace std; 
namespace iquads{

namespace crystal{

// Eclidean distance matrix class
struct eclidean_dis_mat
{

public:
 eclidean_dis_mat( size_t n ){
  this->n_element = n_element; 
  const int length = n_element * n_element;
  this->store.resize( length );
  this->element.resize( this->n_element ); 
  this->is_diagonalized_ = false;
 }

 static double get_distance( tuple<double, double, double> coord1, 
                      tuple<double, double, double> coord2 ){
  double retval = 0.0e0;
  {
   const double x1 = get<0>(coord1);
   const double y1 = get<1>(coord1);
   const double z1 = get<2>(coord2);

   const double x2 = get<0>(coord1);
   const double y2 = get<1>(coord1);
   const double z2 = get<2>(coord2);

   const double dx = x1 - x2;
   const double dy = y1 - y2;
   const double dz = z1 - z2;

   const double dis_sqr = dx * dx + dy * dy + dz * dz;
   retval = sqrt( dis_sqr );
  }

   return retval;
  }

public:
 void compose( fragment big_frag ){
  this->n_element = n_element; 
  const int length = n_element * n_element;
  this->store.resize( length );
  this->element.resize( this->n_element );

  for( size_t i = 0; i < n_element; i++ ){
   this->set_element(i) = big_frag.get_element(i);
  }
  for( size_t i = 0; i < n_element; i++ ){
   tuple<double, double, double> coord_i = big_frag.get_coord(i);
   for( size_t j = 0; j < n_element; j++ ){
    tuple<double, double, double> coord_j = big_frag.get_coord(j);
    this->set( i, j ) = eclidean_dis_mat :: get_distance( coord_i, coord_j );
   }
  }
 
 };
 void diagonalise(){
  size_t length = n_element * n_element;
  eigvec.resize( length );
  eigval.resize( n_element );
  diag( store.data(), eigvec.data(), eigval.data(), n_element );
  this->is_diagonalized_ = true;
 };
 void print_eigen_pairs(){
  if( this->is_diagonalized_ == false ){
   cout << " error: the eclidean distance matrix has not been diagonalised yet " << endl;
   abort();
  }
  cout << " eigenvalues of the eclidean distance matrix: " << endl;
  for( size_t i = 0; i < n_element; i++ ){
   cout << "  eigval[" << i << "] = " << eigval.at(i) << endl;
  }
 };

public:
 vector<double> get_store() const { return this->store; }; 
 vector<double>& set_store() { return this->store; }; 
 vector<string> get_element() const { return this->element; };
 vector<string>& set_element() {  return this->element; };

 // element access
 double& set( int i, int j ) { return store.at( i * n_element + j ); }
 double& operator() ( int i, int j ) { return set( i, j ); }
 string& set_element( int i  ) { return element.at(i); }

private:
 vector<double> store;   // 2-d array to store distance
 vector<double> eigvec;
 vector<double> eigval;
 vector<string> element; // 1-d array to store index
 size_t n_element;       // length of this->element
 bool is_diagonalized_;

};

} // end of crystal

} // end of iquads

#endif
