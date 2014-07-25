      SUBROUTINE GET_Q( DIM, HESSIAN, Q, F )

      INTEGER::DIM
      DOUBLE PRECISION::HESSIAN(DIM,DIM)
      DOUBLE PRECISION::Q(DIM)
      DOUBLE PRECISION::F(DIM)

      DOUBLE PRECISION,ALLOCATABLE::EIGVEC(:,:)
      DOUBLE PRECISION,ALLOCATABLE::EIGVAL(:)

      DOUBLE PRECISION,ALLOCATABLE::SUB_HES(:,:)
      DOUBLE PRECISION,ALLOCATABLE::SUB_EIGVEC(:,:)
      DOUBLE PRECISION,ALLOCATABLE::SUB_Q(:)
      DOUBLE PRECISION,ALLOCATABLE::SUB_F(:)
      INTEGER,ALLOCATABLE::INDX(:)

      CHARACTER trans
      INTEGER m,n,lda,incx,incy
      DOUBLE PRECISION,ALLOCATABLE::a(:,:)
      DOUBLE PRECISION,ALLOCATABLE::x(:),y(:)

      ALLOCATE(EIGVEC(DIM,DIM))
      ALLOCATE(EIGVAL(DIM))
      ALLOCATE(INDX(DIM))

      EIGVEC = HESSIAN
      CALL EIGTQL2(DIM,EIGVEC,EIGVAL)

      write(10,*)' eigvals: '
      ICOUNT = 0
      INDX   = 0
      DO I = 1, DIM
        write(10,*)EIGVAL(I)
        IF( DABS( EIGVAL(I) ) .GE. 1.0D-5 )THEN
         ICOUNT = ICOUNT + 1
         INDX(ICOUNT) = I
        END IF
      END DO

      IF(ICOUNT .EQ. 0) STOP

      ALLOCATE( SUB_HES(ICOUNT,ICOUNT) )
      ALLOCATE( SUB_EIGVEC( DIM, ICOUNT) )
      SUB_HES = 0.0D0
      SUB_EIGVEC = 0.0D0
      DO I = 1, ICOUNT
       J = INDX(I)
       SUB_HES(I,I) = EIGVAL( J )
       SUB_EIGVEC(:,I) = EIGVEC(:, J)
      END DO


      ALLOCATE(SUB_F(ICOUNT))
      allocate(a(dim,icount))
      allocate(x(dim))
      allocate(y(icount))
      a = SUB_EIGVEC
      x = F
      trans = 'T'
      m = dim; n = icount
      lda = dim
      incx = 1; incy = 1
      call dgemv(trans,m,n, 1.0d0, a, lda, x, incx, 0.0d0, y, incy )
      SUB_F = y
      deallocate(a,x,y)

      write(10,*) ' sub_hes'
      write(10,*) sub_hes
      write(10,*) ' sub_f'
      write(10,*) sub_f
      write(10,*) ' sub_q'

      ALLOCATE(SUB_Q(ICOUNT))
      SUB_Q = 0.0D0
!      CALL BICGSTAB( ICOUNT, ICOUNT, SUB_HES, SUB_Q, SUB_F )
      CALL LINEAR_SOLVER( ICOUNT, ICOUNT, SUB_HES, SUB_Q, SUB_F )

      write(10,*)sub_q
      write(10,*) ' sub_eigvec'
      allocate(a(dim,icount))
      allocate(x(icount))
      allocate(y(dim))
      trans = 'N'
      m = dim; n = icount
      a = SUB_EIGVEC
      x = SUB_Q
      lda = dim; incx = 1; incy = 1
      write(10,*)sub_eigvec
      write(10,*) 'Q'
      call dgemv( trans, m, n, 1.0d0, a, lda, x, incx, 0.0d0, y, incy)
      Q = y
      write(10,*)Q
      deallocate(a,x,y)

      write(10,*)'************************************'

      DEALLOCATE(INDX)
      DEALLOCATE(SUB_HES,SUB_EIGVEC,SUB_Q, SUB_F )
      DEALLOCATE(EIGVEC,EIGVAL)

      END SUBROUTINE GET_Q
