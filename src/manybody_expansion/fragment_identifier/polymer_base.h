#ifndef POLYMER_BASE_H
#define POLYMER_BASE_H

#include <vector>
#include <iostream>
#include "utilities/solid_gen/threed_space.h"
#include "utilities/solid_gen/threed_space_function.h"
#include "utilities/solid_gen/coordinate.h"
#include "utilities/solid_gen/atom.h"
#include "utilities/solid_gen/molecule.h"

using namespace std;

namespace iquads {

using namespace threed_space;
using namespace basic;

namespace crystal {

template< size_t NUM >
struct polymer_base{
public:
  polymer_base(){
   this->n_molecule_ = NUM;
   this->group.resize( NUM );
   this->natom_ = 0;
   this->mass_ = 0.0e0;
  }
  polymer_base( MoleculeList poly ){
   this->n_molecule_ = NUM;
   this->group.resize( NUM );
   this->natom_ = 0;
   this->mass_ = 0.0e0;
   this->init_from( poly );
  }

public:
  void init_from( MoleculeList new_molecule_list ){
   try{
    const size_t n_molecule = new_molecule_list.size();
    if( n_molecule != this->n_molecule_ ) throw n_molecule;
    for( size_t imolecule = 0; imolecule < this->n_molecule_; imolecule++ ){
     this->group.at(imolecule) = new_molecule_list.at(imolecule);
     const size_t natom_i = new_molecule_list.at(imolecule).get_natom();
     this->natom_ += natom_i;
     const double mass_i = new_molecule_list.at(imolecule).get_mass();
     this->mass_ += mass_i;
    }
   }
   catch ( size_t n ){
    cout << " polymer exception: init_from() " << endl;
    cout << " n_molecule " << n << " != " << this->n_molecule_ << endl;
    abort();
   }
  }

public:
  bool within_radius( double radius ){
   bool retval = true;
   CoordList coordlist_local = this->get_coordinate_list();
   const size_t ncoord_local = coordlist_local.size();
   for( size_t icoord = 0; icoord < ncoord_local; icoord++ ){
    for( size_t jcoord = 0; jcoord < icoord; jcoord++ ){
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

  bool within_mean_radius_by_center_of_mass( double radius ){
//    const double dist = this->compute_mean_distance_by_center_of_mass();
//    cout << " dist of center of mass "  << dist << "  radius " << radius << "  dist <= radius ? " << (dist <= radius) << endl;
    return ( this->compute_mean_distance_by_center_of_mass() <= radius ? true : false );
  }

  bool within_mean_radius_by_center( double radius ){
   return ( this->compute_mean_distance_by_center() <= radius ? true : false );
  }

  double compute_mean_distance_by_center(){
   double retval = 0.0e0;
   int count = 0;
   for( size_t imole = 0; imole < this->n_molecule_; imole++ ){
    Coord com_i = this->group.at(imole).get_center();
    for( size_t jmole = imole+1; jmole < this->n_molecule_; jmole++ ){
     Coord com_j = this->group.at(jmole).get_center();
     retval += compute_distance( com_i, com_j );
     count = count + 1;
    }
   }
   retval = retval/count;
   return retval;
  }

  double compute_mean_distance_by_center_of_mass(){
   double retval = 0.0e0;
   int count = 0;
   for( size_t imole = 0; imole < this->n_molecule_; imole++ ){
    Coord com_i = this->group.at(imole).get_center_of_mass();
    for( size_t jmole = imole+1; jmole < this->n_molecule_; jmole++ ){
     Coord com_j = this->group.at(jmole).get_center_of_mass();
     retval += compute_distance( com_i, com_j );
     count = count + 1;
    }
   }
   retval = retval/count;
   return retval;
  }

public:
  // interface to Euclidean distance matrix
  CoordList get_coordinate_list(){
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

  friend 
  ostream& operator<< ( ostream& os, polymer_base<NUM> polymer ){
   const size_t n_member = NUM;
   for( size_t imember = 0; imember < n_member; imember++ ){
    molecule mole_i = polymer.set_member(imember);
    os << mole_i << endl;
   }
   return os;
  }

public:
  MoleculeList get_group() const { return this->group; }
  size_t get_natom() const { return this->natom_; }
  double get_mass() const { return this->mass_; }

private:
  molecule& set_member( size_t i ){ return group.at(i); }

private:
  vector< molecule > group;
  double mass_;
  size_t n_molecule_;
  size_t natom_;

};

} // end of crystal

} // end of iquads

#endif
