#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include "interface/psi3/qcread.h"
#include "tensor/tensor.h"

using namespace std;

int psi_natom( std::string file_path );
int psi_nbas ( std::string file_path );
int psi_nocc ( std::string file_path );

int psi_nocc( std::string file_path )
{
   int retval;
   {
      char line[500];
      char* filename = (char*) file_path.c_str();
      ifstream ifs( filename, std::ios::in );
      while( ifs.getline(line,500) )
      {
        if( strncmp(line, "  DOCC:", 7) == 0 )
        {
         sscanf(line,"  DOCC:              %d", &retval);
         break;
        }
      }

   }
   return retval;
}

int psi_natom( std::string file_path )
{
   int retval;
   {
     char line[500];
     char* filename = (char*) file_path.c_str();
//     cout << filename << endl;
     ifstream ifs( filename, std::ios::in );
     while( ifs.getline(line, 500) )
     {
//	cout << line << endl;
	if( strncmp(line,"    Number of atoms", 19) == 0)
        {
//          char cval = line[31];
//          cout << cval << endl;
//          retval = atoi(&cval);
	sscanf(line,"    Number of atoms          =%2d", &retval);
//        cout << retval << endl;
          break;
        }
     }
   }
   return retval;
}

int psi_nbas( std::string file_path )
{
   int retval;
   {
     char line[500];
     char* filename = (char*) file_path.c_str();
//     cout << filename << endl;
     ifstream ifs( filename, std::ios::in );
     while( ifs.getline(line, 500) )
     {
//      cout << line << endl;
      if( strncmp(line,"    Number of AO", 16) == 0)
      {
//        char cval = line[29];
//        retval = atoi(&cval);
	sscanf(line,"    Number of AO          =%2d", &retval);
//        cout << retval << endl;
        break;
      }
     }
   }
//    return 2;
   return retval;
}

double ithaca::qcread::psiread::nuclear_rep( std::string dir_work, std::string psi_outfile)
{
  double retval;

  char line[500];
  string file_path = dir_work + psi_outfile;
  char* file = (char*) file_path.c_str();
  ifstream ifs( file, std::ios::in);
  while( ifs.getline(line, 500) )
  {
    if( strncmp(line,"  nuclear repulsion energy", 26) == 0 )
    {
      sscanf(line,"  nuclear repulsion energy %lf", &retval);
    }
  }
  return retval;
}

void ithaca::qcread::psiread::coord_read( std::string dir_work, std::string psi_outfile)
{
  int natom = this->natom;

  char line[500];
  string file_path = dir_work + psi_outfile;
  char* file = (char*) file_path.c_str();

  ifstream ifs( file, std::ios::in );
  while( ifs.getline(line,500) )
  {
    if( strncmp(line,"  -Geometry after Center-of-Mass",32) == 0  )
    break;
  }
  ifs.getline(line,500);
  ifs.getline(line,500);

  char atom_name[16]; double x,y,z;
  for( int i = 0; i < natom; i++ ){
   ifs.getline(line,500);
    sscanf(line,"%16c  %lf  %lf  %lf\n", atom_name, &x, &y, &z);
    this->coord[i][0] = x;
    this->coord[i][1] = y;
    this->coord[i][2] = z; 
  }
};

void ithaca::qcread::psiread::u_a_read( string dir_work, double** u_a)
{
  int ncoord = this->ncoord;
  int norb   = this->norb;

  for( int i = 0; i < ncoord; i++ ){
  char filename[100];
  sprinf(filename, "psi.u%d.dat", i);
  string file_path = dir_work + filename;
   char* file = ( char* ) file_path.c_str();
   FILE* fp = fopen(file,"r");
   int num, p1 = 0, p2 = 0; double val = 0;
   for( int j = 0; j < norb; j++ ){
    for( int k = 0; k < norb; k++ ){
      fscanf(fp, "%3d %3d %lf\n",&p1, &p2, &val);
      u_a[i][ j * norb + k ] = val;
    }
   }
  fclose(fp);
 }
  
}

void ithaca::qcread::psiread::c_read( string dir_work, double* c)
{
  int norb = this->norb;
  int nbas = this->nbas;

  char filename[100];
  sprintf(filename,"psi.mo.dat");
  string file_path = dir_work + filename;
  char* file = (char*) file_path.c_str();
  FILE* fp = fopen(file,"r");
  int p1, p2; double val = 0;
  for( int i = 0; i < nbas; i++ ){
   for( int j = 0; j < norb; j++ ){
    fscanf(fp, "%3d %3d %lf\n", &p1, &p2, &val );
    c[ p1 * norb + n2 ] = val;
   }
  }
  fclose(fp); 
}

