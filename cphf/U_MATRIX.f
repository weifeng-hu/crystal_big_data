       SUBROUTINE U_MATRIX( NORB, NOCC, E, A, B, U )

       INTEGER::NORB, NOCC
       DOUBLE PRECISION::E(NORB,NORB)
       DOUBLE PRECISION::A(NORB,NORB,NORB,NORB)
       DOUBLE PRECISION::B(NORB,NORB)
       DOUBLE PRECISION::U(NORB,NORB)

       double precision,allocatable::E_indp(:)
       double precision,allocatable::A_indp(:,:)
       double precision,allocatable::B_indp(:)
       double precision,allocatable::U_indp(:)

       double precision tempA(3,3)
       double precision tempB(3)
       double precision tempU(3)

       integer NVIR, N_INDP

       nvir = NORB - NOCC
       N_INDP = NOCC * NVIR

       ALLOCATE( E_INDP( N_INDP ))
       ALLOCATE( A_INDP( N_INDP, N_INDP ))
       ALLOCATE( B_INDP( N_INDP ))
       ALLOCATE( U_INDP( N_INDP ) )

       DO I = 1, NOCC
        DO J = 1, NVIR
           II = I
           JJ = NOCC + J
           KK = (I-1) * NVIR + J
           E_INDP( KK ) = E( II, JJ )
           B_INDP( KK ) = B( II, JJ )
        END DO
       END DO

       DO I = 1, NOCC
        DO J = 1, NVIR
           II = I
           JJ = NOCC + J
           IJ = (I-1) * NVIR + J
          DO K = 1, NOCC
            DO L = 1, NVIR
             KK = K
             LL = NOCC + L
             KL = (K-1) * NVIR + L
             A_INDP (IJ,KL) = A(II,JJ,KK,LL)
            END DO
          END DO
        END DO
       END DO
       U_INDP = 0.0

!       CALL LINEAR_SOLVER(N_INDP, N_INDP, A_INDP, U_INDP, B_INDP)
!        CALL BICGSTAB(N_INDP, N_INDP, A_INDP, U_INDP, B_INDP);
!	write(*,*)A_INDP, U_INDP, B_INDP
!       TempA = 0.0d0
!       TempA(1,1) = 2.0d0; TempA(1,2) = 1.0d0; TempA(1,3) = -1.0d0
!       TempA(2,1) = -3.0d0; TempA(2,2) = -1.0d0; TempA(2,3) = 2.0d0
!       TempA(3,1) = -2.0d0; TempA(3,2) = 1.0d0; TempA(3,3) = 2.0d0
!       TempB(1) = 8.0d0; TempB(2) = -11.0d0; TempB(3) = -3.0d0
!       TempU = 1.0d0
!       CALL BICGSTAB(3,3,TempA,TempU,TempB)

       END SUBROUTINE U_MATRIX
