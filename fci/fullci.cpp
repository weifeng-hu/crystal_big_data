#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <mkl.h>
#include "fullci.h"

using namespace std;

void init (int size , int rank)
{
  FILE *fp;
  int i,j,k,l;

// Read the config file

  fp = fopen("config.txt","r");
  fscanf(fp,"%i\n",&sitenum);
  fscanf(fp,"%i\n",&ne);
  fscanf(fp,"%i %i\n",&Nbasis,&Norb);
  fclose(fp);

// Allocate T
  TAO = new double* [sitenum];
  T = new double* [sitenum];
  oeindex = new int *[sitenum];
  for( i = 0; i < sitenum; i++ )
  { 
    TAO[i] = new double [sitenum];
    T[i] = new double [sitenum];
    oeindex[i] = new int [sitenum];
  }

// Read the integrals
//
   fp = fopen("115.0","r");
   for( i = 1; i <= Nbasis; i++ )
   {
      for( j = 1; j <= Nbasis; j++ )
      {
         fread(&TAO[i-1][j-1],sizeof(double),1,fp);
      }
   }
   fclose(fp);

//	printmtr(sitenum, TAO);

   if( sitenum == 2 ){
   T[0][0]=-1.93210836498900;
   T[0][1]=-0.319236256757229;
   T[1][0]=-0.319236256757229;
   T[1][1]=0.379664574938506; }

// Allocate U
   UAO = new double*** [sitenum];
   U = new double*** [sitenum];
   teindex = new int *** [sitenum];
   for( i = 0; i < sitenum; i++)
   {
     UAO[i] = new double** [sitenum];
     U[i] = new double** [sitenum];
     teindex[i] = new int ** [sitenum];
     for( j = 0; j < sitenum; j++){
     UAO[i][j] = new double* [sitenum];
     U[i][j] = new double* [sitenum];
     teindex[i][j] = new int * [sitenum];
       for( k = 0; k < sitenum; k++ ){
       UAO[i][j][k] = new double [sitenum];
       U[i][j][k] = new double [sitenum];
       teindex[i][j][k] = new int [sitenum];
       }
     }
   }

   int noeterm = pow(sitenum,2);
   k = 0;
   for( i = 0; i < sitenum; i++){
     for( j = 0; j < sitenum; j++){
     oeindex[i][j] = k;
    if(rank ==0 ){
     printf("%i %i %i\n",i,j,k);}
    k++;
     if( k == size ){ k = 0;}
     }
   }

   int icount = 0 ;
   for( i = 0; i < sitenum; i++ ){
     for( j = 0; j < sitenum; j++ ){
       for( k = 0; k < sitenum; k++ ){
         for( l = 0; l < sitenum; l++ ){
           teindex[i][j][k][l] = icount;
           if( rank == 0 ){
            printf( "%i %i %i %i %i\n", i,j,k,l,icount);
           }
           icount++;
           if( icount == size){ icount = 0; }
         }
       }
     }
   }

   MPI::COMM_WORLD.Barrier();
//   MPI::Finalize();
//   exit(1);

   fp = fopen("21.0","r");
   for( i = 1 ; i <= Nbasis; i++ ){
      for( j = 1; j <= Nbasis; j++ ){
         for( k = 1; k <= Nbasis; k++ ){
            for( l = 1; l <= Nbasis; l++){
               fread(&UAO[i-1][k-1][l-1][j-1],sizeof(double),1,fp);
            }
         }
      }
   }
   fclose(fp);

   if( sitenum == 2 ){ 
   U[0][0][0][0]=1.02853685633769;
   U[0][0][0][1]=0.319236255533611;
   U[0][0][1][0]=0.319236255533611;
   U[0][0][1][1]=0.261994438165160;
   U[0][1][0][0]=0.319236255533611;
   U[0][1][0][1]=0.261994438165160;
   U[0][1][1][0]=0.982016253329032;
   U[0][1][1][1]=0.343809128053079;
   U[1][0][0][0]=0.319236255533611;
   U[1][0][0][1]=0.982016253329032;
   U[1][0][1][0]=0.261994438165160;
   U[1][0][1][1]=0.343809128053079;
   U[1][1][0][0]=0.261994438165160;
   U[1][1][0][1]=0.343809128053079;
   U[1][1][1][0]=0.343809128053079;
   U[1][1][1][1]=0.998335018428651;}

// Read the MO coefficients
   coeff_alpha = new double* [Norb];
   coeff_beta = new double* [Norb];
   for( i = 0 ; i < Nbasis; i++ ){
     coeff_alpha[i] = new double [Nbasis];
     coeff_beta[i] = new double [Nbasis];
   }

   orb_energy_alpha = new double [Norb];
   orb_energy_beta = new double [Norb];

   fp = fopen("53.0","r");
   for( i = 0; i < Nbasis; i++){
     for( j = 0; j < Norb; j++){
       fread(&coeff_alpha[i][j],sizeof(double),1,fp);
     }
   }

   for( i = 0; i < Nbasis; i++){
     for( j = 0; j < Norb; j++){
       fread(&coeff_beta[i][j],sizeof(double),1,fp);
     }
   }

   for( i = 0; i < Norb; i++ ){
       fread(&orb_energy_alpha[i],sizeof(double),1,fp);
   }
   for( i = 0; i < Norb; i++ ){
       fread(&orb_energy_beta[i],sizeof(double),1,fp);
   }

   oo( sitenum, sitenum, coeff_alpha, TAO, UAO, T, U);

//   printmtr(sitenum,T);

//   printmtr(2,coeff_alpha);
//   printmtr(2,coeff_beta);
//   exit(1);

// Initialize the operators
  cu = new double* [4];
  cd = new double* [4];
  au = new double* [4];
  ad = new double* [4];
  for( i = 0; i < 4; i++){
    cu[i] =  new double [4];
    cd[i] =  new double [4];
    au[i] =  new double [4];
    ad[i] =  new double [4];
  }

    mtr_set_zero(4,cu);
    mtr_set_zero(4,au);
    mtr_set_zero(4,cd);
    mtr_set_zero(4,ad);
    cu[1][0] = 1.0;
    cu[3][2] = 1.0;

    cd[2][0] = 1.0;
    cd[3][1] = -1.0;

    au[0][1] = 1.0;
    au[2][3] = 1.0;

    ad[0][2] = 1.0;
    ad[1][3] = -1.0;

// unit and parity operators
   u1 = new double* [4];
   for( i = 0; i < 4; i++){
     u1[i] = new double [4];
   }
   mtr_set_zero(4,u1);
   for(i = 0; i < 4; i++){
     u1[i][i] = 1.0;
   }

   u2 = new double* [16];
   for( i = 0; i < 16; i++){
     u2[i] = new double [16];
   }
   mtr_set_zero(16,u2);
   for(i = 0; i < 16; i++){
     u2[i][i] = 1.0;
   }

   u3 = new double* [64];
   for( i = 0; i < 64; i++){
     u3[i] = new double [64];
   }
   mtr_set_zero(64,u3);
   for(i = 0; i < 64; i++){
     u3[i][i] = 1.0;
   }

   u4 = new double* [256];
   for( i = 0; i < 256; i++){
     u4[i] = new double [256];
   }
   mtr_set_zero(256,u4);
   for(i = 0; i < 256; i++){
     u4[i][i] = 1.0;
   }

   p1 = new double* [4];
   for ( i = 0; i < 4 ; i++ ){
      p1[i] = new double [4];
   }
   mtr_set_zero(4,p1);
   p1[0][0] = 1.0;
   p1[1][1] = -1.0;
   p1[2][2] = -1.0;
   p1[3][3] = 1.0;

   p2 = new double* [16];
   for ( i = 0; i < 16; i++) { 
      p2[i] = new double [16];
   }

   for( i = 0; i < 4; i++ ){
     for( j = 0; j < 4; j++ ){
       for( k = 0; k < 4; k++ ){
         for( l = 0; l < 4; l++ ){
      p2[ k * 4 + i ][ l * 4 + j ]= p1[i][j] * p1[k][l];
         }
       }
     }
   }

   p3 = new double* [64];
   for ( i = 0; i < 64; i++) { 
      p3[i] = new double [64];
   }

   for( i = 0; i < 16; i++ ){
     for( j = 0; j < 16; j++ ){
       for( k = 0; k < 4; k++ ){
         for( l = 0; l < 4; l++ ){
      p3[ k * 16 + i ][ l * 4 + j ]= p2[i][j] * p1[k][l];
         }
       }
     }
   }
 
   p4 = new double* [256];
   for ( i = 0; i < 256; i++) { 
      p4[i] = new double [256];
   }

   for( i = 0; i < 64; i++ ){
     for( j = 0; j < 64; j++ ){
       for( k = 0; k < 4; k++ ){
         for( l = 0; l < 4; l++ ){
      p4[ k * 64 + i ][ l * 4 + j ]= p3[i][j] * p1[k][l];
         }
       }
     }
   }

  p = new pu [sitenum];

  for( i = 0; i < sitenum; i++ ) {
    p[i].dim = pow(4,i);

    p[i].mtr = new double* [ p[i].dim ];
    for( j = 0; j < p[i].dim; j++){
      p[i].mtr[j] = new double [ p[i].dim ];
    }

    if( i == 0)p[i].mtr[0][0] = 1.0;
    if( i == 1)mtrmtr(4, p1, p[i].mtr);
    if( i > 1 )mtrdppower(p1, i, p[i].mtr);

  }

  u = new pu [sitenum];

  for( i = 0; i < sitenum;i++ ) {
    u[i].dim = pow(4,i);

    u[i].mtr = new double* [ u[i].dim ];
    for( j = 0; j < u[i].dim; j++){
      u[i].mtr[j] = new double [ u[i].dim ];
    }

    if( i == 0)u[i].mtr[0][0] = 1.0;
    if( i == 1)mtrmtr(4, u1, u[i].mtr);
    if( i > 1 )mtrdppower(u1, i, u[i].mtr);
  } 

// the creation and annihilation operators for all sites
   dim = pow (4,sitenum);
   dim2 = dim * dim;

   cuall = new opall [sitenum];
   for( i = 0; i < sitenum; i++ ){ cuall[i].mtr = new double [dim2];}
   auall = new opall [sitenum];
   for( i = 0; i < sitenum; i++ ){ auall[i].mtr = new double [dim2];}
   cdall = new opall [sitenum];
   for( i = 0; i < sitenum; i++ ){ cdall[i].mtr = new double [dim2];}
   adall = new opall [sitenum];
   for( i = 0; i < sitenum; i++ ){ adall[i].mtr = new double [dim2];}

// do direct product for them
   double **midmtr = new double* [dim];
   for ( i = 0;  i < dim; i++ ){ midmtr[i] = new double [dim];}

   for( i = 1; i <= sitenum; i++ ){
     directproduct(i, cu, midmtr);
     mtr_2to1( dim, cuall[i-1].mtr, midmtr);
     directproduct(i, cd, midmtr);
     mtr_2to1( dim, cdall[i-1].mtr, midmtr);
     directproduct(i, au, midmtr);
     mtr_2to1( dim, auall[i-1].mtr, midmtr);
     directproduct(i, ad, midmtr);
     mtr_2to1( dim, adall[i-1].mtr, midmtr);
   }

}