void ithaca::qcread::psiread::stv_read( string dir_work, const char* stv_name, double* stv)
{
  int ncoord = this->ncoord;
  int norb   = this->norb;

// I doubt these statement for files will cause problems in g++
// icpc recommended !!!
  char filename[100];
  sprintf(filename, "psi.%s.dat",stv_name);
  {
   string file_path = dir_work + filename;
   char* file = (char*) file_path.c_str();
   FILE* fp = fopen(file,"r");
   int num, p1 = 0, p2 = 0; double val = 0;

//   while( feof(fp) == 0 )
   while( true )
   {
     fscanf(fp,"%3d %lf\n",&num, &val);
     if(num == 0 )break;
     if( fabs(val - 1.0e-10 ) < 1.0e-6 ) break;
     stv[p1 * nbas + p2] = val;
     stv[p2 * nbas + p1] = val;

//    cout << stv_name <<"["<<  p1 << "][" << p2 << "] = " << stv[p1][p2] << endl;
     p2 = p2 + 1;
     if( p2 > p1 ){ p2 = 0; p1 = p1 + 1; }   
  
   }
   fclose(fp);

  }

}

void ithaca::qcread::psiread::stv_read( string dir_work, const char* stv_name, double** stv)
{
  int ncoord = this->ncoord;
  int nbas   = this->nbas;

  for( int i = 0; i < ncoord; i++ )
  {

   char filename[100];
   sprintf(filename,"psi.%s%i.dat", stv_name, i);

   {
   string file_path = dir_work + filename;
   char* file = (char*) file_path.c_str();
   FILE* fp = fopen(file, "r");

//   cout << file << endl;


// Note: val = 0 as initial value. 
//       psi3 prints out values when >= 1e-6
//       If val is still 0 after using fscanf()
//       then it means the file is empty and 
//       loop needs to be ended.
     int p1, p2; double val = 0.0;
//     while( feof(fp) == 0  )
     while( true )
     {
// ----------------------------------------------------
//  Hint:
//       In c/c++, the format in (f)scanf() and in 
//       printf() for double are different.
//       If one wants to use fscanf() to get a double
//       precision from a file, he will need to use
//       the argument of "%lf" RATHER THAN things like
//       "20.16f". 
//       However, in printf() for double, he can still 
//       use formatted output "%20.14f" 
// ----------------------------------------------------
//
        fscanf(fp,"%3d %3d %lf\n",&p1,&p2,&val);
        if( fabs(val - 1.0e-10) < 1.0e-6 )break;
        stv[i][p1 * nbas + p2] = val;
        stv[i][p2 * nbas + p1] = val;
//          cout << stv_name << "_a[" << i << "][" << p1 << "][" << p2 << "] = " << stv[i][p1][p2] << endl;
     }
        fclose(fp);
   }
  
//  stv[j][i] = stv[i][j]
/*    for( int j = 0; j < nbas; j++ ){
     for( int k = 0; k <= j ; k++ ){
       stv[i][k][j] = stv[i][j][k];
     }
    } */
  }

} // end of cphf::qcread::psiread::stv_read()

void ithaca::qcread::psiread::grad_enuc_read( std::string dir_work, double* grad_enuc)
{
   int ncoord = this->ncoord;
   char filename[100];
   sprintf(filename, "psi.grad_enuc.dat");
   std::string file_path = dir_work + filename;
   char* file = (char*) file_path.c_str();

   int p1,p2; double val;
   FILE* fp = fopen(file,"r");
   for( int i = 0; i < ncoord; i++ ){
    fscanf(fp,"%3d %3d %lf\n",&p1,&p2,&val);
    grad_enuc[i] = val;
   }
   fclose(fp);

};

void ithaca::qcread::psiread::hessian_read( std::string dir_work, double** hessian )
{
   int nccord = this->ncoord;
   char filename[100];
   sprintf(filename,"psi.hess.dat");
   std::string file_path = dir_work + filename;
   char* file = (char*) file_path.c_str();

   int p1,p2; double val;
   FILE*fp = fopen(file,"r");
   for( int i = 0; i < ncoord; i++ ){
    for( int j = 0; j < ncoord; j++ ){
     fscanf(fp,"%3d %3d %lf\n",&p1,&p2,&val);
     hessian[i][j] = val;
    }
   }
   fclose(fp);
};

