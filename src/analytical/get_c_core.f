       subroutine get_c_core( norb, ncore, c, c_core )

       integer::norb,ncore
       double precision::c(norb,norb)
       double precision::c_core(norb,ncore)

       do i = 1, ncore
        do j = 1, norb
         c_core(i,j) = c(i,j)
       end do; end do

       end subroutine get_c_core
