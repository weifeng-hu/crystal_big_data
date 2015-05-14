       SUBROUTINE LINEAR_SOLVER( m, n, a, x, b )

       integer::m,n
       double precision::a(m,n)
       double precision::x(n)
       double precision::b(n)

       integer,allocatable::ipiv(:)

       integer nhrs
       integer lda, ldb, lwork
       character uplo,trans;

       double precision,allocatable::work(:)

       allocate(ipiv(n))
       allocate(work(n))
       lda = n
       call dgetrf( m, n, a, lda, ipiv, info )
!        uplo = 'L'
!        lwork = n
!        call dsytrf( uplo, n, a, lda, ipiv, work, lwork, info)


       trans = 'N'
       lda = n;  ldb = n
       nhrs = 1
       call dgetrs(trans, n, nrhs, a, lda, ipiv, b, ldb, info);

       x = b

       deallocate(ipiv) 
       deallocate(work)

       END SUBROUTINE LINEAR_SOLVER
