#ifndef UNIT_CELL_BASE_H
#define UNIT_CELL_BASE_H

#include <vector>
#include <string>
#include <iostream>
#include <tuple>
#include "utilities/solid_gen/threed_space.h"

using namespace std;

namespace iquads{

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
   return within_radius;
  }
 
  unit_cell_base <class node_type> 
  translational_duplicate( tuple<int, int, int> direction ){
   double a = get<0>( direction );
   double b = get<1>( direction );
   double c = get<2>( direction );
   return duplicate( a, b, c );
  }
 
  unit_cell_base < class node_type > 
  translational_duplicate( double a, double b, double c ){
   unit_cell_base <node_type> copy;
   size_t n_node_local = this->store.size();
   for( size_t inode = 0; inode < n_node_local; inode++ ){
    node_type new_node = this->store.at(inode);
    new_node += this->get_trans_vector_a() * a;
    new_node += this->get_trans_vector_b() * b;
    new_node += this->get_trans_vector_c() * c;
    copy.add_node( new_node );
   }
   return copy;
  } 

  void operator+= ( array<double, double, double> disp ){
   size_t n_node_local = this->store.size();
   for( size_t inode = 0; inode < n_node_local; inode++ ){
    this->store.at(inode) += disp;
   }
  }

  array< array<double, 2>, 3 > get_edges(){
   array< array<double, 2>, 3 > retval;
   size_t n_node_local = this->store.size();
   double x_plus = 0.0e0;
   double x_minus = 0.0e0;
   double y_plus = 0.0e0;
   double y_minus = 0.0e0;
   double z_plus = 0.0e0;
   double z_minus = 0.0e0;
   for( size_t inode = 0; inode < n_node_local; inode++ ){
    array< array<double, double>, 3 > edges_node
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
   retval.at(0) = { x_plus, x_minus };
   retval.at(1) = { y_plus, y_minus };
   retval.at(2) = { z_plus, z_minus };
   return retval;
  }

  void print_info()
  {
   cout << "Unit Cell Info" << endl;
   cout << "Node List:" << endl;
   const size_t n_node = this->store.size();
   for( size_t inode = 0; i < n_node; inode++ ){
    cout << " node " << inode << endl;
    node_type node_local = store.at(inode);
    node_local.print_info();
   }
   cout << "Crystal Constants" << endl;
   this->constants.print_info();
  } // end of print_info()

  
 
public:
  node_type  get_node( size_t i ) const { return store.at(i); }
  node_type& set_node( size_t i ) { return store.at(i); }
  void resize( size_t n ) { this->store_.resize(n); }
  vector< node_type >  get_store() const { return this->store_; }
  vector< node_type >& set_store() { return this->store_; }

  size_t get_n_node() const { return this->store.size(); }

  // lattice constant
  array<double, 3> get_trans_vector_a() const 
   { return this->constants.get_trans_vector_a(); }
  array<double, 3> get_trans_vector_b() const
   { return this->constants.get_trans_vector_b(); }
  array<double, 3> get_trans_vector_c() const
   { return this->constants.get_trans_vector_c(); }

private:
  vector< node_type > store;
  lattice_parameters constants;

}; // end of struct unit_cell_base

} // end of namespace crystal

} // end of namespace iquads

#endif
