#ifndef MOLECULE_BULK_H
#define MOLECULE_BULK_H

#include <vector>
#include <tuple>
#include <memory>
#include "utilities/solid_gen/molecule.h"
#include "utilities/solid_gen/unit_cell.h"
#include "utilities/solid_gen/lattice.h"

namespace iquads{

namespace crystal{

struct molecule_bulk
{
public:
  mole_bulk(){
   this->bulk.resize(0);
   this->n_molecule_ = 0;
  }
  molecule_bulk( molecular_lattice* ml ){
   this->init_from( ml );
  }

public:
  void init_from( shared_ptr<molecular_lattice> ml ){
   size_t n_cell_local = ml->get_ncell();
   for( size_t icell = 0; icell < n_cell_local; icell++ ){
    molecular_cell cell_local = ml->get_cell(icell);
    size_t n_node_local = cell_local.get_n_node();
    for( size_t inode = 0; inode < n_node_local; inode++ ){
     this->bulk.push_back( cell_local.get_node(inode) );
    }
   }
   this->n_molecule_ = bulk.size();
  }
  void cut( double Radius ){
   this->radius_ = Radius;
   vector< molecule > temp_bulk;
   for( size_t imole = 0; imole < this->n_molecule_; imole++ ){
    molecule mole_local = bulk.at(imole);
    if( mole_local.within_radius( Radius ) == true ){
     temp_bulk.push_back( mole_local );
    }
   }
   this->bulk.resize(0);
   this->bulk = temp_bulk;
   this->n_molecule_ = temp_bulk.size();
  }

public:
  MoleculeList get_molelist_from_list( vector<int> list ){
   MoleculeList retval;
   for( size_t imole = 0; imole < list.size(); imole++ ){
    retval.push_back( this->bulk.at(imole) );
   }
   return retval;
  }

public:
  size_t get_nmolecule() const { return this->n_molecule_; }
  molecule get_molecule( size_t i ) const { return this->bulk.at(i); }

private:
  vector< molecule > bulk;
  double radius_;
  size_t n_molecule_;

};

} // end of crystal

} // end of iquads

#endif
