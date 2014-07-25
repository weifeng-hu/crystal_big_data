       SUBROUTINE A_MATRIX( NBAS, TEI, A )

       INTEGER::NBAS
       DOUBLE PRECISION::TEI(NBAS,NBAS,NBAS,NBAS)
       DOUBLE PRECISION::A(NBAS,NBAS,NBAS,NBAS)

       A = 0.0D0;

       DO I = 1, NBAS
        DO J = 1, NBAS
         DO K = 1, NBAS
          DO L = 1, NBAS
            A(I,J,K,L) = A(I,J,K,L) + 
     &             4.0D0 * TEI(I,J,K,L) + 
     &             (-1.0D0) * TEI(I,K,J,L) +
     &             (-1.0D0) * TEI(I,L,J,K)

          END DO
         END DO
        END DO
       END DO

       END SUBROUTINE A_MATRIX