void mtralloc( int dim, double** mtr ){

   int i,j;

   mtr = new double* [dim];
   for( i = 0 ; i < dim; i++ ){
     mtr[i] = new double [dim];
   }

}

void mtrdealloc ( int dim, double** mtr){
   int i,j;

   for( i = 0; i < dim; i++ ){
    delete( mtr[i] );
   }
   delete(mtr);

}

void mtrmtr( int dim, double** mtr1, double** mtr2){
   int i,j;

   for( i = 0; i < dim; i++ ){
     for( j = 0; j < dim; j++ ){
       mtr2[j][i] = mtr1[j][i];
     }
   }

}

void mtrdppower( double** m1, int power, double** m2){
   int i,j,k,l;
   int origdim, proddim, finaldim;

   double** origmtr;
   double** productmtr;
   double** finalmtr;

   productmtr = new double* [4];
   for( i = 0 ; i< 4 ;i++ ){ productmtr[i] = new double[4];}

   mtrmtr( 4 , m1, productmtr);

   int ii = 2;
   origdim = pow(4,ii-1);
   proddim = 4;

   origmtr = new double* [origdim] ;
   for( i = 0; i < origdim; i++ ){ origmtr[i] = new double [origdim]; }
   mtrmtr( origdim, m1, origmtr );

   do { 

   if( ii > power )break;

   finaldim = origdim * proddim;
   finalmtr = new double* [finaldim];
   for( i = 0; i < finaldim; i++ ){ finalmtr[i] = new double [finaldim]; }

     for( l = 0; l < proddim; l++ ){
     for( k = 0; k < proddim; k++ ){
       for( j = 0; j < origdim; j++ ){ 
       for( i = 0; i < origdim; i++ ){
       finalmtr[ k * origdim + i][ l * origdim + j ] = origmtr[i][j] * productmtr[k][l];
       }
       }
     }
     }

    for( i = 0; i < origdim; i++ ){ delete(origmtr[i]); }
    delete(origmtr);

     origdim = pow(4,ii);
     origmtr = new double* [origdim];
     for( i = 0; i < origdim; i++ ){ origmtr[i] = new double [origdim];  }
     mtrmtr(origdim, finalmtr, origmtr);

     for( i = 0; i < finaldim; i++ ){ delete(finalmtr[i]);}
     delete(finalmtr);

     ii++;

   } while(1);


   mtrmtr(origdim, origmtr , m2);

   for( i = 0; i < origdim; i++ ){ delete(origmtr[i]); }
   delete(origmtr);

   for( i = 0; i < proddim; i++ ){ delete(productmtr[i]); }
   delete(productmtr);

}

