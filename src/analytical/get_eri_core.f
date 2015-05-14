       subroutine get_eri_core( norb, ncore, eri, eri_core )

       integer::norb, ncore
       double precision::eri(norb,norb,norb,norb)
       double precision::eri_core(ncore,ncore,ncore,ncore)

       do i = 1, ncore
         do j = 1, ncore
           do k = 1, ncore
             do l = 1, ncore
             eri_core(i,j,k,l) = eri(i,j,k,l)
       end do; end do; end do; end do

       end subroutine get_eri_core
