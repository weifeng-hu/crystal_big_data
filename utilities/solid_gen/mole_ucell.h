#ifndef MOLE_UCELL_H
#define MOLE_UCELL_H

#include <vector>
#include <string>
#include <tuple>
#include <iostream>
#include "utilities/solid_gen/atom.h"
#include "utilities/solid_gen/molecule.h"

using namespace std;

namespace iquads{

namespace crystal{

struct mole_ucell{
public:
 mole_ucell(){
  this->primitive.resize(0);
  this->n_molecule = 0;
 }

public:
 void add_molecule( molecule new_mole ){
  this->primitive.push_back( new_mole );
  this->n_molecule += 1;
 }

 mole_ucell duplicate( tuple<int, int, int > set ){

 }
 mole_ucell duplicate_vertical( tuple<int, int, int> set ){
  int a = get<0>(set);
  int b = get<1>(set);
  int c = get<2>(set);
  mole_ucell copy;
  size_t n_moles = primitive.size();
  for( size_t imole = 0; imole < n_moles; imole++ ){
   molecule molex = primitive.at(imole);
   size_t n_atom = molex.get_natom();
   molecule new_molecule;
   new_molecule.set_name() = molex.get_name();
   for( size_t iatom = 0; iatom < n_atom; iatom++ ){
    atom atomx = molex.at(iatom);
    const string element = atomx.get_element();
    const int charge     = atomx.get_charge();
    const double R_x     = atomx.get_x();
    const double R_y     = atomx.get_y();
    const double R_z     = atomx.get_z();
    const double r_x     = lc_a * a;
    const double r_y     = lc_b * b;
    const double r_z     = lc_c * c;
    const double R_x_new = R_x + r_x;
    const double R_y_new = R_y + r_y;
    const double R_z_new = R_z + r_z;
    atom new_atom( element, R_x_new, R_y_new, R_z_new, charge );
    new_molecule.add_atom( new_atom );
   }
   copy.add_molecule( new_molecule );
  }
  return copy;
 }
 void print()
 {
   cout << " MOLECULAR UNIT CELL INFO" << endl;
   for( size_t imole = 0; imole < n_molecule; imole++ ){
    molecule molex = primitive.get( imole );
    cout << "  Molecule " << imole << "  name: " << molex.get_name() << endl;
    cout << "   Atom List:" << endl;
    for( size_t iatom = 0; iatom < molex.size(); iatom++ ){
     atom atomx = molex.at(iatom);
     cout << "    " << atomx.get_element() << " " << atomx.get_x() << atomx.get_y() << atomx.get_z() << endl;
    }
   }
   cout << " END" << endl;
 }

public:
 vector<molecule> get_primitive() const { return this->primitive; }
 vector<molecule>& set_primitive() { return this->primitive; }

 tuple<double, double, double > get_lattice_const() const {
  return make_tuple( this->get_a(), this->get_b(), this->get_c() );
 }
 tuple<double, double, double > get_lattice_angle() const {
  return make_tuple( this->get_alpha(), this->get_beta(), this->get_gamma() );
 }

 void set_lattice_const( tuple<double, double, double> const_set ){
  this->set_a() = get<0>( const_set );
  this->set_b() = get<1>( const_set );
  this->set_c() = get<2>( const_set );
 }
 void set_lattice_angle( tuple<double, double, double> angle_set ){
  this->set_alpha() = get<0>( angle_set );
  this->set_beta()  = get<1>( angle_set );
  this->set_gamma() = get<2>( angle_set );
 }

 int get_nmolecule() const { return this->n_molecule; }
 int& set_nmolecule() { return this->n_molecule; }

private:
  double get_a() const { return this->lc_a; }
  double get_b() const { return this->lc_b; }
  double get_c() const { return this->lc_c; }
  double get_alpha() const { return this->alpha; }
  double get_beta()  const { return this->beta; }
  double get_gamma() const { return this->gamma; }
 
  double& set_a() { return this->lc_a; }
  double& set_b() { return this->lc_b; }
  double& set_c() { return this->lc_c; }
  double& set_alpha() { return this->alpha; }
  double& set_beta()  { return this->beta; }
  double& set_gamma() { return this->gamma; }

private:
 vector<molecules> primitive;
 double lc_a, lc_b, lc_c;
 double alpha, beta, gamma;
 int n_molecule;

};

}

}

#endif
