#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

namespace ithaca { namespace qcread {

double* read_array_1d( char* array_name, int dim );
double* read_array_2d( char* array_name, int dim1, int dim2 );

class psiread
{
public:
 psiread(std::string dir_work, std::string psi_infile, std::string psi_outfile);
 ~psiread(){};

public:
  int natom;
  int nbas,norb,nocc,nvir;
  int na,nb,nele;
  int sz;
  int ncoord;

  double** coord;

public:
  double nuclear_repulsion;
// Hartree Fock 
  double* s;
  double* t;
  double* v;
  double* hcore;
  double* eri;

public:
  double* c;
  double* E;

public:
// CPHF part
  double** s_a;
  double** t_a;
  double** v_a;
  double** hcore_a;
  double** eri_a;

  double* grad_enuc;

  double** hessian;
  double** u_a;

// in MO basis
public:
  double* hcore_mo;
  double* eri_mo;

  double** sa_mo;
  double** ha_mo;
  double** eri_mo;

public:
  double** hc();
  double*** hc_a();
  double nuclear_rep( std::string dir_work, std::string psi_outfile );

  void coord_read( std::string dir_work, std::string psi_outfile );
  void stv_read(std::string dir_work, const char* stv_name, double*  stv);
  void stv_read(std::string dir_work, const char* stv_name, double** stv_a );

  void eri_read(std::string dir_work, const char* eri_name, double*  eri);
  void eri_read(std::string dir_work, const char* eri_name, double** eri_a);

  void hessian_read( std::string dir_work, double** hessian);
  void grad_enuc_read( std::string dir_work, double* grad_enuc);

  void u_a_read( std::string dir_work, double** u_a );
  void c_read( std::string dir_work, double* c );

}; // end of psiread

} } // end of cphf::qcread::
