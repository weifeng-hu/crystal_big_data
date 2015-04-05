#ifndef POLYMER_BASE_H
#define POLYMER_BASE_H

#include <vector>
#include <iostream>
#include "utilities/solid_gen/coordinate.h"
#include "utilities/solid_gen/threed_space.h"
#include "utilities/solid_gen/atom.h"
#include "utilities/solid_gen/molecule.h"

using namespace std;

namespace iquads {

using namespace basic;

namespace crystal {

template< size_t NUM >
struct polymer_base{
public:
  polymer(){
   this->n_molecule = NUM;
   this->group.resize( NUM );
   this->natom_ = 0;
  }
  polymer( MoleculeList poly ){
   this->n_molecule = NUM;
   this->group.resize( NUM );
   this->natom_ = 0;
   this->init_from( poly );
  }

public:
  void init_from( MoleculeList new_molecule_list ){
   try{
    const size_t n_molecule = new_molecule_list.size();
    if( n_molecule >= this->NUM ) throw n_molecule;
    for( size_t imolecule = 0; imolecule < n_molecule; imolecule++ ){
     group.at(imolecule) = new_molecule_list.at(imolecule);
     const size_t natom_i = new_molecule_list.at(i).get_natom(imolecule);
     this->natom_ += natom_i;
    }
   }
   catch ( size_t n ){
    cout << " polymer exception: init_from() " << endl;
    cout << " n_molecule " << n << " >= " << this->NUM << endl;
    abort();
   }
  }

public:
  bool within_radius( double radius ){
   bool retval = true;
   CoordList coordlist_local = this->get_coordinate_list();
   const size_t ncoord_local = coordlist_local.size();
   for( size_t icoord = 0; icoord < ncoord_local; icoord++ ){
    for( size_t jcoord = 0; jcoord < icoord; icoord++ ){
     double dist = compute_distance( coordlist_local.at(icoord), coordlist_local.at(jcoord) );
     if( ( dist - radius ) > 0.0e0 ){
      retval = false;
      goto end;
     }
    }
   }
end:
   return retval;
  }

public:
  // interface to Euclidean distance matrix
  CoodList get_coordinate_list(){
   CoordList retval;
   for( size_t imolecule = 0; imolecule < NUM; imolecule++ ){
    molecule mole_i = group.at(imolecule);
    CoordList coordlist_i = mole_i.get_coordinate_list();
    retval.insert( retval.end(), coordlist_i.begin(), coordlist_i.end() );
   }
   return retval;
  }
  AtomList get_atom_list(){
   AtomList retval;
   for( size_t imolecule = 0; imolecule < NUM; imolecule++ ){
    molecule mole_i = group.at(imolecule);
    AtomList atomlist_i = mole_i.get_atom_list();
    retval.insert( retval.end(), atomlist_i.begin(), atomlist_i.end() );
   }
   return retval;
  }
  // should think about using std::move() to append vectors

public:
  MoleculeList get_group() const { return this->group; }
  size_t get_natom() const { return this->natom_; }

private:
  molecule& set_member( size_t i ){ return group.at(i); }

private:
  vector< molecule > group;
  size_t n_molecule;
  size_t natom_;

};

} // end of crystal

} // end of iquads

#endif
