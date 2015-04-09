#ifndef LATTICE_BASE_H
#define LATTICE_BASE_H

#include <stdlib.h>
#include <string>
#include <tuple>
#include <vector>
#include <array>
#include <iostream>
#include "utilities/solid_gen/threed_space_function.h"

using namespace std;

namespace iquads {

namespace crystal {

template< class unit_cell >
struct lattice_base {
public:
  lattice_base() {
   this->reset();
  }

public:
  void reset(){
   this->store.resize(0);
   this->na = 0;
   this->nb = 0;
   this->nc = 0;
   this->unit_cell_is_set_ = false;
  }

  array< array<double, double>, 3 > get_edges(){
   array< array<double, double>, 3 > retval;
   size_t n_cell_local = this->store.size();
   double x_plus = 0.0e0;
   double x_minus = 0.0e0;
   double y_plus = 0.0e0;
   double y_minus = 0.0e0;
   double z_plus = 0.0e0;
   double z_minus = 0.0e0;
   for( size_t icell = 0; icell < n_cell_local; icell++ ){
    array< array<double, double>, 3 > edges_cell
     = this->store.at(icell).get_edges();
    if( ( edges_cell.at(0).at(0) - x_plus ) >= 1.0e-5 )
     { x_plus = edges_cell.at(0).at(0); }
    if( ( edges_cell.at(1).at(0) - y_plus ) >= 1.0e-5 )
     { y_plus = edges_cell.at(1).at(0); }
    if( ( edges_cell.at(2).at(0) - z_plus ) >= 1.0e-5 )
     { z_plus = edges_cell.at(2).at(0); }

    if( ( edges_cell.at(0).at(1) - x_minus ) <= -1.0e-5 )
     { x_minus = edges_cell.at(0).at(1); }
    if( ( edges_cell.at(1).at(1) - y_minus ) <= -1.0e-5 )
     { y_minus = edges_cell.at(1).at(1); }
    if( ( edges_cell.at(2).at(1) - z_minus ) <= -1.0e-5 )
     { z_minus = edges_cell.at(2).at(1); }
   }
   retval.at(0) = { x_plus, x_minus };
   retval.at(1) = { y_plus, y_minus };
   retval.at(2) = { z_plus, z_minus };
   return retval;
  }

  void recenter(){
   array< double, double, double > recenter_vec
    = threed_space :: compute_recenter_vec( this->get_edges() );
   size_t n_node_local = this->store.size();
   for( size_t inode = 0; inode < n_node_local; inode++ ){
    this->store.at(inode) += recenter_vec.at(0);
    this->store.at(inode) += recenter_vec.at(1);
    this->store.at(inode) += recenter_vec.at(2);
   }
  } // end of recenter() 

  void set_primitive( unit_cell prim ){
   this->primitive = prim;
   this->unit_cell_is_set_ = true;
  } // end of set_primitive()
  bool unit_cell_is_set() { return unit_cell_is_set_; }

public:
  void generate_cell( size_t la, size_t lb, size_t lc ){
   if( unit_cell_is_set_ == false ){
    cout << " error: unit cell is not defined " << endl;
    abort();
   }
   for( size_t i = 0; i < la; i++ ){
    for( size_t j = 0; j < lb; j++ ){
     for( size_t k = 0; k < lc; k++ ){
      tuple< int, int, int > direction = make_tuple( i, j, k );
      unit_cell copy = primitive.translational_duplicate( direction );
      store.push_back( cell_copy );
     }
    }
   }
  }

  void generate( tuple<int, int, int> nunits ){
   size_t a = get<0>( nunits );
   size_t b = get<1>( nunits );
   size_t c = get<2>( nunits );
   generate_cell( a, b, c );
  }

  void print_info(){
   cout << "Lattice Info" << endl;
   for( size_t icell = 0; icell < store.size(); icell++ ){
    cout << " Unit Cell " << icell << endl;
    unit_cell unit_cell_local = store.at(icell);
    unit_cell_local.print_info();
   }
  }

  unit_cell get_cell( size_t i ) const { return this->store.at(i); }

private:
  vector< unit_cell > store;
  unit_cell primitive;
  size_t na, nb, nc;
  bool unit_cell_is_set_;

}; // end of struct lattice_base

} // end of namespace crystal

} // end of namespace iquads

#endif
