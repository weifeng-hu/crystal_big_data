        SUBROUTINE SCF(NELE,NORB,NBAS,NUCLEAR_REP,S,HCORE,TEI,C,EPS,
     &                 HFENERGY)

        INTEGER::NORB,NBAS
        DOUBLE PRECISION::NUCLEAR_REP
        DOUBLE PRECISION::S(NBAS,NBAS)
        DOUBLE PRECISION::HCORE(NBAS,NBAS)
        DOUBLE PRECISION::TEI(NBAS,NBAS,NBAS,NBAS)
        DOUBLE PRECISION::C(NBAS,NORB)
        DOUBLE PRECISION::EPS(NORB)
        DOUBLE PRECISION HFENERGY

        INTEGER NELE
        DOUBLE PRECISION,ALLOCATABLE::SDIAG(:)
        DOUBLE PRECISION,ALLOCATABLE::X(:,:)
        DOUBLE PRECISION,ALLOCATABLE::G(:,:)
        DOUBLE PRECISION,ALLOCATABLE::FOCK(:,:)
        DOUBLE PRECISION,ALLOCATABLE::NEWC(:,:)
        DOUBLE PRECISION,ALLOCATABLE::P(:,:)
        DOUBLE PRECISION,ALLOCATABLE::OLDP(:,:)
        DOUBLE PRECISION,ALLOCATABLE::U(:,:)
        DOUBLE PRECISION,ALLOCATABLE::SMHALF(:,:)
        DOUBLE PRECISION,ALLOCATABLE::NEWFOCK(:,:)
        DOUBLE PRECISION,ALLOCATABLE::TEMPMTR(:,:)
        DOUBLE PRECISION,ALLOCATABLE::TEMPVEC(:)
        DOUBLE PRECISION,ALLOCATABLE::PS(:,:)
        DOUBLE PRECISION,ALLOCATABLE::EIGN(:)

        DOUBLE PRECISION ENG_NOW,ENG_LAST

        double precision temp
        integer SYM_ORTH
        integer CAN_ORTH
        integer x_orth

        character*20 title

c	write(*,*)nele,norb,nbas
c	write(*,*)hcore
c	write(*,*)s
c	write(*,*)p
c	do i = 1,2; do j = 1,2; do k = 1,2; do l = 1,2
c	write(*,*)i,j,k,l,tei(i,j,k,l)
c	end do; end do; end do; end do
c	stop

        ALLOCATE(SDIAG(NBAS))
        ALLOCATE(X(NBAS,NBAS))
        ALLOCATE(NEWC(NBAS,NBAS))
        ALLOCATE(P(NORB,NORB))
        ALLOCATE(OLDP(NORB,NORB))
        ALLOCATE(FOCK(NORB,NORB))
        ALLOCATE(G(NORB,NORB))
        ALLOCATE(U(NBAS,NBAS))
        ALLOCATE(NEWFOCK(NORB,NORB))
        ALLOCATE(TEMPMTR(NORB,NBAS))
        ALLOCATE(SMHALF(NBAS,NBAS))
        ALLOCATE(TEMPVEC(NBAS))
        ALLOCATE(PS(NBAS,NBAS))
        ALLOCATE(EIGN(NBAS))

        SDIAG = 0.0D0
        X = 0.0D0
        C = 0.0D0
c        P = 0.0D0
        OLDP = 0.0D0
        FOCK = 0.0D0
        G = 0.0D0
        SMHALF = 0.0D0
        NEWFOCK = 0.0D0
        TEMPMTR = 0.0D0

! DIAGONALIZE S AND GET X
        U = S
!        CALL EIGTQL2(NBAS,U,SDIAG)

        SMHALF = 0.0D0
        DO I = 1,NBAS
          SMHALF(I,I) = 1.0d0/DSQRT(SDIAG(I))
        END DO

        X_ORTH = 1

        SELECT CASE(X_ORTH)
        CASE(1)
        CALL DGEMM('N','T',NBAS,NBAS,NBAS,1.0D0,SMHALF,NBAS,
     &         U,NBAS,0.0D0,TEMPMTR,NBAS)
        CALL DGEMM('N','N',NBAS,NBAS,NBAS,1.0D0,U,NBAS,
     &         TEMPMTR,NBAS,0.0D0,X,NBAS)
        CASE(2)
        CALL DGEMM('N','N',NBAS,NBAS,NBAS,1.0D0,U,NBAS,
     &                  SMHALF,NBAS,0.0D0,X,NBAS)
        END SELECT

