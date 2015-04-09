#ifndef MOLECULE_H
#define MOLECULE_H

#include <vector>
#include <string>
#include <tuple>
#include <fstream>
#include <iostream>
#include "utilities/solid_gen/coordinate.h"
#include "utilities/solid_gen/atom.h"

using namespace std;

namespace iquads {

namespace basic {

struct molecule{
public:
  molecule(){
   this->atom_list.resize(0);
   this->molecule_name_ = "not set";
   this->natom_ = 0;
  }

public:
  void add_atom( atom new_atom ){
   this->atom_list.push_back( new_atom );
   this->natom += 1;
  }
  void print_info(){
   cout << " MOLECULE(" << this->molecule_name_ << ")" << endl;
   for( size_t iatom = 0; iatom < natom_; iatom++ ){
    (this->atom_list.at(iatom)).print_info();
   }
  }

public:
  bool within_radius( double Radius ){
   bool retval = true;
   size_t n_atom_local = this->atom_list.size();
   for( size_t iatom = 0; iatom < n_atom_local; iatom++ ){
    atom atom_local = atom_list.at(iatom);
    if( atom_local.within_radius( Radius ) == false ){
     retval = false;
     break;
    }
   }
   return retval;
  }

  void operator+= ( array<double, double, double> x ){
   size_t n_atom_local = this->atom_list.size();
   for( size_t iatom = 0; iatom < n_atom_local; iatom++ ){
    atom_list.at(iatom) += x;
   }
  }

  void operator>> ( ifstream ifs ){
   ifs >> this->molecule_name_;
   ifs >> this->natom_;
   this->atom_list.resize( this->natom_ );
   for( size_t iatom = 0; iatom < this->natom_; iatom++ ){
    atom new_atom;
    ifs >> new_atom;
    this->add_atom( new_atom );
   }
  }

  array< array<double, double>, 3 > get_edges(){
   array< array<double, double>, 3 > retval;
   size_t natom_local = this->atom_list.size();
   double x_plus = 0.0e0;
   double x_minus = 0.0e0;
   double y_plus = 0.0e0;
   double y_minus = 0.0e0;
   double z_plus = 0.0e0;
   double z_minus = 0.0e0;
   for( size_t iatom = 0; iatom < natom_local; iatom++ ){
    array< array<double, double>, 3> edge_atom;
     = this->atom_list.at(iatom).get_edges();
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


public:
  AtomList get_atom_list() const { return this->atom_list; }
  atom get_atom( size_t i ) const { return this->atom_list.at(i); }
  string get_name() const { return this->molecule_name_; }
  int get_natom() const { return this->natom_; }

  AtomList& set_atom_list() { return this->atom_list; }
  atom& set_atom( size_t i ) { return this->atom_list.at(i); }
  string& set_name() { return this->molecule_name_; }
  int& set_natom() { return this->natom_; }

  CoordList get_coordinate_list(){
   CoordList retval;
   for( size_t iatom = 0; iatom < natom_; iatom++ ){
    const Coord set = this->atom_list.at(iatom).get_coordiante_set();
    retval.push_back(set);
   }
   return retval;
  }

  void print_info(){
   cout << "MOLECULE INFO" << endl;
   cout << " molecule name: " << this->molecule_name_ << endl;
   AtomList atomlist_local = this->get_atom_list();
   const size_t natom = atomlist_local.size();
   cout << " number of atom: " << natom << endl;
   cout << " Atom List:" << endl;
   for( size_t iatom = 0; iatom < natom; iatom++ ){
    atomlist_local[iatom].print_info();
   }
   cout << endl;
  }

private:
  // we enforce the use of vector to store atom_list in the heap
  // Note the that the construction of the atom coordinate is also
  // in the heap
  AtomList atom_list;
  size_t natom_;
  string molecule_name_;

};

typedef vector<molecule> MoleculeList;

} // end of crystal

} // end of iquads

#endif
