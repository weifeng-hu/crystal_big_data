       SUBROUTINE E_MATRIX( NBAS, OrbEns, E )

       INTEGER::NBAS
       DOUBLE PRECISION::OrbEns(NBAS)
       DOUBLE PRECISION::E(NBAS,NBAS)

       DO I = 1, NBAS
        DO J = 1, NBAS
         E(J,I) = E(J,I) + OrbEns(J) - OrbEns(I)
        END DO
       END DO

       END SUBROUTINE E_MATRIX