! SET INITIAL P
        P = 0.0D0

        ENG_NOW   = 0.0D0
        ENG_LAST  = 0.0D0
        ITER = 1
! CALCULATE G 
50      CONTINUE

!        WRITE(*,*)'CYCLE   ', ITER


        DO I = 1,NBAS
         DO J = 1,NBAS
        G(I,J) = 0.0D0
          DO K = 1,NBAS
           DO L = 1,NBAS
         G(I,J) = G(I,J) +
     &       P(K,L) *  TEI(I,J,K,L)- P(K,L) * 0.5D0 * TEI(I,K,L,J) 
           END DO
          END DO
         END DO
        END DO

! CALCULATE FOCK

        FOCK =0.0D0
        DO I = 1, NBAS
          DO J = 1,NBAS
        FOCK(I,J) = HCORE(I,J) + G(I,J)
          END DO
        END DO

! CALCULATE HF ENERGY
        HFENERGY = 0.0D0
        DO I = 1,NORB
          DO J = 1,NORB
        HFENERGY = HFENERGY + 0.5d0 * P(J,I)*(HCORE(I,J) + FOCK(I,J))
          END DO
        END DO
        HFENERGY = HFENERGY + NUCLEAR_REP
!        WRITE(*,*)HFENERGY

        ENG_NOW = HFENERGY

! CALCULATE NEW FOCK
! NOTE THESE DIMENSIONS ARE NOT QUITE RIGHT, WILL ADJUST LATER
        TEMPMTR = 0.0D0
        CALL DGEMM('N','N',NBAS,NBAS,NBAS,1.0d0,FOCK,NORB,
     &                  X,NBAS,0.0D0,TEMPMTR,NBAS)
        NEWFOCK = 0.0D0
        CALL DGEMM('T','N',NBAS,NBAS,NBAS,1.0D0,X,NORB,
     &                  TEMPMTR,NBAS,0.0D0,NEWFOCK,NBAS)

! DIAGONALIZE FOCK MATRIX
        C = NEWFOCK
!        CALL EIGTQL2(NBAS,C,EPS)
        
c       WRITE(*,'(100(F14.9))')(EPS(I),I = 1,NBAS)
C       STOP

        CALL DGEMM('N','N',NBAS,NBAS,NBAS,1.0D0,S,NBAS,
     &                  C,NBAS,0.0D0,TEMPMTR,NBAS)
        CALL DGEMM('T','N',NBAS,NBAS,NBAS,1.0D0,C,NBAS,
     &                  TEMPMTR,NBAS,0.0D0,NEWC,NBAS)

! GET NEW C
        CALL DGEMM('N','N',NBAS,NBAS,NBAS,1.0D0,X,NBAS,
     &                  C,NBAS,0.0D0,NEWC,NBAS)

        CALL DGEMM('T','N',NBAS,NBAS,NBAS,1.0D0,C,NBAS,
     &                  C,NBAS,0.0D0,TEMPMTR,NBAS)
c        WRITE(*,*)TEMPMTR

! GET NEW P
        P = 0.0D0
        DO I = 1, NBAS
           DO J = 1, NBAS
             DO K = 1, NELE/2
                 P(I,J) = P(I,J) + 2.0d0 * NEWC(I,K) * NEWC(J,K)
             END DO
           END DO
        END DO 


        TEMPMTR = 0.0D0
        CALL DGEMM('N','N',NBAS,NBAS,NBAS,1.0d0,S,NORB,
     &                   NEWC,NBAS,0.0D0,TEMPMTR,NBAS)
        NEWFOCK = 0.0D0
        CALL DGEMM('T','N',NBAS,NBAS,NBAS,1.0D0,NewC,NORB,
     &                  TEMPMTR,NBAS,0.0D0,NEWFOCK,NBAS)

        CALL DGEMM('N','N',NBAS,NBAS,NBAS,1.0D0,P,NBAS,
     &                  S,NBAS,0.0D0,PS,NBAS)
        temp = 0.0d0
        DO I=1,NBAS
        temp = temp + ps(i,i)
        END DO
c        write(*,*)temp

c        WRITE(2,*)'____________________________________________________'

        ITER = ITER + 1

        IF( (DABS( ENG_NOW - ENG_LAST) .LE. 1.0D-6)
     &             .OR.
     &       ITER .GT. 50  )THEN
             GOTO 60
        ELSE
             ENG_LAST = ENG_NOW
             GOTO 50
        END IF
           

60      CONTINUE 
        C = NEWC

c        DEALLOCATE(SDIAG,X,C,FOCK,G)

        END SUBROUTINE SCF
