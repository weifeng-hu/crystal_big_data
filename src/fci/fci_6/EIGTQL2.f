      SUBROUTINE EIGTQL2(DIM,EIGVEC,EIGVAL)
      
      INTEGER::DIM
      DOUBLE PRECISION::EIGVEC(DIM,DIM)
      DOUBLE PRECISION::EIGVAL(DIM)
      
      character*1 uplo
      integer n,lda,lwork
      double precision,allocatable::a(:,:),tmatrix(:,:)
      double precision,allocatable::d(:),e(:),tau(:)
      double precision,allocatable::work(:),work2(:)
      
      character*1 compz
      integer ldz
      double precision,allocatable::z(:,:)
      
      allocate(a(dim,dim),tmatrix(dim,dim))
      allocate(d(dim),e(dim),tau(dim))
      allocate(work(dim))
      
      uplo ='U'
      n = DIM
      a = EIGVEC
      lda = DIM
      lwork = DIM 
      
      d=0.0d0;e=0.0d0;tau=0.0d0
      
      CALL DSYTRD(uplo,n,a,lda,d,e,tau,work,lwork,info)
      
      lda = dim; lwork = dim
      CALL DORGTR(uplo,n,a,lda,tau,work,lwork,info)
      
      allocate(z(dim,dim))
      allocate(work2(2*n-2))
      compz = 'V'
      ldz = Dim
      z = a
      CALL DSTEQR(compz,n,d,e,z,ldz,work2,info)
      
      EIGVEC = z
      EIGVAL = d
      
      deallocate(a,tmatrix,d,e,z,tau,work,work2)
      
      END SUBROUTINE EIGTQL2
