#include <string>
#include <tuple>
#include <vector>
#include <stdlib.h>

namespace iquads{

using namespace std;

namespace crystal{

struct atom{
 typedef tuple< string, double, double, double > coord_atom;

public:
 atom( string elem, double cx, double cy, double cz, int chrg ){
  this->element = elem;
  this->x = cx;
  this->y = cy;
  this->z = cz;
  this->charge = chrg;
 }

public:
 string get_element() const { return element; }
 double get_x() const { return x; }
 double get_y() const { return y; }
 double get_z() const { return z; }
 int get_charge() const { return charge; }
 coord_atom get_coord(){
  const coord_atom single_set = make_tuple< string, double, double, double >( element, x, y, z );
  return coord_atom;
 }

 string& set_element() { return element; }
 double& set_x() { return x; }
 double& set_y() { return y; }
 double& set_z() { return z; }
 int& set_charge() { return charge; }

private:
 std::string element;
 double x, y, z;
 int charge;

};

struct unit_cell{

public:
 void add_atom( atom at ){
  store_.push_back(at);
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
   const double r_x = lc_a * a;
   const double r_y = lc_b * b;
   const double r_z = lc_c * c;
   double R_x_new = store_.at(i).get_x() + r_x;
   double R_y_new = store_.at(i).get_y() + r_y;
   double R_z_new = store_.at(i).get_z() + r_z;
   atom new_atom( this->element, R_x_new, R_y_new, R_z_new, this->charge );
   copy.add_atom( new_atom );
  }
  return copy;
 }

public:
 vector< atom > get_store() const { return store_; }
 double get_a() const { return lc_a; }
 double get_b() const { return lc_b; }
 double get_c() const { return lc_c; }
 atom get_atom( size_t i ) const { return store_.at(i); }

private:
 vector< atom > store_;
 double lc_a, lc_b, lc_c;

};

struct cell{
public:
 cell(){
  this->store_.resize(0);
  this->unit_cell_is_set_ = false;
 }

public:
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
     unit_cell cell_copy = primary.duplicate( direction );
     store_.push_back( cell_copy );
    }
   }
  }
 }
 void generate_cell( size_t l ){
  generate_cell( l, l, l );
 }

private:
 unit_cell primary;
 vector< unit_cell > store_;
 double len_a, len_b, len_c;
 bool unit_cell_is_set_;

};

} // end of crystall

} // end of iquads
