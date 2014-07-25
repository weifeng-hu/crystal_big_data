       subroutine get_sa_core(ncoord,norb,ncore)

       integer::ncoord,norb,ncore
       double precision::sa(norb,norb)
       double precision::sa_core(ncore,ncore)

       do i = 1, ncore
         do j = 1, ncore
          sa_core(i,j) = sa(i,j)
       end do; end do

       end subroutine get_sa_core
