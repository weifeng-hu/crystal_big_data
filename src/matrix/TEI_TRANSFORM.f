c$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
c
c    This is a standard two-electron integral transformation subroutine
c    It works for the two-electron integrals with orders:
c
c        1 1'2 2'(chemistry order)   and   1 2 2' 1'(physics order)
c
c$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

       SUBROUTINE TEI_TRANSFORM(NBAS, NORB, U, TEI1, TEI2 )

       INTEGER::NBAS,NORB
       DOUBLE PRECISION::U(NBAS,NORB)
       DOUBLE PRECISION::TEI1(NBAS,NBAS,NBAS,NBAS)
       DOUBLE PRECISION::TEI2(NORB,NORB,NORB,NORB)

       DOUBLE PRECISION,ALLOCATABLE::MTR1(:,:)
       DOUBLE PRECISION,ALLOCATABLE::MTR2(:,:)
       DOUBLE PRECISION,ALLOCATABLE::MTR3(:,:)
       DOUBLE PRECISION,ALLOCATABLE::MIDU1(:,:,:,:)

       ALLOCATE(MIDU1(NORB,NORB,NBAS,NBAS))
       ALLOCATE(MTR1(NBAS,NBAS))
       ALLOCATE(MTR2(NORB,NBAS))
       ALLOCATE(MTR3(NORB,NORB))

       DO L = 1, NBAS
        DO K = 1, NBAS

           DO J = 1, NBAS; DO I = 1, NBAS
            MTR1(I,J) = TEI1(I,J,K,L)
            !write(*,*)i,j,k,l, tei1(i,j,k,l)
           END DO; END DO

           CALL DGEMM('T','N',NORB,NBAS,NBAS,
     &                 1.0D0,U,
     &                 NBAS,MTR1,NBAS,0.0D0,MTR2,
     &                 NORB)

           CALL DGEMM('T','T',NORB,NORB,NBAS,
     &                 1.0D0,U,NBAS,
     &                 MTR2,NORB,0.0D0,
     &                 MTR3,NORB)

           DO JJ=1,NORB; DO II=1,NORB
            MIDU1(II,JJ,K,L)=MTR3(II,JJ)
           END DO; END DO

        END DO
       END DO

       DO II=1,NORB
         DO JJ=1,NORB

           DO L=1,NBAS; DO K=1,NBAS
            MTR1(K,L)=MIDU1(II,JJ,K,L)
           END DO; END DO

           CALL DGEMM('N','N',NBAS,NORB,NBAS,
     &                 1.0D0,MTR1,
     &                 NBAS,U,NBAS,0.0D0,MTR2,
     &                 NBAS)

           CALL DGEMM('T','N',NORB,NORB,NBAS,
     &                 1.0D0,MTR2,NBAS,
     &                 U,NBAS,0.0D0,
     &                 MTR3,NORB)

           DO LL=1,NORB; DO KK=1,NORB
             TEI2(II,JJ,KK,LL)=MTR3(KK,LL)
           END DO; END DO

         END DO
       END DO

       DEALLOCATE(MTR1,MTR2,MTR3)
       DEALLOCATE(MIDU1)
 
       END SUBROUTINE TEI_TRANSFORM
