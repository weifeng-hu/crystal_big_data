#include <fstream>
#include <iostream>
#include <string>
#include "transform_info.h"

using namespace std;

namespace ph_analysis{

int transform_info::read()
{

  {
   ifstream ifs;
   ifs.open( this->configfile.c_str() );

   string entry;
   while( ifs.good() ){
    ifs >> entry;
    if( entry == "basename" ) ifs >> this->basename;
    if( entry == "prefix" ) ifs >> this->prefix;
    if( entry == "norb"     ) ifs >> this->norb;
    if( entry == "nact"     ) ifs >> this->nact;
    if( entry == "t1_thresh") ifs >> this->t1_thresh;
    if( entry == "t2_thresh") ifs >> this->t2_thresh;
    if( entry == "p1_filename" ) ifs >> this->p1_filename;
    if( entry == "p2_filename" ) ifs >> this->p2_filename;
    if( entry == "solve_u" ) ifs >> this->solve_u;
    if( entry == "compute_s_only" ) ifs >> this->compute_s_only;
   }
   ifs.close();

   if( norb == 0 ){ cout << " error: norb = 0 !" << endl; abort; } 
   if( norb*norb > NMO_THRESH * NMO_THRESH ){ cout << " number of orbital is larger than limit" << endl; abort(); }
   if( basename == "not set" ){ cout << " error: basename not set " << endl; abort(); }
   if( solve_u == -1 ){ cout << " error: solve_u method not defined" << endl; abort(); }
   if( compute_s_only == -1 ){ cout << " error: compute_s_only not defined" << endl; abort(); }

   this->s_filename = prefix + basename + ".orca.sa";
   this->c_filename = prefix + basename + ".orca.mo";
   if( solve_u == 1 ) this->cl_filename = prefix + basename + ".orca.loc.mo";
   if( solve_u == 0 ) this->u_filename = prefix + basename + ".orca.u";
   this->p1_filename = prefix + basename + ".trans_onepdm";
   this->p2_filename = prefix + basename + ".trans_twopdm";
   this->act_filename = prefix + basename + ".orca.act_orbs";

   cout << " basename = " << basename << endl;
   cout << " prefix = " << prefix << endl;
   cout << " norb = " << norb << endl;
   cout << " nact = " << nact << endl;
   cout << " t1_thresh = " << t1_thresh << endl;
   cout << " t2_thresh = " << t2_thresh << endl;
   cout << " s_filename = " << s_filename << endl;
   cout << " c_filename = " << c_filename << endl;
   cout << " cl_filename = " << cl_filename << endl;
   cout << " u_filename = " << u_filename << endl;
   cout << " p1_filename = " << p1_filename << endl;
   cout << " p2_filename = " << p2_filename << endl;
   cout << " act_filename = " << act_filename << endl;
   cout << " solve_u = " << solve_u << endl;
   cout << " compute_s_only = " << compute_s_only << endl;
  }

  {
    this->s_ov.set_nao() = this->norb;
    this->s_ov.set_nmo() = this->norb;
    FILE* f_ov = fopen( s_filename.c_str(), "rt" );
    for( int i = 0; i < norb; i++ ){
     for( int j = 0; j < norb; j++ ){
      double value;
      int ind_i, ind_j;
      fscanf( f_ov, "%d %d %lf", &ind_i, &ind_j, &value );
      s_ov( ind_j-1, ind_i-1 ) = value;
     }
    }
    fclose(f_ov);
  }

  {
    this->s_full.set_nao() = this->norb;
    FILE* f_ov = fopen( s_filename.c_str(), "rt" );
    for( int i = 0; i < norb; i++ ){
     for( int j = 0; j < norb; j++ ){
      double value;
      int ind_i, ind_j;
      fscanf( f_ov, "%d %d %lf", &ind_i, &ind_j, &value );
      s_full( ind_j-1, ind_i-1 ) = value;
     }
    }
    fclose(f_ov);
    s_full.compute_auxiliary();
    s_full.print_inversehalf( prefix, basename );
    if( this->compute_s_only != 0 ){ return 0;}
  }

  {
    this->c_mo.set_nao() = this->norb;
    this->c_mo.set_nmo() = this->norb;
    FILE* f_cmo = fopen( c_filename.c_str(), "rt" );
    for( int i = 0; i < norb; i++ ){
     for( int j = 0; j < norb; j++ ){
      double value;
      int ind_i, ind_j;
      fscanf( f_cmo, "%d %d %lf", &ind_i, &ind_j, &value );
      c_mo( ind_i-1, ind_j-1 ) = value;
     }
    }
    fclose(f_cmo);
  }

  {
    FILE* fact = fopen( act_filename.c_str(), "rt" );
    for( int i = 0; i < nact; i++ ){
     int value;
     fscanf( fact, "%d", &value );
     active_space.at(i) = value;
    }
    fclose(fact);
  }

  if( cl_filename != "not set" && u_filename == "not set" )
  {
    this->c_lmo.set_nao() = this->norb;
    this->c_lmo.set_nmo() = this->norb;
    FILE* f_clmo = fopen( cl_filename.c_str(), "rt" );
    for( int i = 0; i < norb; i++ ){
     for( int j = 0; j < norb; j++ ){
      double value;
      int ind_i, ind_j;
      fscanf( f_clmo, "%d %d %lf", &ind_i, &ind_j, &value );
      c_lmo( ind_i-1, ind_j-1 ) = value;
     }
    }
    fclose(f_clmo);
  }

  if( cl_filename == "not set" && u_filename != "not set" )
  {
    this->u_tr.set_nao() = this->norb;
    this->u_tr.set_nmo() = this->norb;
    FILE* f_utr = fopen( u_filename.c_str(), "rt" );
    for( int i = 0; i < norb; i++ ){
     for( int j = 0; j < norb; j++ ){
      double value;
      int ind_i, ind_j;
      fscanf( f_utr, "%lf %d %d", &value, &ind_j, &ind_i );
      u_tr( ind_i-1, ind_j-1 ) = value;
     }
    }
    fclose(f_utr);
  }

  {
    FILE* f_act = fopen( act_filename.c_str(), "rt");
    for( int i = 0; i < nact; i++ ){
     int value;
     fscanf( f_act, "%d", &value );
     active_space.at(i) = value;
    }
    fclose( f_act );
  }

  // temperarily set gamma1
  // only one element
  this->gamma1.set_norb() = this->nact;
  this->gamma1.set_n_element() = nact * nact;
  this->gamma1.set_store().fill(0.0e0);
//  this->gamma1( 5, 4 ) = 1.3338e0;

  {
    ifstream if1pdm;
    if1pdm.open( p1_filename.c_str() );
    while( if1pdm.good() ){
      double value;
      int ind_i, ind_j;
      if1pdm >> value >> ind_i >> ind_j;
      gamma1(ind_i, ind_j) = value;
    }
    if1pdm.close();
  }

/*
  {
    FILE* f_2pdm = fopen( p2_filename.c_str(), "rt" );
    for( int i = 0; i < norb; i++ ){
     for( int j = 0; j < norb; j++ ){
      for( int k = 0; k < norb; k++ ){
       for( int l = 0; l < norb; l++ ){
        double value;
        int ind_i, ind_j, ind_k, ind_l;
        fscanf( f_2pdm, "%lf %d %d %d %d", &value, &ind_i, &ind_j, &ind_k, &ind_l );
        gamma2(ind_i, ind_j, ind_k, ind_l) = value;
       }
      }
     }
    }
    fclose(f_2pdm);
  }
*/
  // compute inverse of C

  return 0;

}

transform_info::transform_info( std::string inputfile )
{

  this->norb = 0;
  this->nact = 0;
  this->t1_thresh = 1.0e-2;
  this->t2_thresh = 1.0e-2;

  this->active_space.fill(0);

  this->configfile = "not set";
  this->basename = "not set";
  this->prefix = "";
  this->p1_filename = "not set";
  this->p2_filename = "not set";
  this->s_filename = "not set";
  this->c_filename = "not set";
  this->cl_filename = "not set";
  this->u_filename = "not set";
  this->act_filename = "not set";
  this->solve_u = -1;
  this->compute_s_only = -1;

  this->configfile = inputfile;

  
  this->read();

}

} // end of ph_analysis
