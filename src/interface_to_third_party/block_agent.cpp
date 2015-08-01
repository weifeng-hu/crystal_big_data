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

#include <interface_to_third_party/external_program_agent.h>

namespace iquads {

namespace interface_to_third_party {

void BlockAgent :: write_input()
{

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

} // end of namespace interface_to_third_party

} // end of namespace iquads
