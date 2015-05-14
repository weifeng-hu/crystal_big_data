/* 
  This is a small tool to compute the overlap of any two different 
  sets of orbitals, e.g., canonical orbitals, natural orbitals, 
  localized orbitals. All we need is the orbital coefficients of 
  the two sets of orbitals, and the AO overlap matrix of a set 
  of these two,  assuring that they are using the same set of AOs. 
*/

#include <stdlib.h>
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <cmath>
#include "utilities/compute_overlap/overlap_config_class.h"
#include "matrix/square_matrix.h"
#include "matrix/general_matrix.h"
#include "matrix/functions.h"

using namespace std;

int main( int argc, char* argv[] )
{

   if( argc != 2 ){ cout << "usage: overlap configfile" << endl; exit(1); }

   string input = argv[1];
   iqs::utilities::overlap_config config( input );

   iqs::matrix::general_matrix ov_mtr( config.nbas(), config.nbas() );
   ov_mtr.read_matrix( config.ov_file() );

   iqs::matrix::general_matrix c1_mtr( config.nbas(), config.norb() );
   c1_mtr.read_matrix( config.c1_file() );

   iqs::matrix::general_matrix c2_mtr( config.nbas(), config.norb() );
   if( config.same_c1c2() == false ){
    c2_mtr.read_matrix( config.c2_file() );
   }

//   cout << "nbas = " << config.nbas() << "\t" << " norb = " << config.norb() << endl;
//   cout << "ov_file = " << config.ov_file() << endl;
//   cout << "c1_file = " << config.c1_file() << "\t" << " c2_file = " << config.c2_file() << endl;
//   cout << "reorder2 = " << config.reorder2_file() << endl;
//   cout << "reorder2_ao = " << config.reorder2_ao_file() << endl;

   vector<int> orb_seq1;
   vector<int> orb_seq2;
   vector<int> ao_seq1;
   vector<int> ao_seq2;
   if( config.do_reorder1() == true ){ orb_seq1 = iqs::matrix::read_vector( config.reorder1_file() ); }
   if( config.do_reorder2() == true ){ orb_seq2 = iqs::matrix::read_vector( config.reorder2_file() ); }
   if( config.do_reorder1_ao() == true ){ ao_seq1 = iqs::matrix::read_vector( config.reorder1_ao_file() ); }
   if( config.do_reorder2_ao() == true ){ ao_seq2 = iqs::matrix::read_vector( config.reorder2_ao_file() ); }

   if( config.do_reorder1() == true ){ c1_mtr.reorder_col( orb_seq1 ); }
   if( config.do_reorder2() == true ){ c2_mtr.reorder_col( orb_seq2 ); }
   if( config.do_reorder1_ao() == true ){ ov_mtr.reorder_row( ao_seq1 ); }
   if( config.do_reorder2_ao() == true ){ ov_mtr.reorder_col( ao_seq2 ); }

   iqs::matrix::general_matrix new_ov_mtr( config.norb(), config.norb() );
//   for( int i = 0; i < ov_mtr.nrow(); i++ ){ for( int j = 0; j <= i; j++ ){ ov_mtr( j, i ) = ov_mtr( i, j ); } }
   iqs::matrix::A_x_B_x_C( true, false, false, c1_mtr, ov_mtr, c2_mtr, new_ov_mtr );

   vector< multimap< double, pair <int, int> > > ov_map;
   for( int i = 0; i < new_ov_mtr.nrow(); i++ ){
     multimap< double, pair< int, int> > row_map;
     for( int j = 0; j <= i; j++ ){
      row_map.insert( pair< double, pair<int, int> >( fabs(new_ov_mtr( i, j )), make_pair< int, int >( i, j ) ) );
     }
     ov_map.push_back(row_map);
   }

   for( int i = 0; i < config.norb(); i++ ){
    multimap< double, pair<int, int> > :: reverse_iterator it_map = ov_map.at(i).rbegin();
    cout << " 1st set orb " << i << " has the largest overlap with 2nd set orb: " << (it_map->second).second << " overlap = " << it_map->first << endl;
   }

   ofstream store; store.precision(16);
   store.open("ov_orb.dat", std::ios::out );
   for( int i = 0; i < new_ov_mtr.nrow(); i++ ){ for( int j = 0; j < new_ov_mtr.ncol(); j++ ){ store << i << " " << j << " " << new_ov_mtr( i, j ) << endl;} }
   store.close();

}