void hamiltonian(int rank)
{
   int i,j,k,l;
   int isite,jsite,ksite,lsite;
   int nsite;
   double** term_mtr;

   nsite = nl;
   dim = pow (4,nsite);

   h = new double [dim2];
   for( i = 0; i < dim2; i++ ){ h[i] = 0.0;}

   if(rank == 0){
    h_all = new double [dim2];
    for( i = 0; i < dim2; i++ ){ h_all[i] = 0.0; }
   }

// Onebody Terms
   for( isite = 1; isite <= sitenum ; isite++ ) {
     for( jsite = 1; jsite <= sitenum ; jsite++ ){
     if( rank == oeindex[isite-1][jsite-1]){
      printf("%i %i \n",isite, jsite);
     onebodyterm(isite-1,jsite-1);}
     }
   }


// Twobody Terms
   for( isite = 1; isite <= nsite; isite++ ){
//     isite = rank + 1;
     for( jsite = 1; jsite <= nsite; jsite++ ){
       for( ksite = 1; ksite <= nsite; ksite++){
         for( lsite = 1; lsite <= nsite; lsite++){

         if(teindex[isite-1][jsite-1][ksite-1][lsite-1] == rank ){
         printf("%i %i %i %i\n",isite, jsite, ksite, lsite);
         twobodyterm(isite-1, jsite-1, ksite-1, lsite-1);}

        } 
       }
     }
   }


   MPI::COMM_WORLD.Reduce(h, h_all ,dim2, MPI::DOUBLE, MPI::SUM, 0 );

}

