//#ifdef _FULLCI_H_
//#define _FULLCI_H_

#define nl 5
#define nr 0

//  Calculation configuration
//
//  Number of sites (orbitals)
  int sitenum;
//  Number of electrons
  int ne;
//  Number of Basis
  int Nbasis,Norb;
// 
  int dim,diml,dimr;
  int dim2;

//  SCF orbital energies
  double* orb_energy_alpha;
  double* orb_energy_beta;
//  AO Integrals
//     One-electron integral
 double** TAO;
 double** T;
//     Two-electron integral
  double**** UAO;
  double**** U;
//  MO coefficients
 double** coeff_alpha;
 double** coeff_beta;

// MPI index
 int ** oeindex;
 int **** teindex;

// Basic creation and annihilation operator
 double** cu;
 double** au;
 double** cd;
 double** ad;

 struct opall{
  double *mtr;
 } *cuall, *cdall, *auall, *adall;

// Unit operator 
  struct pu{
   int dim;
   double **mtr;
  } *p,*u;
 double **u1,**u2,**u3,**u4;

// Parity Operator l and r
 double **p1,**p2,**p3,**p4;

// hamiltonian 
 double *h;
 double *h_all;
 double **m1, ** m2, ** m3, **m4;

// GPU
/*  double *a_d, *b_d, *c_d;
  double *a1_d, b1_d, *c1_d;
  double *a2_d, b2_d, *c2_d;
  double *c3_d;*/

//#endif
//
void init(int, int);
void hamiltonian(int);
void onebodyterm(int, int);
void twobodyterm(int, int, int, int);
void directproduct(int, double**, double**);
void qr();
void davidson();
void lanzos();
void printmtr(int , double**);
void printmtr_nonzero(int, double**);
void mtr_set_zero(int, double**);
void mtr_add(int, double**, double**);
void mtr_1to2(int, double*, double**);
void mtr_2to1(int, double*, double**);
void mtrdppower(double**, int, double** );
void mtralloc( int, double** );
void mtrdealloc( int, double** );
void mtrmtr( int, double**, double**);
void oo(int, int, double**, double**, double****, double**, double****);
