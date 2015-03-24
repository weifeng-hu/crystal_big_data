#ifndef ATOM_H
#define ATOM_H

#include <string>
#include <tuple>

using namespace std;

namespace iquads{

namespace crystal{

typedef tuple< double, double, double > coord_atom;

struct atom{
public:
 atom(){
  this->element = "not set";
  this->x = 0.0e0;
  this->y = 0.0e0;
  this->z = 0.0e0;
  this->charge = 0;
 }
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
  coord_atom single_set = tuple< double, double, double >( x, y, z );
  return single_set;
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

}

}

#endif