void ithaca::qcread::psiread::eri_read( string dir_work, const char* eri_name, double**** eri)
{
   int ncoord = this->ncoord;
   int nbas   = this->nbas;

   char filename[100];
   sprintf(filename,"psi.%s.dat",eri_name);
   std::string file_path  = dir_work + filename;
   char* file = (char*) file_path.c_str();

//   cout << file << endl;

   FILE* fp = fopen(file, "r" );
   int p1,p2,p3,p4; double val = 0 ;

//   while( feof(fp) == 0 )
   while( true )
   {
     fscanf(fp,"%5d%5d%5d%5d%lf\n", &p1,&p2,&p3,&p4,&val);
//     cout << p1 << p2 << p3 << p4 << val << endl;

     if( fabs( val - 1.0e-10) < 1.0e-6 ) break;
     p1--; p2--; p3--; p4--;
     eri[p1*nbas*nbas*nbas + p2*nbas*nbas + p3*nbas + p4] = val;
     eri[p2*nbas*nbas*nbas + p1*nbas*nbas + p3*nbas + p4] = val;
     eri[p1*nbas*nbas*nbas + p2*nbas*nbas + p4*nbas + p3] = val;
     eri[p2*nbas*nbas*nbas + p1*nbas*nbas + p4*nbas + p3] = val;

     eri[p3*nbas*nbas*nbas + p4*nbas*nbas + p1*nbas + p2] = val;
     eri[p4*nbas*nbas*nbas + p3*nabs*nbas + p1*nbas + p2] = val;
     eri[p3*nbas*nbas*nbas + p4*nbas*nbas + p2*nbas + p1] = val;
     eri[p4*nbas*nbas*nbas + p3*nbas*nbas + p2*nbas + p1] = val;
   }
   fclose(fp);

}

void ithaca::qcread::psiread::eri_read( string dir_work, const char* eri_name, double** eri )
{
   int ncoord = this->ncoord;
   int nbas   = this->nbas;

   for( int ii = 0; ii < ncoord; ii++ )
   {
     char filename[100];
     sprintf(filename,"psi.%s%i.dat",eri_name, ii );
     {
       std::string file_path = dir_work + filename;
//       cout << file_path << endl;
       char* file = (char*) file_path.c_str();

       FILE* fp  = fopen( file, "r");
       int p1, p2, p3, p4; double val = 0.0;

//       while( !feof(fp) )
        while( true )
       {
         fscanf(fp,"%3d %3d %3d %3d %lf\n",&p1,&p2,&p3,&p4,&val);
         if( fabs(val - 1.0e-10) < 1.0e-6 )break;
         eri[ii][p1*nbas*nbas*nbas + p2*nbas*nbas + p3*nbas + p4] = val;
         eri[ii][p2*nbas*nbas*nbas + p1*nbas*nbas + p3*nbas + p4] = val;
         eri[ii][p1*nbas*nbas*nbas + p2*nbas*nbas + p4*nbas + p3] = val;
         eri[ii][p2*nbas*nbas*nbas + p1*nbas*nbas + p4*nbas + p3] = val;

         eri[ii][p3*nbas*nbas*nbas + p4*nbas*nbas + p1*nbas + p2] = val;
         eri[ii][p4*nbas*nbas*nbas + p3*nbas*nbas + p1*nbas + p2] = val;
         eri[ii][p3*nbas*nbas*nbas + p4*nbas*nbas + p2*nbas + p1] = val;
         eri[ii][p4*nbas*nbas*nbas + p3*nbas*nbas + p2*nbas + p1] = val;
//         cout << eri_name << "[" << ii << "][" << p1 << "][" << p2 << "][" << p3 << "][" << p4 << 
//            "] = " <<  eri[ii][p1][p2][p3][p4] <<  endl;
       }
       fclose(fp);

     }
   }
  
} // end of cphf::qcread::psiread::eri_read

double** ithaca::qcread::psiread::hc()
{
  for( int i = 0; i < nbas; i++){
   for( int j = 0; j < nbas; j++ ){
     this->hcore[j*nbas + i] = this->t[j*nbas + i] + this->v[j*nbas + i];
   }
  }
  return this->hcore;
}

