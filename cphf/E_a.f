      SUBROUTINE E_a(NBAS,NORB,NOCC,Ha_AO,ERIa_AO,C,Sa,EPS,Ea)

      INTEGER::NBAS,NORB
      INTEGER::NOCC
      DOUBLE PRECISION::Ha_AO(NBAS,NBAS)
      DOUBLE PRECISION::ERIa_AO(NBAS,NBAS,NBAS,NBAS)
      DOUBLE PRECISION::C(NBAS,NORB)
      DOUBLE PRECISION::Sa(NBAS,NBAS)
      DOUBLE PRECISION::EPS(NORB)

      DOUBLE PRECISION::Ea

      INTEGER MU,YU,ROU,SIGMA

      Ea = 0.0D0

      DO I = 1, NOCC
       DO MU = 1, NBAS
        DO YU =  1, NBAS
         Ea = Ea + 2.0D0 * C(MU,I) * C(YU,I) * Ha_AO(MU,YU)
        END DO
       END DO
      END DO

      DO I = 1, NOCC
       DO J = 1, NOCC
         DO MU = 1, NBAS
          DO YU = 1, NBAS
           DO ROU  = 1, NBAS
            DO SIGMA = 1, NBAS
             Ea = Ea + 
     &      2.0D0 * 
     &      C(MU,I)*C(YU,I)*C(ROU,J)*C(SIGMA,J)*ERIa_AO(MU,YU,ROU,SIGMA)
     &    - 1.0D0 * 
     &      C(MU,I)*C(YU,J)*C(ROU,I)*C(SIGMA,J)*ERIa_AO(MU,YU,ROU,SIGMA)
            END DO
           END DO
          END DO
         END DO
       END DO
      END DO

      DO I = 1, NOCC
       DO MU = 1, NBAS
        DO YU = 1, NBAS
         Ea = Ea -
     &      2.0D0 * C(MU,I) * C(YU,I) * EPS(I) * Sa(MU,YU)
        END DO
       END DO
      END DO      

      END SUBROUTINE E_a
