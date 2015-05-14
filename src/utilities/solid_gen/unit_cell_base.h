/*
 *  This source code applies all the terms in 
 *  GNU GENERAL PUBLIC LICENSE (GPL), Version3, 29 June 2007.
 *
 *  Copyright (C) 2013-2015 Weifeng Hu, all rights reserved.
 *  
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef UNIT_CELL_BASE_H
#define UNIT_CELL_BASE_H

#include <vector>
#include <string>
#include <iostream>
#include <tuple>
#include "utilities/solid_gen/threed_space.h"
#include "utilities/solid_gen/lattice_parameters.h"

using namespace std;

namespace iquads{

using namespace threed_space;

namespace crystal{

template < class node_type >
struct unit_cell_base
{
public:
  void add_node( node_type new_node ){
   this->store.push_back(new_node);
  }

  bool within_radius( double Radius ){
   size_t n_node_local = this->store.size();
   bool within_radius_local = true;
   for( size_t inode = 0; inode < n_node_local; inode++ ){
    node_type node_local = store.at(inode);
    if( node_local.within_radius( Radius ) == false ){
     within_radius_local = false;
     break;
    }
   }
   return within_radius_local;
  }
 
  unit_cell_base<node_type> 
  translational_duplicate( tuple<int, int, int> direction ){
   int a = get<0>( direction );
   int b = get<1>( direction );
   int c = get<2>( direction );
   return this->translational_duplicate( a, b, c );
  }
  unit_cell_base<node_type> 
  translational_duplicate( int a_, int b_, int c_ ){
   double a = a_;
   double b = b_;
   double c = c_;
   unit_cell_base <node_type> copy;
   copy.set_translation_vec() = array<int, 3> { a_, b_, c_ };
   copy.set_constants() = this->get_constants();
   size_t n_node_local = this->store.size();
   for( size_t inode = 0; inode < n_node_local; inode++ ){
    node_type new_node = this->store.at(inode);
    new_node.set_translation_vec() = array<int, 3> { a_, b_, c_ };
    new_node += this->get_trans_vector_a() * a;
    new_node += this->get_trans_vector_b() * b;
    new_node += this->get_trans_vector_c() * c;
    copy.add_node( new_node );
   }
   return copy;
  } 

  void operator+= ( array<double, 3> disp ){
   size_t n_node_local = this->store.size();
   for( size_t inode = 0; inode < n_node_local; inode++ ){
    this->store.at(inode) += disp;
   }
  }

  friend 
  ifstream& operator>> ( ifstream& ifs, unit_cell_base<node_type>& cell ){
   size_t n_node;
   ifs >> n_node;
   for( size_t inode = 0; inode < n_node; inode++ ){
    node_type node_i;
    ifs >> node_i;
    cell.add_node( node_i );
   }
   lattice_parameters lp;
   ifs >> lp;
   cell.set_constants() = lp;
   return ifs;
  }

  friend
  ostream& operator<< ( ostream& os, unit_cell_base<node_type>& cell ){
   const size_t n_node = cell.get_n_node();
   for( size_t inode = 0; inode < n_node; inode++ ){
    node_type node_i = cell.get_node( inode );
    os << node_i << endl;
   }
   return os;
  }

  array< array<double, 2>, 3 > get_edges(){
   array< array<double, 2>, 3 > retval;
   size_t n_node_local = this->store.size();
   double x_plus  = this->store.at(0).get_edges().at(0).at(0); 
   double x_minus = this->store.at(0).get_edges().at(0).at(1); 
   double y_plus  = this->store.at(0).get_edges().at(1).at(0); 
   double y_minus = this->store.at(0).get_edges().at(1).at(1); 
   double z_plus  = this->store.at(0).get_edges().at(2).at(0); 
   double z_minus = this->store.at(0).get_edges().at(2).at(1); 
   for( size_t inode = 0; inode < n_node_local; inode++ ){
    array< array<double, 2>, 3 > edges_node
     = this->store.at(inode).get_edges();
    if( ( edges_node.at(0).at(0) - x_plus ) >= 1.0e-5 )
     { x_plus = edges_node.at(0).at(0); }
    if( ( edges_node.at(1).at(0) - y_plus ) >= 1.0e-5 )
     { y_plus = edges_node.at(1).at(0); }
    if( ( edges_node.at(2).at(0) - z_plus ) >= 1.0e-5 )
     { z_plus = edges_node.at(2).at(0); }

    if( ( edges_node.at(0).at(1) - x_minus ) <= -1.0e-5 )
     { x_minus = edges_node.at(0).at(1); }
    if( ( edges_node.at(1).at(1) - y_minus ) <= -1.0e-5 )
     { y_minus = edges_node.at(1).at(1); }
    if( ( edges_node.at(2).at(1) - z_minus ) <= -1.0e-5 )
     { z_minus = edges_node.at(2).at(1); }
   }
   retval.at(0) = array<double, 2> { x_plus, x_minus };
   retval.at(1) = array<double, 2> { y_plus, y_minus };
   retval.at(2) = array<double, 2> { z_plus, z_minus };
   return retval;
  }

  void print_info()
  {
   cout << "Unit Cell Info" << endl;
   cout << "{" << endl;
   cout << "Node List:" << endl;
   const size_t n_node = this->store.size();
   for( size_t inode = 0; inode < n_node; inode++ ){
    cout << "Node " << inode << endl;
    cout << "{" << endl;
    node_type node_local = store.at(inode);
    node_local.print_info();
    cout << "}" << endl;
   }
   cout << "Crystal Constants" << endl;
   this->constants.print_info();
   cout << "}" << endl;
  } // end of print_info()

  void print_atomlist()
  {
   const size_t n_node = this->store.size();
   for( size_t inode = 0; inode < n_node; inode++ ){
    node_type node_local = store.at(inode);
    node_local.print_atomlist();
   }
  }

public:
  node_type  get_node( size_t i ) const { return store.at(i); }
  node_type& set_node( size_t i ) { return store.at(i); }
  void resize( size_t n ) { this->store.resize(n); }
  vector< node_type >  get_store() const { return this->store; }
  vector< node_type >& set_store() { return this->store; }
  lattice_parameters& set_constants() { return this->constants; }
  lattice_parameters  get_constants() const { return this->constants; }

  size_t get_n_node() const { return this->store.size(); }

  // lattice constant
  array<double, 3> get_trans_vector_a() const 
   { return this->constants.get_trans_vector_a(); }
  array<double, 3> get_trans_vector_b() const
   { return this->constants.get_trans_vector_b(); }
  array<double, 3> get_trans_vector_c() const
   { return this->constants.get_trans_vector_c(); }

  array<int, 3>& set_translation_vec()
   { return this->translation_vec; }

private:
  vector< node_type > store;
  lattice_parameters constants;
  array<int, 3> translation_vec;

}; // end of struct unit_cell_base

} // end of namespace crystal

} // end of namespace iquads

#endif