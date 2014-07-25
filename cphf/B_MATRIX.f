       SUBROUTINE B_MATRIX(NBAS,NOCC,Fa,Sa,E,TEI,B)

       INTEGER::NBAS,NOCC
       DOUBLE PRECISION::Fa(NBAS,NBAS)
       DOUBLE PRECISION::Sa(NBAS,NBAS)
       DOUBLE PRECISION::E(NBAS)
       DOUBLE PRECISION::TEI(NBAS,NBAS,NBAS,NBAS)
       DOUBLE PRECISION::B(NBAS,NBAS)

       B = 0.0D0
       DO J = 1, NBAS
         DO I = 1, NBAS
          B(I,J) = B(I,J) + Fa(I,J) - Sa(I,J) * E(J)
           DO L = 1, NOCC
            DO K = 1, NOCC
             B(I,J) = B(I,J) - 
     &               Sa(K,L) * ( 2.0D0 * TEI(I,J,K,L) - TEI(I,K,J,L))
            END DO
           END DO
         END DO
       END DO

       END SUBROUTINE B_MATRIX
