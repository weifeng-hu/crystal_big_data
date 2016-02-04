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

#ifndef UNIT_CELL_CANONICALIZER_HPP
#define UNIT_CELL_CANONICALIZER_HPP

#include <array>
#include <vector>
#include <map>
#include <matrix/matrix_typedef.hpp>
#include <matrix/matrix_function.hpp>
#include <geometrical_space/coordinate.hpp>
#include <structure/atom_list.hpp>
#include <structure/molecule.hpp>
#include <structure/unit_cell_instant.hpp>
#include <structure/euclidean_distance_matrix.hpp>
#include <structure/molecule_isolator.hpp>

namespace iquads {

namespace structure {

class UnitCellCanonicalizer {
public:
  typedef double distance_type;
  typedef double bond_length_type;
  typedef iquads :: geometrical_space :: CartesianCoordinate3D coordinate_type;
  typedef iquads :: structure :: Atom atom_type;
  typedef iquads :: structure :: Molecule molecule_type;
  typedef iquads :: structure :: AtomList atom_list_type;
  typedef std :: vector< molecule_type > molecule_list_type;
  typedef iquads :: structure :: MolecularUnitCell unit_cell_type;
  typedef iquads :: structure :: LatticeParameter lattice_parameter_type;
  typedef iquads :: matrix :: DMatrixHeap matrix_type;
  typedef std :: array< double, 3 > threed_vector_type;

public:
  UnitCellCanonicalizer() {
    this->edm_eigvals_reference_.resize(0);
    this->distance_to_center_list_.resize(0);
    this->bond_length_limit_ = 0.0e0;
    this->natom_per_molecule_ = 0;
  }

  UnitCellCanonicalizer( const unit_cell_type& ref_unit_cell, const double bond_length_limit ) {

    this->reference_unit_cell_ = ref_unit_cell;
    this->bond_length_limit_ = bond_length_limit;
    this->natom_per_molecule_ = this->reference_unit_cell_[0].size();
    this->edm_eigvals_reference_.resize(0);
    this->distance_to_center_list_.resize(0);

    {
      molecule_list_type molecule_list = this->reference_unit_cell_.node_list();
      coordinate_type center_of_cell = this->reference_unit_cell_.center();
      for( size_t imole = 0; imole < molecule_list.size(); imole++ ) {
        molecule_type molecule_plus = molecule_list[imole];
        coordinate_type com_of_molecule = molecule_plus.center_of_mass();
        this->distance_to_center_list_.push_back
          ( iquads :: geometrical_space :: threed_space :: compute_distance( com_of_molecule, center_of_cell ) );
        molecule_plus.push_back( atom_type( "H", std :: get<0>( center_of_cell ), 
                                                 std :: get<1>( center_of_cell ),
                                                 std :: get<2>( center_of_cell ), "angstrom" ) );

        iquads :: structure :: EuclideanDistanceMatrix edm_plus( molecule_plus.size() );
        edm_plus.compose_from_atomlist( molecule_plus.atom_list() );
        edm_plus.diagonalise();
        this->edm_eigvals_reference_.push_back( edm_plus.eigval() );
      }
    } // end of the block of determining edm and distance

  } // end of user-defined constructor

private:
  void check_lattice_vectors( std :: array< threed_vector_type, 3 > set_1, 
                              std :: array< threed_vector_type, 3 > set_2 ) {

    threed_vector_type a_vec = set_1[0];
    threed_vector_type b_vec = set_1[1];
    threed_vector_type c_vec = set_1[2];

    double angle_alpha = iquads :: geometrical_space :: threed_space :: compute_angle_between_two_vectors( a_vec, c_vec );
    double angle_beta  = iquads :: geometrical_space :: threed_space :: compute_angle_between_two_vectors( b_vec, c_vec );
    double angle_gamma = iquads :: geometrical_space :: threed_space :: compute_angle_between_two_vectors( a_vec, b_vec );

    double norm_a_vec = iquads :: geometrical_space :: threed_space :: norm( a_vec );
    double norm_b_vec = iquads :: geometrical_space :: threed_space :: norm( b_vec );
    double norm_c_vec = iquads :: geometrical_space :: threed_space :: norm( c_vec );

    threed_vector_type new_a_vec = set_2[0];
    threed_vector_type new_b_vec = set_2[1];
    threed_vector_type new_c_vec = set_2[2];

    double norm_new_a_vec = iquads :: geometrical_space :: threed_space :: norm( new_a_vec );
    double norm_new_b_vec = iquads :: geometrical_space :: threed_space :: norm( new_b_vec );
    double norm_new_c_vec = iquads :: geometrical_space :: threed_space :: norm( new_c_vec );

    double new_angle_alpha = iquads :: geometrical_space :: threed_space :: compute_angle_between_two_vectors( new_a_vec, new_c_vec );
    double new_angle_beta  = iquads :: geometrical_space :: threed_space :: compute_angle_between_two_vectors( new_b_vec, new_c_vec );
    double new_angle_gamma = iquads :: geometrical_space :: threed_space :: compute_angle_between_two_vectors( new_a_vec, new_b_vec );

    if( fabs( norm_a_vec - norm_new_a_vec ) > 1.0e-10 ) { std :: cout << "norm of vector a changed " << std :: endl; abort(); }
    if( fabs( norm_b_vec - norm_new_b_vec ) > 1.0e-10 ) { std :: cout << "norm of vector b changed " << std :: endl; abort(); }
    if( fabs( norm_c_vec - norm_new_c_vec ) > 1.0e-10 ) { std :: cout << "norm of vector c changed " << std :: endl; abort(); }
    if( fabs( angle_alpha - new_angle_alpha ) > 1.0e-10 ) { std :: cout << "angle alpha changed " << std :: endl; abort(); }
    if( fabs( angle_beta  - new_angle_beta  ) > 1.0e-10 ) { std :: cout << "angle beta  changed " << std :: endl; abort(); }
    if( fabs( angle_gamma - new_angle_gamma ) > 1.0e-10 ) { std :: cout << "angle gamma changed " << std :: endl; abort(); }

  }