void onebodyterm(int isum , int jsum ){

   int i,j;
   char *transa = "N", *transb = "N";
   const MKL_INT *m, *n, *k;
   const MKL_INT *lda, *ldb, *ldc;
   double zero = 0.0, one = 1.0;

// set for GPU
   double *a_d, *b_d, *c_d;
   double ALPHA = T[isum][jsum]; 
   double BETA = 1.0;

   m = &dim; 
   n = &dim;
   k = &dim;
   lda = &dim;
   ldb = &dim;
   ldc = &dim;

   dim2 = pow(dim,2);

   double *alpha, *beta;
   alpha = &T[isum][jsum];
//   beta = &zero;
   beta = &one;

   dgemm(transa,transb,
                 m,n,k,alpha,cuall[isum].mtr,lda,auall[jsum].mtr,ldb,beta,h,ldc); 

   dgemm(transa,transb,
                 m,n,k,alpha,cdall[isum].mtr,lda,adall[jsum].mtr,ldb,beta,h,ldc);

}

void twobodyterm(int isum, int jsum, int ksum, int lsum ){

   int i,j;
   char *transa = "N", *transb = "N";
   const MKL_INT *m, *n, *k;
   const MKL_INT *lda, *ldb, *ldc;
   double zero = 0.0;
   double one = 1.0;

   double *a1_d, *a2_d;
   double *b1_d, *b2_d;
   double *c1_d, *c2_d, *c3_d;

   m = &dim;
   n = &dim;
   k = &dim;
   lda = &dim;
   ldb = &dim;
   ldc = &dim;

   dim2 = pow(dim,2);

   double *alpha1, *beta1;
   double *alpha2, *beta2;
   double *alpha3, *beta3;
   alpha1 = &U[isum][jsum][ksum][lsum];
   *alpha1 = 0.5 * (*alpha1);
   beta1 = &zero;
   alpha2 = &one;
   beta2 = &zero;
   alpha3 = &one;
   beta3 = &one;

   double *c1 = new double [dim2];
   double *c2 = new double [dim2];

   double ALPHA1 = U[isum][jsum][ksum][lsum] * 0.50000000000000000 ;
   double BETA1 = 0.0;
   double ALPHA2 = 1.0;
   double BETA2 = 0.0;
   double ALPHA3 = 1.0;
   double BETA3 = 1.0;

   dgemm(transa,transb,
                 m,n,k,alpha1,cuall[isum].mtr,lda,cuall[jsum].mtr,ldb,beta1,c1,ldc);
   dgemm(transa,transb,
                 m,n,k,alpha2,auall[ksum].mtr,lda,auall[lsum].mtr,ldb,beta2,c2,ldc);
   dgemm(transa,transb,
                 m,n,k,alpha3,c1,lda,c2,ldb,beta3,h,ldc);

   dgemm(transa,transb,
                 m,n,k,alpha1,cuall[isum].mtr,lda,cdall[jsum].mtr,ldb,beta1,c1,ldc);
   dgemm(transa,transb,
                 m,n,k,alpha2,adall[ksum].mtr,lda,auall[lsum].mtr,ldb,beta2,c2,ldc);
   dgemm(transa,transb,
                 m,n,k,alpha3,c1,lda,c2,ldb,beta3,h,ldc);

   dgemm(transa,transb,
                 m,n,k,alpha1,cdall[isum].mtr,lda,cuall[jsum].mtr,ldb,beta1,c1,ldc);
   dgemm(transa,transb,
                 m,n,k,alpha2,auall[ksum].mtr,lda,adall[lsum].mtr,ldb,beta2,c2,ldc);
   dgemm(transa,transb,
                 m,n,k,alpha3,c1,lda,c2,ldb,beta3,h,ldc);

   dgemm(transa,transb,
                 m,n,k,alpha1,cdall[isum].mtr,lda,cdall[jsum].mtr,ldb,beta1,c1,ldc);
   dgemm(transa,transb,
                 m,n,k,alpha2,adall[ksum].mtr,lda,adall[lsum].mtr,ldb,beta2,c2,ldc);
   dgemm(transa,transb,
                 m,n,k,alpha3,c1,lda,c2,ldb,beta3,h,ldc);

   delete(c1);
   delete(c2);

}

