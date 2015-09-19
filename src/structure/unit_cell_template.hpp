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

#ifndef UNIT_CELL_TEMPLATE_HPP
#define UNIT_CELL_TEMPLATE_HPP

#include <vector>
#include <string>
#include <iostream>
#include <tuple>
#include <geometrical_space/threed_space.hpp>
#include <structure/lattice_parameter.hpp>

using std::cout;
using std::endl;
using std::tuple;

namespace iquads {

using namespace geometrical_space :: threed_space;
using std :: vector;
using std :: string;

  /**
   *   A template class to represent primitive unit cells in crystals
   *
   *   It is designed to be a template class, with the template
   *   parameter as node type. to be instantiated as molecular 
   *   unit cells or atomic unit cells, thus can be used for 
   *   ionic, molecular, and atomic crystals.
   *
   *   Data members are:
   *    + a list of nodes in the unit cell
   *    + lattice parameter
   *
   *   These are external quantities of an unit cell
   *    + unit cell id
   *    + translational vector from the original primitive cell
   */

namespace structure {

template < class NodeType > class UnitCell {
public:
  typedef vector<NodeType> node_list_type;
  typedef LatticeParameter lattice_parameter_type;
  typedef unsigned int     cell_id_type;
  typedef array< int, 3 >  translation_

public:
  void add_node( NodeType new_node )
   {
    this->store.push_back(new_node);
   }

  bool within_radius( double Radius )
   {
    size_t n_node_local = this->store.size();
    bool within_radius_local = true;
    for( size_t inode = 0; inode < n_node_local; inode++ ){
     NodeType node_local = store.at(inode);
     if( node_local.within_radius( Radius ) == false ){
      within_radius_local = false;
      break;
     }
    }
    return within_radius_local;
   }
 
  UnitCell<NodeType> 
   translational_duplicate( tuple<int, int, int> direction )
   {
    using std::get;
    int a = get<0>( direction );
    int b = get<1>( direction );
    int c = get<2>( direction );
    return this->translational_duplicate( a, b, c );
   }

  UnitCell<NodeType> 
  translational_duplicate( int a_, int b_, int c_ )
   {
    double a = a_;
    double b = b_;
    double c = c_;
    UnitCell <NodeType> copy;
    copy.set_translation_vec() = array<int, 3> { a_, b_, c_ };
    copy.set_constants() = this->get_constants();
    size_t n_node_local = this->store.size();
    for( size_t inode = 0; inode < n_node_local; inode++ ){
     NodeType new_node = this->store.at(inode);
     new_node.set_translation_vec() = array<int, 3> { a_, b_, c_ };
     new_node += this->get_trans_vector_a() * a;
     new_node += this->get_trans_vector_b() * b;
     new_node += this->get_trans_vector_c() * c;
     copy.add_node( new_node );
    }
    return copy;
   } 

  void operator+= ( array<double, 3> disp )
   {
    size_t n_node_local = this->store.size();
    for( size_t inode = 0; inode < n_node_local; inode++ ){
     this->store.at(inode) += disp;
    }
   }

  friend 
   ifstream& operator>> ( ifstream& ifs, UnitCell<NodeType>& cell )
    {
     size_t n_node;
     ifs >> n_node;
     for( size_t inode = 0; inode < n_node; inode++ ){
      NodeType node_i;
      ifs >> node_i;
      cell.add_node( node_i );
     }
     LatticeParameters lp;
     ifs >> lp;
     cell.set_constants() = lp;
     return ifs;
    }

  friend
   ostream& operator<< ( ostream& os, UnitCell<NodeType>& cell )
   {
    const size_t n_node = cell.get_n_node();
    for( size_t inode = 0; inode < n_node; inode++ ){
     NodeType node_i = cell.get_node( inode );
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
    NodeType node_local = store.at(inode);
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
    NodeType node_local = store.at(inode);
    node_local.print_atomlist();
   }
  }

public:
  /**
   *  Container-related overloaded functions
   */

  /**
   *   + at()
   *     We do not perform range check for index i, leaving
   *     it to the at() function of std :: vector.
   */
  NodeType& at( size_t i )
    { return this->node_list_.at(i) }
  vector< NodeType >  get_store() const { return this->store; }
  vector< NodeType >& set_store() { return this->store; }
  LatticeParameters& set_constants() { return this->constants; }
  LatticeParameters  get_constants() const { return this->constants; }

  size_t get_n_node() const { return this->store.size(); }

public:
  /**
   *  Accessors
   *
   */
  node

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
  node_list_type           node_list_;
  lattice_parameter_type   lattice_parameter_;
  cell_id_type             cell_id_;
  array<int, 3> translation_vec;

}; // end of class UnitCell

} // end of namespace structure

} // end of namespace iquads

#endif