  atom_list_type atom_list_duplicate( const atom_list_type& atom_list, 
                                      const std :: array< threed_vector_type, 3 >& lattice_vectors,
                                      const std :: array< std :: tuple< int, int >, 3 >& ranges )
  {
    threed_vector_type a_vec = lattice_vectors[0];
    threed_vector_type b_vec = lattice_vectors[1];
    threed_vector_type c_vec = lattice_vectors[2];

    atom_list_type new_atom_list;
    new_atom_list.resize(0);
    for( int ia = std :: get<0> ( ranges[0] ); ia <= std :: get<1> ( ranges[0] ); ia++ ) {
      for( int ib = std :: get<0> ( ranges[1] ); ib <= std :: get<1> ( ranges[1] ); ib++ ) {
        for( int ic = std :: get<0> ( ranges[2] ); ic <= std :: get<1> ( ranges[2] ); ic++ ) {
          atom_list_type atom_list_i = atom_list;
          coordinate_type vec = std :: make_tuple( ia * a_vec[0] + ib * b_vec[0] + ic * c_vec[0] ,  
                                                   ia * a_vec[1] + ib * b_vec[1] + ic * c_vec[1] ,
                                                   ia * a_vec[2] + ib * b_vec[2] + ic * c_vec[2]  );
          for( size_t iatom = 0; iatom < atom_list_i.size(); iatom++ ) {
            atom_list_i[iatom] += vec;
          }
          new_atom_list.insert( new_atom_list.begin(), atom_list_i.begin(), atom_list_i.end() );
        }
      }
    }
    return new_atom_list; 
  }

