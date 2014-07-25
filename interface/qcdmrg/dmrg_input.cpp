#include "qcdmrg_class.h"
#include <stdio.h>
#include <stdlib.h>

namespace ithaca { namespace analytical {

void dmrg_input( qcdmrg_class dmrg_data ){

  FILE* fp;

  {
  char* file_name = dmrg_data._conf;
  fp = fopen( filename, "wt");
  fprintf( fp, "%2i %2i %2i\n", dmrg_data.norb, dmrg_data.na, dmrg_data.nb );
  fprintf( fp, "defaulthf\n");
  fprintf( fp, "schedule %2i\n ", dmrg_data.n_schdl );
  for( int i = 0; i < dmrg_data.n_schdl; i++ ){
    fprintf( fp, "%2i %4i 0 %10.6f %10.6f 0.0\n", dmrg_data.schedule[i].iter, dmrg_data.schedule[i].M, dmrg_data.schedule[i].david_threshold, dmrg_data.schedule[i].noise );
  }
  fprintf( fp, "nroots %i\n", dmrg_data.nroots);
  fprintf( fp, "weights ");
  for( int i = 0; i < dmrg_data.nroots; i++ ){
    fprintf( fp, "%f ", dmrg_data.weights[i] );
  }
  fprintf( fp, "\nbigdavid\n" );
  fprintf( fp, "maxiter %2i\n", dmrg_data.maxiter );
  fprintf( fp, "oneintegral %s\n", dmrg_data._oneintegral );
  fprintf( fp, "twointegral %s\n", dmrg_data._twointegral );
  fprintf( fp, "twodot_to_onedot %2i\n", dmrg_data.two_to_one );
  fprintf( fp, "sweep_tol %10.6f\n", dmrg_data.sweep_tol);
  fclose(fp);
  }

  {
  char* file_name = dmrg_data._conf_genblock;
  fp = fopen( filename, "wt");
  fprintf( fp, "%2i %2i %2i\n", dmrg_data.norb, dmrg_data.na, dmrg_data.nb );
  fprintf( fp, "defaulthf\n");
  fprintf( fp, "schedule %2i\n ", dmrg_data.n_schdl );
  for( int i = 0; i < dmrg_data.n_schdl; i++ ){
    fprintf( fp, "%2i %4i 0 %10.6f %10.6f 0.0\n", dmrg_data.schedule[i].iter, dmrg_data.schedule[i].M, dmrg_data.schedule[i].david_threshold, dmrg_data.schedule[i].noise );
  }
  fprintf( fp, "nroots %i\n", dmrg_data.nroots);
  fprintf( fp, "weights ");
  for( int i = 0; i < dmrg_data.nroots; i++ ){
    fprintf( fp, "%f ", dmrg_data.weights[i] );
  }
  fprintf( fp, "\nbigdavid\n" );
  fprintf( fp, "maxiter %2i\n", dmrg_data.maxiter );
  fprintf( fp, "oneintegral %s\n", dmrg_data._oneintegral );
  fprintf( fp, "twointegral %s\n", dmrg_data._twointegral );
  fprintf( fp, "twodot_to_onedot %2i\n", dmrg_data.two_to_one );
  fprintf( fp, "docd\n");
  fprintf( fp, "sweep_tol %10.6f\n", dmrg_data.sweep_tol);
  fprintf( fp, "genblock\n");
  fclose(fp);
  }

  {
  char* file_name = dmrg_data._conf_onepdm;
  fp = fopen( filename, "wt");
  fprintf( fp, "%2i %2i %2i\n", dmrg_data.norb, dmrg_data.na, dmrg_data.nb );
  fprintf( fp, "defaulthf\n");
  fprintf( fp, "schedule %2i\n ", dmrg_data.n_schdl );
  for( int i = 0; i < dmrg_data.n_schdl; i++ ){
    fprintf( fp, "%2i %4i 0 %10.6f %10.6f 0.0\n", dmrg_data.schedule[i].iter, dmrg_data.schedule[i].M, dmrg_data.schedule[i].david_threshold, dmrg_data.schedule[i].noise );
  }
  fprintf( fp, "nroots %i\n", dmrg_data.nroots);
  fprintf( fp, "weights ");
  for( int i = 0; i < dmrg_data.nroots; i++ ){
    fprintf( fp, "%f ", dmrg_data.weights[i] );
  }
  fprintf( fp, "\nbigdavid\n" );
  fprintf( fp, "maxiter %2i\n", dmrg_data.maxiter );
  fprintf( fp, "oneintegral %s\n", dmrg_data._oneintegral );
  fprintf( fp, "twointegral %s\n", dmrg_data._twointegral );
  fprintf( fp, "docd\n");
  fprintf( fp, "twodot_to_onedot %2i\n", dmrg_data.two_to_one );
  fprintf( fp, "sweep_tol %10.6f\n", dmrg_data.sweep_tol);
  fprintf( fp, "onepdm\n");
  fclose(fp);
  }

  {
  char* file_name = dmrg_data._conf_twopdm;
  fp = fopen( filename, "wt");
  fprintf( fp, "%2i %2i %2i\n", dmrg_data.norb, dmrg_data.na, dmrg_data.nb );
  fprintf( fp, "defaulthf\n");
  fprintf( fp, "schedule %2i\n ", dmrg_data.n_schdl );
  for( int i = 0; i < dmrg_data.n_schdl; i++ ){
    fprintf( fp, "%2i %4i 0 %10.6f %10.6f 0.0\n", dmrg_data.schedule[i].iter, dmrg_data.schedule[i].M, dmrg_data.schedule[i].david_threshold, dmrg_data.schedule[i].noise );
  }
  fprintf( fp, "nroots %i\n", dmrg_data.nroots);
  fprintf( fp, "weights ");
  for( int i = 0; i < dmrg_data.nroots; i++ ){
    fprintf( fp, "%f ", dmrg_data.weights[i] );
  }
  fprintf( fp, "\nbigdavid\n" );
  fprintf( fp, "maxiter %2i\n", dmrg_data.maxiter );
  fprintf( fp, "oneintegral %s\n", dmrg_data._oneintegral );
  fprintf( fp, "twointegral %s\n", dmrg_data._twointegral );
  fprintf( fp, "docd\n");
  fprintf( fp, "twodot_to_onedot %2i\n", dmrg_data.two_to_one );
  fprintf( fp, "sweep_tol %10.6f\n", dmrg_data.sweep_tol);
  fprintf( fp, "twopdm\n");
  fclose(fp);
  }

}

} }
