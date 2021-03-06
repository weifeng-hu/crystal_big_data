      SUBROUTINE E_a_CI(NORB,Q,G,h,TEI,h_a,TEI_a,U,E_a)

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
 

      INTEGER::NORB
      DOUBLE PRECISION::E_a
      DOUBLE PRECISION::Q(NORB,NORB)
      DOUBLE PRECISION::G(NORB,NORB,NORB,NORB)
      DOUBLE PRECISION::h(NORB,NORB)
      DOUBLE PRECISION::TEI(NORB,NORB,NORB,NORB)
      DOUBLE PRECISION::h_a(NORB,NORB)
      DOUBLE PRECISION::TEI_a(NORB,NORB,NORB,NORB)
      DOUBLE PRECISION::U(NORB,NORB)
      DOUBLE PRECISION::X(NORB,NORB)

      DOUBLE PRECISION E_a_oe, E_a_te, E_a_ux

      E_a = 0.0D0

c  Calculate the One-electron contribution to E_a
      E_a_oe = 0.0D0
      DO I = 1, NORB
       DO J = 1, NORB
        E_a_oe = E_a_oe + Q(I,J) * h_a(I,J)
       END DO
      END DO
      E_a = E_a + E_a_oe


c  Calculate the Two-electron contribution to E_a
      E_a_te = 0.0D0
      DO I = 1, NORB
       DO J = 1, NORB
        DO K = 1, NORB
         DO L = 1, NORB
          E_a_te = E_a_te + G(I,J,K,L) * TEI_a(I,J,K,L)
         END DO
        END DO
       END DO
      END DO
      E_a = E_a + E_a_te

c  Calculate X matrix 
      X = 0.0D0
      DO I = 1, NORB
       DO J = 1, NORB

        DO M = 1, NORB
         X(I,J) = X(I,J) + Q(J,M) * h(I,M)
        END DO

        DO M = 1, NORB
         DO K = 1, NORB
          DO L = 1, NORB
           X(I,J) = X(I,J) + 2.0d0 * G(J,M,K,L) * TEI(I,M,K,L)
          END DO
         END DO
        END DO

       END DO
      END DO

c  Apply X matrix to the contribution from UX term
      E_a_ux = 0.0D0
      DO I = 1, NORB
       DO J = 1, NORB
        E_a_ux = E_a_ux + 2.0d0 * U(I,J) * X(I,J)
       END DO
      END DO
      E_a = E_a + E_a_ux

c  End calculation

      END SUBROUTINE E_a_CI
