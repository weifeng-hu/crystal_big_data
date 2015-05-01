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

using namespace threed_space;

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

  array< array<double, 2>, 3 > get_edges(){
   array< array<double, 2>, 3 > retval;
   size_t n_cell_local = this->store.size();
   double x_plus  = this->store.at(0).get_edges().at(0).at(0); 
   double x_minus = this->store.at(0).get_edges().at(0).at(1); 
   double y_plus  = this->store.at(0).get_edges().at(1).at(0); 
   double y_minus = this->store.at(0).get_edges().at(1).at(1); 
   double z_plus  = this->store.at(0).get_edges().at(2).at(0); 
   double z_minus = this->store.at(0).get_edges().at(2).at(1); 
   for( size_t icell = 0; icell < n_cell_local; icell++ ){
    array< array<double, 2>, 3 > edges_cell
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
   retval.at(0) = array<double,2>{ x_plus, x_minus };
   retval.at(1) = array<double,2>{ y_plus, y_minus };
   retval.at(2) = array<double,2>{ z_plus, z_minus };
   return retval;
  }

  void recenter(){
   cout << "Re-centering lattice ..." << endl;
   array< array<double,2>, 3 > lattice_edges = this->get_edges();
   {
    cout << "  Original lattice edges: " << endl;
    cout << "  x:  [ " << lattice_edges.at(0).at(0) << " <--> " << lattice_edges.at(0).at(1) << " ]" << endl;
    cout << "  y:  [ " << lattice_edges.at(1).at(0) << " <--> " << lattice_edges.at(1).at(1) << " ]" << endl;
    cout << "  z:  [ " << lattice_edges.at(2).at(0) << " <--> " << lattice_edges.at(2).at(1) << " ]" << endl;
   }
   array< double, 3> recenter_vec
    = compute_recenter_vec( lattice_edges );
   {
    cout << "  Recenter vector:" << endl;
    cout << "  [ ";
    cout << recenter_vec.at(0) << " " << recenter_vec.at(1) << " " << recenter_vec.at(2);
    cout << " ]";
    cout << endl;
   }
   size_t n_node_local = this->store.size();
   for( size_t inode = 0; inode < n_node_local; inode++ ){
    this->store.at(inode) += recenter_vec;
   }
   array< array<double,2>, 3> new_lattice_edges = this->get_edges();
   {
    cout << "  Adjusted lattice edges: " << endl;
    cout << "  x:  [ " << new_lattice_edges.at(0).at(0) << " <--> " << new_lattice_edges.at(0).at(1) << " ]" << endl;
    cout << "  y:  [ " << new_lattice_edges.at(1).at(0) << " <--> " << new_lattice_edges.at(1).at(1) << " ]" << endl;
    cout << "  z:  [ " << new_lattice_edges.at(2).at(0) << " <--> " << new_lattice_edges.at(2).at(1) << " ]" << endl;
   }
  } // end of recenter() 

  void set_primitive( unit_cell prim ){
   this->primitive = prim;
   this->unit_cell_is_set_ = true;
  } // end of set_primitive()
  bool unit_cell_is_set() { return unit_cell_is_set_; }

public:
  void generate_cell( size_t la, size_t lb, size_t lc ){
   cout << "Generating lattice from unit cell ... " << endl;
   cout << "  Times of duplication:" << endl;
   cout << "  a direction: " << la << "\tb direction: " << lb << "\tc direction: " << lc << endl;
   if( unit_cell_is_set_ == false ){
    cout << "error: unit cell is not defined " << endl;
    abort();
   }
   for( size_t i = 0; i < la; i++ ){
    for( size_t j = 0; j < lb; j++ ){
     for( size_t k = 0; k < lc; k++ ){
      tuple< int, int, int > direction = make_tuple( i, j, k );
      unit_cell copy = primitive.translational_duplicate( direction );
      store.push_back( copy );
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

  void print_atomlist(){
   cout << "Atom List" << endl;
   for( size_t icell = 0; icell < store.size(); icell++ ){
    unit_cell unit_cell_local = store.at(icell);
    unit_cell_local.print_atomlist();
   }
  }

  friend 
  ostream& operator<< ( ostream& os, lattice_base<unit_cell>& lattice ){
   const size_t n_cell = lattice.get_ncell();
   for( size_t icell = 0; icell < n_cell; icell++ ){
    unit_cell cell_i = lattice.get_cell(icell);
    os << cell_i << endl;
   }
   return os;
  }

  unit_cell get_cell( size_t i ) const { return this->store.at(i); }
  size_t get_ncell() const { return this->store.size(); }

private:
  vector< unit_cell > store;
  unit_cell primitive;
  size_t na, nb, nc;
  bool unit_cell_is_set_;

}; // end of struct lattice_base

} // end of namespace crystal

} // end of namespace iquads

#endif
