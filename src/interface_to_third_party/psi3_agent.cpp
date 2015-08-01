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

#include <string>

namespace iquads {

namespace interface_to_third_party {

string Psi3Agent :: write_input( std::string dir_work, std::string psi_infile, double distance)
{
  std::string file_path =  dir_work + psi_infile;
//  cout << file_path << endl;
  char* file = (char*) file_path.c_str();
  FILE* fp = fopen( file ,"w");
  fprintf(fp,"psi: (\n");
  fprintf(fp,"  exec = (\n" );
   char a =  char('"') ;
  fprintf(fp,"  %cinput%c \n", a, a);
  fprintf(fp,"  %ccints%c \n", a, a);
  fprintf(fp,"  %ccscf%c \n", a, a);
  fprintf(fp,"  %ccints --deriv1%c\n", a, a);
  fprintf(fp,"  %ccints --deriv2%c\n", a, a);
  fprintf(fp,"  )\n");
  fprintf(fp,"\n");
  fprintf(fp,"  label = %cSTO-3G H2%c\n", a, a);
  fprintf(fp,"  jobtype = sp\n");
  fprintf(fp,"  wfn = scf\n");
  fprintf(fp,"  reference = rhf\n");
  fprintf(fp,"  dertype = second\n");
  fprintf(fp,"  subgroup = c1\n");
  fprintf(fp,"  basis = %cSTO-3G%c\n",a, a);
  fprintf(fp,"  puream = false\n");
  fprintf(fp,"  convergence = 13\n");
  fprintf(fp,"  conv = 10\n");
  fprintf(fp,"  zmat = (\n");
  fprintf(fp,"  h\n");
  fprintf(fp,"  h 1 %f\n",distance/1.889725988579e0);
  fprintf(fp,"  )\n");
  fprintf(fp,"  print = 5\n");
  fprintf(fp,"  print_mos = true\n");
  fprintf(fp,"  )");
  fclose(fp);

};

} // end of namespace interface_to_third_party

} // end of namespace iquads
