/*
 *  This source code applies all the terms in 
 *  GNU GENERAL PUBLIC LICENSE (GPL), Version3, 29 June 2007.
 *
 *  Copyright (C) 2013-2015 Weifeng Hu, all rights reserved.
 *  
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef MOLECULE_BULK_H
#define MOLECULE_BULK_H

#include <vector>
#include <tuple>
#include <map>
#include <memory>
#include "utilities/solid_gen/molecule.h"
#include "utilities/solid_gen/unit_cell.h"
#include "utilities/solid_gen/lattice.h"
#include "utilities/solid_gen/lattice_parameters.h"

namespace iquads{

namespace crystal{

struct molecule_bulk
{
public:
  molecule_bulk(){
   this->bulk.resize(0);
   this->n_molecule_ = 0;
   this->radius_ = 0.0e0;
  }
  molecule_bulk( molecular_lattice* ml ){
   this->init_from( ml );
  }

public:
  void init_from( molecular_lattice* ml ){
   cout << "Initialising molecule bulk from lattice ..." << endl;
   ml->recenter();
   cout << "Transforming to molecule bulk ...";
   size_t n_cell_local = ml->get_ncell();
   for( size_t icell = 0; icell < n_cell_local; icell++ ){
    molecular_ucell cell_local = ml->get_cell(icell);
    size_t n_node_local = cell_local.get_n_node();
    for( size_t inode = 0; inode < n_node_local; inode++ ){
     this->bulk.push_back( cell_local.get_node(inode) );
    }
   }
   cout << " done" << endl;
   this->n_molecule_ = bulk.size();
   this->lp = ml->get_constants();
  }
  void recenter_to_central_molecule( tuple< array< double, 3 >, int > center_mole_info ){
   cout << "Recentering the origin to the center of mass of the central molecule ... " << endl;
   array< double, 3 > vec = get<0>( center_mole_info );
   for( size_t imole = 0; imole < this->n_molecule_; imole++ ){
    (this->bulk.at(imole)) += vec;
   }
   this->central_molecule_ = get<1>(center_mole_info);
   cout << "   central molecule is " << this->central_molecule_ << endl;
  }
  tuple< array< double, 3 >, int > identify_central_molecule(){

   array< double, 3 > recenter_vec;
   int index;
   {
    multimap< double, int > dist_map;
    for( size_t imole = 0; imole < this->n_molecule_; imole++ ){
     molecule mole_i = this->bulk.at(imole);
     Coord com_i = mole_i.get_center_of_mass();
     Coord orig = make_tuple( 0.0, 0.0, 0.0 );
     double dist = compute_distance( com_i, orig );
     dist_map.insert( pair<double, int>( dist, imole) );
    }
    multimap< double, int > :: iterator it = dist_map.begin();
    index = it->second;
   }
   Coord center_of_mass = (this->bulk.at(index)).get_center_of_mass();
   recenter_vec 
    = array<double, 3>{ -get<0>(center_of_mass), -get<1>(center_of_mass), -get<2>(center_of_mass) };
   return make_tuple( recenter_vec, index );
  }

  void cut( double Radius ){
   cout << "Performing sphere cut using radius " << Radius << " Angstrom ..." << endl;
   this->radius_ = Radius;
   vector< molecule > temp_bulk;
   for( size_t imole = 0; imole < this->n_molecule_; imole++ ){
    molecule mole_local = this->bulk.at(imole);
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
    size_t xmole = list.at(imole);
    retval.push_back( this->bulk.at(xmole) );
   }
   return retval;
  }

  friend
   ostream& operator<< ( ostream& os, const molecule_bulk& mole_bulk )
   {
    for( size_t i = 0 ; i < mole_bulk.get_nmolecule(); i++ ){
     os << mole_bulk.get_molecule(i);
    }
    return os;
   }

public:
  size_t get_nmolecule() const { return this->n_molecule_; }
  molecule get_molecule( size_t i ) const { return this->bulk.at(i); }
  int get_central_molecule() const { return this->central_molecule_; }
  lattice_parameters get_constants() const { return this->lp; }

private:
  vector< molecule > bulk;
  lattice_parameters lp;
  int central_molecule_;
  double radius_;
  size_t n_molecule_;

};

} // end of crystal

} // end of iquads

#endif
