      SUBROUTINE SYMDIAG( EIGVEC, EIGVAL, N )

      implicit none      

      INTEGER :: N
      DOUBLE PRECISION :: EIGVEC(N,N)
      DOUBLE PRECISION :: EIGVAL(N)

      double precision a( N, N ), tmatrix( n, n )
      double precision z( N, N )
      double precision d( n )
      double precision e( n )
      double precision tau( n )
      double precision work( n )
      double precision work2( 2 * N  - 2 )
c      double precision work( 2* n * n + 6 * n + 2 )
c      double precision w(n)
c      integer iwork( 5 * n + 3 )
      character*1 uplo
      integer lda,lwork,liwork
      integer info

c      character*1 jobz
      character*1 compz
      integer ldz

      integer i,j
 
c	eigvec=2.0d0
c	eigvec(1,2) = 0.0d0
c	eigvec(2,1) = 0.0d0
      uplo ='U'
      a = EIGVEC
      lda = n
      lwork = n
c	write(*,*)n, a, lda
      d=0.0d0;e=0.0d0;tau=0.0d0

c      jobz='V'
c      uplo='U'
      
c      lwork = 2 * n * n + 6 * n + 2
c      write(*,*)lwork
c      liwork = 5 * n + 3
c      call dsyevd(jobz,uplo,n,a,lda,w,work,lwork,iwork,liwork,info)
c      write(*,*)info
      CALL DSYTRD(uplo,n,a,lda,d,e,tau,work,lwork,info)
      
      lda = n; lwork = n
      CALL DORGTR(uplo,n,a,lda,tau,work,lwork,info)
      
      compz = 'V'
      ldz = n
      z = a
      CALL DSTEQR(compz,n,d,e,z,ldz,work2,info)
      EIGVEC = z
      EIGVAL = d
c      write(*,*)eigvec, eigval; 
c      stop
      END SUBROUTINE SYMDIAG