void directproduct( int isum, double **op, double **exop)
{

// calculate the expanded matrix for isum(th) operator matrix 
// isum = 1,2,3 ... sitenum

  int i,j,k,l;
  int subdim;
  int dimpo, dimf;

  double **mid;
  double **p1, **u2;
  int isite, jsite;

// Do p1 * Operator
// define the dimension of p1, subdim is
    isite = isum - 1;

    subdim = p[isite].dim;

    dimpo = subdim * 4;

// allocate p1
    p1 = new double* [subdim];
    for( i = 0; i < subdim; i++ ){
      p1[i] = new double [subdim];
    }

//copy the corresponded p to p1 of dimension subdim
    mtrmtr(subdim, p[isite].mtr, p1);

//allocate the after-multiplication operator of subdim * 4
    mid = new double* [ dimpo ];
    for( i = 0; i < dimpo ; i++ ){
      mid[i] = new double [ dimpo ];
    }

//do the direct product mid = p ** op
   for( i = 0; i < subdim ; i++ ){
     for( j = 0 ; j < subdim ; j++ ){
       for( k = 0; k < 4 ; k++ ){
         for( l = 0; l < 4 ; l++ ){
         mid[ l * subdim + j ][ k * subdim + i ] = p1[j][i] * op[l][k];
         }
       }
     }
   }

//  printmtr(dimpo,mid);
//deallocate p1
  for( i = 0; i < subdim; i++ ){
    delete( p1[i] );
  }
  delete( p1 );

// Do PO * p2

   jsite = sitenum - isum ;

   subdim = u[jsite].dim;

   u2 = new double* [subdim];
   for( i = 0; i < subdim; i++){
     u2[i] = new double [subdim];
   }

//   cout << dim << "\n";

   mtrmtr(subdim, u[jsite].mtr, u2);
//   printmtr_nonzero(subdim,u2);


   for( i = 0; i < subdim ; i++ ){
     for( j = 0 ; j < subdim ; j++){
       for( k = 0; k < dimpo ; k++){
         for( l = 0; l < dimpo  ; l++){
         exop[ j * dimpo + l ][ i * dimpo + k ] = mid[l][k] * u2[j][i];
         }
       }
     }
   }

//   printmtr(dimpo*subdim,exop);

   for( i = 0; i < subdim; i++ ){
     delete( u2[i] );
   }
   delete( u2 );

   for( i = 0; i < dimpo; i++ ){
     delete( mid[i] );
   }
   delete( mid );

/*  if( isum == 1 ){
  subdim = dim / 4;

  for( i = 0; i < subdim ; i++ ){
    for( j = 0 ; j < subdim ; j++){
      for( k = 0; k < 4 ; k++){
        for( l = 0; l < 4 ; l++){
        exop[ j * 4 + l ][ i * 4 + k ] = op[l][k] * u1[j][i];
        }
      }
    }
  }  
 
   }
  else if( isum == 2 ){
  subdim = dim / 4;
  for( i = 0; i < 4 ; i++ ){
    for( j = 0 ; j < 4 ; j++){
      for( k = 0; k < subdim ; k++){
        for( l = 0; l < subdim ; l++){
        exop[ j * subdim + l ][ i * subdim + k ] = p1[l][k] * op[j][i];
        }
      }
    }
  }

  }
  else if( isum == 3 ){
  }*/
}

