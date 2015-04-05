#ifndef MOLECULE_H
#define MOLECULE_H

#include <vector>
#include <string>
#include <tuple>
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
