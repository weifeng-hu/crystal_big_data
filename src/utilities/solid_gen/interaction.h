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

#ifndef INTERACTION_H
#define INTERACTION_H

#include <iostream>
#include <fstream>
#include <memory>
#include "utilities/solid_gen/polymer_group_base.h"
#include "utilities/solid_gen/molecule_bulk.h"
#include "utilities/solid_gen/fragment_group_info.h"

using namespace std;

namespace iquads {

namespace crystal {

struct interaction {
public:
  interaction(){
   this->fragment_group_list.resize(0);
   this->n_fraggroup = 0;
   this->bulk_radius = 0.0e0;
   this->short_range_radius = 0.0e0;
   this->long_range_radius = 0.0e0;
  }

public:
  template< size_t NUM >
  fragment_group_info identify_subgroups( double Radius )
  {
   fragment_group_info retval;
   {
    polymer_group_base < NUM > polymer_group;
    shared_ptr< molecule_bulk > bulk_ptr_local 
      = make_shared< molecule_bulk > ( (this->bulk) );
    polymer_group.init_from_bulk ( bulk_ptr_local, Radius );
    polymer_group.evaluate_subgroups();
    retval = polymer_group.get_fragment_group_info();
   }
   return retval;
  }

public:
  // add a fragment_info object to the list
  void add_fragment_group( fragment_group_info fraggroup ){
   this->fragment_group_list.push_back( fraggroup );
   this->n_fraggroup += 1;
  }

public:
  void print_fragment_groups(){
   for( size_t igroup = 0; igroup < this->n_fraggroup; igroup++ ){
    fragment_group_info frag_group_local 
      = this->fragment_group_list.at(igroup);
    cout << frag_group_local << endl;
//    frag_group_local.print_info();
   }
  } // end of print_fragment_groups() 

  void print_summary(){
   for( size_t igroup = 0; igroup < this->n_fraggroup; igroup++ ){
    fragment_group_info frag_group_local 
      = this->fragment_group_list.at(igroup);
    frag_group_local.print_summary();
//    frag_group_local.print_info();
   }
  }

  void run_gview(){
   cout << "Writing Gaussian gjf files ...";
   vector<string> file_list;
   for( size_t igroup = 0; igroup < this->n_fraggroup; igroup++ ){
    fragment_group_info frag_group_local
     = this->fragment_group_list.at(igroup);
    for( size_t itype = 0; itype < frag_group_local.set_store().size(); itype++ ){
      fragment_info frag_local 
        = frag_group_local.set_store().at(itype);
      AtomList atom_list_i;
      for( size_t imole = 0; imole < get<0>(frag_local.set_primitive_info()).size(); imole++){
       AtomList atom_list_local 
        = get<0>(frag_local.set_primitive_info()).at(imole).get_atom_list();
       for( size_t iatom = 0; iatom < atom_list_local.size(); iatom++ ){
        atom_list_i.push_back( atom_list_local.at(iatom) );
       } // end of loop iatom
      } // end of loop imole
      char file_i[100];
      sprintf( file_i,"%i.%i.primitive.gjf", igroup, itype);
      file_list.push_back( string(file_i) );
      this->write_gview_file( string(file_i), atom_list_i );
    } // end of loop itype
   } // end of loop igroup
   cout << " done" << endl;

   cout << "Starting gview ..."<< endl;
   {
    string command = "/home/wh288/Apps/gv-508/gview ";
    for( size_t ifile = 0; ifile < file_list.size(); ifile++ ){
     const string file_i = file_list.at(ifile);
     command += file_i;
     command += " ";
    }
//    cout << command << endl;
    int res = system( command.c_str() );
   }
  }

  void write_gview_file( string filename, AtomList atom_list ){
   ofstream ofs;
   ofs.open( filename.c_str(), ios::out );
   ofs << "#HF/3-21G" << endl;
   ofs << endl;
   ofs << "title card" << endl;
   ofs << endl;
   ofs << "0  1" << endl;
   for( size_t iatom = 0; iatom < atom_list.size(); iatom++ ){
    atom atom_i = atom_list.at(iatom);
    ofs << atom_i << endl;
   }
   ofs.close();
  }

  molecule_bulk& set_bulk() { return this->bulk; }

  double& set_short_range_radius() { return this->short_range_radius; }
  double& set_long_range_radius() { return this->long_range_radius; }

private:
  // a copy of the molecule bulk information
  molecule_bulk bulk;
  // fragment info for all kinds of fragment groups
  vector< fragment_group_info > fragment_group_list;
  // number of fragment groups, is size of fraginfo_list
  size_t n_fraggroup;
  // a copy of the bulk radius;
  double bulk_radius;
  // a copy of the short range radius
  double short_range_radius;
  // a copy of the long range radius
  double long_range_radius;

}; // end of struct interaction

} // end of namespace iquads

} // end of namespace iquads

#endif