void qr(){

   int i,j;
   int kk = 0;
   double value = 0.0;

   char *uplo = "U";
   MKL_INT *m , *n ;
   MKL_INT *lda,*lwork;
   MKL_INT *info;

   double *d = new double [dim];
   double *e = new double [dim];
   double *tau = new double [dim];

   double *a = new double [dim2];
   double *work = new double [dim];
   for( i = 0 ; i < dim2 ; i++ ){
        a[ i  ] = h_all[i];
//        printf("%f ",h[i][j]);
//        if(j == dim -1 ) printf("\n");
   }


   n = &dim;
   lda = &dim;
   lwork = &dim;
   info = &kk;

   *d = 0.0; *e = 0.0; *tau = 0.0;
   dsytrd(uplo, n ,a, lda, d, e, tau, work, lwork, info);
   dorgtr(uplo, n ,a, lda, tau, work, lwork, info);

   char *compz = "V";
   MKL_INT *ldz;
   ldz = &dim;
   double *z = new double [dim2]; 
   for( i = 0 ; i < dim2; i++ ){ 
        z[i] = a[i];
//   printf("%f\n",a[i]);
   }

//exit(1);
   double *work2 = new double [ 2*(*n)-2 ];

//   info = &kk;

   dsteqr( compz, n, d, e, z, ldz, work2, info);

   FILE* fp = fopen("eigenvalues.txt","w");

   for(i = 0; i < dim; i++ ){fprintf(fp,"%24.16f\n ",1,d[i]);}

   delete(a);
   delete(z);
   delete(d);
   delete(e);
   delete(tau);
   delete(work);
   delete(work2);

}

