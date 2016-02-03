/**
 * @file
 * @author Weifeng Hu
 *
 * @section LICENSE
 *
 * Copyright (C) 2013, 2014, 2015  Weifeng Hu
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @section DESCRIPTION
 *
 *
 */

#ifndef MOLECULE_ISOLATOR_HPP
#define MOLECULE_ISOLATOR_HPP

#include <vector>
#include <map>
#include <matrix/matrix_typedef.hpp>
#include <matrix/matrix_function.hpp>
#include <structure/atom_list.hpp>
#include <structure/molecule.hpp>

namespace iquads {

namespace structure {

class MoleculeIsolator {
public:
  typedef Atom atom_type;
  typedef AtomList atom_list_type;
  typedef Molecule molecule_type;
  typedef std :: vector< Molecule > molecule_list_type;
  typedef atom_type :: coordinate_type coordinate_type;

public:
  MoleculeIsolator() {
    this->radius_ = 1.5e0;
  }
  MoleculeIsolator( double radius ) :
   radius_( radius )
   {} 

public:
  molecule_list_type split( const atom_list_type& atom_list_obj ) {

   const size_t natom = atom_list_obj.size();
   iquads :: matrix :: IMatrixHeap adjacency_matrix( natom, natom );

   // produce an initial adjaceny matrix
   for( size_t iatom = 0; iatom < natom; iatom++ ) {
     atom_type atom_i = atom_list_obj[iatom];
     coordinate_type coord_i = atom_i.coordinate();
     for( size_t jatom = 0; jatom < natom; jatom++ ) {
       atom_type atom_j = atom_list_obj[jatom];
       coordinate_type coord_j = atom_j.coordinate();
       const double distance_ij
         = iquads :: geometrical_space :: threed_space :: compute_distance( coord_i, coord_j );
       if( ( distance_ij - this->radius_ ) < 0.0e0 ) { adjacency_matrix( iatom, jatom ) = 1; }
     }
   }

   // check in the matrix, to link atoms which were indirectly linked
   // means, they are belong to the same molecule, or finally, the same block
   for( size_t iatom = 0; iatom < natom; iatom++ ) {
     std :: vector<int> linked_i;
     linked_i.resize(0);
     for( size_t jatom = 0; jatom < natom; jatom++ ) {
       if( adjacency_matrix(iatom, jatom) == 1 ) { linked_i.push_back(jatom); } 
     }
     for( size_t ind_m = 0; ind_m < linked_i.size(); ind_m++ ) {
       int m = linked_i[ind_m];
       for( size_t ind_n = 0; ind_n < linked_i.size(); ind_n++ ) {
         int n = linked_i[ind_n];
         adjacency_matrix( m, n ) = 1;
       }
     }
   } 

   // OK, looks good. Now we have to generate a vector of std :: map for each row
   std :: vector< std :: map< int, int > > bond_map;
   bond_map.resize(0);
   for( size_t iatom = 0; iatom < natom; iatom++ ) {
     std :: map< int, int > map_local;
     for( size_t jatom = 0; jatom < natom; jatom++ ) {
       if( adjacency_matrix( iatom, jatom) == 1 ) {
         map_local.insert( std :: pair< int, int > ( jatom, 1 ) );
       }
     }
     bond_map.push_back( map_local );
//     std :: cout << map_local.size() << std :: endl;
   }

   // Now, we can call matrix functions
   std :: vector< std :: vector< int > > group_indices = iquads :: matrix :: get_groups( bond_map );

   molecule_list_type molecule_list;
   molecule_list.resize(0);
   std :: cout << "number of molecules: " << group_indices.size() << std :: endl;
   for( size_t ivec = 0; ivec < group_indices.size(); ivec++ ) {
     atom_list_type new_atom_list_i;
     std :: vector< int > indices_i = group_indices[ivec];
     for( size_t iatom = 0; iatom < indices_i.size(); iatom++ ) {
       const int ind_atom = indices_i[iatom];
       new_atom_list_i.push_back( atom_list_obj.at(ind_atom) );
     }
     molecule_list.push_back( iquads :: structure :: Molecule( new_atom_list_i, 0 ) );
   }

   // Do a little bit more sorting
   // Sort atoms in each molecule by distance to center of mass
   for( size_t imolecule = 0; imolecule < molecule_list.size(); imolecule++ ) {
     molecule_type molecule_i = molecule_list[imolecule];
     coordinate_type center_of_mass = molecule_i.center_of_mass();
     std :: map < double, iquads :: structure :: Atom > dist_map;
     for( size_t iatom = 0; iatom < molecule_i.size(); iatom++ ) {
       atom_type atom_i = molecule_i[iatom];
       double distance_to_com 
         = iquads :: geometrical_space :: threed_space :: compute_distance( center_of_mass, atom_i.coordinate() );
       dist_map.insert( std :: pair< double, iquads :: structure :: Atom > ( distance_to_com, atom_i )  );
     }

     atom_list_type new_atom_list_i;
     new_atom_list_i.resize(0);
     typedef std :: map < double, iquads :: structure :: Atom > :: iterator dist_map_iterator;
     for( dist_map_iterator it = dist_map.begin(); it != dist_map.end(); ++it ) {
       atom_type atom_it = it->second;
       new_atom_list_i.push_back(atom_it);
     }

     molecule_list[imolecule] = iquads :: structure :: Molecule( new_atom_list_i, 0 );

   }

   return molecule_list;

  } // end of function split()

private:
  double radius_;

}; // end of class MoleculeIsolator

} // end of namespace structure

} // end of namespace iquads

#endif
