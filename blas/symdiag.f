      SUBROUTINE SYMDIAG( EIGVEC, EIGVAL, N )

      implicit none      

      INTEGER N
      DOUBLE PRECISION EIGVEC(N,N)
      DOUBLE PRECISION EIGVAL(N)

      double precision a( N, N ), tmatrix( n, n )
      double precision z( N, N )
      double precision d( n )
      double precision e( n )
      double precision tau( n )
      double precision work( n )
      double precision work2( 2 * N  - 2 )
      character*1 uplo
      integer lda,lwork
      integer info

      character*1 compz
      integer ldz

      integer i,j
 
      uplo ='U'
      a = EIGVEC
      lda = n
      lwork = n
      
      d=0.0d0;e=0.0d0;tau=0.0d0
      CALL DSYTRD(uplo,n,a,lda,d,e,tau,work,lwork,info)
      
      lda = n; lwork = n
      CALL DORGTR(uplo,n,a,lda,tau,work,lwork,info)
      
      compz = 'V'
      ldz = n
      z = a
      CALL DSTEQR(compz,n,d,e,z,ldz,work2,info)
      
      EIGVEC = z
      EIGVAL = d
      
      END SUBROUTINE SYMDIAG