  coordinate_type center_of_atom_list( const atom_list_type& atom_list_obj ) {
    coordinate_type center_of_list;
    {
      molecule_type molecule_unknown( atom_list_obj, 0 );
      center_of_list = molecule_unknown.center();
    }
    return center_of_list; 
  }

  void atom_list_reorigin( atom_list_type& atom_list ) {
    coordinate_type center_of_atom_list = this->center_of_atom_list( atom_list );
    coordinate_type recenter_vec = std :: make_tuple( -std :: get<0> ( center_of_atom_list ),
                                                      -std :: get<1> ( center_of_atom_list ), 
                                                      -std :: get<2> ( center_of_atom_list ) );
    for( size_t iatom = 0; iatom < atom_list.size(); iatom++ ) { atom_list[iatom] += recenter_vec; }
  }

  molecule_list_type determine_node_list( const atom_list_type& atom_list, const std :: array< threed_vector_type, 3 >& lattice_vectors ) {
 
    std :: array< std :: tuple< int, int >, 3 > ranges = { std :: make_tuple( 0, 1 ), std :: make_tuple( 0, 1 ), std :: make_tuple( 0, 1 ) };
    atom_list_type new_atom_list = this->atom_list_duplicate( atom_list,
                                                              lattice_vectors,
                                                              ranges );

    // recenter the atom list
    this->atom_list_reorigin( new_atom_list );
    coordinate_type center_of_list = this->center_of_atom_list( new_atom_list );

    // split the atom list to molecules
    iquads :: structure :: MoleculeIsolator molecule_isolator( this->bond_length_limit_ );
    molecule_list_type molecule_list_of_unknown = molecule_isolator.split( new_atom_list );

    // eliminate molecules which have different numbers of atoms
    for( molecule_list_type :: iterator it = molecule_list_of_unknown.begin(); it != molecule_list_of_unknown.end(); ++it ) {
      if( it->size() != this->natom_per_molecule_ ) { molecule_list_of_unknown.erase( it ); --it; }
    }

    std :: cout << "number of complete molecules: " << molecule_list_of_unknown.size() << std :: endl;

    // compute distance from center of mass to center of list
    std :: vector< distance_type > distance_to_center_of_unknown;
    distance_to_center_of_unknown.resize(0);
    for( size_t imole = 0; imole < molecule_list_of_unknown.size(); imole++ ) {
      distance_to_center_of_unknown.push_back
        ( iquads :: geometrical_space :: threed_space :: compute_distance( molecule_list_of_unknown[imole].center_of_mass(), center_of_list ) );
    }

    // compute EDM of each molecule, by including the center in each EDM
    std :: vector< matrix_type > edm_eigvals_of_unknown;
    edm_eigvals_of_unknown.resize(0);
    for( size_t imole = 0; imole < molecule_list_of_unknown.size(); imole++ ) {
      molecule_type molecule_plus = molecule_list_of_unknown[imole];
      molecule_plus.push_back( atom_type( "H",
                                           std :: get<0> ( center_of_list ), 
                                           std :: get<1> ( center_of_list ),
                                           std :: get<2> ( center_of_list ),
                                           "angstrom" ) );
      iquads :: structure :: EuclideanDistanceMatrix edm_plus( molecule_plus.size() );
      edm_plus.compose_from_atomlist( molecule_plus.atom_list() );
      edm_plus.diagonalise();
      edm_eigvals_of_unknown.push_back( edm_plus.eigval() );
    }

    std :: vector< std :: map< double, int > > edm_mat_distance_map;
    edm_mat_distance_map.resize(0);
    for( size_t iref = 0; iref < this->edm_eigvals_reference_.size(); iref++ ) {
      std :: map< double, int > map_local;
      for( size_t iunknown = 0; iunknown < edm_eigvals_of_unknown.size(); iunknown++ ) {
        map_local.insert( std :: pair< double, int > ( iquads :: matrix :: distance_of_two_matrices( this->edm_eigvals_reference_[iref],
                                                                                                     edm_eigvals_of_unknown[iunknown] ),
                                                       iunknown ) );
      }
      edm_mat_distance_map.push_back( map_local );
    }

    // start to get result
    std :: vector< int > result;
    result.resize(0);
    for( size_t iref = 0; iref < this->edm_eigvals_reference_.size(); iref++ ) {
      std :: map < double, int > map_local = edm_mat_distance_map[iref];
      for( std :: map< double, int > :: iterator it = map_local.begin(); it != map_local.end(); ++it ) {
        int ind = it->second;
        if( std :: find( result.begin(), result.end(), ind ) == result.end() ) {
          result.push_back( ind );
          break;
        }
      }
    }

    // check the distance to center
    for( size_t ind = 0; ind < result.size(); ind++ ) {
      if( fabs( this->distance_to_center_list_[ind] - distance_to_center_of_unknown[ result[ind] ] > 0.5e0  ) ) {
        std :: cout << "distance diff too big " << ind << ": " 
                    << this->distance_to_center_list_[ind] << " ----- " << result[ind] << ": " 
                    << distance_to_center_of_unknown[ result[ind] ] << std :: endl;
        abort();
      }
    }

    molecule_list_type new_node_list;
    new_node_list.resize(0);
    for( size_t ind = 0; ind < result.size(); ind++ ) {
      molecule_type molecule_i = molecule_list_of_unknown[ result[ind] ];
      new_node_list.push_back( molecule_i );
    }

    std :: cout << "number of identified unit cell nodes: " << result.size() << std :: endl;

    return new_node_list;

  }


public:
  unit_cell_type canonicalize( const atom_list_type& atom_list, const std :: array< threed_vector_type, 3 >& lattice_vectors ) {

    // get the rotator first
    threed_vector_type vec_1 = lattice_vectors[0];
    threed_vector_type vec_2 = { 1.0e0, 0.0e0, 0.0e0 };
    iquads :: geometrical_space :: Rotator rotator( vec_1, vec_2 );

    // rotate lattice vectors
    std :: array< threed_vector_type, 3 > new_lattice_vectors;
    for( size_t ivec = 0; ivec < 3; ivec++ ) { new_lattice_vectors[ivec] = rotator * lattice_vectors[ivec]; }
    this->check_lattice_vectors( lattice_vectors, new_lattice_vectors ); // it will abort if somethings gets wrong

    // produce new lattice parameters
    using iquads :: geometrical_space :: threed_space :: norm;
    using iquads :: geometrical_space :: threed_space :: compute_angle_between_two_vectors;
    iquads :: structure :: LatticeParameter lattice_parameter( norm( new_lattice_vectors[0] ),
                                                               norm( new_lattice_vectors[1] ),
                                                               norm( new_lattice_vectors[2] ),
                                                               compute_angle_between_two_vectors( new_lattice_vectors[0], new_lattice_vectors[2] ),
                                                               compute_angle_between_two_vectors( new_lattice_vectors[1], new_lattice_vectors[2] ),
                                                               compute_angle_between_two_vectors( new_lattice_vectors[0], new_lattice_vectors[1] ) );

    // then rotate the atom list
    atom_list_type new_atom_list;
    new_atom_list = atom_list;
    for( size_t iatom = 0; iatom < atom_list.size(); iatom++ ) {
      new_atom_list[iatom].set_coordinate() = rotator * atom_list[iatom].coordinate();
    }

    // get the node list of unit cell from this atom list
    molecule_list_type node_list_of_cell = this->determine_node_list( new_atom_list, new_lattice_vectors );

    return unit_cell_type( node_list_of_cell, lattice_parameter );
  }

private:
  unit_cell_type reference_unit_cell_;
  std :: vector< matrix_type > edm_eigvals_reference_;
  std :: vector< double > distance_to_center_list_;
  bond_length_type bond_length_limit_;
  size_t natom_per_molecule_;

}; // end of class UnitCellCanonicalizer

} // end of namespace structure

} // end of namespace iquads

#endif 
