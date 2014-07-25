#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include "matrix/square_matrix.h"
#include "rcm/star_matrix.h"
#include "rcm/rcm_main.h"
#include "rcm.h"

using namespace std;

int main( int argc, char* argv[] )
{

   if( argc !=1 ){
    if( ( argv[1][0] == '-' ) && ( argv[1][1] == 'r' ) ){

     if( argc != 6 ){ iqs::rcm::rcm_help(); exit(1); }

     cout << " Entering reorder mode " << endl;

     bool exchange = false;
     if( argv[2][0] == 'e' ){ exchange = true; }
     else if( argv[2][0] == 'h' ){ exchange = false;}
     string filename = argv[3];
     double threshold = atof(argv[4]);
     double show_threshold = atof( argv[5] );
     char type;

     if( exchange == true ){ type = 'e'; } else { type = 'h'; }
     iqs::matrix::square_matrix mtr = iqs::rcm::input_matrix( filename , type );
     int dim = mtr.get_dim();
     iqs::rcm::star_matrix star_mat( threshold, mtr );

     star_mat.print_star_mat();

     vector<int> xadjv, adjv;
     star_mat.generate_adj( xadjv, adjv );

     vector<int> new_order = star_mat.reorder( xadjv, adjv );
     for( int i = 0; i < new_order.size(); i++ ){ cout << new_order.at(i) + 1 << "," ; }
     cout << endl;
     for( int i = 0; i < new_order.size(); i++ ){
     }
//     FILE* fp = fopen("genetic_reorder.dat", "wt" );
//     for( int i = 0; i < new_order.size(); i++ ){ fprintf( fp, "%i,", new_order.at(i)+1); }

     int nocc = 15;
//     iqs::matrix::square_matrix fock = iqs::rcm::calc_fock( dim, nocc, filename );
//     exit(1);

     iqs::matrix::square_matrix u( dim );
     for( int i = 0; i < dim; i++ ){ for( int j = 0; j < dim; j++ ){ u(i,j) = 0.0e0; } }
     for( int i = 0; i < dim; i++ ){
      int ii = new_order.at(i);
      int jj = i;
      u(  jj, ii  ) = 1.0e0;
     }

     iqs::matrix::square_matrix new_mtr = mtr.transform( u );

     iqs::rcm::star_matrix new_star_mat( show_threshold, new_mtr );
     new_star_mat.print_star_mat();
     cout << " number of stars( non-zero elements ) = " << new_star_mat.nstar() << endl;
    }
    else if ( ( argv[1][0] == '-' ) && ( argv[1][1] == 's' ) ){

     if( argc != 6 ){ iqs::rcm::rcm_help(); exit(1); } 

     cout << " Entering show mode " << endl;

     bool print_hii;

     bool exchange;
     if( argv[2][0] == 'e' ){ exchange = true; }
     else if( argv[2][0] == 'h' ){ exchange = false;}
     string integral_file = argv[3];
     string reorder_file = argv[4];
     double threshold = atof( argv[5] );

     char type;
     if( exchange == true ){ type = 'e'; }else{ type = 'h';}

     iqs::matrix::square_matrix mtr = iqs::rcm::input_matrix( integral_file, type );
     int dim = mtr.get_dim();
     vector<int> order;
     FILE* fp = fopen( reorder_file.c_str(), "rt");
     int val;
     for( int i = 0; i < dim; i++ ){ fscanf(fp, "%d,", &val); order.push_back(val-1); }

     if( exchange == false ){
        map<double, int> diag_map;
        for( int i = 0; i < order.size(); i++ ){ diag_map.insert( make_pair<double, int>( mtr(order.at(i), order.at(i) ), order.at(i) ) ); }
        map<double, int>::iterator it_diag;
        for( it_diag = diag_map.begin(); it_diag != diag_map.end(); ++it_diag ){
          cout << "h(" << it_diag->second << "," << it_diag->second << " ) = " << it_diag->first << endl; 
        }
     }

     iqs::matrix::square_matrix u( dim );
     for( int i = 0; i < dim; i++ ){
      int ii = order.at(i);
      int jj = i;
      u( jj, ii ) = 1.0e0;
     }
     iqs::matrix::square_matrix new_mtr = mtr.transform( u );
     ofstream ofs;
     ofs.open( "kij.txt", std::ofstream::out );
     ofs.precision(10);
     for( int i = 0; i < dim; i++ ){
      for( int j = 0; j < dim; j++ ){
       ofs << new_mtr(i,j) << endl;
      }
     }
     ofs.close();
     iqs::rcm::star_matrix new_star_mat( threshold, new_mtr );
     new_star_mat.print_star_mat();
     cout << " number of stars( non-zero elements ) = " << new_star_mat.nstar() << endl;

    }
   }
   else if( argc == 1 ){ 
     iqs::rcm::rcm_help(); exit(1);
   }

}
