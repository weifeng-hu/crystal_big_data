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


#ifndef LATTICE_TEMPLATE_HPP
#define LATTICE_TEMPLATE_HPP

#include <stdlib.h>
#include <string>
#include <tuple>
#include <vector>
#include <array>
#include <iostream>
#include <geometrical_space/threed_space_function.hpp>

using std::string;
using std::tuple;
using std::vector;
using std::array;
using std::cout;
using std::endl;

namespace iquads {

using namespace geometrical_space :: threed_space;

namespace structure {

template < class UnitCell_Type >
struct Lattice {
public:
  Lattice() {
   this->reset();
  }

public:
  typedef typename UnitCell_Type unit_cell_type;

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

  void set_primitive( unit_cell_type prim ){
   this->primitive = prim;
   this->lp = prim.get_constants();
   this->unit_cell_is_set_ = true;
  } // end of set_primitive()
  bool unit_cell_is_set() { return unit_cell_is_set_; }

public:
  void generate_cell( size_t la, size_t lb, size_t lc )
   {
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
       unit_cell_type copy = primitive.translational_duplicate( direction );
       store.push_back( copy );
      }
     }
    }
   }

  void generate_cell_from_center( size_t la, size_t lb, size_t lc )
   {
    cout << "Generating lattice from unit cell, spread from center ... " << endl;
    cout << "  Times of duplication:" << endl;
    cout << "  a+ direction: " << la << "\tb+ direction: " << lb << "\tc+ direction: " << lc << endl;
    if( unit_cell_is_set_ == false ){
     cout << "error: unit cell is not defined " << endl;
     abort();
    }
    for( int i = -la; i <= la; i++ ){
     for( int j = -lb; j <= lb; j++ ){
      for( int k = -lc; k <= lc; k++ ){
       if( i == 0 && j == 0 && k == 0 ) continue;
       tuple< int, int, int > direction = make_tuple( i, j, k );
       unit_cell_type copy = primitive.translational_duplicate( direction );
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
   //generate_cell_from_center( a, b, c );
  }

  void print_info(){
   cout << "Lattice Info" << endl;
   for( size_t icell = 0; icell < store.size(); icell++ ){
    cout << " Unit Cell " << icell << endl;
    unit_cell_type unit_cell_local = store.at(icell);
    unit_cell_local.print_info();
   }
  }

  void print_atomlist(){
   cout << "Atom List" << endl;
   for( size_t icell = 0; icell < store.size(); icell++ ){
    unit_cell_type unit_cell_local = store.at(icell);
    unit_cell_local.print_atomlist();
   }
  }

  friend 
  ostream& operator<< ( ostream& os, lattice_base<unit_cell_type>& lattice ){
   const size_t n_cell = lattice.get_ncell();
   for( size_t icell = 0; icell < n_cell; icell++ ){
    unit_cell_type cell_i = lattice.get_cell(icell);
    os << cell_i << endl;
   }
   return os;
  }

  unit_cell_type get_cell( size_t i ) const { return this->store.at(i); }
  size_t get_ncell() const { return this->store.size(); }
  lattice_parameters get_constants() const { return this->lp; }

private:
  vector< unit_cell_type > store;
  unit_cell_type primitive;
  lattice_parameters lp;
  size_t na, nb, nc;
  bool unit_cell_is_set_;

}; // end of struct lattice_base

} // end of namespace structure

} // end of namespace iquads

#endif
