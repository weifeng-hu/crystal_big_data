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
   this->natom_ += 1;
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

  void operator+= ( array<double, 3> x ){
   size_t n_atom_local = this->atom_list.size();
   for( size_t iatom = 0; iatom < n_atom_local; iatom++ ){
    atom_list.at(iatom) += x;
   }
  }

  friend ifstream& operator>> ( ifstream& ifs, molecule& new_mole ){
   ifs >> new_mole.set_name();
   ifs >> new_mole.set_natom();
   new_mole.set_atom_list().resize( new_mole.get_natom() );
   for( size_t iatom = 0; iatom < new_mole.get_natom(); iatom++ ){
    atom new_atom;
    ifs >> new_atom;
    new_mole.add_atom( new_atom );
   }
   return ifs;
  }

  array< array<double, 2>, 3 > get_edges(){
   array< array<double, 2>, 3 > retval;
   size_t natom_local = this->atom_list.size();
   double x_plus  = this->atom_list.at(0).get_edges().at(0).at(0);
   double x_minus = this->atom_list.at(0).get_edges().at(0).at(1);
   double y_plus  = this->atom_list.at(0).get_edges().at(1).at(0);
   double y_minus = this->atom_list.at(0).get_edges().at(1).at(1);
   double z_plus  = this->atom_list.at(0).get_edges().at(2).at(0);
   double z_minus = this->atom_list.at(0).get_edges().at(2).at(1);
   for( size_t iatom = 0; iatom < natom_local; iatom++ ){
    array< array<double, 2>, 3> edges_atom
     = this->atom_list.at(iatom).get_edges();
    if( ( edges_atom.at(0).at(0) - x_plus ) >= 0.0e0 )
     { x_plus = edges_atom.at(0).at(0); }
    if( ( edges_atom.at(1).at(0) - y_plus ) >= 0.0e0 )
     { y_plus = edges_atom.at(1).at(0); }
    if( ( edges_atom.at(2).at(0) - z_plus ) >= 0.0e0 )
     { z_plus = edges_atom.at(2).at(0); }

    if( ( edges_atom.at(0).at(1) - x_minus ) < 0.0e0 )
     { x_minus = edges_atom.at(0).at(1); }
    if( ( edges_atom.at(1).at(1) - y_minus ) < 0.0e0 )
     { y_minus = edges_atom.at(1).at(1); }
    if( ( edges_atom.at(2).at(1) - z_minus ) < 0.0e0 )
     { z_minus = edges_atom.at(2).at(1); }
   }
   retval.at(0) = array<double, 2> { x_plus, x_minus };
   retval.at(1) = array<double, 2> { y_plus, y_minus };
   retval.at(2) = array<double, 2> { z_plus, z_minus };
   return retval;
  }


public:
  AtomList get_atom_list() const { return this->atom_list; }
  atom get_atom( size_t i ) const { return this->atom_list.at(i); }
  string get_name() const { return this->molecule_name_; }
  size_t get_natom() const { return this->natom_; }

  AtomList& set_atom_list() { return this->atom_list; }
  atom& set_atom( size_t i ) { return this->atom_list.at(i); }
  string& set_name() { return this->molecule_name_; }
  size_t& set_natom() { return this->natom_; }

  CoordList get_coordinate_list(){
   CoordList retval;
   for( size_t iatom = 0; iatom < natom_; iatom++ ){
    const Coord set = this->atom_list.at(iatom).get_coordinate_set();
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
