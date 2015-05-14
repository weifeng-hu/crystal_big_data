#include "integral.h"
#include "config.h"
#include "fci.h"

using namespace std;

namespace fci{

vector<double> lanczos_solver( config& fci_config, const int nroots, const int particle, const int sz )
{

  two_integral v2 = fci_config.get_two_integral();
  one_integral v1 = fci_config.get_one_integral();

  wavefunction v0;
  wavefunction r1;

  for( int iter = 1; iter <= maxiter; iter++ ){
   const int subdim = iter;

   vi += ri_1 * (1.0e0/beta[subdim-1]);
   v_buf|vi;

   ri = vi.multiplyH();

   ri -= (1.0e0/beta[subdim-1]) * vi_1;

   const double a_i = vi*ri;
   alpha.at(subdim) = a_i;

   eigvec.full(0.0e0);
   eigval.fill(0.0e0);
   tri_diagonal_lanczos( eigvec, eigval, alpha, beta, subdim );

   ri = ri + ( -1.0e0*alpha.at(subdim) ) * vi;

   // reorthogonalize
   for( int i = 0; i <= subdim; i++ ){
    v_tmp = 
    double projection = ri * vtmp;
    projection = -1.0e0 * projection;
    ri -= projection*vtmp;
   }
   r_buf|ri;

   const double b_i = sqrt( ri.norm() );
   beta.at(subdim) = b_i;

   // compute residual
   const int ilast = iroot * subdim + subdim - 1;
   const double residual = b_i * eigvec.at(ilast);

   vi_1 = vi;
   ri_1 = ri;

   vi.reset();
   ri.reset();

   if( fabs( residual ) <= 1.0e-4 ){
    iroot = iroot + 1;
   }

  }

}

void solve( config& fci_conf )
{

  const int nblock = fci_conf.get_nblock();
  const vector<block> blocks = fci_conf.get_blocks();

  for( int i = 0; i < nblock; i++ ){
   const int nroots   = blocks.get_nroots();
   const int particle = blocks.get_particle();
   const int sz       = blocks.get_sz();

   vector<double> energies( nroots, 0.0e0 );

   energies = lanczos_solver( fci_conf, nroots, particle, sz );

   fci_conf.set_blocks().at(i).set_energies() = energies;
  }

}

}
