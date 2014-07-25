#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "qcwrite.h"
#include <iostream>

using namespace std;

cphf::qcwrite::psiwrite::psiwrite( std::string dir_work, std::string psi_infile, double distance)
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
