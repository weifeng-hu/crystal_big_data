      subroutine mat_x_mat( a, b, c, coeff, 
     & nrow_a, ncol_a, nrow_b, ncol_b, ta, tb )

       integer nrow_a, ncol_a, nrow_b, ncol_b
       double precision a(nrow_a, ncol_a)
       double precision b(nrow_b, ncol_b)
       double precision c(*)

       double precision coeff
       integer ta, tb

       double precision alpha,beta
       character*1 transa, transb
       integer m, n, k
       integer lda, ldb, ldc

       alpha = coeff
       beta = 0.0d0

       if( ta .eq. 0 )then
        transa = 'n'
       else
        transa = 't'
       end if

       if( tb .eq. 0 )then
        transb = 'n'
       else 
        transb = 't'
       end if

c      m n k
       if( ta .eq. 0 .and. tb .eq. 0 )then
         m = nrow_a
         n = ncol_b
         if( ncol_a .ne. nrow_b )then
          write(*,*)" error: A*B: ncol_a != nrow_b "
          stop 
         endif
         k = ncol_a
       end if

       if( ta .eq. 1 .and. tb .eq. 0 )then
         m = ncol_a
         n = ncol_b
         if( nrow_a .ne. nrow_b )then
          write(*,*)" error: At * B: nrow_a != nrow_b "
          stop
         endif
         k = nrow_a
       endif
       
       if( ta .eq. 0 .and. tb .eq. 1 )then
         m = nrow_a
         n = nrow_b
         if( ncol_a .ne. ncol_b )then
          write(*,*)" error: A * Bt: ncol_a != ncol_b "
          stop
         endif
         k = ncol_a
       endif

       if( ta .eq. 1 .and. tb .eq. 1 )then
         m = ncol_a
         n = nrow_b
         if( nrow_a .ne. ncol_b )then
          write(*,*)" error: At * Bt: nrow_a != ncol_b "
          stop
         endif
         k = nrow_a
       endif

c      lda ldb ldc
       if( ta .eq. 0 )then
         lda = max(1, m)
       else
         lda = max(1, k)
       endif

       if( tb .eq. 0 )then
         ldb = max(1, k)
       else
         ldb = max(1, n)
       endif

       ldc = max(1, m)

c       write(*,*) transa, transb, m, n, k, lda, ldb, ldc, alpha, beta
c       write(*,*) a(nrow_a, ncol_a), b(nrow_b, ncol_b)
c      run dgemm
       call dgemm(transa,transb,m,n,k,alpha,a,lda,b,ldb,beta,c,
     & ldc)


      end subroutine mat_x_mat