void printmtr(int dim, double** mtr){
    int i,j;

    for( i = 0; i < dim; i++ ){
      for( j = 0; j < dim; j++ ){
        printf("%f ", mtr[i][j]);
        if( j == (dim - 1)) printf("\n");
     }
   }

}

void mtr_set_zero(int dim, double **mtr){
     int i,j;

    for( i = 0; i < dim; i++ ){
      for( j = 0; j < dim; j++ ){
      mtr[j][i] = 0.0;
     }
   }

}

void mtr_add( int dim, double **m1, double** m2){
     int i,j;

    for( i = 0; i < dim; i++ ){
      for( j = 0; j < dim; j++ ){
       m1[j][i] = m1[j][i] + m2[j][i];
      }
    }

}

void mtr_1to2( int dim, double *m1, double **m2){
     int i,j;
     const int dim2 = pow (dim,2);

    for( i = 0; i < dim; i++){
      for( j = 0; j < dim; j++){
      m2[j][i] = m1[ i * dim + j ];
      }
    }
}

void mtr_2to1( int dim, double *m1, double **m2){
     int i,j;
     const int dim2 = pow (dim,2);

    for( i = 0; i < dim; i++ ){
      for( j = 0; j < dim; j++){
      m1[ i * dim + j ] = m2[j][i];
      }
    }

}

void printmtr_nonzero( int dim, double **mtr){

    int i,j;

    for( i = 0; i < dim; i++ ){
      for( j = 0; j < dim; j++ ){
       if( fabs(mtr[j][i]) >  1.0e-7 ){ printf("%i %i %24.16f\n",j,i,mtr[j][i]);}
      }
    }

}

