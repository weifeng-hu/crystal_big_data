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

#include <vector>
#include <geometrical_space/threed_space_function.hpp>
#include <structure/atom_list.hpp>
#include <structure/euclidean_distance_matrix.hpp>

namespace iquads {

namespace structure {

class DuplicationRemover {
public:
  typedef iquads :: structure :: AtomList atom_list_type;

public:
  DuplicationRemover() {}
  DuplicationRemover( double threshold ) :
    threshold_ ( threshold ) {}

public:
  atom_list_type strip( const atom_list_type& atom_list_obj ) {

    std :: vector<int> duplicated_list;
    duplicated_list.resize(0);
    for( size_t iatom = 0; iatom < atom_list_obj.size(); iatom++ ) {
      for( size_t jatom = iatom + 1; jatom < atom_list_obj.size(); jatom++ ) {
        double distance_ij
          = iquads :: geometrical_space :: threed_space :: compute_distance( atom_list_obj[iatom].coordinate(), atom_list_obj[jatom].coordinate() );
        if( distance_ij < this->threshold_ ) { duplicated_list.push_back( jatom ); }
      }
    }

    atom_list_type new_atom_list;
    new_atom_list.resize(0);
    for( size_t iatom = 0; iatom < atom_list_obj.size(); iatom++ ) {
      if( std :: find( duplicated_list.begin(), duplicated_list.end(), iatom ) != duplicated_list.end() ) { continue; }
      new_atom_list.push_back( atom_list_obj[iatom] );
    }

    return new_atom_list;

  }

private:
  double threshold_;

}; // end of class DuplicationRemover

} // end of namespace structure

} // end of namespace iquads
