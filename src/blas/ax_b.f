      subroutine ax_b( a, b, x, dimen )

      implicit none
      integer::dimen
      double precision::a(dimen,dimen)
      double precision::b(dimen)
      double precision::x(dimen)

      integer ipiv(dimen)
      integer m,n
      integer lda, ldb
      integer info
      integer nrhs
      character*1 trans

      m = dimen;
      n = dimen;
      lda = n;

      call dgetrf( m, n, a, lda, ipiv, info )

      trans = 'N';
      nrhs = 1;
      lda = n;
      ldb = n;
      call dgetrs( trans, n, nrhs, a, lda, ipiv, b, ldb, info )

      x = b

      end subroutine ax_b
