       SUBROUTINE F_a(NBAS,NOCC,ha,TEIa,Fa)

       INTEGER::NBAS,NOCC
       DOUBLE PRECISION::ha(NBAS,NBAS)
       DOUBLE PRECISION::TEIa(NBAS,NBAS,NBAS,NBAS)
       DOUBLE PRECISION::Fa(NBAS,NBAS)

       Fa = 0.0d0
       DO J = 1, NBAS
        DO I = 1, NBAS
           Fa(I,J) = Fa(I,J) + ha(I,J)
         DO K = 1, NOCC
           Fa(I,J) = Fa(I,J) + 
     &               2.0d0 * TEIa(I,J,K,K) - TEIa(I,K,J,K)
         END DO
        END DO
       END DO


       END SUBROUTINE F_a
