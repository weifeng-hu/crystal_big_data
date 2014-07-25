      subroutine fci_gradient(norb,Q,G,h,TEI,h_a,TEI_a,U,E_a)

c ===========================================================================
c     This subroutine calculates the 1st order energy derivative
c     in CI wavefunction to a specific coordinate *a*
c
c     The overall formula is:
c         E_a = Sigma_ij[ Q_ij * h_a_ij] + Sigma_ijkl[ G_ijkl * (ij|kl)_a ] 
c               + 2 Sigma_ij[ U_ij * X_ij]
c
c     where X_ij = Sigma_m[ Q_jm * h_im ] + 2 Sigma_mkl[ G_jmkl * (im|kl) ]
c
c     All the induces are of MOs 
c     and summmations all run over the whole MO space
c
c     Quantities: 
c         E_a       First order energy derivative to coordinate *a*
c         Q         One-body reduced density matrix in CI wavefunction
c         G         Two-body reduced density matrix in CI wavefunction
c         h         Core Hamiltonian in MO basis
c         TEI       Two-electron integral in MO basis
c         h_a       Transformed from 
c                                 (C^+) * (h'_a) * (C)
c                   where h'_a is the core hamiltonian 1st order
c                   derivative, C is the MO coefficients
c         TEI_a     Transformed from TEI in AO basis
c         U         U matrix solved from CPHF equation
c         X         Lagrangian matrix
c
c     The original verision of all the formulars above can be found in
c     Yamaguchi, Goddard, Osamura Schaefer et al.
c     A New Dimension to Quantum Chemistry - Analytic Derivative Meothds
c     in Ab Initio Molecular Electronic Structure Theory
c
c ===========================================================================
 

      integer::norb
      double precision::E_a
      double precision::q(norb,norb)
      double precision::g(norb,norb,norb,norb)
      double precision::h(norb,norb)
      double precision::tei(norb,norb,norb,norb)
      double precision::h_a(norb,norb)
      double precision::tei_a(norb,norb,norb,norb)
      double precision::u(norb,norb)
      double precision::x(norb,norb)

      integer m
      double precision E_a_oe, E_a_te, E_a_ux

      E_a = 0.0D0

c  Calculate the One-electron contribution to E_a
      E_a_oe = 0.0D0
      do i = 1, norb
       do j = 1, norb
        E_a_oe = E_a_oe + q(i,j) * h_a(i,j)
      end do; end do
      E_a = E_a + E_a_oe


c  Calculate the Two-electron contribution to E_a
      E_a_te = 0.0D0
      do i = 1, norb
       do j = 1, norb
        do k = 1, norb
         do l = 1, norb
          E_a_te = E_a_te + g(i,j,k,l) * tei_a(i,j,k,l)
      end do; end do; end do; end do
      E_a = E_a + E_a_te

c  Calculate X matrix 
      X = 0.0D0
      do i = 1, norb
       do j = 1, norb

        do m = 1, norb
         x(i,j) = x(i,j) + q(j,m) * h(i,m)
        end do

        do m = 1, norb
         do k = 1, norb
          do l = 1, norb
           x(i,j) = x(i,j) + 2.0d0 * g(j,m,k,l) * tei(i,m,k,l)
        end do; end do; end do
      end do; end do

c  Apply X matrix to the contribution from UX term
      E_a_ux = 0.0D0
      do i = 1, norb
       do j = 1, norb
        E_a_ux = E_a_ux + 2.0d0 * u(i,j) * x(i,j)
      end do; end do
      E_a = E_a + E_a_ux

c  End calculation

      end subroutine fci_gradient
