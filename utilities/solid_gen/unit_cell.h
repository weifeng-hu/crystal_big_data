#ifndef UNIT_CELL_H
#define UNIT_CELL_H

#include <vector>
#include <string>
#include <tuple>
#include "utilities/solid_gen/atom.h"
#include "utilities/solid_gen/eclidean_dis_mat.h"

using namespace std;

namespace iquads{

namespace crystal{

struct unit_cell
{
public:
 void add_atom( atom at ){
  store_.push_back(at);
 }
 bool out_of_range( double cutoff ){
  size_t natom = this->get_store().size();
  bool inside = true;
  for( size_t iatom = 0; iatom < natom; iatom++ ){
   coord_atom coord = store_.at(iatom).get_coord();
   coord_atom coord_zero = make_tuple ( 0.0e0, 0.0e0, 0.0e0 );
   double R = eclidean_dis_mat :: get_distance( coord, coord_zero );
   if( R > cutoff ){
    inside = false;
   }
  }
  return ( inside ? false : true );
 }

 unit_cell duplicate( tuple<int, int, int> direction ){
  int a = get<0>( direction );
  int b = get<1>( direction );
  int c = get<2>( direction );
  return duplicate( a, b, c );
 }

 unit_cell duplicate( int a, int b, int c ){
  unit_cell copy;
  size_t natoms = store_.size();
  for( size_t i = 0; i < natoms; i++ ){
   const string element = store_.at(i).get_element();
   const double r_x = lc_a * a;
   const double r_y = lc_b * b;
   const double r_z = lc_c * c;
   const int charge = store_.at(i).get_charge();
   double R_x_new = store_.at(i).get_x() + r_x;
   double R_y_new = store_.at(i).get_y() + r_y;
   double R_z_new = store_.at(i).get_z() + r_z;
   atom new_atom( element, R_x_new, R_y_new, R_z_new, charge );
   copy.add_atom( new_atom );
  }
  return copy;
 }

public:
 void resize( size_t n ) { this->store_.resize(n); }
 vector< atom > get_store() const { return store_; }
 double get_a() const { return lc_a; }
 double get_b() const { return lc_b; }
 double get_c() const { return lc_c; }
 atom get_atom( size_t i ) const { return store_.at(i); }
 atom& set_atom( size_t i ) { return store_.at(i); }

private:
 vector< atom > store_;
 double lc_a, lc_b, lc_c;

};

}

}

#endif