double*** ithaca::qcread::psiread::hc_a()
{
  for( int i = 0; i < ncoord; i++ ){
   for( int j = 0; j < nbas; j++ ){
    for( int k = 0; k < nbas; k++ ){
    this->hcore_a[i][j*nbas + k] = this->t_a[i][j*nbas + k] + this->v_a[i][j*nbas + k];
    }
   }
  }
  return this->hcore_a;
}

double* read_array_1d ( char* array_name, int dim )
{
  double* array = new double [dim];
  for( int i = 0; i < dim; i++ ){ array[i] = 0.0e+00; }

  string file_name = array_name + ".tmp";
  char* _file_name = ( char* ) file_name.c_str();
  FILE* fp = fopen( _file_name, "r");
  int p1,p2; double val;
  for( int i = 0; i < dim; i++ ){
    fscanf(fp, "%3i %3i %lf\n ",&p1, &p2, &val);
    array[i] = val;
  }
  fclose(fp);

  return array;
}


double** read_array_2d ( char* array_name, int dim1, int dim2 )
{
  double** array = new double* [dim1];
  for( int i = 0; i < dim1; i++ ){
    array[i] = new double [dim2];
  }
  for( int i = 0; i < dim1; i++ ){
   for( int j = 0; j < dim2; j++ ){
    array[i][j] = 0.0e+00;
   }
  }

  for( int i = 0; i < dim1; i++ ){
    char* index;
    index = itoa( i, index, 10 );
    string file_name = array_name + index + ".tmp";
    char* _file_name = ( char* ) file_name.c_str();
    FILE* fp = fopen( _file_name, "r");
    int p1,p2; double val;
    for( int i = 0; i < dim; i++ ){
      fscanf(fp, "%3i %3i %lf\n ",&p1, &p2, &val);
      array[i][j] = val;
    }
    fclose(fp);
  }

  return array;
}

ithaca::qcread::psiread::psiread
(std::string dir_work, std::string psi_infile, std::string psi_outfile )
{

  std::string file_path = dir_work + psi_outfile;
  this->natom  = psi_natom( file_path );
  this->ncoord = (this->natom) * 3;
  this->nbas   = psi_nbas( file_path );
  this->norb   = this->nbas;
  this->nocc   = psi_nocc( file_path );
  this->nele   = (this->nocc) * 2;
  this->nuclear_repulsion = nuclear_rep( dir_work, psi_outfile );
//  cout << nuclear_repulsion << endl;

    coord = tensor( natom, 3 , this->coord );
    this->coord_read( dir_work, psi_outfile );

    s = tensor( nbas*nbas, s );
    this->stv_read(dir_work,"s",this->s);
//    cout << s[1][1] << endl;

    t = tensor( nbas*nbas, t );
    this->stv_read(dir_work,"t",this->t);
//    cout << t[1][1] << endl;

    v = tensor( nbas*nbas, v );
    this->stv_read(dir_work,"v",this->v);
//    cout << v[1][1] << endl;

    c = tensor( nbas*norb, this->c );
    this->c_read( dir_work, this->c );

    hcore = tensor( nbas*nbas, this->hcore );
    this->hc();

    s_a = tensor( ncoord, nbas*nbas, s_a );
    this->stv_read(dir_work,"s",this->s_a );
//      cout << s_a[2][1][0] << endl;

    t_a = tensor( ncoord, nbas*nbas, t_a);
    this->stv_read(dir_work,"t",this->t_a );
//      cout << t_a[2][1][0] << endl;

    v_a = tensor( ncoord, nbas*nbas, v_a);
    this->stv_read(dir_work,"v",this->v_a );
//      cout << v_a[2][1][0] << endl;

    hcore_a = tensor( ncoord, nbas*nbas, hcore_a);
    this->hcore_a = this->hc_a();

    this->grad_enuc = tensor( ncoord, this->grad_enuc );
    this->grad_enuc_read( dir_work, this->grad_enuc );


    this->eri = tensor( nbas*nbas*nbas*nbas, this->eri );
    this->eri_read(dir_work,"eriout",this->eri);  

    this->eri_a = tensor( ncoord, nbas*nbas*nbas*nbas, this->eri_a);
    this->eri_read(dir_work,"eri",this->eri_a);


//    this->hessian = tensor( ncoord, ncoord, this->hessian );
//    this->hessian_read( dir_work, this->hessian );

    this->u_a = tensor( ncoord, norb*norb, this->u_a );
    this->u_a_read( dir_work, this->u_a );

}
