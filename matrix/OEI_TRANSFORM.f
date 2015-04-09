       SUBROUTINE OEI_TRANSFORM(NBAS, NORB, U, OEI1, OEI2)

       INTEGER::NBAS,NORB
       DOUBLE PRECISION::U(NBAS, NORB)
       DOUBLE PRECISION::OEI1(NBAS, NBAS)
       DOUBLE PRECISION::OEI2(NORB, NORB)

       DOUBLE PRECISION,ALLOCATABLE::MTR1(:,:)

       ALLOCATE(MTR1(NORB,NBAS))
       CALL DGEMM('T','N',NORB,NBAS,NBAS,
     &          1.0D0,U,
     &          NBAS,OEI1,NBAS,0.0D0,MTR1,
     &          NORB)

       CALL DGEMM('N','N',NORB,NORB,NBAS,
     &          1.0D0,MTR1,NORB,
     &          U,NBAS,0.0D0,
     &          OEI2,NORB)
       DEALLOCATE(MTR1)

       END SUBROUTINE OEI_TRANSFORM