void oo( int Nbasis, int Norb, double **coeff, double **TAO, double ****UAO,
         double **T, double ****U ){

   int i,j,k,l;
   int ii,jj,kk,ll;
   double *a, *b, *c, *d;
   double **mid,****midu;
   double one = 1.0;
   double zero = 1.0;

   double *alpha, *beta;
   int N2;

   N2 = pow(sitenum,2);
   alpha = &one;
   beta = &zero;
   const MKL_INT *mm = &sitenum;
   const MKL_INT *nn = &sitenum;
   const MKL_INT *kkk = &sitenum;
   const MKL_INT *lda = &sitenum;
   const MKL_INT *ldb = &sitenum;
   const MKL_INT *ldc = &sitenum;
   char NO = 'N', TR = 'T';
   char *transa , *transb ; 

   a = new double [N2];
   b = new double [N2];
   c = new double [N2];

//One electron integral
//   mid = new double [N2];
   mtr_2to1( sitenum, a, coeff);
   mtr_2to1( sitenum, b, TAO);
   for( i = 0; i < N2; i++ ){c[i] == 0.0;}
   transa = &NO; transb = &NO;
   dgemm(transa, transb,
                 mm,nn,kkk,alpha,a,lda,b,ldb,beta,c,ldc);
   mtr_2to1( sitenum, b, coeff);
   for( i = 0; i < N2; i++ ){
     a[i] = c[i]; c[i] = 0.0;
//     cout << a[i] << "\n";
   }

   transa = &NO; transb = &TR;
   dgemm(transa, transb,
                 mm,nn,kkk,alpha,a,lda,b,ldb,beta,c,ldc);
   mtr_1to2(sitenum,c,T);
//   printmtr(sitenum, T);

   mid = new double* [sitenum];
   for( i = 0; i < sitenum; i++ ){
     mid[i] = new double [sitenum];
   }

//Two electron integral
   midu = new double*** [sitenum];
   for( i = 0; i < sitenum; i++)
   {
     midu[i] = new double** [sitenum];
     for( j = 0; j < sitenum; j++){
     midu[i][j] = new double* [sitenum];
       for( k = 0; k < sitenum; k++ ){
       midu[i][j][k] = new double [sitenum];
       }
     }
   }

  for( l = 0; l < sitenum; l++ ){
    for( k = 0 ; k < sitenum; k++ ){

       for( j = 0; j < sitenum; j++ ){
         for( i = 0; i < sitenum; i++ ){
           mid[i][j] = UAO[i][j][k][l];
         }
       }

       mtr_2to1(sitenum,a,coeff);
       mtr_2to1(sitenum,b,mid);
       for( ii = 0; ii < N2; ii++ ){
         c[ii] = 0.0;
       }
       transa = &NO; transb = &NO;
       dgemm(transa, transb,
                  mm, nn,kkk,alpha,a,lda,b,ldb,beta,c,ldc);
       for( ii = 0; ii < N2; ii++ ){
         b[ii] = c[ii];
         c[ii] = 0.0;
       }
       transa = &NO; transb = &TR;
       dgemm(transa, transb,
                  mm, nn,kkk,alpha,a,lda,b,ldb,beta,c,ldc);
       mtr_1to2(sitenum, c, mid );

       for( jj = 0; jj < sitenum; jj++ ){
         for( ii = 0; ii < sitenum; ii++ ){
            midu[ii][jj][k][l] = mid[ii][jj];
         }
       }

     }
   }
 
   for( ii = 0; ii < sitenum ; ii++ ){
     for( jj = 0; jj < sitenum ; jj++ ){

       for( l = 0; l < sitenum; l++ ){
         for( k = 0; k < sitenum; k++ ){
            mid[k][l] = midu[ii][jj][k][l];
         }
       }

       mtr_2to1(sitenum,a,mid);
       mtr_2to1(sitenum,b,coeff);
       for( i = 0; i < N2; i++ ){
         c[i] = 0.0;
       }
       transa = &NO; transb = &TR;
       dgemm(transa, transb,
                  mm, nn,kkk,alpha,a,lda,b,ldb,beta,c,ldc);
       for( i = 0; i < N2; i++ ){
         a[i] = c[i];
         c[i] = 0.0;
       }
       mtr_2to1(sitenum, b, coeff);
       transa = &TR; transb = &TR;
       dgemm(transa, transb,
                  mm, nn,kkk,alpha,a,lda,b,ldb,beta,c,ldc);
       mtr_1to2(sitenum, c, mid );

       for( ll = 0; ll < sitenum; ll++ ){
         for( kk = 0; kk < sitenum; kk++ ){
           U[ii][jj][kk][ll] = mid[kk][ll];
         }
       }

    }
  }


/*  for( i = 0; i < sitenum; i++ ){
    for( j = 0; j < sitenum; j++ ){
      for( k = 0; k < sitenum; k++ ){
        for( l = 0; l < sitenum; l++){
 cout << i << j << k << l << " " << U[i][j][k][l] << "\n";
        }
      }
    }
  }
*/

}
