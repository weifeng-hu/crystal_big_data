       subroutine get_eps_core( norb, ncore, eps, eps_core )

       integer::norb,ncore
       double precision::eps(norb)
       double precision::eps_core(ncore)

       do i = 1, ncore
         eps_core(i) = eps(i)
       end do

       end subroutine get_eps_core
